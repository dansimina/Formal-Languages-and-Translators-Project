%{
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include <stdlib.h>

    // Constants for fixed array sizes
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

    typedef struct {
        char* name;
        bool takeable;
        char* requires_name;
        char* contents_names[MAX_CONTENTS_PER_OBJECT];
        int content_count;
        char* hidden_item_name;
        char* examine_text;
        bool consume_key;
    } TempObject;

    typedef struct {
        char* direction;
        char* room_name;
    } TempConnection;

    typedef struct {
        int damage;
        char* message;
        char* protection_name;
        char* protection_message;
    } TempTrap;

    typedef struct {
        char* name;
        int damage;
        char* weakness_name;
        char* defeat_reward_name;
    } TempEnemy;

    typedef struct {
        char* name;
        char* description;
        TempConnection connections[MAX_CONNECTIONS_PER_ROOM];
        int connection_count;
        char* objects_names[MAX_OBJECTS_PER_ROOM];
        int object_count;
        char* requires_names[MAX_REQUIREMENTS_PER_ROOM];
        int requires_count;
        char* entry_message;
        bool has_trap;
        TempTrap trap;
        bool has_enemy;
        TempEnemy enemy;
        bool win_condition;
    } TempRoom;

    Game game_data;
    TempObject temp_object;
    TempRoom temp_room;
    TempTrap temp_trap;
    TempEnemy temp_enemy;
    
    TempObject temp_objects[MAX_OBJECTS];
    int temp_object_count;
    TempRoom temp_rooms[MAX_ROOMS];
    int temp_room_count;
    char* temp_start_room_name;

    int parse_error_count = 0;
    bool parsing_failed = false;

    void init_game();
    bool add_temp_object(TempObject obj);
    bool add_temp_room(TempRoom room);
    void link_references();
    Object* find_object(char* name);
    Room* find_room(char* name);
    void print_game_data();
    void reset_temp_object();
    void reset_temp_room();
    
    bool object_name_exists(char* name);
    bool room_name_exists(char* name);
    void report_error(const char* message);
    bool validate_game_data();

    int yylex(void);
    void yyerror(const char* str);
    extern FILE* yyin;
    extern int yylineno;
%}

%union {
    char* str;
    int number;
}

%token <str> STRING IDENTIFIER
%token <number> NUMBER
%token TRUE FALSE

%token GAME START_ROOM HEALTH ROOM
%token DESCRIPTION OBJECTS CONNECTIONS
%token TAKEABLE REQUIRES CONTENTS HIDDEN_ITEM EXAMINE CONSUME_KEY
%token TRAP ENEMY DAMAGE WEAKNESS DEFEAT_REWARD WIN_CONDITION
%token NAME MESSAGE PROTECTION PROTECTION_MESSAGE ENTRY_MESSAGE

%token EQUALS OPEN_BRACE CLOSED_BRACE LIST_START LIST_END COMMA COLON

%%

program: GAME STRING OPEN_BRACE { 
            init_game(); 
            if ($2 == NULL || strlen($2) == 0) {
                report_error("Game name cannot be empty");
                YYERROR;
            }
            game_data.game_name = strdup($2); 
        } configuration CLOSED_BRACE {
            if (!parsing_failed && validate_game_data()) {
                link_references();
            } else {
                printf("Parsing failed due to validation errors.\n");
                YYERROR;
            }
        }
        ;

configuration: start_room health objects rooms
            ;

start_room: START_ROOM EQUALS STRING { 
            if ($3 == NULL || strlen($3) == 0) {
                report_error("Start room name cannot be empty");
                YYERROR;
            }
            temp_start_room_name = strdup($3); 
        }
        ;

health: HEALTH EQUALS NUMBER { 
            if ($3 <= 0) {
                report_error("Health must be a positive number");
                YYERROR;
            }
            game_data.health = $3; 
        }
        ;

objects: OBJECTS OPEN_BRACE list_of_objects CLOSED_BRACE
        ;

list_of_objects: list_of_objects COMMA object_config
            | object_config
            ;

