#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_OBJECTS 50
#define MAX_ROOMS 20
#define MAX_OBJECTS_PER_ROOM 10
#define MAX_CONNECTIONS_PER_ROOM 8
#define MAX_CONTENTS_PER_OBJECT 5
#define MAX_REQUIREMENTS_PER_ROOM 5
#define MAX_INVENTORY_SIZE 20
#define MAX_NAME_LENGTH 64
#define MAX_DESCRIPTION_LENGTH 512

typedef struct Object Object;
typedef struct Room Room;

typedef struct Object {
    char* name;
    bool takeable;
    Object* requires;
    Object* contents[MAX_CONTENTS_PER_OBJECT];
    int content_count;
    Object* hidden_item;
    char* examine_text;
    bool consume_key;
    bool hidden_revealed;
    bool opened;
} Object;

typedef struct {
    char* direction;
    Room* room;
} Connection;

typedef struct {
    int damage;
    char* message;
    Object* protection;
    char* protection_message;
} Trap;

typedef struct {
    char* name;
    int damage;
    Object* weakness;
    Object* defeat_reward;
} Enemy;

typedef struct Room {
    char* name;
    char* description;
    Connection connections[MAX_CONNECTIONS_PER_ROOM];
    int connection_count;
    Object* objects[MAX_OBJECTS_PER_ROOM];
    int object_count;
    Object* requires[MAX_REQUIREMENTS_PER_ROOM];
    int requires_count;
    char* entry_message;
    bool has_trap;
    Trap trap;
    bool has_enemy;
    Enemy enemy;
    bool win_condition;
} Room;

typedef struct {
    char* game_name;
    Room* start_room;
    int health;
    Object objects[MAX_OBJECTS];
    int object_count;
    Room rooms[MAX_ROOMS];
    int room_count;
} Game;

// Player state
typedef struct {
    Room* current_room;
    Object* inventory[MAX_INVENTORY_SIZE];
    int inventory_count;
    int max_health;
    int current_health;
    bool game_won;
    bool game_over;
} Player;

extern Game game_data;

void init_player(Player* player) {
    player->current_room = game_data.start_room;
    player->inventory_count = 0;
    player->max_health = game_data.health;
    player->current_health = game_data.health;
    player->game_won = false;
    player->game_over = false;
}

void to_lowercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

bool add_object_to_room(Room* room, Object* obj) {
    if (room->object_count >= MAX_OBJECTS_PER_ROOM) {
        printf("Error: Room '%s' is full (max %d objects)\n", room->name, MAX_OBJECTS_PER_ROOM);
        return false;
    }
    room->objects[room->object_count++] = obj;
    return true;
}

void reveal_hidden_item(Player* player, Object* obj) {
    if (obj->hidden_item && !obj->hidden_revealed) {
        printf("You found a hidden %s!\n", obj->hidden_item->name);
        if (!add_object_to_room(player->current_room, obj->hidden_item)) {
            printf("The room is too full to place the %s!\n", obj->hidden_item->name);
        }
        obj->hidden_revealed = true;
    }
}

void print_room(Room* room) {
    printf("\n--- %s ---\n", room->name);
    if (room->description) {
        printf("%s\n", room->description);
    }
    
    if (room->entry_message) {
        printf("\n%s\n", room->entry_message);
    }
    
    // Show objects in room
    if (room->object_count > 0) {
        printf("\nYou can see: ");
        for (int i = 0; i < room->object_count; i++) {
            if (room->objects[i]) {
                printf("%s", room->objects[i]->name);
                
                // Add status indicators
                if (room->objects[i]->content_count > 0) {
                    if (room->objects[i]->opened) {
                        printf(" (open)");
                    } else if (room->objects[i]->requires) {
                        printf(" (locked)");
                    } else {
                        printf(" (closed)");
                    }
                }
                
                if (i < room->object_count - 1) printf(", ");
            }
        }
        printf("\n");
    }
    
    // Show connections with room names and requirement hints
    if (room->connection_count > 0) {
        printf("\nExits:\n");
        for (int i = 0; i < room->connection_count; i++) {
            printf("  %s", room->connections[i].direction);
            
            // Add room name
            if (room->connections[i].room) {
                printf(" (to %s)", room->connections[i].room->name);
                
                // Add hint if the connected room has requirements
                if (room->connections[i].room->requires_count > 0) {
                    printf(" - requires items");
                }
            }
            printf("\n");
        }
        printf("(Use 'check <direction>' to see specific requirements)\n");
    }
}

