/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 12 "commands.y"

#include <bibtool/bibtool.h>
#include <bibtool/sbuffer.h>
#include "term.h"
#define YYSTYPE Term
#include "commands.h"

  static Term t_true = TermNULL;
  static Term t_false = TermNULL;

  static FILE* in_file;
  static Term result = TermNULL;
  static int linenum = 1;
  static char * error_msg = NULL;

  static int save_term();



/* Line 268 of yacc.c  */
#line 91 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     B_ON = 258,
     B_OFF = 259,
     FIELD = 260,
     STRING = 261,
     BLOCK = 262,
     NUMBER = 263,
     NOT = 264,
     AND = 265,
     OR = 266,
     LIKE = 267,
     ILIKE = 268,
     UMINUS = 269,
     PLUS = 270,
     MINUS = 271,
     TIMES = 272,
     DIVIDE = 273,
     EQ = 274,
     NE = 275,
     LT = 276,
     LE = 277,
     GT = 278,
     GE = 279,
     FCT_LOWERCASE = 280,
     FCT_UPPERCASE = 281,
     FCT_SUBSTRING = 282,
     FCT_TRIM = 283,
     PAIR = 284,
     ADD_FIELD = 285,
     APPLY_ALIAS = 286,
     APPLY_MODIFY = 287,
     APPLY_INCLUDE = 288,
     BIBTEX_ENV_NAME = 289,
     BIBTEX_SEARCH_PATH = 290,
     CHECK_DOUBLE = 291,
     CHECK_DOUBLE_DELETE = 292,
     CHECK_RULE = 293,
     CHECK_CASE_SENSITIVE = 294,
     CLEAR_IGNORED_WORDS = 295,
     COUNT_ALL = 296,
     COUNT_USED = 297,
     CROSSREF_LIMIT = 298,
     DEFAULT_KEY = 299,
     DELETE_FIELD = 300,
     DIR_FILE_SEPARATOR = 301,
     DUMP_SYMBOLS = 302,
     ENV_SEPARATOR = 303,
     EXTRACT_FILE = 304,
     EXTRACT_REGEX = 305,
     EXPAND_MACROS = 306,
     EXPAND_CROSSREF = 307,
     FMT_INTER_NAME = 308,
     FMT_NAME_PRE = 309,
     FMT_NAME_NAME = 310,
     FMT_NAME_TITLE = 311,
     FMT_TITLE_TITLE = 312,
     FMT_ET_AL = 313,
     FMT_WORD_SEPARATOR = 314,
     FIELD_TYPE = 315,
     INPUT = 316,
     IGNORED_WORD = 317,
     KEY_GENERATION = 318,
     KEY_BASE = 319,
     KEY_FORMAT = 320,
     KEY_MAKE_ALIAS = 321,
     KEY_NUMBER_SEPARATOR = 322,
     KEY_EXPAND_MACROS = 323,
     MACRO_FILE = 324,
     NEW_ENTRY_TYPE = 325,
     NEW_FIELD_TYPE = 326,
     NEW_FORMAT_TYPE = 327,
     OUTPUT_FILE = 328,
     PASS_COMMENTS = 329,
     PRESERVE_KEY_CASE = 330,
     PRESERVE_KEYS = 331,
     PRINT = 332,
     PRINT_ALIGN_STRING = 333,
     PRINT_ALIGN_COMMENT = 334,
     PRINT_ALIGN_PREAMBLE = 335,
     PRINT_ALIGN_KEY = 336,
     PRINT_ALIGN = 337,
     PRINT_ALL_STRINGS = 338,
     PRINT_ENTRY_TYPES = 339,
     PRINT_EQUAL_RIGHT = 340,
     PRINT_BRACES = 341,
     PRINT_COMMA_AT_END = 342,
     PRINT_DELETED_PREFIX = 343,
     PRINT_DELETED_ENTRIES = 344,
     PRINT_INDENT = 345,
     PRINT_LINE_LENGTH = 346,
     PRINT_NEWLINE = 347,
     PRINT_PARENTHESES = 348,
     PRINT_TERMINAL_COMMA = 349,
     PRINT_USE_TAB = 350,
     PRINT_WIDE_EQUAL = 351,
     QUIET = 352,
     REGEXP_SYNTAX = 353,
     RENAME_FIELD = 354,
     RESOURCE = 355,
     RESOURCE_SEARCH_PATH = 356,
     REWRITE_RULE = 357,
     REWRITE_CASE_SENSITIVE = 358,
     REWRITE_LIMIT = 359,
     SELECT = 360,
     SELECT_BY_STRING = 361,
     SELECT_BY_NON_STRING = 362,
     SELECT_BY_STRING_IGNORED = 363,
     SELECT_CASE_SENSITIVE = 364,
     SELECT_FIELDS = 365,
     SELECT_NON = 366,
     SELECT_CROSSREFS = 367,
     SORT = 368,
     SORT_CASED = 369,
     SORT_MACROS = 370,
     SORT_REVERSE = 371,
     SORT_ORDER = 372,
     SORT_FORMAT = 373,
     SUPPRESS_INITIAL_NEWLINE = 374,
     SYMBOL_TYPE = 375,
     TEX_DEFINE = 376,
     VERBOSE = 377,
     VERSION = 378
   };