object_config: IDENTIFIER COLON OPEN_BRACE {
                if ($1 == NULL || strlen($1) == 0) {
                    report_error("Object name cannot be empty");
                    YYERROR;
                }
                if (object_name_exists($1)) {
                    char error_msg[256];
                    snprintf(error_msg, sizeof(error_msg), "Object '%s' already exists", $1);
                    report_error(error_msg);
                    YYERROR;
                }
                reset_temp_object();
                temp_object.name = strdup($1);
            } object_props CLOSED_BRACE {
                if (!add_temp_object(temp_object)) {
                    YYERROR;
                }
            }
            ;

object_props: object_props object_prop
            | object_prop
            |
            ;
        
object_prop: TAKEABLE EQUALS TRUE { temp_object.takeable = true; }
            | TAKEABLE EQUALS FALSE { temp_object.takeable = false; }
            | REQUIRES EQUALS IDENTIFIER { 
                if ($3 == NULL || strlen($3) == 0) {
                    report_error("Required object name cannot be empty");
                    YYERROR;
                }
                temp_object.requires_name = strdup($3); 
            }
            | CONTENTS EQUALS LIST_START item_list LIST_END
            | HIDDEN_ITEM EQUALS IDENTIFIER { 
                if ($3 == NULL || strlen($3) == 0) {
                    report_error("Hidden item name cannot be empty");
                    YYERROR;
                }
                temp_object.hidden_item_name = strdup($3); 
            }
            | EXAMINE EQUALS STRING { 
                if ($3 == NULL) {
                    report_error("Examine text cannot be null");
                    YYERROR;
                }
                temp_object.examine_text = strdup($3); 
            }
            | CONSUME_KEY EQUALS TRUE { temp_object.consume_key = true; }
            | CONSUME_KEY EQUALS FALSE { temp_object.consume_key = false; }
            ;

item_list: item_list COMMA IDENTIFIER {
            if ($3 == NULL || strlen($3) == 0) {
                report_error("Item name in contents list cannot be empty");
                YYERROR;
            }
            if (temp_object.content_count >= MAX_CONTENTS_PER_OBJECT) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Object '%s' has too many contents (max %d)", 
                        temp_object.name, MAX_CONTENTS_PER_OBJECT);
                report_error(error_msg);
                YYERROR;
            }
            temp_object.contents_names[temp_object.content_count++] = strdup($3);
        }
        | IDENTIFIER {
            if ($1 == NULL || strlen($1) == 0) {
                report_error("Item name in contents list cannot be empty");
                YYERROR;
            }
            if (temp_object.content_count >= MAX_CONTENTS_PER_OBJECT) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Object '%s' has too many contents (max %d)", 
                        temp_object.name, MAX_CONTENTS_PER_OBJECT);
                report_error(error_msg);
                YYERROR;
            }
            temp_object.contents_names[temp_object.content_count++] = strdup($1);
        }
        |
        ;

rooms: rooms room_definition
        | room_definition
        |
        ;

room_definition: ROOM STRING OPEN_BRACE {
                if ($2 == NULL || strlen($2) == 0) {
                    report_error("Room name cannot be empty");
                    YYERROR;
                }
                if (room_name_exists($2)) {
                    char error_msg[256];
                    snprintf(error_msg, sizeof(error_msg), "Room '%s' already exists", $2);
                    report_error(error_msg);
                    YYERROR;
                }
                reset_temp_room();
                temp_room.name = strdup($2);
            } room_content_list CLOSED_BRACE {
                if (!add_temp_room(temp_room)) {
                    YYERROR;
                }
            }
            ;

room_content_list: room_content_list room_content
                | room_content
                |
                ;

room_content: DESCRIPTION EQUALS STRING { 
                if ($3 == NULL) {
                    report_error("Room description cannot be null");
                    YYERROR;
                }
                temp_room.description = strdup($3); 
            }
            | OBJECTS EQUALS LIST_START object_list LIST_END
            | CONNECTIONS EQUALS LIST_START connection_list LIST_END
            | REQUIRES EQUALS IDENTIFIER { 
                if ($3 == NULL || strlen($3) == 0) {
                    report_error("Required object name cannot be empty");
                    YYERROR;
                }
                if (temp_room.requires_count >= MAX_REQUIREMENTS_PER_ROOM) {
                    char error_msg[256];
                    snprintf(error_msg, sizeof(error_msg), "Room '%s' has too many requirements (max %d)", 
                            temp_room.name, MAX_REQUIREMENTS_PER_ROOM);
                    report_error(error_msg);
                    YYERROR;
                }
                temp_room.requires_names[temp_room.requires_count++] = strdup($3);
            }
            | REQUIRES EQUALS LIST_START req_list LIST_END
            | ENTRY_MESSAGE EQUALS STRING { 
                if ($3 == NULL) {
                    report_error("Entry message cannot be null");
                    YYERROR;
                }
                temp_room.entry_message = strdup($3); 
            }
            | trap_definition
            | enemy_definition
            | WIN_CONDITION EQUALS TRUE { temp_room.win_condition = true; }
            ;