void print_inventory(Player* player) {
    if (player->inventory_count == 0) {
        printf("Your inventory is empty.\n");
        return;
    }
    
    printf("Inventory: ");
    for (int i = 0; i < player->inventory_count; i++) {
        printf("%s", player->inventory[i]->name);
        if (i < player->inventory_count - 1) printf(", ");
    }
    printf("\n");
}

void print_help() {
    printf("\nAvailable commands:\n");
    printf("  look - Look around the current room\n");
    printf("  go <direction> - Move in a direction (north, south, east, west, etc.)\n");
    printf("  check <direction> - Check what's needed to enter a room\n");
    printf("  take <object> - Take an object\n");
    printf("  drop <object> - Drop an object from your inventory\n");
    printf("  open <object> - Open a container (like a chest)\n");
    printf("  examine <object> - Examine an object closely\n");
    printf("  search <object> - Search an object for hidden items\n");
    printf("  use <object> - Use/interact with an object\n");
    printf("  inventory - Show your inventory\n");
    printf("  health - Show your health\n");
    printf("  help - Show this help\n");
    printf("  quit - Quit the game\n");
}

bool has_object_in_inventory(Player* player, Object* obj) {
    if (!obj) return false;
    for (int i = 0; i < player->inventory_count; i++) {
        if (player->inventory[i] == obj) {
            return true;
        }
    }
    return false;
}

bool can_enter_room(Player* player, Room* room) {
    if (!room || room->requires_count == 0) return true;
    
    for (int i = 0; i < room->requires_count; i++) {
        if (!has_object_in_inventory(player, room->requires[i])) {
            return false;
        }
    }
    return true;
}

void show_room_requirements(Player* player, Room* room, bool trying_to_enter) {
    if (!room || room->requires_count == 0) return;
    
    if (trying_to_enter) {
        printf("You cannot enter this room. ");
    }
    
    // Show entry message if available
    if (room->entry_message) {
        printf("%s\n", room->entry_message);
    }
    
    // List required items
    printf("Required items: ");
    for (int i = 0; i < room->requires_count; i++) {
        if (room->requires[i]) {
            printf("%s", room->requires[i]->name);
            if (i < room->requires_count - 1) printf(", ");
        }
    }
    printf("\n");
    
    // Show which items player has vs needs
    printf("You have: ");
    bool has_any_required = false;
    for (int i = 0; i < room->requires_count; i++) {
        if (room->requires[i] && has_object_in_inventory(player, room->requires[i])) {
            if (has_any_required) printf(", ");
            printf("%s", room->requires[i]->name);
            has_any_required = true;
        }
    }
    
    if (!has_any_required) {
        printf("none of the required items");
    }
    printf("\n");
    
    // Show what's still needed
    printf("You still need: ");
    bool first_missing = true;
    for (int i = 0; i < room->requires_count; i++) {
        if (room->requires[i] && !has_object_in_inventory(player, room->requires[i])) {
            if (!first_missing) printf(", ");
            printf("%s", room->requires[i]->name);
            first_missing = false;
        }
    }
    printf("\n");
}

void check_room_requirements(Player* player, Room* room) {
    show_room_requirements(player, room, true);
}