#endif
/* Tokens.  */
#define B_ON 258
#define B_OFF 259
#define FIELD 260
#define STRING 261
#define BLOCK 262
#define NUMBER 263
#define NOT 264
#define AND 265
#define OR 266
#define LIKE 267
#define ILIKE 268
#define UMINUS 269
#define PLUS 270
#define MINUS 271
#define TIMES 272
#define DIVIDE 273
#define EQ 274
#define NE 275
#define LT 276
#define LE 277
#define GT 278
#define GE 279
#define FCT_LOWERCASE 280
#define FCT_UPPERCASE 281
#define FCT_SUBSTRING 282
#define FCT_TRIM 283
#define PAIR 284
#define ADD_FIELD 285
#define APPLY_ALIAS 286
#define APPLY_MODIFY 287
#define APPLY_INCLUDE 288
#define BIBTEX_ENV_NAME 289
#define BIBTEX_SEARCH_PATH 290
#define CHECK_DOUBLE 291
#define CHECK_DOUBLE_DELETE 292
#define CHECK_RULE 293
#define CHECK_CASE_SENSITIVE 294
#define CLEAR_IGNORED_WORDS 295
#define COUNT_ALL 296
#define COUNT_USED 297
#define CROSSREF_LIMIT 298
#define DEFAULT_KEY 299
#define DELETE_FIELD 300
#define DIR_FILE_SEPARATOR 301
#define DUMP_SYMBOLS 302
#define ENV_SEPARATOR 303
#define EXTRACT_FILE 304
#define EXTRACT_REGEX 305
#define EXPAND_MACROS 306
#define EXPAND_CROSSREF 307
#define FMT_INTER_NAME 308
#define FMT_NAME_PRE 309
#define FMT_NAME_NAME 310
#define FMT_NAME_TITLE 311
#define FMT_TITLE_TITLE 312
#define FMT_ET_AL 313
#define FMT_WORD_SEPARATOR 314
#define FIELD_TYPE 315
#define INPUT 316
#define IGNORED_WORD 317
#define KEY_GENERATION 318
#define KEY_BASE 319
#define KEY_FORMAT 320
#define KEY_MAKE_ALIAS 321
#define KEY_NUMBER_SEPARATOR 322
#define KEY_EXPAND_MACROS 323
#define MACRO_FILE 324
#define NEW_ENTRY_TYPE 325
#define NEW_FIELD_TYPE 326
#define NEW_FORMAT_TYPE 327
#define OUTPUT_FILE 328
#define PASS_COMMENTS 329
#define PRESERVE_KEY_CASE 330
#define PRESERVE_KEYS 331
#define PRINT 332
#define PRINT_ALIGN_STRING 333
#define PRINT_ALIGN_COMMENT 334
#define PRINT_ALIGN_PREAMBLE 335
#define PRINT_ALIGN_KEY 336
#define PRINT_ALIGN 337
#define PRINT_ALL_STRINGS 338
#define PRINT_ENTRY_TYPES 339
#define PRINT_EQUAL_RIGHT 340
#define PRINT_BRACES 341
#define PRINT_COMMA_AT_END 342
#define PRINT_DELETED_PREFIX 343
#define PRINT_DELETED_ENTRIES 344
#define PRINT_INDENT 345
#define PRINT_LINE_LENGTH 346
#define PRINT_NEWLINE 347
#define PRINT_PARENTHESES 348
#define PRINT_TERMINAL_COMMA 349
#define PRINT_USE_TAB 350
#define PRINT_WIDE_EQUAL 351
#define QUIET 352
#define REGEXP_SYNTAX 353
#define RENAME_FIELD 354
#define RESOURCE 355
#define RESOURCE_SEARCH_PATH 356
#define REWRITE_RULE 357
#define REWRITE_CASE_SENSITIVE 358
#define REWRITE_LIMIT 359
#define SELECT 360
#define SELECT_BY_STRING 361
#define SELECT_BY_NON_STRING 362
#define SELECT_BY_STRING_IGNORED 363
#define SELECT_CASE_SENSITIVE 364
#define SELECT_FIELDS 365
#define SELECT_NON 366
#define SELECT_CROSSREFS 367
#define SORT 368
#define SORT_CASED 369
#define SORT_MACROS 370
#define SORT_REVERSE 371
#define SORT_ORDER 372
#define SORT_FORMAT 373
#define SUPPRESS_INITIAL_NEWLINE 374
#define SYMBOL_TYPE 375
#define TEX_DEFINE 376
#define VERBOSE 377
#define VERSION 378




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 379 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  75
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   190

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  135
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNRULES -- Number of states.  */
#define YYNSTATES  126

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   378

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   131,     2,     2,     2,     2,     2,     2,
     129,   130,    16,    14,   134,    15,     2,    17,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     133,   128,   132,     2,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     7,    11,    15,    19,    23,    27,    30,
      32,    34,    36,    38,    40,    42,    44,    46,    48,    50,
      52,    54,    56,    58,    60,    62,    64,    66,    68,    70,
      72,    74,    76,    78,    80,    82,    84,    86,    88,    90,
      92,    94,    96,    98,   100,   102,   104,   106,   108,   110,
     112,   114,   116,   118,   120,   122,   124,   126,   128,   130,
     132,   134,   136,   138,   140,   141,   143,   145,   147,   149,
     151,   153,   157,   161,   164,   168,   172,   174,   176,   178,
     181,   183,   186,   188,   191,   193,   195,   197,   199,   201,
     203,   205,   209,   212,   216,   221,   222,   224,   226
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     136,     0,    -1,   137,   140,   142,    -1,   138,   140,   141,
      -1,   139,   140,   143,    -1,    65,   140,   142,    -1,   104,
     140,   142,    -1,   109,   140,   142,    -1,   109,   144,    -1,
       1,    -1,    38,    -1,    39,    -1,    50,    -1,    52,    -1,
      88,    -1,    92,    -1,   112,    -1,   114,    -1,    35,    -1,
      36,    -1,    37,    -1,    40,    -1,    41,    -1,    43,    -1,
      45,    -1,    46,    -1,    51,    -1,    55,    -1,    56,    -1,
      67,    -1,    70,    -1,    72,    -1,    78,    -1,    79,    -1,
      80,    -1,    87,    -1,    89,    -1,    90,    -1,    91,    -1,
      93,    -1,    97,    -1,    98,    -1,    99,    -1,   100,    -1,
     101,    -1,   107,    -1,   113,    -1,   116,    -1,   117,    -1,
     118,    -1,   119,    -1,   120,    -1,   123,    -1,   126,    -1,
      47,    -1,    82,    -1,    83,    -1,    84,    -1,    85,    -1,
      86,    -1,    94,    -1,    95,    -1,    96,    -1,   108,    -1,
      -1,   128,    -1,     3,    -1,     4,    -1,     6,    -1,     7,
      -1,     8,    -1,   147,   145,   147,    -1,   129,   144,   130,
      -1,     9,   144,    -1,   144,    10,   144,    -1,   144,    11,
     144,    -1,    12,    -1,    13,    -1,   128,    -1,   131,   128,
      -1,   132,    -1,   132,   128,    -1,   133,    -1,   133,   128,
      -1,    14,    -1,    15,    -1,    16,    -1,    17,    -1,     5,
      -1,     6,    -1,     8,    -1,   147,   146,   147,    -1,    15,
     147,    -1,   129,   147,   130,    -1,     5,   129,   148,   130,
      -1,    -1,   149,    -1,   147,    -1,   149,   134,   147,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   152,   152,   154,   156,   158,   161,   163,   164,   165,
     169,   170,   171,   172,   173,   174,   175,   176,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   227,   228,   230,   232,   235,   236,
     238,   241,   246,   248,   250,   252,   256,   258,   260,   262,
     264,   266,   268,   270,   274,   276,   278,   280,   283,   284,
     285,   286,   291,   293,   295,   311,   312,   314,   316
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "B_ON", "B_OFF", "FIELD", "STRING",
  "BLOCK", "NUMBER", "NOT", "AND", "OR", "LIKE", "ILIKE", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "PLUS", "MINUS", "TIMES", "DIVIDE", "EQ", "NE",
  "LT", "LE", "GT", "GE", "FCT_LOWERCASE", "FCT_UPPERCASE",
  "FCT_SUBSTRING", "FCT_TRIM", "PAIR", "ADD_FIELD", "APPLY_ALIAS",
  "APPLY_MODIFY", "APPLY_INCLUDE", "BIBTEX_ENV_NAME", "BIBTEX_SEARCH_PATH",
  "CHECK_DOUBLE", "CHECK_DOUBLE_DELETE", "CHECK_RULE",
  "CHECK_CASE_SENSITIVE", "CLEAR_IGNORED_WORDS", "COUNT_ALL", "COUNT_USED",
  "CROSSREF_LIMIT", "DEFAULT_KEY", "DELETE_FIELD", "DIR_FILE_SEPARATOR",
  "DUMP_SYMBOLS", "ENV_SEPARATOR", "EXTRACT_FILE", "EXTRACT_REGEX",
  "EXPAND_MACROS", "EXPAND_CROSSREF", "FMT_INTER_NAME", "FMT_NAME_PRE",
  "FMT_NAME_NAME", "FMT_NAME_TITLE", "FMT_TITLE_TITLE", "FMT_ET_AL",
  "FMT_WORD_SEPARATOR", "FIELD_TYPE", "INPUT", "IGNORED_WORD",
  "KEY_GENERATION", "KEY_BASE", "KEY_FORMAT", "KEY_MAKE_ALIAS",
  "KEY_NUMBER_SEPARATOR", "KEY_EXPAND_MACROS", "MACRO_FILE",
  "NEW_ENTRY_TYPE", "NEW_FIELD_TYPE", "NEW_FORMAT_TYPE", "OUTPUT_FILE",
  "PASS_COMMENTS", "PRESERVE_KEY_CASE", "PRESERVE_KEYS", "PRINT",
  "PRINT_ALIGN_STRING", "PRINT_ALIGN_COMMENT", "PRINT_ALIGN_PREAMBLE",
  "PRINT_ALIGN_KEY", "PRINT_ALIGN", "PRINT_ALL_STRINGS",
  "PRINT_ENTRY_TYPES", "PRINT_EQUAL_RIGHT", "PRINT_BRACES",
  "PRINT_COMMA_AT_END", "PRINT_DELETED_PREFIX", "PRINT_DELETED_ENTRIES",
  "PRINT_INDENT", "PRINT_LINE_LENGTH", "PRINT_NEWLINE",
  "PRINT_PARENTHESES", "PRINT_TERMINAL_COMMA", "PRINT_USE_TAB",
  "PRINT_WIDE_EQUAL", "QUIET", "REGEXP_SYNTAX", "RENAME_FIELD", "RESOURCE",
  "RESOURCE_SEARCH_PATH", "REWRITE_RULE", "REWRITE_CASE_SENSITIVE",
  "REWRITE_LIMIT", "SELECT", "SELECT_BY_STRING", "SELECT_BY_NON_STRING",
  "SELECT_BY_STRING_IGNORED", "SELECT_CASE_SENSITIVE", "SELECT_FIELDS",
  "SELECT_NON", "SELECT_CROSSREFS", "SORT", "SORT_CASED", "SORT_MACROS",
  "SORT_REVERSE", "SORT_ORDER", "SORT_FORMAT", "SUPPRESS_INITIAL_NEWLINE",
  "SYMBOL_TYPE", "TEX_DEFINE", "VERBOSE", "VERSION", "'='", "'('", "')'",
  "'!'", "'>'", "'<'", "','", "$accept", "command", "string_command",
  "boolean_command", "num_command", "opt_eq", "boolean", "string_expr",
  "num_expr", "term", "cmp", "op", "expr", "opt_args", "args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,    43,    45,    42,    47,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   378,    61,    40,
      41,    33,    62,    60,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   135,   136,   136,   136,   136,   136,   136,   136,   136,
     137,   137,   137,   137,   137,   137,   137,   137,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   140,   140,   141,   141,   142,   142,
     143,   144,   144,   144,   144,   144,   145,   145,   145,   145,
     145,   145,   145,   145,   146,   146,   146,   146,   147,   147,
     147,   147,   147,   147,   147,   148,   148,   149,   149
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     3,     3,     2,     3,     3,     1,     1,     1,     2,
       1,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     3,     4,     0,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     9,    18,    19,    20,    10,    11,    21,    22,    23,
      24,    25,    54,    12,    26,    13,    27,    28,    64,    29,
      30,    31,    32,    33,    34,    55,    56,    57,    58,    59,
      35,    14,    36,    37,    38,    15,    39,    60,    61,    62,
      40,    41,    42,    43,    44,    64,    45,    63,    64,    16,
      46,    17,    47,    48,    49,    50,    51,    52,    53,     0,
      64,    64,    64,    65,     0,     0,    88,    89,    90,     0,
       0,     0,     0,     8,     0,     1,     0,     0,     0,    68,
      69,     5,     6,    95,    73,     0,    92,     0,     0,     7,
       0,     0,    76,    77,    84,    85,    86,    87,    78,     0,
      80,    82,     0,     0,     2,    66,    67,     3,    70,     4,
      97,     0,    96,     0,    72,    93,    74,    75,    79,    81,
      83,    71,    91,    94,     0,    98
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    59,    60,    61,    62,    64,   107,    81,   109,    73,
     102,   103,    74,   111,   112
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -124
static const yytype_int8 yypact[] =
{
      -1,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -123,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,  -124,  -123,  -124,  -124,    -2,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,    10,
    -123,  -123,  -123,  -124,    41,    41,  -113,  -124,  -124,     3,
       9,     3,    41,    52,    44,  -124,    41,    64,    15,  -124,
    -124,  -124,  -124,     9,    52,     9,   114,    -9,    13,  -124,
       3,     3,  -124,  -124,  -124,  -124,  -124,  -124,  -124,   -96,
     -87,   -85,     9,     9,  -124,  -124,  -124,  -124,  -124,  -124,
     114,   -60,   -61,     5,  -124,  -124,    52,    52,  -124,  -124,
    -124,   114,   114,  -124,     9,   114
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -124,  -124,  -124,  -124,  -124,    94,  -124,     0,  -124,   -38,
    -124,  -124,    66,  -124,  -124
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       1,    90,    91,    66,    67,    63,    68,    69,    66,    67,
      75,    68,    69,    70,    66,    67,    83,    68,    70,    94,
      95,    96,    97,   108,    70,    92,    93,    94,    95,    96,
      97,    84,   118,    87,     2,     3,     4,     5,     6,     7,
       8,   119,     9,   120,    10,    11,    12,    79,    80,    13,
      14,    15,   116,   117,    16,    17,    92,    93,    94,    95,
      96,    97,    90,    91,    18,    82,    19,   105,   106,    20,
     123,    21,    89,   124,     0,     0,   104,    22,    23,    24,
       0,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,     0,     0,    45,     0,     0,    46,    47,    48,     0,
       0,    49,    50,    51,     0,    52,    53,    54,    55,    56,
       0,   114,    57,     0,     0,    58,    63,    71,    94,    95,
      96,    97,    71,     0,     0,   115,    86,    88,    85,    65,
       0,    98,    72,   115,    99,   100,   101,     0,     0,   110,
       0,   113,     0,     0,    76,    77,    78,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   121,   122,
       0,     0,    98,     0,     0,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     125
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-124))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,    10,    11,     5,     6,   128,     8,     9,     5,     6,
       0,     8,     9,    15,     5,     6,   129,     8,    15,    14,
      15,    16,    17,     8,    15,    12,    13,    14,    15,    16,
      17,    69,   128,    71,    35,    36,    37,    38,    39,    40,
      41,   128,    43,   128,    45,    46,    47,     6,     7,    50,
      51,    52,    90,    91,    55,    56,    12,    13,    14,    15,
      16,    17,    10,    11,    65,    65,    67,     3,     4,    70,
     130,    72,    72,   134,    -1,    -1,    76,    78,    79,    80,
      -1,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,    -1,    -1,   104,    -1,    -1,   107,   108,   109,    -1,
      -1,   112,   113,   114,    -1,   116,   117,   118,   119,   120,
      -1,   130,   123,    -1,    -1,   126,   128,   129,    14,    15,
      16,    17,   129,    -1,    -1,   130,    70,    71,   129,    45,
      -1,   128,    48,   130,   131,   132,   133,    -1,    -1,    83,
      -1,    85,    -1,    -1,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
      -1,    -1,   128,    -1,    -1,   131,   132,   133,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    35,    36,    37,    38,    39,    40,    41,    43,
      45,    46,    47,    50,    51,    52,    55,    56,    65,    67,
      70,    72,    78,    79,    80,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   104,   107,   108,   109,   112,
     113,   114,   116,   117,   118,   119,   120,   123,   126,   136,
     137,   138,   139,   128,   140,   140,     5,     6,     8,     9,
      15,   129,   140,   144,   147,     0,   140,   140,   140,     6,
       7,   142,   142,   129,   144,   129,   147,   144,   147,   142,
      10,    11,    12,    13,    14,    15,    16,    17,   128,   131,
     132,   133,   145,   146,   142,     3,     4,   141,     8,   143,
     147,   148,   149,   147,   130,   130,   144,   144,   128,   128,
     128,   147,   147,   130,   134,   147
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 153 "commands.y"
    { save_term((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 155 "commands.y"
    { save_term((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 157 "commands.y"
    { save_term((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 159 "commands.y"
    {
		}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 162 "commands.y"
    { load_rsc(TermString((yyvsp[(3) - (3)]))); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 166 "commands.y"
    { yyclearin; }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 231 "commands.y"
    { (yyval) = t_true; }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 233 "commands.y"
    { (yyval) = t_false; }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 242 "commands.y"
    { (yyval) = (yyvsp[(2) - (3)]);
		  TermTerm((yyval)) = (yyvsp[(1) - (3)]);
		  TermTerm2((yyval)) = (yyvsp[(3) - (3)]);
		}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 247 "commands.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 249 "commands.y"
    { (yyval) = new_term(NOT, (yyvsp[(2) - (2)]), TermNULL); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 251 "commands.y"
    { (yyval) = new_term(AND, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 253 "commands.y"
    { (yyval) = new_term(OR, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 257 "commands.y"
    { (yyval) = new_term(LIKE, TermNULL, TermNULL); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 259 "commands.y"
    { (yyval) = new_term(ILIKE, TermNULL, TermNULL); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 261 "commands.y"
    { (yyval) = new_term(EQ, TermNULL, TermNULL); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 263 "commands.y"
    { (yyval) = new_term(NE, TermNULL, TermNULL); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 265 "commands.y"
    { (yyval) = new_term(GT, TermNULL, TermNULL); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 267 "commands.y"
    { (yyval) = new_term(GE, TermNULL, TermNULL); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 269 "commands.y"
    { (yyval) = new_term(LT, TermNULL, TermNULL); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 271 "commands.y"
    { (yyval) = new_term(LE, TermNULL, TermNULL); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 275 "commands.y"
    { (yyval) = new_term(PLUS, TermNULL, TermNULL); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 277 "commands.y"
    { (yyval) = new_term(MINUS, TermNULL, TermNULL); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 279 "commands.y"
    { (yyval) = new_term(TIMES, TermNULL, TermNULL); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 281 "commands.y"
    { (yyval) = new_term(DIVIDE, TermNULL, TermNULL); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 287 "commands.y"
    { (yyval) = (yyvsp[(2) - (3)]);
		  TermTerm((yyval)) = (yyvsp[(1) - (3)]);
		  TermTerm2((yyval)) = (yyvsp[(3) - (3)]);
		}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 292 "commands.y"
    { (yyval) = new_term(UMINUS, (yyvsp[(2) - (2)]), TermNULL); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 294 "commands.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 296 "commands.y"
    { int op = find_function_op(TermString((yyvsp[(1) - (4)])));
		  if (op < 0)
		  { if ((yyvsp[(3) - (4)])) free_term((yyvsp[(3) - (4)]));
		    free_term((yyvsp[(1) - (4)]));
		    error_msg = "unknown function";
		    YYERROR;
		  } else {
		    (yyval)	= (yyvsp[(1) - (4)]);
		    TermOp((yyval)) = op;
		    TermTerm((yyval)) = (yyvsp[(3) - (4)]);
		  }
		}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 311 "commands.y"
    { (yyval) = TermNULL; }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 315 "commands.y"
    { (yyval) = new_term(PAIR, (yyvsp[(1) - (1)]), TermNULL); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 317 "commands.y"
    { (yyval) = new_term(PAIR, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); }
    break;



/* Line 1806 of yacc.c  */
#line 2020 "y.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 320 "commands.y"
 /*------------------------------------------------------------------------*/

static int save_term(t, a)
  Term t;
  Term a;
{
  TermTerm2(t) = a; 
  result = new_term(PAIR, t, result);
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	yyerror()
** Type:	int
** Purpose:	
**		
** Arguments:
**		
**		
** Returns:	
**___________________________________________________			     */
int yyerror(s)					   /*                        */
  char *s;					   /*                        */
{						   /*                        */
  if (error_msg)				   /*                        */
  { s = error_msg;				   /*                        */
    error_msg = NULL;				   /*                        */
  }						   /*                        */
 						   /*                        */
  if (fgetc(in_file)  > 0)			   /*                        */
  { fprintf(stderr,"*** %s at line %d\n%.32s\n",   /*                        */
	    s, linenum, "");			   /*                        */
  } else					   /*                        */
  { fprintf(stderr, "*** %s at EOF\n", s);	   /*                        */
  }						   /*                        */
}						   /*------------------------*/

#define GETC fgetc(in_file)
#define UNGETC(C) ungetc(C, in_file)

/*-----------------------------------------------------------------------------
** Function:	yylex()
** Type:	int
** Purpose:	
**		
** Arguments:
**		
**		
** Returns:	
**___________________________________________________			     */
int yylex()					   /*                        */
{					   	   /*                        */
  int c;					   /*                        */
  						   /*                        */
  for (c = GETC; c > 0; c = GETC)	   	   /*                        */
  {						   /*                        */
    switch (c) {				   /*                        */
      case '\n':				   /*                        */
	linenum++;				   /*                        */
      case ' ':					   /*                        */
      case '\f':				   /*                        */
      case '\r':				   /*                        */
      case '\b':				   /*                        */
	continue;				   /*                        */
      case '"':					   /*                        */
	{ StringBuffer *sb = sbopen();		   /*                        */
	  for (c = GETC; c && c != '"'; c = GETC) { sbputc(c, sb); }/*       */
	  					   /*                        */
	  yylval = new_term_string(STRING, sbflush(sb));/*                 */
	  return STRING;			   /*                        */
	}					   /*                        */
      case '\'':				   /*                        */
	{ StringBuffer *sb = sbopen();		   /*                        */
	  for (c = GETC; c && c != '\''; c = GETC) { sbputc(c, sb); }/*      */
	  					   /*                        */
	  yylval = new_term_string(FIELD, sbflush(sb));/*                  */
	  return FIELD;				   /*                        */
	}					   /*                        */
      case '{':					   /*                        */
	{ StringBuffer *sb = sbopen();		   /*                        */
	  int n = 1;				   /*                        */
	  for (c = GETC; c; c = GETC)		   /*                        */
	  { if (c == '{')			   /*                        */
	    { n++;				   /*                        */
	    } else if (c == '}')		   /*                        */
	    { if (--n < 1) { break; }		   /*                        */
	    }					   /*                        */
	    sbputc(c, sb);			   /*                        */
	  }					   /*                        */
	  					   /*                        */
	  yylval = new_term_string(BLOCK, sbflush(sb));/*                  */
	  return BLOCK;				   /*                        */
	}					   /*                        */
      case '0':					   /*                        */
	yylval = new_term_num(0);		   /*                        */
	c = GETC;				   /*                        */
	if (c == 0)				   /*                        */
	{ return NUMBER;			   /*                        */
	} else if (c == 'x')			   /*                        */
	{ for (c = GETC; c; c = GETC)		   /*                        */
	  { if (c >= '0' && c <= '9')		   /*                        */
	    { TermNumber(yylval) = TermNumber(yylval) * 16 + c - '0';/*      */
	    } else if (c >= 'a' && c <= 'f')	   /*                        */
	    { TermNumber(yylval) = TermNumber(yylval) * 16 + c - 'a';/*      */
	    } else if (c >= 'A' && c <= 'F')	   /*                        */
	    { TermNumber(yylval) = TermNumber(yylval) * 16 + c - 'A';/*      */
	    } else 				   /*                        */
	    { break; }				   /*                        */
	  }					   /*                        */
	} else if (c >= '0' && c <= '7')	   /*                        */
	{ for (c = GETC; c >= '0' && c <= '7'; c = GETC)/*                   */
	  { TermNumber(yylval) = TermNumber(yylval) * 8 + c - '0';/*         */
	  }					   /*                        */
	}					   /*                        */
	UNGETC(c);				   /*                        */
	return NUMBER;				   /*                        */
      case '1':					   /*                        */
      case '2':					   /*                        */
      case '3':					   /*                        */
      case '4':					   /*                        */
      case '5':					   /*                        */
      case '6':					   /*                        */
      case '7':					   /*                        */
      case '8':					   /*                        */
      case '9':					   /*                        */
	yylval = new_term_num(c - '0');		   /*                        */
	for (c = GETC; c >= '0' && c <= '9'; c = GETC)/*                     */
	{ TermNumber(yylval) = TermNumber(yylval) * 10 + c - '0';/*          */
	}					   /*                        */
	UNGETC(c);				   /*                        */
	return NUMBER;				   /*                        */
      default:					   /*                        */
	if ((c >= 'a' && c <= 'z') ||		   /*                        */
	    (c >= 'A' && c <= 'Z') ||		   /*                        */
	    c == '$' || c == '@' || c == '_' || c == '.')/*                  */
	{ StringBuffer *sb = sbopen();		   /*                        */
	  char* s;				   /*                        */
	  sbputc((char)c ,sb);			   /*                        */
	  for (c = GETC; isalpha(c) || c == '_' || c == '.'; c = GETC)/*     */
	  { sbputc((char)c ,sb); }		   /*                        */
	  UNGETC(c);				   /*                        */
	  s = sbflush(sb);			   /*                        */
#define ON(S,T)  if (strcmp(S, s) == 0)	\
	  { sbclose(sb); return T; }
#define ON_T(S,T)  if (strcmp(S, s) == 0)	\
	  { sbclose(sb);\
	    yylval = new_term(T, new_term_string(S), TermNULL); return T; }
	  switch (*s)				   /*                        */
	  { case 'a':				   /*                        */
	      ON("and", AND)			   /*                        */
	      ON_T("add.field", ADD_FIELD)
	      ON_T("apply.alias", APPLY_ALIAS)
	      ON_T("apply.modify", APPLY_MODIFY)
	      ON_T("apply.include", APPLY_INCLUDE)
	      break;				   /*                        */
	    case 'b':				   /*                        */
	      ON_T("bibtex.env.name", BIBTEX_ENV_NAME)/*                       */
	      ON_T("bibtex.search.path", BIBTEX_SEARCH_PATH)
	      break;				   /*                        */
	    case 'c':				   /*                        */
	      ON_T("check.double", CHECK_DOUBLE)
	      ON_T("check.double.delete", CHECK_DOUBLE_DELETE)
	      ON_T("check.rule", CHECK_RULE)
	      ON_T("check.case.sensitive", CHECK_CASE_SENSITIVE)
	      ON_T("clear.ignored.words", CLEAR_IGNORED_WORDS)
	      ON_T("count.all", COUNT_ALL)
	      ON_T("count.used", COUNT_USED)
	      ON_T("crossref.limit", CROSSREF_LIMIT)
	      break;				   /*                        */
	    case 'd':				   /*                        */
	      ON_T("dir.file.separator", DIR_FILE_SEPARATOR)
	      ON_T("default.key", DEFAULT_KEY)
	      ON_T("delete.field", DELETE_FIELD)
	      ON_T("dump.symbols", DUMP_SYMBOLS)
	      break;				   /*                        */
	    case 'e':				   /*                        */
	      ON_T("env.separator", ENV_SEPARATOR)
	      ON_T("extract.file", EXTRACT_FILE)
	      ON_T("extract.regex", EXTRACT_REGEX)
	      ON_T("expand.macros", EXPAND_MACROS)
	      ON_T("expand.crossref", EXPAND_CROSSREF)
	      break;				   /*                        */
	    case 'f':				   /*                        */
	      ON_T("fmt.inter.name", FMT_INTER_NAME)
	      ON_T("fmt.name.pre", FMT_NAME_PRE)
	      ON_T("fmt.name.name", FMT_NAME_NAME)
	      ON_T("fmt.name.title", FMT_NAME_TITLE)
	      ON_T("fmt.title.title", FMT_TITLE_TITLE)
	      ON_T("fmt.et.al", FMT_ET_AL)
	      ON_T("fmt.word.separator", FMT_WORD_SEPARATOR)
	      ON_T("field.type", FIELD_TYPE)
	      break;				   /*                        */
	    case 'i':				   /*                        */
	      ON("ilike", ILIKE)		   /*                        */
	      ON_T("input", INPUT)		   /*                        */
	      ON_T("ignored.word", IGNORED_WORD)
	      break;				   /*                        */
	    case 'k':				   /*                        */
	      ON_T("key.generation", KEY_GENERATION)
	      ON_T("key.base", KEY_BASE)
	      ON_T("key.format", KEY_FORMAT)
	      ON_T("key.make.alias", KEY_MAKE_ALIAS)
	      ON_T("key.number.separator", KEY_NUMBER_SEPARATOR)
	      ON_T("key.expand.macros", KEY_EXPAND_MACROS)
	      break;				   /*                        */
	    case 'l':				   /*                        */
	      ON("like", LIKE)			   /*                        */
	      break;				   /*                        */
	    case 'm':				   /*                        */
	      ON_T("macro.file", MACRO_FILE)
	      break;				   /*                        */
	    case 'n':				   /*                        */
	      ON("not", NOT)			   /*                        */
	      ON_T("new.entry.type", NEW_ENTRY_TYPE)
	      ON_T("new.field.type", NEW_FIELD_TYPE)
	      ON_T("new.format.type", NEW_FORMAT_TYPE)
	      break;				   /*                        */
	    case 'o':				   /*                        */
	      ON("off", B_OFF)			   /*                        */
	      ON("on", B_ON)			   /*                        */
	      ON("or", OR)			   /*                        */
	      ON_T("output.file", OUTPUT_FILE)
	      break;				   /*                        */
	    case 'p':				   /*                        */
	      ON_T("print.entry.types", PRINT_ENTRY_TYPES)
	      ON_T("print.deleted.prefix", PRINT_DELETED_PREFIX)
	      ON_T("pass.comments", PASS_COMMENTS)
	      ON_T("preserve.key.case", PRESERVE_KEY_CASE)
	      ON_T("preserve.keys", PRESERVE_KEYS)
	      ON_T("print", PRINT)
	      ON_T("print.align.string", PRINT_ALIGN_STRING)
	      ON_T("print.align.comment", PRINT_ALIGN_COMMENT)
	      ON_T("print.align.preamble", PRINT_ALIGN_PREAMBLE)
	      ON_T("print.align.key", PRINT_ALIGN_KEY)
	      ON_T("print.align", PRINT_ALIGN)
	      ON_T("print.all.strings", PRINT_ALL_STRINGS)
	      ON_T("print.equal.right", PRINT_EQUAL_RIGHT)
	      ON_T("print.braces", PRINT_BRACES)
	      ON_T("print.comma.at.end", PRINT_COMMA_AT_END)
	      ON_T("print.deleted.entries", PRINT_DELETED_ENTRIES)
	      ON_T("print.indent", PRINT_INDENT)
	      ON_T("print.line.length", PRINT_LINE_LENGTH)
	      ON_T("print.newline", PRINT_NEWLINE)
	      ON_T("print.parentheses", PRINT_PARENTHESES)
	      ON_T("print.terminal.comma", PRINT_TERMINAL_COMMA)
	      ON_T("print.use.tab", PRINT_USE_TAB)
	      ON_T("print.wide.equal", PRINT_WIDE_EQUAL)
	      break;				   /*                        */
	    case 'q':				   /*                        */
	      ON_T("quiet", QUIET)		   /*                        */
	      break;				   /*                        */
	    case 'r':				   /*                        */
	      ON_T("regexp.syntax", REGEXP_SYNTAX)
	      ON_T("rename.field", RENAME_FIELD)
	      ON_T("resource", RESOURCE)
	      ON_T("resource.search.path", RESOURCE_SEARCH_PATH)
	      ON_T("rewrite.rule", REWRITE_RULE)
	      ON_T("rewrite.case.sensitive", REWRITE_CASE_SENSITIVE)
	      ON_T("rewrite.limit", REWRITE_LIMIT)
	      break;				   /*                        */
	    case 's':				   /*                        */
	      ON_T("select.by.string.ignored", SELECT_BY_STRING_IGNORED)
	      ON_T("select.fields", SELECT_FIELDS)
	      ON_T("select", SELECT)
	      ON_T("select.by.string", SELECT_BY_STRING)
	      ON_T("select.by.non.string", SELECT_BY_NON_STRING)
	      ON_T("select.case.sensitive", SELECT_CASE_SENSITIVE)
	      ON_T("select.non", SELECT_NON)
	      ON_T("select.crossrefs", SELECT_CROSSREFS)
	      ON_T("sort", SORT)
	      ON_T("sort.cased", SORT_CASED)
	      ON_T("sort.macros", SORT_MACROS)
	      ON_T("sort.reverse", SORT_REVERSE)
	      ON_T("sort.order", SORT_ORDER)
	      ON_T("sort.format", SORT_FORMAT)
	      ON_T("suppress.initial.newline", SUPPRESS_INITIAL_NEWLINE)
	      ON_T("symbol.type", SYMBOL_TYPE)
	      break;				   /*                        */
	    case 't':				   /*                        */
	      ON_T("tex.define", TEX_DEFINE)
	      break;				   /*                        */
	    case 'v':				   /*                        */
	      ON_T("verbose", VERBOSE)		   /*                        */
	      ON_T("version", VERSION)
	      break;				   /*                        */
	  }					   /*                        */
	  yylval = new_term_string(FIELD, s);	   /*                        */
	  return FIELD;				   /*                        */
	}					   /*                        */
    }						   /*                        */
    return c < 0 ? 0: c;			   /*                        */
  }						   /*                        */
  return 0;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	find_function_op()
** Type:	int
** Purpose:	
**		
** Arguments:
**	s	
** Returns:	
**___________________________________________________			     */
int find_function_op(s)				   /*                        */
  char * s;					   /*                        */
{						   /*                        */
#undef ON
#define ON(S,T)  if (strcmp(S, s) == 0)	{ return T; }
  switch (*s)					   /*                        */
  { case 'l':					   /*                        */
      ON("lowercase", FCT_LOWERCASE);		   /*                        */
      break;					   /*                        */
    case 's':					   /*                        */
      ON("substring", FCT_SUBSTRING);		   /*                        */
      break;					   /*                        */
    case 't':					   /*                        */
      ON("trim", FCT_TRIM);			   /*                        */
      break;					   /*                        */
    case 'u':					   /*                        */
      ON("uppercase", FCT_UPPERCASE);		   /*                        */
      break;					   /*                        */
  }						   /*                        */
  return -1;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_command()
** Type:	int
** Purpose:	
**		
** Arguments:
**	fname	
** Returns:	
**___________________________________________________			     */
int eval_command(fname)			   	   /*                        */
  char * fname;					   /*                        */
{						   /*                        */
  if (t_true == TermNULL) t_true = new_term_num(1);/*                        */
  if (t_false == TermNULL) t_false = new_term_num(0);/*                      */
 						   /*                        */
  in_file = fopen(fname, "r");			   /*                        */
  if (in_file == NULL) return 1;		   /*                        */
 						   /*                        */
  while (yyparse()) ;		   		   /*                        */
 						   /*                        */
  fclose(in_file);				   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

