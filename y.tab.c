/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "yacc_source.y"

    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include <stdlib.h>

    // Forward declarations
    typedef struct Object Object;
    typedef struct Room Room;

    // Struct-uri cu referințe directe
    typedef struct Object {
        char* name;
        bool takeable;
        Object* requires;               // pointer direct la obiect
        Object** contents;              // array de pointeri la obiecte
        int content_count;
        Object* hidden_item;            // pointer direct la obiect
        char* examine_text;
        bool consume_key;
    } Object;

    typedef struct {
        char* direction;
        Room* room;                     // pointer direct la cameră
    } Connection;

    typedef struct {
        int damage;
        char* message;
        Object* protection;             // pointer direct la obiect
        char* protection_message;
    } Trap;

    typedef struct {
        char* name;
        int damage;
        Object* weakness;               // pointer direct la obiect
        Object* defeat_reward;          // pointer direct la obiect
    } Enemy;

    typedef struct Room {
        char* name;
        char* description;
        Connection* connections;
        int connection_count;
        Object** objects;               // array de pointeri la obiecte
        int object_count;
        Object** requires;              // array de pointeri la obiecte necesare
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
        Room* start_room;               // pointer direct la cameră
        int health;
        Object* objects;
        int object_count;
        Room* rooms;
        int room_count;
    } Game;

    // Structuri temporare pentru parsing (cu nume ca string-uri)
    typedef struct {
        char* name;
        bool takeable;
        char* requires_name;
        char** contents_names;
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
        TempConnection* connections;
        int connection_count;
        char** objects_names;
        int object_count;
        char** requires_names;
        int requires_count;
        char* entry_message;
        bool has_trap;
        TempTrap trap;
        bool has_enemy;
        TempEnemy enemy;
        bool win_condition;
    } TempRoom;

    // Variabile globale
    Game game_data;
    TempObject temp_object;
    TempRoom temp_room;
    TempTrap temp_trap;
    TempEnemy temp_enemy;
    
    // Arrays temporare pentru parsing
    TempObject* temp_objects;
    int temp_object_count;
    TempRoom* temp_rooms;
    int temp_room_count;
    char* temp_start_room_name;

    // Error tracking
    int parse_error_count = 0;
    bool parsing_failed = false;

    // Funcții helper
    void init_game();
    void add_temp_object(TempObject obj);
    void add_temp_room(TempRoom room);
    void link_references();
    Object* find_object(char* name);
    Room* find_room(char* name);
    void print_game_data();
    void reset_temp_object();
    void reset_temp_room();
    
    // Error handling and validation functions
    bool object_name_exists(char* name);
    bool room_name_exists(char* name);
    void report_error(const char* message);
    bool validate_game_data();

    int yylex(void);
    void yyerror(const char* str);
    extern FILE* yyin;
    extern int yylineno;

#line 228 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
#line 158 "yacc_source.y"

    char* str;
    int number;

