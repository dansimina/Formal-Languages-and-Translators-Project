%{
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>

    int yylex(void);
    void yyerror(const char* str);

    extern FILE* yyin;
%}

%union {
    char* str;
    int number;
}

%token <str> STRING
%token <number> NUMBER
%token TRUE FALSE

%token <str> IDENTIFIER

%token GAME START_ROOM HEALTH ROOM
%token DESCRIPTION OBJECTS CONNECTIONS
%token TAKEABLE REQUIRES CONTENTS HIDDEN_ITEM EXAMINE

%token EQUALS OPEN_BRACE CLOSED_BRACE LIST_START LIST_END COMMA COLON

%%

program: GAME STRING OPEN_BRACE configuration CLOSED_BRACE  { printf("Game: %s\n", $2); }
        ;

configuration: start_room health list_of_rooms
            ;

start_room: START_ROOM EQUALS STRING { printf("Start Room: %s\n", $3); }
            ;

health: HEALTH EQUALS NUMBER { printf("Health: %d\n", $3); }
            ;

list_of_rooms: list_of_rooms room_config
            |room_config
            ;

room_config: ROOM STRING OPEN_BRACE room_description room_objects room_connections CLOSED_BRACE
            { printf("Room: %s\n", $2); }
            ;

room_description: DESCRIPTION EQUALS STRING { printf("Description: %s\n", $3); }
            ;

room_objects: OBJECTS EQUALS LIST_START object_list LIST_END
            ;

object_list: object_list COMMA object_config
            |object_config
            ;

object_config: IDENTIFIER COLON OPEN_BRACE object_description_list CLOSED_BRACE
            { printf("Object: %s\n", $1); }

object_description_list: object_description_list COMMA object_description
            |object_description
            ;
        
object_description: TAKEABLE EQUALS TRUE { printf("Takeable: TRUE\n"); }
            |TAKEABLE EQUALS FALSE { printf("Takeable: FALSE\n"); }
            |REQUIRES EQUALS STRING { printf("Requires: %s\n", $3); }
            |CONTENTS EQUALS list_of_items
            |HIDDEN_ITEM EQUALS STRING { printf("Hidden Item: %s\n", $3); }
            |EXAMINE EQUALS STRING { printf("Examine: %s\n", $3); }
            ;

list_of_items: LIST_START item_list LIST_END
            ;

item_list: item_list COMMA item
            |item
            ;
item: STRING    { printf("Item: %s\n", $1); }
            ;

room_connections: CONNECTIONS EQUALS LIST_START connection_list LIST_END
            ;

connection_list: connection_list connection
            |connection
            ;

connection: IDENTIFIER COLON STRING
            { printf("Connection: %s -> %s\n", $1, $3); }
            ;
%%

int main() {
    
    FILE* config_file = fopen("config.txt", "r");
    if (!config_file) {
        fprintf(stderr, "Error: Could not open config.txt\n");
        return 1;
    }

    yyin = config_file;

    int result = yyparse();

    fclose(config_file);

    //if (result == 0) {
    //}

    return result;
}

void yyerror(const char* str) {
    fprintf(stderr, "Syntax error: %s\n", str);
}