/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    STRING = 258,                  /* STRING  */
    IDENTIFIER = 259,              /* IDENTIFIER  */
    NUMBER = 260,                  /* NUMBER  */
    TRUE = 261,                    /* TRUE  */
    FALSE = 262,                   /* FALSE  */
    GAME = 263,                    /* GAME  */
    START_ROOM = 264,              /* START_ROOM  */
    HEALTH = 265,                  /* HEALTH  */
    ROOM = 266,                    /* ROOM  */
    DESCRIPTION = 267,             /* DESCRIPTION  */
    OBJECTS = 268,                 /* OBJECTS  */
    CONNECTIONS = 269,             /* CONNECTIONS  */
    TAKEABLE = 270,                /* TAKEABLE  */
    REQUIRES = 271,                /* REQUIRES  */
    CONTENTS = 272,                /* CONTENTS  */
    HIDDEN_ITEM = 273,             /* HIDDEN_ITEM  */
    EXAMINE = 274,                 /* EXAMINE  */
    CONSUME_KEY = 275,             /* CONSUME_KEY  */
    TRAP = 276,                    /* TRAP  */
    ENEMY = 277,                   /* ENEMY  */
    DAMAGE = 278,                  /* DAMAGE  */
    WEAKNESS = 279,                /* WEAKNESS  */
    DEFEAT_REWARD = 280,           /* DEFEAT_REWARD  */
    WIN_CONDITION = 281,           /* WIN_CONDITION  */
    NAME = 282,                    /* NAME  */
    MESSAGE = 283,                 /* MESSAGE  */
    PROTECTION = 284,              /* PROTECTION  */
    PROTECTION_MESSAGE = 285,      /* PROTECTION_MESSAGE  */
    ENTRY_MESSAGE = 286,           /* ENTRY_MESSAGE  */
    EQUALS = 287,                  /* EQUALS  */
    OPEN_BRACE = 288,              /* OPEN_BRACE  */
    CLOSED_BRACE = 289,            /* CLOSED_BRACE  */
    LIST_START = 290,              /* LIST_START  */
    LIST_END = 291,                /* LIST_END  */
    COMMA = 292,                   /* COMMA  */
    COLON = 293                    /* COLON  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define STRING 258
#define IDENTIFIER 259
#define NUMBER 260
#define TRUE 261
#define FALSE 262
#define GAME 263
#define START_ROOM 264
#define HEALTH 265
#define ROOM 266
#define DESCRIPTION 267
#define OBJECTS 268
#define CONNECTIONS 269
#define TAKEABLE 270
#define REQUIRES 271
#define CONTENTS 272
#define HIDDEN_ITEM 273
#define EXAMINE 274
#define CONSUME_KEY 275
#define TRAP 276
#define ENEMY 277
#define DAMAGE 278
#define WEAKNESS 279
#define DEFEAT_REWARD 280
#define WIN_CONDITION 281
#define NAME 282
#define MESSAGE 283
#define PROTECTION 284
#define PROTECTION_MESSAGE 285
#define ENTRY_MESSAGE 286
#define EQUALS 287
#define OPEN_BRACE 288
#define CLOSED_BRACE 289
#define LIST_START 290
#define LIST_END 291
#define COMMA 292
#define COLON 293

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 160 "yacc_source.y"

    char* str;
    int number;

#line 148 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