object_list: object_list COMMA IDENTIFIER {
            if ($3 == NULL || strlen($3) == 0) {
                report_error("Object name in room cannot be empty");
                YYERROR;
            }
            if (temp_room.object_count >= MAX_OBJECTS_PER_ROOM) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Room '%s' has too many objects (max %d)", 
                        temp_room.name, MAX_OBJECTS_PER_ROOM);
                report_error(error_msg);
                YYERROR;
            }
            temp_room.objects_names[temp_room.object_count++] = strdup($3);
        }
        | IDENTIFIER {
            if ($1 == NULL || strlen($1) == 0) {
                report_error("Object name in room cannot be empty");
                YYERROR;
            }
            if (temp_room.object_count >= MAX_OBJECTS_PER_ROOM) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Room '%s' has too many objects (max %d)", 
                        temp_room.name, MAX_OBJECTS_PER_ROOM);
                report_error(error_msg);
                YYERROR;
            }
            temp_room.objects_names[temp_room.object_count++] = strdup($1);
        }
        |
        ;

req_list: req_list COMMA IDENTIFIER {
            if ($3 == NULL || strlen($3) == 0) {
                report_error("Required object name cannot be empty");
                YYERROR;
            }
            if (temp_room.requires_count >= MAX_REQUIREMENTS_PER_ROOM) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Room '%s' has too many requirements (max %d)", 
                        temp_room.name, MAX_REQUIREMENTS_PER_ROOM);
                report_error(error_msg);
                YYERROR;
            }
            temp_room.requires_names[temp_room.requires_count++] = strdup($3);
        }
        | IDENTIFIER {
            if ($1 == NULL || strlen($1) == 0) {
                report_error("Required object name cannot be empty");
                YYERROR;
            }
            if (temp_room.requires_count >= MAX_REQUIREMENTS_PER_ROOM) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Room '%s' has too many requirements (max %d)", 
                        temp_room.name, MAX_REQUIREMENTS_PER_ROOM);
                report_error(error_msg);
                YYERROR;
            }
            temp_room.requires_names[temp_room.requires_count++] = strdup($1);
        }
        ;

connection_list: connection_list COMMA connection
                | connection
                |
                ;

connection: IDENTIFIER COLON STRING {
            if ($1 == NULL || strlen($1) == 0) {
                report_error("Connection direction cannot be empty");
                YYERROR;
            }
            if ($3 == NULL || strlen($3) == 0) {
                report_error("Connected room name cannot be empty");
                YYERROR;
            }
            if (temp_room.connection_count >= MAX_CONNECTIONS_PER_ROOM) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Room '%s' has too many connections (max %d)", 
                        temp_room.name, MAX_CONNECTIONS_PER_ROOM);
                report_error(error_msg);
                YYERROR;
            }
            temp_room.connections[temp_room.connection_count].direction = strdup($1);
            temp_room.connections[temp_room.connection_count].room_name = strdup($3);
            temp_room.connection_count++;
        }
        ;

trap_definition: TRAP OPEN_BRACE trap_props CLOSED_BRACE {
                temp_room.has_trap = true;
                temp_room.trap = temp_trap;
            }
            ;

trap_props: trap_props trap_prop
            | trap_prop
            |
            ;

trap_prop: DAMAGE EQUALS NUMBER { 
                if ($3 < 0) {
                    report_error("Trap damage cannot be negative");
                    YYERROR;
                }
                temp_trap.damage = $3; 
            }
            | MESSAGE EQUALS STRING { 
                if ($3 == NULL) {
                    report_error("Trap message cannot be null");
                    YYERROR;
                }
                temp_trap.message = strdup($3); 
            }
            | PROTECTION EQUALS IDENTIFIER { 
                if ($3 == NULL || strlen($3) == 0) {
                    report_error("Protection object name cannot be empty");
                    YYERROR;
                }
                temp_trap.protection_name = strdup($3); 
            }
            | PROTECTION_MESSAGE EQUALS STRING { 
                if ($3 == NULL) {
                    report_error("Protection message cannot be null");
                    YYERROR;
                }
                temp_trap.protection_message = strdup($3); 
            }
            ;

