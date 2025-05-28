%{
    #include "y.tab.h"
    #include <string.h>
    #include <stdlib.h>
%}

%%

game                return GAME;
start_room          return START_ROOM;
health              return HEALTH;  
room                return ROOM;
description         return DESCRIPTION;
objects             return OBJECTS;
connections         return CONNECTIONS;
takeable            return TAKEABLE;
requires            return REQUIRES;
contents            return CONTENTS;
hidden_item         return HIDDEN_ITEM;
examine             return EXAMINE;
consume_key         return CONSUME_KEY;
trap                return TRAP;
enemy               return ENEMY;
damage              return DAMAGE;
weakness            return WEAKNESS;
defeat_reward       return DEFEAT_REWARD;
win_condition       return WIN_CONDITION;
name                return NAME;
message             return MESSAGE;
protection          return PROTECTION;
protection_message  return PROTECTION_MESSAGE;
entry_message       return ENTRY_MESSAGE;
true                return TRUE;
false               return FALSE;

"="                 return EQUALS;
"{"                 return OPEN_BRACE;
"}"                 return CLOSED_BRACE;
"["                 return LIST_START;
"]"                 return LIST_END;
","                 return COMMA;
":"                 return COLON;

[a-zA-Z_][a-zA-Z0-9_]* {
                    yylval.str = strdup(yytext);
                    return IDENTIFIER;
                }

\"[^\"]*\"          {
                    yylval.str = strdup(yytext + 1);
                    yylval.str[strlen(yylval.str) - 1] = '\0';
                    return STRING;
                }

[0-9]+              {
                    yylval.number = atoi(yytext);
                    return NUMBER;
                }

[ \t\n\r]+          ;
#.*\n               ;   /* Comments */
.                   ;   /* Ignore other characters */

%%

int yywrap() {
    return 1;
}