bool add_to_inventory(Player* player, Object* obj) {
    if (player->inventory_count >= MAX_INVENTORY_SIZE) {
        printf("Your inventory is full (max %d items)!\n", MAX_INVENTORY_SIZE);
        return false;
    }
    player->inventory[player->inventory_count++] = obj;
    return true;
}

void remove_from_inventory(Player* player, Object* obj) {
    for (int i = 0; i < player->inventory_count; i++) {
        if (player->inventory[i] == obj) {
            // Shift remaining items
            for (int j = i; j < player->inventory_count - 1; j++) {
                player->inventory[j] = player->inventory[j + 1];
            }
            player->inventory_count--;
            break;
        }
    }
}

Object* find_object_in_room(Room* room, char* name) {
    for (int i = 0; i < room->object_count; i++) {
        if (room->objects[i] && strcasecmp(room->objects[i]->name, name) == 0) {
            return room->objects[i];
        }
    }
    return NULL;
}

Object* find_object_in_inventory(Player* player, char* name) {
    for (int i = 0; i < player->inventory_count; i++) {
        if (strcasecmp(player->inventory[i]->name, name) == 0) {
            return player->inventory[i];
        }
    }
    return NULL;
}

Room* find_connected_room(Room* current, char* direction) {
    for (int i = 0; i < current->connection_count; i++) {
        if (strcasecmp(current->connections[i].direction, direction) == 0) {
            return current->connections[i].room;
        }
    }
    return NULL;
}

void handle_trap(Player* player, Room* room) {
    if (!room->has_trap) return;
    
    // Check if player has protection
    if (room->trap.protection && has_object_in_inventory(player, room->trap.protection)) {
        if (room->trap.protection_message) {
            printf("%s\n", room->trap.protection_message);
        } else {
            printf("Your %s protects you from the trap!\n", room->trap.protection->name);
        }
        return;
    }
    
    // Take trap damage
    printf("%s\n", room->trap.message ? room->trap.message : "You triggered a trap!");
    player->current_health -= room->trap.damage;
    printf("You lose %d health! Health: %d/%d\n", room->trap.damage, player->current_health, player->max_health);
    
    if (player->current_health <= 0) {
        printf("You have died! Game Over.\n");
        player->game_over = true;
    }
}

void handle_enemy(Player* player, Room* room) {
    if (!room->has_enemy) return;
    
    printf("You encounter %s!\n", room->enemy.name);
    
    // Check if player has weakness item
    if (room->enemy.weakness && has_object_in_inventory(player, room->enemy.weakness)) {
        printf("You use %s against %s!\n", room->enemy.weakness->name, room->enemy.name);
        printf("You defeat %s!\n", room->enemy.name);
        
        // Give reward if any
        if (room->enemy.defeat_reward) {
            printf("You found %s!\n", room->enemy.defeat_reward->name);
            if (!add_to_inventory(player, room->enemy.defeat_reward)) {
                printf("Your inventory is full! %s falls to the ground.\n", room->enemy.defeat_reward->name);
                add_object_to_room(player->current_room, room->enemy.defeat_reward);
            }
        }
        
        // Remove enemy from room
        room->has_enemy = false;
    } else {
        // Take damage
        printf("%s attacks you!\n", room->enemy.name);
        player->current_health -= room->enemy.damage;
        printf("You lose %d health! Health: %d/%d\n", room->enemy.damage, player->current_health, player->max_health);
        
        if (player->current_health <= 0) {
            printf("You have been defeated! Game Over.\n");
            player->game_over = true;
        }
    }
}