enemy_definition: ENEMY OPEN_BRACE enemy_props CLOSED_BRACE {
                temp_room.has_enemy = true;
                temp_room.enemy = temp_enemy;
            }
            ;

enemy_props: enemy_props enemy_prop
            | enemy_prop
            |
            ;

enemy_prop: NAME EQUALS STRING { 
                if ($3 == NULL || strlen($3) == 0) {
                    report_error("Enemy name cannot be empty");
                    YYERROR;
                }
                temp_enemy.name = strdup($3); 
            }
            | DAMAGE EQUALS NUMBER { 
                if ($3 < 0) {
                    report_error("Enemy damage cannot be negative");
                    YYERROR;
                }
                temp_enemy.damage = $3; 
            }
            | WEAKNESS EQUALS IDENTIFIER { 
                if ($3 == NULL || strlen($3) == 0) {
                    report_error("Enemy weakness object name cannot be empty");
                    YYERROR;
                }
                temp_enemy.weakness_name = strdup($3); 
            }
            | DEFEAT_REWARD EQUALS IDENTIFIER { 
                if ($3 == NULL || strlen($3) == 0) {
                    report_error("Enemy defeat reward object name cannot be empty");
                    YYERROR;
                }
                temp_enemy.defeat_reward_name = strdup($3); 
            }
            ;

%%

void report_error(const char* message) {
    fprintf(stderr, "ERROR (line %d): %s\n", yylineno, message);
    parse_error_count++;
    parsing_failed = true;
}

bool object_name_exists(char* name) {
    if (!name) return false;
    for (int i = 0; i < temp_object_count; i++) {
        if (temp_objects[i].name && strcmp(temp_objects[i].name, name) == 0) {
            return true;
        }
    }
    return false;
}

bool room_name_exists(char* name) {
    if (!name) return false;
    for (int i = 0; i < temp_room_count; i++) {
        if (temp_rooms[i].name && strcmp(temp_rooms[i].name, name) == 0) {
            return true;
        }
    }
    return false;
}

bool validate_game_data() {
    bool valid = true;
    
    // Check if game has at least one room
    if (temp_room_count == 0) {
        report_error("Game must have at least one room");
        valid = false;
    }
    
    // Check if start room exists
    if (temp_start_room_name && !room_name_exists(temp_start_room_name)) {
        char error_msg[256];
        snprintf(error_msg, sizeof(error_msg), "Start room '%s' does not exist", temp_start_room_name);
        report_error(error_msg);
        valid = false;
    }
    
    // Validate object references
    for (int i = 0; i < temp_object_count; i++) {
        TempObject* obj = &temp_objects[i];
        
        if (obj->requires_name && !object_name_exists(obj->requires_name)) {
            char error_msg[256];
            snprintf(error_msg, sizeof(error_msg), "Object '%s' requires non-existent object '%s'", 
                    obj->name, obj->requires_name);
            report_error(error_msg);
            valid = false;
        }
        
        if (obj->hidden_item_name && !object_name_exists(obj->hidden_item_name)) {
            char error_msg[256];
            snprintf(error_msg, sizeof(error_msg), "Object '%s' has non-existent hidden item '%s'", 
                    obj->name, obj->hidden_item_name);
            report_error(error_msg);
            valid = false;
        }
        
        for (int j = 0; j < obj->content_count; j++) {
            if (obj->contents_names[j] && !object_name_exists(obj->contents_names[j])) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Object '%s' contains non-existent object '%s'", 
                        obj->name, obj->contents_names[j]);
                report_error(error_msg);
                valid = false;
            }
        }
    }
    
    // Validate room references
    for (int i = 0; i < temp_room_count; i++) {
        TempRoom* room = &temp_rooms[i];
        
        // Check room object references
        for (int j = 0; j < room->object_count; j++) {
            if (room->objects_names[j] && !object_name_exists(room->objects_names[j])) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Room '%s' contains non-existent object '%s'", 
                        room->name, room->objects_names[j]);
                report_error(error_msg);
                valid = false;
            }
        }
        
        // Check room requirement references
        for (int j = 0; j < room->requires_count; j++) {
            if (room->requires_names[j] && !object_name_exists(room->requires_names[j])) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Room '%s' requires non-existent object '%s'", 
                        room->name, room->requires_names[j]);
                report_error(error_msg);
                valid = false;
            }
        }
        
        // Check connection references
        for (int j = 0; j < room->connection_count; j++) {
            if (room->connections[j].room_name && !room_name_exists(room->connections[j].room_name)) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Room '%s' has connection to non-existent room '%s'", 
                        room->name, room->connections[j].room_name);
                report_error(error_msg);
                valid = false;
            }
        }
        
        // Check trap protection reference
        if (room->has_trap && room->trap.protection_name && 
            !object_name_exists(room->trap.protection_name)) {
            char error_msg[256];
            snprintf(error_msg, sizeof(error_msg), "Room '%s' trap protection references non-existent object '%s'", 
                    room->name, room->trap.protection_name);
            report_error(error_msg);
            valid = false;
        }
        
        // Check enemy references
        if (room->has_enemy) {
            if (room->enemy.weakness_name && !object_name_exists(room->enemy.weakness_name)) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Room '%s' enemy weakness references non-existent object '%s'", 
                        room->name, room->enemy.weakness_name);
                report_error(error_msg);
                valid = false;
            }
            
            if (room->enemy.defeat_reward_name && !object_name_exists(room->enemy.defeat_reward_name)) {
                char error_msg[256];
                snprintf(error_msg, sizeof(error_msg), "Room '%s' enemy defeat reward references non-existent object '%s'", 
                        room->name, room->enemy.defeat_reward_name);
                report_error(error_msg);
                valid = false;
            }
        }
    }
    
    return valid;
}

