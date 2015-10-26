/*** term.h ********************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

typedef struct S_TERM {
  int op;
  union {
    struct S_TERM * term;
    unsigned char * str;
    long num;
  } arg1;
  struct S_TERM * arg2;
} STerm, *Term;

#define TermNULL (Term)0

#define TermOp(T)     ((T)->op)
#define TermArg1(T)   ((T)->arg1)
#define TermTerm(T)   ((T)->arg1.term)
#define TermString(T) ((T)->arg1.str)
#define TermNumber(T) ((T)->arg1.num)
#define TermTerm2(T)   ((T)->arg2)


extern Term new_term();
extern Term new_term_num();
extern Term new_term_string();
extern void free_term();
extern void dump_term();

/*

#define T_EOF			0

#define T_FIELD			1000
#define T_NUMBER		1001
#define T_STRING		1002
#define T_BLOCK			1003

#define T_PAIR			1010

#define T_EQ			1020
#define T_NE			1021
#define T_LT			1022
#define T_LE			1023
#define T_GT			1024
#define T_GE			1025
#define T_LIKE			1026
#define T_ILIKE			1027

#define T_UMINUS		1030
#define T_PLUS			1031
#define T_MINUS			1032
#define T_TIMES			1033
#define T_DIVIDE		1034

#define T_NOT			1035
#define T_AND			1036
#define T_OR			1037

#define T_FCT_LOWERCASE		2001
#define T_FCT_UPPERCASE		2002
#define T_FCT_SUBSTRING		2003
#define T_FCT_TRIM		2004

#define ADD_FIELD		3000
#define APPLY_ALIAS		3001
#define APPLY_MODIFY		3002
#define APPLY_INCLUDE		3003
#define BIBTEX_ENV_NAME		3004
#define BIBTEX_SEARCH_PATH	3005
#define CHECK_DOUBLE		3006
#define CHECK_DOUBLE_DELETE	3007
#define CHECK_RULE		3008
#define CHECK_CASE_SENSITIVE	3009
#define CLEAR_IGNORED_WORDS	3010
#define COUNT_ALL		3011
#define COUNT_USED		3012
#define CROSSREF_LIMIT		3013
#define DEFAULT_KEY		3014
#define DELETE_FIELD		3015
#define DIR_FILE_SEPARATOR	3016
#define DUMP_SYMBOLS		3017
#define ENV_SEPARATOR		3018
#define EXTRACT_FILE		3019
#define EXTRACT_REGEX		3020
#define EXPAND_MACROS		3021
#define EXPAND_CROSSREF		3022
#define FMT_INTER_NAME		3023
#define FMT_NAME_PRE		3024
#define FMT_NAME_NAME		3025
#define FMT_NAME_TITLE		3026
#define FMT_TITLE_TITLE		3027
#define FMT_ET_AL		3028
#define FMT_WORD_SEPARATOR	3029
#define FIELD_TYPE		3030
#define INPUT			3031
#define IGNORED_WORD		3032
#define KEY_GENERATION		3033
#define KEY_BASE		3034
#define KEY_FORMAT		3035
#define KEY_MAKE_ALIAS		3036
#define KEY_NUMBER_SEPARATOR	3037
#define KEY_EXPAND_MACROS	3038
#define MACRO_FILE		3039
#define NEW_ENTRY_TYPE		3040
#define NEW_FIELD_TYPE		3041
#define NEW_FORMAT_TYPE		3042
#define OUTPUT_FILE		3043
#define PASS_COMMENTS		3044
#define PRESERVE_KEY_CASE	3045
#define PRESERVE_KEYS		3046
#define PRINT			3047
#define PRINT_ALIGN_STRING	3048
#define PRINT_ALIGN_COMMENT	3049
#define PRINT_ALIGN_PREAMBLE	3050
#define PRINT_ALIGN_KEY		3051
#define PRINT_ALIGN		3052
#define PRINT_ALL_STRINGS	3053
#define PRINT_ENTRY_TYPES	3054
#define PRINT_EQUAL_RIGHT	3055
#define PRINT_BRACES		3056
#define PRINT_COMMA_AT_END	3057
#define PRINT_DELETED_PREFIX	3058
#define PRINT_DELETED_ENTRIES	3059
#define PRINT_INDENT		3060
#define PRINT_LINE_LENGTH	3061
#define PRINT_NEWLINE		3062
#define PRINT_PARENTHESES	3063
#define PRINT_TERMINAL_COMMA	3064
#define PRINT_USE_TAB		3065
#define PRINT_WIDE_EQUAL	3066
#define QUIET			3067
#define REGEXP_SYNTAX		3068
#define RENAME_FIELD		3069
#define RESOURCE		3070
#define RESOURCE_SEARCH_PATH	3071
#define REWRITE_RULE		3072
#define REWRITE_CASE_SENSITIVE	3073
#define REWRITE_LIMIT		3074
#define SELECT			3075
#define SELECT_BY_STRING	3076
#define SELECT_BY_NON_STRING	3077
#define SELECT_BY_STRING_IGNORED	3078
#define SELECT_CASE_SENSITIVE	3079
#define SELECT_FIELDS		3080
#define SELECT_NON		3081
#define SELECT_CROSSREFS	3082
#define SORT			3083
#define SORT_CASED		3084
#define SORT_MACROS		3085
#define SORT_REVERSE		3086
#define SORT_ORDER		3087
#define SORT_FORMAT		3088
#define SUPPRESS_INITIAL_NEWLINE	3089
#define SYMBOL_TYPE		3090
#define TEX_DEFINE		3091
#define VERBOSE			3092
#define VERSION			3093
*/

/*---------------------------------------------------------------------------*/