#line 362 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_STRING = 3,                     /* STRING  */
  YYSYMBOL_IDENTIFIER = 4,                 /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 5,                     /* NUMBER  */
  YYSYMBOL_TRUE = 6,                       /* TRUE  */
  YYSYMBOL_FALSE = 7,                      /* FALSE  */
  YYSYMBOL_GAME = 8,                       /* GAME  */
  YYSYMBOL_START_ROOM = 9,                 /* START_ROOM  */
  YYSYMBOL_HEALTH = 10,                    /* HEALTH  */
  YYSYMBOL_ROOM = 11,                      /* ROOM  */
  YYSYMBOL_DESCRIPTION = 12,               /* DESCRIPTION  */
  YYSYMBOL_OBJECTS = 13,                   /* OBJECTS  */
  YYSYMBOL_CONNECTIONS = 14,               /* CONNECTIONS  */
  YYSYMBOL_TAKEABLE = 15,                  /* TAKEABLE  */
  YYSYMBOL_REQUIRES = 16,                  /* REQUIRES  */
  YYSYMBOL_CONTENTS = 17,                  /* CONTENTS  */
  YYSYMBOL_HIDDEN_ITEM = 18,               /* HIDDEN_ITEM  */
  YYSYMBOL_EXAMINE = 19,                   /* EXAMINE  */
  YYSYMBOL_CONSUME_KEY = 20,               /* CONSUME_KEY  */
  YYSYMBOL_TRAP = 21,                      /* TRAP  */
  YYSYMBOL_ENEMY = 22,                     /* ENEMY  */
  YYSYMBOL_DAMAGE = 23,                    /* DAMAGE  */
  YYSYMBOL_WEAKNESS = 24,                  /* WEAKNESS  */
  YYSYMBOL_DEFEAT_REWARD = 25,             /* DEFEAT_REWARD  */
  YYSYMBOL_WIN_CONDITION = 26,             /* WIN_CONDITION  */
  YYSYMBOL_NAME = 27,                      /* NAME  */
  YYSYMBOL_MESSAGE = 28,                   /* MESSAGE  */
  YYSYMBOL_PROTECTION = 29,                /* PROTECTION  */
  YYSYMBOL_PROTECTION_MESSAGE = 30,        /* PROTECTION_MESSAGE  */
  YYSYMBOL_ENTRY_MESSAGE = 31,             /* ENTRY_MESSAGE  */
  YYSYMBOL_EQUALS = 32,                    /* EQUALS  */
  YYSYMBOL_OPEN_BRACE = 33,                /* OPEN_BRACE  */
  YYSYMBOL_CLOSED_BRACE = 34,              /* CLOSED_BRACE  */
  YYSYMBOL_LIST_START = 35,                /* LIST_START  */
  YYSYMBOL_LIST_END = 36,                  /* LIST_END  */
  YYSYMBOL_COMMA = 37,                     /* COMMA  */
  YYSYMBOL_COLON = 38,                     /* COLON  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_program = 40,                   /* program  */
  YYSYMBOL_41_1 = 41,                      /* $@1  */
  YYSYMBOL_configuration = 42,             /* configuration  */
  YYSYMBOL_start_room = 43,                /* start_room  */
  YYSYMBOL_health = 44,                    /* health  */
  YYSYMBOL_objects = 45,                   /* objects  */
  YYSYMBOL_list_of_objects = 46,           /* list_of_objects  */
  YYSYMBOL_object_config = 47,             /* object_config  */
  YYSYMBOL_48_2 = 48,                      /* $@2  */
  YYSYMBOL_object_props = 49,              /* object_props  */
  YYSYMBOL_object_prop = 50,               /* object_prop  */
  YYSYMBOL_item_list = 51,                 /* item_list  */
  YYSYMBOL_rooms = 52,                     /* rooms  */
  YYSYMBOL_room_definition = 53,           /* room_definition  */
  YYSYMBOL_54_3 = 54,                      /* $@3  */
  YYSYMBOL_room_content_list = 55,         /* room_content_list  */
  YYSYMBOL_room_content = 56,              /* room_content  */
  YYSYMBOL_object_list = 57,               /* object_list  */
  YYSYMBOL_req_list = 58,                  /* req_list  */
  YYSYMBOL_connection_list = 59,           /* connection_list  */
  YYSYMBOL_connection = 60,                /* connection  */
  YYSYMBOL_trap_definition = 61,           /* trap_definition  */
  YYSYMBOL_trap_props = 62,                /* trap_props  */
  YYSYMBOL_trap_prop = 63,                 /* trap_prop  */
  YYSYMBOL_enemy_definition = 64,          /* enemy_definition  */
  YYSYMBOL_enemy_props = 65,               /* enemy_props  */
  YYSYMBOL_enemy_prop = 66                 /* enemy_prop  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   141

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   177,   177,   177,   195,   198,   207,   216,   219,   220,
     223,   223,   241,   242,   243,   246,   247,   248,   255,   256,
     263,   270,   271,   274,   283,   292,   295,   296,   297,   300,
     300,   318,   319,   320,   323,   330,   331,   332,   341,   342,
     349,   350,   351,   354,   363,   372,   375,   384,   395,   396,
     397,   400,   417,   423,   424,   425,   428,   435,   442,   449,
     458,   464,   465,   466,   469,   476,   483,   490
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "STRING", "IDENTIFIER",
  "NUMBER", "TRUE", "FALSE", "GAME", "START_ROOM", "HEALTH", "ROOM",
  "DESCRIPTION", "OBJECTS", "CONNECTIONS", "TAKEABLE", "REQUIRES",
  "CONTENTS", "HIDDEN_ITEM", "EXAMINE", "CONSUME_KEY", "TRAP", "ENEMY",
  "DAMAGE", "WEAKNESS", "DEFEAT_REWARD", "WIN_CONDITION", "NAME",
  "MESSAGE", "PROTECTION", "PROTECTION_MESSAGE", "ENTRY_MESSAGE", "EQUALS",
  "OPEN_BRACE", "CLOSED_BRACE", "LIST_START", "LIST_END", "COMMA", "COLON",
  "$accept", "program", "$@1", "configuration", "start_room", "health",
  "objects", "list_of_objects", "object_config", "$@2", "object_props",
  "object_prop", "item_list", "rooms", "room_definition", "$@3",
  "room_content_list", "room_content", "object_list", "req_list",
  "connection_list", "connection", "trap_definition", "trap_props",
  "trap_prop", "enemy_definition", "enemy_props", "enemy_prop", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-29)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       0,     1,    19,    -6,   -29,   -29,    20,    21,    -2,    52,
      64,   -29,    42,    60,   -29,    70,    43,    66,   -29,    74,
      76,    66,   -29,    44,   -28,   -29,    47,   -29,    48,   -29,
      74,   -29,   -29,   -29,    12,    40,    51,    53,    54,    55,
      56,    57,    59,    61,   -11,   -29,   -29,   -29,    62,    63,
      65,    67,    68,    69,    29,   -29,    81,    71,    72,    -4,
       7,    41,    82,    89,   -29,   -29,    10,    92,    73,    94,
      99,    15,   -29,   -29,   -29,   100,   101,   -29,   105,    78,
      79,    80,    83,   -16,   -29,    84,    85,    86,    87,    27,
     -29,   -29,   -29,   -29,   -29,   -29,   109,   -29,   -29,   -29,
     -29,   -29,     3,    88,     5,   -29,   -29,    33,    98,   111,
     116,   118,   -29,   -29,   117,   119,   120,   122,   -29,   -29,
     -29,    35,   -29,   123,   125,   -29,   101,   -29,   126,   -29,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   127,   -29,
     -29,   -29,   -29,   -29
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     2,     0,     0,     0,     0,
       0,     3,     0,     0,     5,     0,     0,    28,     6,     0,
       0,     4,    27,     0,     0,     9,     0,    26,     0,     7,
       0,    29,    10,     8,    33,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    32,    40,    41,     0,     0,
       0,     0,     0,     0,     0,    13,     0,     0,     0,     0,
      55,    63,     0,     0,    30,    31,     0,     0,     0,     0,
       0,     0,    11,    12,    34,    45,    50,    37,     0,     0,
       0,     0,     0,     0,    54,     0,     0,     0,     0,     0,
      62,    42,    39,    15,    16,    17,    25,    19,    20,    21,
      22,    44,     0,     0,     0,    49,    47,     0,     0,     0,
       0,     0,    52,    53,     0,     0,     0,     0,    60,    61,
      24,     0,    35,     0,     0,    36,     0,    38,     0,    56,
      57,    58,    59,    65,    66,    67,    64,    18,     0,    43,
      51,    48,    46,    23
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   102,   -29,
     -29,    75,   -29,   -29,   112,   -29,   -29,    90,   -29,   -29,
     -29,     9,   -29,   -29,    58,   -29,   -29,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     6,     8,     9,    13,    17,    24,    25,    35,
      54,    55,   121,    21,    22,    34,    44,    45,   102,   107,
     104,   105,    46,    83,    84,    47,    89,    90
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      77,    36,    37,    38,     3,    39,    29,    79,     1,    30,
      40,    41,    80,    81,    82,    42,    93,    94,   112,     4,
      43,    99,   100,    64,    36,    37,    38,     5,    39,     7,
      79,    78,    11,    40,    41,    80,    81,    82,    42,   122,
     123,   125,   126,    43,    48,    49,    50,    51,    52,    53,
      85,    86,    87,    10,    88,    48,    49,    50,    51,    52,
      53,   118,    12,    72,    85,    86,    87,    14,    88,   127,
     128,   137,   138,    16,    15,    18,    19,    20,    23,    26,
      31,    32,    28,    56,    74,    57,    58,    59,    91,    60,
      61,    62,    92,    63,    66,    67,    95,    68,    97,    69,
      70,    71,    98,   129,   101,   103,    75,    76,    96,   106,
     108,   109,   110,   120,   130,   111,   114,   115,   116,   117,
     131,   132,   133,   134,   135,   136,   124,   139,   140,    73,
     142,   143,    33,    27,    65,   141,     0,     0,   119,     0,
       0,   113
};

static const yytype_int8 yycheck[] =
{
       4,    12,    13,    14,     3,    16,    34,    23,     8,    37,
      21,    22,    28,    29,    30,    26,     6,     7,    34,     0,
      31,     6,     7,    34,    12,    13,    14,    33,    16,     9,
      23,    35,    34,    21,    22,    28,    29,    30,    26,    36,
      37,    36,    37,    31,    15,    16,    17,    18,    19,    20,
      23,    24,    25,    32,    27,    15,    16,    17,    18,    19,
      20,    34,    10,    34,    23,    24,    25,     3,    27,    36,
      37,    36,    37,    13,    32,     5,    33,    11,     4,     3,
      33,    33,    38,    32,     3,    32,    32,    32,     6,    33,
      33,    32,     3,    32,    32,    32,     4,    32,     4,    32,
      32,    32,     3,     5,     4,     4,    35,    35,    35,     4,
      32,    32,    32,     4,     3,    32,    32,    32,    32,    32,
       4,     3,     5,     4,     4,     3,    38,     4,     3,    54,
       4,     4,    30,    21,    44,   126,    -1,    -1,    89,    -1,
      -1,    83
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    40,     3,     0,    33,    41,     9,    42,    43,
      32,    34,    10,    44,     3,    32,    13,    45,     5,    33,
      11,    52,    53,     4,    46,    47,     3,    53,    38,    34,
      37,    33,    33,    47,    54,    48,    12,    13,    14,    16,
      21,    22,    26,    31,    55,    56,    61,    64,    15,    16,
      17,    18,    19,    20,    49,    50,    32,    32,    32,    32,
      33,    33,    32,    32,    34,    56,    32,    32,    32,    32,
      32,    32,    34,    50,     3,    35,    35,     4,    35,    23,
      28,    29,    30,    62,    63,    23,    24,    25,    27,    65,
      66,     6,     3,     6,     7,     4,    35,     4,     3,     6,
       7,     4,    57,     4,    59,    60,     4,    58,    32,    32,
      32,    32,    34,    63,    32,    32,    32,    32,    34,    66,
       4,    51,    36,    37,    38,    36,    37,    36,    37,     5,
       3,     4,     3,     5,     4,     4,     3,    36,    37,     4,
       3,    60,     4,     4
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    41,    40,    42,    43,    44,    45,    46,    46,
      48,    47,    49,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    51,    51,    51,    52,    52,    52,    54,
      53,    55,    55,    55,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    57,    57,    57,    58,    58,    59,    59,
      59,    60,    61,    62,    62,    62,    63,    63,    63,    63,
      64,    65,    65,    65,    66,    66,    66,    66
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     6,     4,     3,     3,     4,     3,     1,
       0,     6,     2,     1,     0,     3,     3,     3,     5,     3,
       3,     3,     3,     3,     1,     0,     2,     1,     0,     0,
       6,     2,     1,     0,     3,     5,     5,     3,     5,     3,
       1,     1,     3,     3,     1,     0,     3,     1,     3,     1,
       0,     3,     4,     2,     1,     0,     3,     3,     3,     3,
       4,     2,     1,     0,     3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 177 "yacc_source.y"
                                { 
            init_game(); 
            if ((yyvsp[-1].str) == NULL || strlen((yyvsp[-1].str)) == 0) {
                report_error("Game name cannot be empty");
                YYERROR;
            }
            game_data.game_name = strdup((yyvsp[-1].str)); 
        }
#line 1507 "y.tab.c"
    break;

  case 3: /* program: GAME STRING OPEN_BRACE $@1 configuration CLOSED_BRACE  */
