/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

extern YYSTYPE yylval;