void init_game() {
    memset(&game_data, 0, sizeof(Game));
    memset(temp_objects, 0, sizeof(temp_objects));
    memset(temp_rooms, 0, sizeof(temp_rooms));
    temp_object_count = 0;
    temp_room_count = 0;
    parse_error_count = 0;
    parsing_failed = false;
}

void reset_temp_object() {
    memset(&temp_object, 0, sizeof(TempObject));
}

void reset_temp_room() {
    memset(&temp_room, 0, sizeof(TempRoom));
    memset(&temp_trap, 0, sizeof(TempTrap));
    memset(&temp_enemy, 0, sizeof(TempEnemy));
}

bool add_temp_object(TempObject obj) {
    if (temp_object_count >= MAX_OBJECTS) {
        char error_msg[256];
        snprintf(error_msg, sizeof(error_msg), "Too many objects defined (max %d)", MAX_OBJECTS);
        report_error(error_msg);
        return false;
    }
    temp_objects[temp_object_count++] = obj;
    return true;
}

bool add_temp_room(TempRoom room) {
    if (temp_room_count >= MAX_ROOMS) {
        char error_msg[256];
        snprintf(error_msg, sizeof(error_msg), "Too many rooms defined (max %d)", MAX_ROOMS);
        report_error(error_msg);
        return false;
    }
    temp_rooms[temp_room_count++] = room;
    return true;
}

Object* find_object(char* name) {
    if (!name) return NULL;
    for (int i = 0; i < game_data.object_count; i++) {
        if (strcmp(game_data.objects[i].name, name) == 0) {
            return &game_data.objects[i];
        }
    }
    return NULL;
}

Room* find_room(char* name) {
    if (!name) return NULL;
    for (int i = 0; i < game_data.room_count; i++) {
        if (strcmp(game_data.rooms[i].name, name) == 0) {
            return &game_data.rooms[i];
        }
    }
    return NULL;
}