#line 184 "yacc_source.y"
                                     {
            if (!parsing_failed && validate_game_data()) {
                link_references();
                // Don't print game data here anymore
            } else {
                printf("Parsing failed due to validation errors.\n");
                YYERROR;
            }
        }
#line 1521 "y.tab.c"
    break;

  case 5: /* start_room: START_ROOM EQUALS STRING  */
#line 198 "yacc_source.y"
                                     { 
            if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                report_error("Start room name cannot be empty");
                YYERROR;
            }
            temp_start_room_name = strdup((yyvsp[0].str)); 
        }
#line 1533 "y.tab.c"
    break;

  case 6: /* health: HEALTH EQUALS NUMBER  */
#line 207 "yacc_source.y"
                             { 
            if ((yyvsp[0].number) <= 0) {
                report_error("Health must be a positive number");
                YYERROR;
            }
            game_data.health = (yyvsp[0].number); 
        }
#line 1545 "y.tab.c"
    break;

  case 10: /* $@2: %empty  */
#line 223 "yacc_source.y"
                                           {
                if ((yyvsp[-2].str) == NULL || strlen((yyvsp[-2].str)) == 0) {
                    report_error("Object name cannot be empty");
                    YYERROR;
                }
                if (object_name_exists((yyvsp[-2].str))) {
                    char error_msg[256];
                    snprintf(error_msg, sizeof(error_msg), "Object '%s' already exists", (yyvsp[-2].str));
                    report_error(error_msg);
                    YYERROR;
                }
                reset_temp_object();
                temp_object.name = strdup((yyvsp[-2].str));
            }