void process_command(Player* player, char* input) {
    char command[100];
    char argument[100] = "";
    
    // Parse command and argument
    sscanf(input, "%s %[^\n]", command, argument);
    to_lowercase(command);
    
    if (strcmp(command, "look") == 0 || strcmp(command, "l") == 0) {
        print_room(player->current_room);
        
    } else if (strcmp(command, "go") == 0 || strcmp(command, "move") == 0) {
        if (strlen(argument) == 0) {
            printf("Go where? (Example: go north)\n");
            return;
        }
        
        to_lowercase(argument);
        Room* next_room = find_connected_room(player->current_room, argument);
        
        if (!next_room) {
            printf("You can't go that way.\n");
            return;
        }
        
        if (!can_enter_room(player, next_room)) {
            check_room_requirements(player, next_room);
            return;
        }
        
        player->current_room = next_room;
        print_room(player->current_room);
        
        // Handle room events
        handle_trap(player, player->current_room);
        if (!player->game_over) {
            handle_enemy(player, player->current_room);
        }
        
        // Check win condition
        if (player->current_room->win_condition) {
            printf("\nCongratulations! You have won the game!\n");
            player->game_won = true;
        }
        
    } else if (strcmp(command, "check") == 0) {
        if (strlen(argument) == 0) {
            printf("Check which direction? (Example: check north)\n");
            return;
        }
        
        to_lowercase(argument);
        Room* next_room = find_connected_room(player->current_room, argument);
        
        if (!next_room) {
            printf("There's no exit %s from here.\n", argument);
            return;
        }
        
        printf("Room to the %s: %s\n", argument, next_room->name);
        
        if (next_room->requires_count == 0) {
            printf("No special requirements to enter.\n");
        } else {
            show_room_requirements(player, next_room, false);
        }
        
    } else if (strcmp(command, "open") == 0) {
        if (strlen(argument) == 0) {
            printf("Open what? (Example: open chest)\n");
            return;
        }
        
        Object* obj = find_object_in_room(player->current_room, argument);
        if (!obj) {
            printf("There's no %s here.\n", argument);
            return;
        }
        
        // Check if object can be opened (has contents)
        if (obj->content_count == 0) {
            printf("You can't open %s.\n", obj->name);
            return;
        }
        
        // Check if already opened
        if (obj->opened) {
            printf("The %s is already open and empty.\n", obj->name);
            return;
        }
        
        // Check if requires a key
        if (obj->requires && !has_object_in_inventory(player, obj->requires)) {
            printf("The %s is locked. You need %s to open it.\n", obj->name, obj->requires->name);
            return;
        }
        
        // Open the container
        printf("You open the %s.\n", obj->name);
        
        // Consume key if required
        if (obj->requires && obj->consume_key) {
            printf("The %s is consumed in the process.\n", obj->requires->name);
            remove_from_inventory(player, obj->requires);
        }
        
        // Add contents to room
        if (obj->content_count > 0) {
            printf("Inside the %s you find: ", obj->name);
            for (int i = 0; i < obj->content_count; i++) {
                if (obj->contents[i]) {
                    printf("%s", obj->contents[i]->name);
                    if (i < obj->content_count - 1) printf(", ");
                    
                    // Add to room
                    if (!add_object_to_room(player->current_room, obj->contents[i])) {
                        printf("\n(The room is too full for some items!)");
                        break;
                    }
                }
            }
            printf("\n");
        }
        
        // Mark as opened
        obj->opened = true;
        
    } else if (strcmp(command, "take") == 0 || strcmp(command, "get") == 0) {
        if (strlen(argument) == 0) {
            printf("Take what? (Example: take key)\n");
            return;
        }
        
        Object* obj = find_object_in_room(player->current_room, argument);
        if (!obj) {
            printf("There's no %s here.\n", argument);
            return;
        }
        
        if (!obj->takeable) {
            // Special message for containers
            if (obj->content_count > 0 && !obj->opened) {
                printf("You can't take the %s. Try opening it instead.\n", obj->name);
            } else {
                printf("You can't take %s.\n", obj->name);
            }
            return;
        }
        
        // Check if requires another object
        if (obj->requires && !has_object_in_inventory(player, obj->requires)) {
            printf("You need %s to take %s.\n", obj->requires->name, obj->name);
            return;
        }
        
        // Check if inventory is full
        if (!add_to_inventory(player, obj)) {
            return;
        }
        
        // Remove from room
        for (int i = 0; i < player->current_room->object_count; i++) {
            if (player->current_room->objects[i] == obj) {
                for (int j = i; j < player->current_room->object_count - 1; j++) {
                    player->current_room->objects[j] = player->current_room->objects[j + 1];
                }
                player->current_room->object_count--;
                break;
            }
        }
        
        printf("You take %s.\n", obj->name);
        
        // Add contents to room if any
        if (obj->content_count > 0) {
            printf("The %s contains: ", obj->name);
            for (int i = 0; i < obj->content_count; i++) {
                if (obj->contents[i]) {
                    printf("%s", obj->contents[i]->name);
                    if (i < obj->content_count - 1) printf(", ");
                    
                    // Add to room
                    if (!add_object_to_room(player->current_room, obj->contents[i])) {
                        printf("\n(The room is too full for some items!)");
                        break;
                    }
                }
            }
            printf("\n");
        }
        
        // Reveal hidden item if any
        reveal_hidden_item(player, obj);
        
    } else if (strcmp(command, "drop") == 0) {
        if (strlen(argument) == 0) {
            printf("Drop what? (Example: drop key)\n");
            return;
        }
        
        Object* obj = find_object_in_inventory(player, argument);
        if (!obj) {
            printf("You don't have %s in your inventory.\n", argument);
            return;
        }
        
        // Remove from inventory and add to current room
        remove_from_inventory(player, obj);
        if (!add_object_to_room(player->current_room, obj)) {
            // If room is full, put it back in inventory
            add_to_inventory(player, obj);
            return;
        }
        
        printf("You drop %s.\n", obj->name);
        
    } else if (strcmp(command, "examine") == 0 || strcmp(command, "ex") == 0) {
        if (strlen(argument) == 0) {
            printf("Examine what? (Example: examine key)\n");
            return;
        }
        
        Object* obj = find_object_in_room(player->current_room, argument);
        if (!obj) {
            obj = find_object_in_inventory(player, argument);
        }
        
        if (!obj) {
            printf("There's no %s here.\n", argument);
            return;
        }
        
        if (obj->examine_text) {
            printf("%s\n", obj->examine_text);
        } else {
            printf("It's a %s. Nothing special about it.\n", obj->name);
        }
        
        // Give hints based on object properties
        if (obj->content_count > 0 && !obj->opened) {
            if (obj->requires) {
                printf("(The %s appears to be locked. Try opening it with the right key.)\n", obj->name);
            } else {
                printf("(The %s looks like it can be opened.)\n", obj->name);
            }
        } else if (obj->opened) {
            printf("(The %s is open and empty.)\n", obj->name);
        }
        
        // For non-takeable objects with hidden items, give a hint
        if (!obj->takeable && obj->hidden_item && !obj->hidden_revealed) {
            printf("(Try searching or using the %s)\n", obj->name);
        }
        
    } else if (strcmp(command, "search") == 0 || strcmp(command, "s") == 0) {
        if (strlen(argument) == 0) {
            printf("Search what? (Example: search brick)\n");
            return;
        }
        
        Object* obj = find_object_in_room(player->current_room, argument);
        if (!obj) {
            obj = find_object_in_inventory(player, argument);
        }
        
        if (!obj) {
            printf("There's no %s here.\n", argument);
            return;
        }
        
        if (obj->hidden_item && !obj->hidden_revealed) {
            reveal_hidden_item(player, obj);
        } else if (obj->hidden_revealed) {
            printf("You already searched the %s.\n", obj->name);
        } else {
            printf("You search the %s but find nothing hidden.\n", obj->name);
        }
        
    } else if (strcmp(command, "use") == 0) {
        if (strlen(argument) == 0) {
            printf("Use what? (Example: use brick)\n");
            return;
        }
        
        // Check if it's a "use X on Y" command
        char* on_pos = strstr(argument, " on ");
        if (on_pos) {
            *on_pos = '\0'; // Split the string
            char* item_name = argument;
            char* target_name = on_pos + 4;
            
            Object* item = find_object_in_inventory(player, item_name);
            Object* target = find_object_in_room(player->current_room, target_name);
            
            if (!item) {
                printf("You don't have %s.\n", item_name);
                return;
            }
            
            if (!target) {
                printf("There's no %s here.\n", target_name);
                return;
            }
            
            // Handle using key on container
            if (target->content_count > 0 && target->requires == item) {
                if (target->opened) {
                    printf("The %s is already open.\n", target->name);
                } else {
                    printf("You use %s on %s.\n", item->name, target->name);
                    
                    // Open the container
                    printf("You open the %s.\n", target->name);
                    
                    // Consume key if required
                    if (target->consume_key) {
                        printf("The %s is consumed in the process.\n", item->name);
                        remove_from_inventory(player, item);
                    }
                    
                    // Add contents to room
                    if (target->content_count > 0) {
                        printf("Inside the %s you find: ", target->name);
                        for (int i = 0; i < target->content_count; i++) {
                            if (target->contents[i]) {
                                printf("%s", target->contents[i]->name);
                                if (i < target->content_count - 1) printf(", ");
                                
                                // Add to room
                                if (!add_object_to_room(player->current_room, target->contents[i])) {
                                    printf("\n(The room is too full for some items!)");
                                    break;
                                }
                            }
                        }
                        printf("\n");
                    }
                    
                    // Mark as opened
                    target->opened = true;
                }
                return;
            } else {
                printf("You can't use %s on %s.\n", item->name, target->name);
                return;
            }
        }
        
        Object* obj = find_object_in_room(player->current_room, argument);
        if (!obj) {
            obj = find_object_in_inventory(player, argument);
        }
        
        if (!obj) {
            printf("There's no %s here.\n", argument);
            return;
        }
        
        // For objects with hidden items, using them reveals the item
        if (obj->hidden_item && !obj->hidden_revealed) {
            printf("You interact with the %s.\n", obj->name);
            reveal_hidden_item(player, obj);
        } else if (obj->hidden_revealed) {
            printf("You already used the %s.\n", obj->name);
        } else {
            printf("You can't use the %s in any meaningful way.\n", obj->name);
        }
        
    } else if (strcmp(command, "inventory") == 0 || strcmp(command, "i") == 0) {
        print_inventory(player);
        
    } else if (strcmp(command, "health") == 0 || strcmp(command, "hp") == 0) {
        printf("Health: %d/%d\n", player->current_health, player->max_health);
        
    } else if (strcmp(command, "help") == 0 || strcmp(command, "h") == 0) {
        print_help();
        
    } else if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0) {
        printf("Thanks for playing!\n");
        player->game_over = true;
        
    } else {
        printf("Unknown command. Type 'help' for available commands.\n");
    }
}

void game_loop(Player* player) {
    char input[200];
    
    printf("\n=== Welcome to %s ===\n", game_data.game_name);
    printf("Type 'help' for available commands.\n");
    print_room(player->current_room);
    
    while (!player->game_over && !player->game_won) {
        printf("\n> ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        if (strlen(input) == 0) continue;
        
        process_command(player, input);
    }
}

// Declare external parse function
int parse_game_file();

int main() {
    printf("Loading game configuration...\n");
    
    // Parse the game file
    if (parse_game_file() != 0) {
        printf("Failed to load game configuration!\n");
        return 1;
    }
    
    Player player;
    init_player(&player);
    
    game_loop(&player);
    
    if (player.game_won) {
        printf("\nYou completed the game successfully!\n");
    } else {
        printf("\nGame ended.\n");
    }
	return 0;
}