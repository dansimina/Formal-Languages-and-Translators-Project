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

%token GAME START_ROOM HEALTH ROOM

%token EQUALS OPEN_BRACE CLOSED_BRACE LIST_START LIST_END COMMA

%%

program: GAME STRING OPEN_BRACE configuration CLOSED_BRACE  { printf("Game: %s\n", $2); }
        ;

configuration: start_room health rooms
            ;

start_room: START_ROOM EQUALS STRING { printf("Start Room: %s\n", $3); }
            ;

health: HEALTH EQUALS NUMBER { printf("Health: %d\n", $3); }
            ;

rooms: ROOM EQUALS OPEN_BRACE room_list CLOSED_BRACE
room_list: 
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