#line 1564 "y.tab.c"
    break;

  case 11: /* object_config: IDENTIFIER COLON OPEN_BRACE $@2 object_props CLOSED_BRACE  */
#line 236 "yacc_source.y"
                                        {
                add_temp_object(temp_object);
            }
#line 1572 "y.tab.c"
    break;

  case 15: /* object_prop: TAKEABLE EQUALS TRUE  */
#line 246 "yacc_source.y"
                                  { temp_object.takeable = true; }
#line 1578 "y.tab.c"
    break;

  case 16: /* object_prop: TAKEABLE EQUALS FALSE  */
#line 247 "yacc_source.y"
                                    { temp_object.takeable = false; }
#line 1584 "y.tab.c"
    break;

  case 17: /* object_prop: REQUIRES EQUALS IDENTIFIER  */
#line 248 "yacc_source.y"
                                         { 
                if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                    report_error("Required object name cannot be empty");
                    YYERROR;
                }
                temp_object.requires_name = strdup((yyvsp[0].str)); 
            }
#line 1596 "y.tab.c"
    break;

  case 19: /* object_prop: HIDDEN_ITEM EQUALS IDENTIFIER  */
#line 256 "yacc_source.y"
                                            { 
                if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                    report_error("Hidden item name cannot be empty");
                    YYERROR;
                }
                temp_object.hidden_item_name = strdup((yyvsp[0].str)); 
            }
