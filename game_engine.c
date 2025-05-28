#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Include structurile din parser
typedef struct Object Object;
typedef struct Room Room;

typedef struct Object {
    char* name;
    bool takeable;
    Object* requires;
    Object** contents;
    int content_count;
    Object* hidden_item;
    char* examine_text;
    bool consume_key;
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
    Connection* connections;
    int connection_count;
    Object** objects;
    int object_count;
    Object** requires;
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
    Object* objects;
    int object_count;
    Room* rooms;
    int room_count;
} Game;

// Player state
typedef struct {
    Room* current_room;
    Object** inventory;
    int inventory_count;
    int max_health;
    int current_health;
    bool game_won;
    bool game_over;
} Player;

// External game data (from parser)
extern Game game_data;

// Function prototypes
void init_player(Player* player);
void print_room(Room* room);
void print_inventory(Player* player);
void print_help();
bool has_object_in_inventory(Player* player, Object* obj);
bool can_enter_room(Player* player, Room* room);
void add_to_inventory(Player* player, Object* obj);
void remove_from_inventory(Player* player, Object* obj);
Object* find_object_in_room(Room* room, char* name);
Object* find_object_in_inventory(Player* player, char* name);
Room* find_connected_room(Room* current, char* direction);
void handle_trap(Player* player, Room* room);
void handle_enemy(Player* player, Room* room);
void process_command(Player* player, char* input);
void to_lowercase(char* str);
void game_loop(Player* player);

void init_player(Player* player) {
    player->current_room = game_data.start_room;
    player->inventory = malloc(20 * sizeof(Object*)); // Max 20 objects
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
                if (i < room->object_count - 1) printf(", ");
            }
        }
        printf("\n");
    }
    
    // Show connections
    if (room->connection_count > 0) {
        printf("\nExits: ");
        for (int i = 0; i < room->connection_count; i++) {
            printf("%s", room->connections[i].direction);
            if (i < room->connection_count - 1) printf(", ");
        }
        printf("\n");
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
    printf("  take <object> - Take an object\n");
    printf("  examine <object> - Examine an object\n");
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

void add_to_inventory(Player* player, Object* obj) {
    if (player->inventory_count < 20) {
        player->inventory[player->inventory_count++] = obj;
    }
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
            add_to_inventory(player, room->enemy.defeat_reward);
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
            printf("You need certain items to enter that room.\n");
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
            printf("You can't take %s.\n", obj->name);
            return;
        }
        
        // Check if requires another object
        if (obj->requires && !has_object_in_inventory(player, obj->requires)) {
            printf("You need %s to take %s.\n", obj->requires->name, obj->name);
            return;
        }
        
        // Remove from room and add to inventory
        for (int i = 0; i < player->current_room->object_count; i++) {
            if (player->current_room->objects[i] == obj) {
                for (int j = i; j < player->current_room->object_count - 1; j++) {
                    player->current_room->objects[j] = player->current_room->objects[j + 1];
                }
                player->current_room->object_count--;
                break;
            }
        }
        
        add_to_inventory(player, obj);
        printf("You take %s.\n", obj->name);
        
        // Add contents to room if any
        if (obj->content_count > 0) {
            printf("The %s contains: ", obj->name);
            for (int i = 0; i < obj->content_count; i++) {
                if (obj->contents[i]) {
                    printf("%s", obj->contents[i]->name);
                    if (i < obj->content_count - 1) printf(", ");
                    
                    // Add to room
                    player->current_room->objects = realloc(player->current_room->objects, 
                        (player->current_room->object_count + 1) * sizeof(Object*));
                    player->current_room->objects[player->current_room->object_count++] = obj->contents[i];
                }
            }
            printf("\n");
        }
        
        // Reveal hidden item if any
        if (obj->hidden_item) {
            printf("You found a hidden %s!\n", obj->hidden_item->name);
            player->current_room->objects = realloc(player->current_room->objects, 
                (player->current_room->object_count + 1) * sizeof(Object*));
            player->current_room->objects[player->current_room->object_count++] = obj->hidden_item;
        }
        
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
        return 0;
    } else {
        printf("\nGame ended.\n");
        return 0;
    }
}