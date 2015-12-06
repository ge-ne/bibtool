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
     BOOLEAN = 264,
     NOT = 265,
     AND = 266,
     OR = 267,
     LIKE = 268,
     ILIKE = 269,
     UMINUS = 270,
     PLUS = 271,
     MINUS = 272,
     TIMES = 273,
     DIVIDE = 274,
     EQ = 275,
     NE = 276,
     LT = 277,
     LE = 278,
     GT = 279,
     GE = 280,
     FCT_LOWERCASE = 281,
     FCT_UPPERCASE = 282,
     FCT_SUBSTRING = 283,
     FCT_TRIM = 284,
     CONS = 285,
     ADD_FIELD = 286,
     APPLY_ALIAS = 287,
     APPLY_MODIFY = 288,
     APPLY_INCLUDE = 289,
     BIBTEX_ENV_NAME = 290,
     BIBTEX_SEARCH_PATH = 291,
     CHECK_DOUBLE = 292,
     CHECK_DOUBLE_DELETE = 293,
     CHECK_RULE = 294,
     CHECK_CASE_SENSITIVE = 295,
     CLEAR_IGNORED_WORDS = 296,
     COUNT_ALL = 297,
     COUNT_USED = 298,
     CROSSREF_LIMIT = 299,
     DEFAULT_KEY = 300,
     DELETE_FIELD = 301,
     DIR_FILE_SEPARATOR = 302,
     DUMP_SYMBOLS = 303,
     ENV_SEPARATOR = 304,
     EXTRACT_FILE = 305,
     EXTRACT_REGEX = 306,
     EXPAND_MACROS = 307,
     EXPAND_CROSSREF = 308,
     FMT_INTER_NAME = 309,
     FMT_NAME_PRE = 310,
     FMT_NAME_NAME = 311,
     FMT_NAME_TITLE = 312,
     FMT_TITLE_TITLE = 313,
     FMT_ET_AL = 314,
     FMT_WORD_SEPARATOR = 315,
     FIELD_TYPE = 316,
     INPUT = 317,
     IGNORED_WORD = 318,
     KEY_GENERATION = 319,
     KEY_BASE = 320,
     KEY_FORMAT = 321,
     KEY_MAKE_ALIAS = 322,
     KEY_NUMBER_SEPARATOR = 323,
     KEY_EXPAND_MACROS = 324,
     MACRO_FILE = 325,
     NEW_ENTRY_TYPE = 326,
     NEW_FIELD_TYPE = 327,
     NEW_FORMAT_TYPE = 328,
     OUTPUT_FILE = 329,
     PASS_COMMENTS = 330,
     PRESERVE_KEY_CASE = 331,
     PRESERVE_KEYS = 332,
     PRINT = 333,
     PRINT_ALIGN_STRING = 334,
     PRINT_ALIGN_COMMENT = 335,
     PRINT_ALIGN_PREAMBLE = 336,
     PRINT_ALIGN_KEY = 337,
     PRINT_ALIGN = 338,
     PRINT_ALL_STRINGS = 339,
     PRINT_ENTRY_TYPES = 340,
     PRINT_EQUAL_RIGHT = 341,
     PRINT_BRACES = 342,
     PRINT_COMMA_AT_END = 343,
     PRINT_DELETED_PREFIX = 344,
     PRINT_DELETED_ENTRIES = 345,
     PRINT_INDENT = 346,
     PRINT_LINE_LENGTH = 347,
     PRINT_NEWLINE = 348,
     PRINT_PARENTHESES = 349,
     PRINT_TERMINAL_COMMA = 350,
     PRINT_USE_TAB = 351,
     PRINT_WIDE_EQUAL = 352,
     QUIET = 353,
     REGEXP_SYNTAX = 354,
     RENAME_FIELD = 355,
     RESOURCE = 356,
     RESOURCE_SEARCH_PATH = 357,
     REWRITE_RULE = 358,
     REWRITE_CASE_SENSITIVE = 359,
     REWRITE_LIMIT = 360,
     SELECT = 361,
     SELECT_BY_STRING = 362,
     SELECT_BY_NON_STRING = 363,
     SELECT_BY_STRING_IGNORED = 364,
     SELECT_CASE_SENSITIVE = 365,
     SELECT_FIELDS = 366,
     SELECT_NON = 367,
     SELECT_CROSSREFS = 368,
     SORT = 369,
     SORT_CASED = 370,
     SORT_MACROS = 371,
     SORT_REVERSE = 372,
     SORT_ORDER = 373,
     SORT_FORMAT = 374,
     SUPPRESS_INITIAL_NEWLINE = 375,
     SYMBOL_TYPE = 376,
     TEX_DEFINE = 377,
     VERBOSE = 378,
     VERSION = 379
   };