#line 1608 "y.tab.c"
    break;

  case 20: /* object_prop: EXAMINE EQUALS STRING  */
#line 263 "yacc_source.y"
                                    { 
                if ((yyvsp[0].str) == NULL) {
                    report_error("Examine text cannot be null");
                    YYERROR;
                }
                temp_object.examine_text = strdup((yyvsp[0].str)); 
            }
#line 1620 "y.tab.c"
    break;

  case 21: /* object_prop: CONSUME_KEY EQUALS TRUE  */
#line 270 "yacc_source.y"
                                      { temp_object.consume_key = true; }
#line 1626 "y.tab.c"
    break;

  case 22: /* object_prop: CONSUME_KEY EQUALS FALSE  */
#line 271 "yacc_source.y"
                                       { temp_object.consume_key = false; }
#line 1632 "y.tab.c"
    break;

  case 23: /* item_list: item_list COMMA IDENTIFIER  */
#line 274 "yacc_source.y"
                                      {
            if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                report_error("Item name in contents list cannot be empty");
                YYERROR;
            }
            temp_object.contents_names = realloc(temp_object.contents_names, 
                (temp_object.content_count + 1) * sizeof(char*));
            temp_object.contents_names[temp_object.content_count++] = strdup((yyvsp[0].str));
        }
#line 1646 "y.tab.c"
    break;

  case 24: /* item_list: IDENTIFIER  */
#line 283 "yacc_source.y"
                     {
            if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                report_error("Item name in contents list cannot be empty");
                YYERROR;
            }
            temp_object.contents_names = malloc(sizeof(char*));
            temp_object.contents_names[0] = strdup((yyvsp[0].str));
            temp_object.content_count = 1;
        }
#line 1660 "y.tab.c"
    break;

  case 29: /* $@3: %empty  */
#line 300 "yacc_source.y"
                                        {
                if ((yyvsp[-1].str) == NULL || strlen((yyvsp[-1].str)) == 0) {
                    report_error("Room name cannot be empty");
                    YYERROR;
                }
                if (room_name_exists((yyvsp[-1].str))) {
                    char error_msg[256];
                    snprintf(error_msg, sizeof(error_msg), "Room '%s' already exists", (yyvsp[-1].str));
                    report_error(error_msg);
                    YYERROR;
                }
                reset_temp_room();
                temp_room.name = strdup((yyvsp[-1].str));
            }