void link_references() {
    // Set final counts
    game_data.object_count = temp_object_count;
    game_data.room_count = temp_room_count;
    
    // Copy objects (without references yet)
    for (int i = 0; i < temp_object_count; i++) {
        game_data.objects[i].name = temp_objects[i].name;
        game_data.objects[i].takeable = temp_objects[i].takeable;
        game_data.objects[i].examine_text = temp_objects[i].examine_text;
        game_data.objects[i].consume_key = temp_objects[i].consume_key;
        game_data.objects[i].content_count = 0;  // Will be set below
        game_data.objects[i].requires = NULL;
        game_data.objects[i].hidden_item = NULL;
    }
    
    // Copy rooms (without references yet)
    for (int i = 0; i < temp_room_count; i++) {
        game_data.rooms[i].name = temp_rooms[i].name;
        game_data.rooms[i].description = temp_rooms[i].description;
        game_data.rooms[i].entry_message = temp_rooms[i].entry_message;
        game_data.rooms[i].win_condition = temp_rooms[i].win_condition;
        game_data.rooms[i].has_trap = temp_rooms[i].has_trap;
        game_data.rooms[i].has_enemy = temp_rooms[i].has_enemy;
        game_data.rooms[i].connection_count = 0;
        game_data.rooms[i].object_count = 0;
        game_data.rooms[i].requires_count = 0;
    }
    
    // Now link references for objects
    for (int i = 0; i < temp_object_count; i++) {
        // Link requires
        game_data.objects[i].requires = find_object(temp_objects[i].requires_name);
        
        // Link hidden_item
        game_data.objects[i].hidden_item = find_object(temp_objects[i].hidden_item_name);
        
        // Link contents
        game_data.objects[i].content_count = temp_objects[i].content_count;
        for (int j = 0; j < temp_objects[i].content_count; j++) {
            game_data.objects[i].contents[j] = find_object(temp_objects[i].contents_names[j]);
        }
    }
    
    // Link references for rooms
    for (int i = 0; i < temp_room_count; i++) {
        // Link objects
        game_data.rooms[i].object_count = temp_rooms[i].object_count;
        for (int j = 0; j < temp_rooms[i].object_count; j++) {
            game_data.rooms[i].objects[j] = find_object(temp_rooms[i].objects_names[j]);
        }
        
        // Link requires
        game_data.rooms[i].requires_count = temp_rooms[i].requires_count;
        for (int j = 0; j < temp_rooms[i].requires_count; j++) {
            game_data.rooms[i].requires[j] = find_object(temp_rooms[i].requires_names[j]);
        }
        
        // Link connections
        game_data.rooms[i].connection_count = temp_rooms[i].connection_count;
        for (int j = 0; j < temp_rooms[i].connection_count; j++) {
            game_data.rooms[i].connections[j].direction = temp_rooms[i].connections[j].direction;
            game_data.rooms[i].connections[j].room = find_room(temp_rooms[i].connections[j].room_name);
        }
        
        // Link trap protection
        if (game_data.rooms[i].has_trap) {
            game_data.rooms[i].trap.damage = temp_rooms[i].trap.damage;
            game_data.rooms[i].trap.message = temp_rooms[i].trap.message;
            game_data.rooms[i].trap.protection_message = temp_rooms[i].trap.protection_message;
            game_data.rooms[i].trap.protection = find_object(temp_rooms[i].trap.protection_name);
        }
        
        // Link enemy weakness and reward
        if (game_data.rooms[i].has_enemy) {
            game_data.rooms[i].enemy.name = temp_rooms[i].enemy.name;
            game_data.rooms[i].enemy.damage = temp_rooms[i].enemy.damage;
            game_data.rooms[i].enemy.weakness = find_object(temp_rooms[i].enemy.weakness_name);
            game_data.rooms[i].enemy.defeat_reward = find_object(temp_rooms[i].enemy.defeat_reward_name);
        }
    }
    
    // Link start room
    game_data.start_room = find_room(temp_start_room_name);
}

// Export function for game engine
int parse_game_file() {
    FILE* config_file = fopen("config.txt", "r");
    if (!config_file) {
        fprintf(stderr, "Error: Could not open config.txt\n");
        return 1;
    }

    yyin = config_file;
    int result = yyparse();
    fclose(config_file);

    if (result == 0 && !parsing_failed) {
        printf("Game configuration loaded successfully!\n");
        printf("Loaded %d objects and %d rooms.\n", game_data.object_count, game_data.room_count);
        return 0;
    } else {
        printf("Failed to load game configuration!\n");
        printf("Total errors: %d\n", parse_error_count);
        return 1;
    }
}

void yyerror(const char* str) {
    fprintf(stderr, "Parse Error (line %d): %s\n", yylineno, str);
    parse_error_count++;
    parsing_failed = true;
}