#endif
/* Tokens.  */
#define B_ON 258
#define B_OFF 259
#define FIELD 260
#define STRING 261
#define BLOCK 262
#define NUMBER 263
#define BOOLEAN 264
#define NOT 265
#define AND 266
#define OR 267
#define LIKE 268
#define ILIKE 269
#define UMINUS 270
#define PLUS 271
#define MINUS 272
#define TIMES 273
#define DIVIDE 274
#define EQ 275
#define NE 276
#define LT 277
#define LE 278
#define GT 279
#define GE 280
#define FCT_LOWERCASE 281
#define FCT_UPPERCASE 282
#define FCT_SUBSTRING 283
#define FCT_TRIM 284
#define CONS 285
#define ADD_FIELD 286
#define APPLY_ALIAS 287
#define APPLY_MODIFY 288
#define APPLY_INCLUDE 289
#define BIBTEX_ENV_NAME 290
#define BIBTEX_SEARCH_PATH 291
#define CHECK_DOUBLE 292
#define CHECK_DOUBLE_DELETE 293
#define CHECK_RULE 294
#define CHECK_CASE_SENSITIVE 295
#define CLEAR_IGNORED_WORDS 296
#define COUNT_ALL 297
#define COUNT_USED 298
#define CROSSREF_LIMIT 299
#define DEFAULT_KEY 300
#define DELETE_FIELD 301
#define DIR_FILE_SEPARATOR 302
#define DUMP_SYMBOLS 303
#define ENV_SEPARATOR 304
#define EXTRACT_FILE 305
#define EXTRACT_REGEX 306
#define EXPAND_MACROS 307
#define EXPAND_CROSSREF 308
#define FMT_INTER_NAME 309
#define FMT_NAME_PRE 310
#define FMT_NAME_NAME 311
#define FMT_NAME_TITLE 312
#define FMT_TITLE_TITLE 313
#define FMT_ET_AL 314
#define FMT_WORD_SEPARATOR 315
#define FIELD_TYPE 316
#define INPUT 317
#define IGNORED_WORD 318
#define KEY_GENERATION 319
#define KEY_BASE 320
#define KEY_FORMAT 321
#define KEY_MAKE_ALIAS 322
#define KEY_NUMBER_SEPARATOR 323
#define KEY_EXPAND_MACROS 324
#define MACRO_FILE 325
#define NEW_ENTRY_TYPE 326
#define NEW_FIELD_TYPE 327
#define NEW_FORMAT_TYPE 328
#define OUTPUT_FILE 329
#define PASS_COMMENTS 330
#define PRESERVE_KEY_CASE 331
#define PRESERVE_KEYS 332
#define PRINT 333
#define PRINT_ALIGN_STRING 334
#define PRINT_ALIGN_COMMENT 335
#define PRINT_ALIGN_PREAMBLE 336
#define PRINT_ALIGN_KEY 337
#define PRINT_ALIGN 338
#define PRINT_ALL_STRINGS 339
#define PRINT_ENTRY_TYPES 340
#define PRINT_EQUAL_RIGHT 341
#define PRINT_BRACES 342
#define PRINT_COMMA_AT_END 343
#define PRINT_DELETED_PREFIX 344
#define PRINT_DELETED_ENTRIES 345
#define PRINT_INDENT 346
#define PRINT_LINE_LENGTH 347
#define PRINT_NEWLINE 348
#define PRINT_PARENTHESES 349
#define PRINT_TERMINAL_COMMA 350
#define PRINT_USE_TAB 351
#define PRINT_WIDE_EQUAL 352
#define QUIET 353
#define REGEXP_SYNTAX 354
#define RENAME_FIELD 355
#define RESOURCE 356
#define RESOURCE_SEARCH_PATH 357
#define REWRITE_RULE 358
#define REWRITE_CASE_SENSITIVE 359
#define REWRITE_LIMIT 360
#define SELECT 361
#define SELECT_BY_STRING 362
#define SELECT_BY_NON_STRING 363
#define SELECT_BY_STRING_IGNORED 364
#define SELECT_CASE_SENSITIVE 365
#define SELECT_FIELDS 366
#define SELECT_NON 367
#define SELECT_CROSSREFS 368
#define SORT 369
#define SORT_CASED 370
#define SORT_MACROS 371
#define SORT_REVERSE 372
#define SORT_ORDER 373
#define SORT_FORMAT 374
#define SUPPRESS_INITIAL_NEWLINE 375
#define SYMBOL_TYPE 376
#define TEX_DEFINE 377
#define VERBOSE 378
#define VERSION 379




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