#line 1679 "y.tab.c"
    break;

  case 30: /* room_definition: ROOM STRING OPEN_BRACE $@3 room_content_list CLOSED_BRACE  */
#line 313 "yacc_source.y"
                                             {
                add_temp_room(temp_room);
            }
#line 1687 "y.tab.c"
    break;

  case 34: /* room_content: DESCRIPTION EQUALS STRING  */
#line 323 "yacc_source.y"
                                        { 
                if ((yyvsp[0].str) == NULL) {
                    report_error("Room description cannot be null");
                    YYERROR;
                }
                temp_room.description = strdup((yyvsp[0].str)); 
            }
#line 1699 "y.tab.c"
    break;

  case 37: /* room_content: REQUIRES EQUALS IDENTIFIER  */
#line 332 "yacc_source.y"
                                         { 
                if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                    report_error("Required object name cannot be empty");
                    YYERROR;
                }
                temp_room.requires_names = malloc(sizeof(char*));
                temp_room.requires_names[0] = strdup((yyvsp[0].str));
                temp_room.requires_count = 1;
            }
#line 1713 "y.tab.c"
    break;

  case 39: /* room_content: ENTRY_MESSAGE EQUALS STRING  */
#line 342 "yacc_source.y"
                                          { 
                if ((yyvsp[0].str) == NULL) {
                    report_error("Entry message cannot be null");
                    YYERROR;
                }
                temp_room.entry_message = strdup((yyvsp[0].str)); 
            }
#line 1725 "y.tab.c"
    break;

  case 42: /* room_content: WIN_CONDITION EQUALS TRUE  */
#line 351 "yacc_source.y"
                                        { temp_room.win_condition = true; }
#line 1731 "y.tab.c"
    break;

  case 43: /* object_list: object_list COMMA IDENTIFIER  */
#line 354 "yacc_source.y"
                                          {
            if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                report_error("Object name in room cannot be empty");
                YYERROR;
            }
            temp_room.objects_names = realloc(temp_room.objects_names, 
                (temp_room.object_count + 1) * sizeof(char*));
            temp_room.objects_names[temp_room.object_count++] = strdup((yyvsp[0].str));
        }
#line 1745 "y.tab.c"
    break;

  case 44: /* object_list: IDENTIFIER  */
#line 363 "yacc_source.y"
                     {
            if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                report_error("Object name in room cannot be empty");
                YYERROR;
            }
            temp_room.objects_names = malloc(sizeof(char*));
            temp_room.objects_names[0] = strdup((yyvsp[0].str));
            temp_room.object_count = 1;
        }
#line 1759 "y.tab.c"
    break;

  case 46: /* req_list: req_list COMMA IDENTIFIER  */
#line 375 "yacc_source.y"
                                    {
            if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                report_error("Required object name cannot be empty");
                YYERROR;
            }
            temp_room.requires_names = realloc(temp_room.requires_names, 
                (temp_room.requires_count + 1) * sizeof(char*));
            temp_room.requires_names[temp_room.requires_count++] = strdup((yyvsp[0].str));
        }
#line 1773 "y.tab.c"
    break;

  case 47: /* req_list: IDENTIFIER  */
#line 384 "yacc_source.y"
                     {
            if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                report_error("Required object name cannot be empty");
                YYERROR;
            }
            temp_room.requires_names = malloc(sizeof(char*));
            temp_room.requires_names[0] = strdup((yyvsp[0].str));
            temp_room.requires_count = 1;
        }
#line 1787 "y.tab.c"
    break;

  case 51: /* connection: IDENTIFIER COLON STRING  */
#line 400 "yacc_source.y"
                                    {
            if ((yyvsp[-2].str) == NULL || strlen((yyvsp[-2].str)) == 0) {
                report_error("Connection direction cannot be empty");
                YYERROR;
            }
            if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                report_error("Connected room name cannot be empty");
                YYERROR;
            }
            temp_room.connections = realloc(temp_room.connections, 
                (temp_room.connection_count + 1) * sizeof(TempConnection));
            temp_room.connections[temp_room.connection_count].direction = strdup((yyvsp[-2].str));
            temp_room.connections[temp_room.connection_count].room_name = strdup((yyvsp[0].str));
            temp_room.connection_count++;
        }
#line 1807 "y.tab.c"
    break;

  case 52: /* trap_definition: TRAP OPEN_BRACE trap_props CLOSED_BRACE  */
#line 417 "yacc_source.y"
                                                         {
                temp_room.has_trap = true;
                temp_room.trap = temp_trap;
            }
