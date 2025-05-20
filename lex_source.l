%{
    #include "y.tab.h"
    #include <string.h>
%}

%%

game            return GAME;
start_room      return START_ROOM;
health          return HEALTH;  
room            return ROOM;

description     return DESCRIPTION;
objects         return OBJECTS;
connections     return CONNECTIONS;

takeable        return TAKEABLE;
requires        return REQUIRES;
contents        return CONTENTS;
hidden_item     return HIDDEN_ITEM;
examine         return EXAMINE;

true          return TRUE;
false         return FALSE;

"="             return EQUALS;
"{"             return OPEN_BRACE;
"}"             return CLOSED_BRACE;
"["             return LIST_START;
"]"             return LIST_END;
","             return COMMA;
":"             return COLON;


[a-zA-Z_][a-zA-Z_][a-zA-Z0-9_]* {
                                    yylval.str = strdup(yytext);
                                    return IDENTIFIER;
                                }

\"[^\"]*\"      {
                    yylval.str = strdup(yytext + 1);
                    yylval.str[strlen(yylval.str) - 1] = '\0';
                    return STRING;
                }

[0-9]+          {
                    yylval.number = atoi(yytext);
                    return NUMBER;
                }

[ \t\n\r]+      ;

#.*\n           ;

.               ;

%%