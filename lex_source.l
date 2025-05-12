%{
    #include "y.tab.h"
    #include <string.h>
%}

%%

game            return GAME;
start_room      return START_ROOM;
health          return HEALTH;  
room            return ROOM;

"="             return EQUALS;
"{"             return OPEN_BRACE;
"}"             return CLOSED_BRACE;
"["             return LIST_START;
"]"             return LIST_END;
","             return COMMA;

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