#line 1816 "y.tab.c"
    break;

  case 56: /* trap_prop: DAMAGE EQUALS NUMBER  */
#line 428 "yacc_source.y"
                                { 
                if ((yyvsp[0].number) < 0) {
                    report_error("Trap damage cannot be negative");
                    YYERROR;
                }
                temp_trap.damage = (yyvsp[0].number); 
            }
#line 1828 "y.tab.c"
    break;

  case 57: /* trap_prop: MESSAGE EQUALS STRING  */
#line 435 "yacc_source.y"
                                    { 
                if ((yyvsp[0].str) == NULL) {
                    report_error("Trap message cannot be null");
                    YYERROR;
                }
                temp_trap.message = strdup((yyvsp[0].str)); 
            }
#line 1840 "y.tab.c"
    break;

  case 58: /* trap_prop: PROTECTION EQUALS IDENTIFIER  */
#line 442 "yacc_source.y"
                                           { 
                if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                    report_error("Protection object name cannot be empty");
                    YYERROR;
                }
                temp_trap.protection_name = strdup((yyvsp[0].str)); 
            }
#line 1852 "y.tab.c"
    break;

  case 59: /* trap_prop: PROTECTION_MESSAGE EQUALS STRING  */
#line 449 "yacc_source.y"
                                               { 
                if ((yyvsp[0].str) == NULL) {
                    report_error("Protection message cannot be null");
                    YYERROR;
                }
                temp_trap.protection_message = strdup((yyvsp[0].str)); 
            }
#line 1864 "y.tab.c"
    break;

  case 60: /* enemy_definition: ENEMY OPEN_BRACE enemy_props CLOSED_BRACE  */
#line 458 "yacc_source.y"
                                                            {
                temp_room.has_enemy = true;
                temp_room.enemy = temp_enemy;
            }
#line 1873 "y.tab.c"
    break;

  case 64: /* enemy_prop: NAME EQUALS STRING  */
#line 469 "yacc_source.y"
                               { 
                if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                    report_error("Enemy name cannot be empty");
                    YYERROR;
                }
                temp_enemy.name = strdup((yyvsp[0].str)); 
            }
#line 1885 "y.tab.c"
    break;

  case 65: /* enemy_prop: DAMAGE EQUALS NUMBER  */
#line 476 "yacc_source.y"
                                   { 
                if ((yyvsp[0].number) < 0) {
                    report_error("Enemy damage cannot be negative");
                    YYERROR;
                }
                temp_enemy.damage = (yyvsp[0].number); 
            }
#line 1897 "y.tab.c"
    break;

  case 66: /* enemy_prop: WEAKNESS EQUALS IDENTIFIER  */
#line 483 "yacc_source.y"
                                         { 
                if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                    report_error("Enemy weakness object name cannot be empty");
                    YYERROR;
                }
                temp_enemy.weakness_name = strdup((yyvsp[0].str)); 
            }
#line 1909 "y.tab.c"
    break;

  case 67: /* enemy_prop: DEFEAT_REWARD EQUALS IDENTIFIER  */
#line 490 "yacc_source.y"
                                              { 
                if ((yyvsp[0].str) == NULL || strlen((yyvsp[0].str)) == 0) {
                    report_error("Enemy defeat reward object name cannot be empty");
                    YYERROR;
                }
                temp_enemy.defeat_reward_name = strdup((yyvsp[0].str)); 
            }
#line 1921 "y.tab.c"
    break;


#line 1925 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 499 "yacc_source.y"


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
    temp_objects = NULL;
    temp_rooms = NULL;
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

void add_temp_object(TempObject obj) {
    temp_objects = realloc(temp_objects, (temp_object_count + 1) * sizeof(TempObject));
    if (!temp_objects) {
        report_error("Memory allocation failed for objects");
        return;
    }
    temp_objects[temp_object_count++] = obj;
}

void add_temp_room(TempRoom room) {
    temp_rooms = realloc(temp_rooms, (temp_room_count + 1) * sizeof(TempRoom));
    if (!temp_rooms) {
        report_error("Memory allocation failed for rooms");
        return;
    }
    temp_rooms[temp_room_count++] = room;
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
    // Creează array-urile finale
    game_data.objects = malloc(temp_object_count * sizeof(Object));
    if (!game_data.objects && temp_object_count > 0) {
        report_error("Memory allocation failed for final objects array");
        return;
    }
    game_data.object_count = temp_object_count;
    
    game_data.rooms = malloc(temp_room_count * sizeof(Room));
    if (!game_data.rooms && temp_room_count > 0) {
        report_error("Memory allocation failed for final rooms array");
        return;
    }
    game_data.room_count = temp_room_count;
    
    // Copiază obiectele (fără referințe încă)
    for (int i = 0; i < temp_object_count; i++) {
        game_data.objects[i].name = temp_objects[i].name;
        game_data.objects[i].takeable = temp_objects[i].takeable;
        game_data.objects[i].examine_text = temp_objects[i].examine_text;
        game_data.objects[i].consume_key = temp_objects[i].consume_key;
        game_data.objects[i].content_count = 0;  // Va fi setat mai jos
        game_data.objects[i].contents = NULL;
        game_data.objects[i].requires = NULL;
        game_data.objects[i].hidden_item = NULL;
    }
    
    // Copiază camerele (fără referințe încă)
    for (int i = 0; i < temp_room_count; i++) {
        game_data.rooms[i].name = temp_rooms[i].name;
        game_data.rooms[i].description = temp_rooms[i].description;
        game_data.rooms[i].entry_message = temp_rooms[i].entry_message;
        game_data.rooms[i].win_condition = temp_rooms[i].win_condition;
        game_data.rooms[i].has_trap = temp_rooms[i].has_trap;
        game_data.rooms[i].has_enemy = temp_rooms[i].has_enemy;
        game_data.rooms[i].connection_count = 0;
        game_data.rooms[i].connections = NULL;
        game_data.rooms[i].object_count = 0;
        game_data.rooms[i].objects = NULL;
        game_data.rooms[i].requires_count = 0;
        game_data.rooms[i].requires = NULL;
    }
    
    // Acum leagă referințele pentru obiecte
    for (int i = 0; i < temp_object_count; i++) {
        // Link requires
        game_data.objects[i].requires = find_object(temp_objects[i].requires_name);
        
        // Link hidden_item
        game_data.objects[i].hidden_item = find_object(temp_objects[i].hidden_item_name);
        
        // Link contents
        if (temp_objects[i].content_count > 0) {
            game_data.objects[i].contents = malloc(temp_objects[i].content_count * sizeof(Object*));
            if (!game_data.objects[i].contents) {
                report_error("Memory allocation failed for object contents");
                continue;
            }
            game_data.objects[i].content_count = temp_objects[i].content_count;
            for (int j = 0; j < temp_objects[i].content_count; j++) {
                game_data.objects[i].contents[j] = find_object(temp_objects[i].contents_names[j]);
            }
        }
    }
    
    // Leagă referințele pentru camere
    for (int i = 0; i < temp_room_count; i++) {
        // Link objects
        if (temp_rooms[i].object_count > 0) {
            game_data.rooms[i].objects = malloc(temp_rooms[i].object_count * sizeof(Object*));
            if (!game_data.rooms[i].objects) {
                report_error("Memory allocation failed for room objects");
                continue;
            }
            game_data.rooms[i].object_count = temp_rooms[i].object_count;
            for (int j = 0; j < temp_rooms[i].object_count; j++) {
                game_data.rooms[i].objects[j] = find_object(temp_rooms[i].objects_names[j]);
            }
        }
        
        // Link requires
        if (temp_rooms[i].requires_count > 0) {
            game_data.rooms[i].requires = malloc(temp_rooms[i].requires_count * sizeof(Object*));
            if (!game_data.rooms[i].requires) {
                report_error("Memory allocation failed for room requirements");
                continue;
            }
            game_data.rooms[i].requires_count = temp_rooms[i].requires_count;
            for (int j = 0; j < temp_rooms[i].requires_count; j++) {
                game_data.rooms[i].requires[j] = find_object(temp_rooms[i].requires_names[j]);
            }
        }
        
        // Link connections
        if (temp_rooms[i].connection_count > 0) {
            game_data.rooms[i].connections = malloc(temp_rooms[i].connection_count * sizeof(Connection));
            if (!game_data.rooms[i].connections) {
                report_error("Memory allocation failed for room connections");
                continue;
            }
            game_data.rooms[i].connection_count = temp_rooms[i].connection_count;
            for (int j = 0; j < temp_rooms[i].connection_count; j++) {
                game_data.rooms[i].connections[j].direction = temp_rooms[i].connections[j].direction;
                game_data.rooms[i].connections[j].room = find_room(temp_rooms[i].connections[j].room_name);
            }
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
