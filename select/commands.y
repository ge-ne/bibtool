/*** commands.y *****************************************************************
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
%{
#include <bibtool/bibtool.h>
#include <bibtool/sbuffer.h>
#include "term.h"
#define YYSTYPE Term
#include "commands.h"

  static Term t_true = TermNULL;
  static Term t_false = TermNULL;

  static FILE* in_file;
  static int linenum	   = 1;
  static char * error_msg = NULL;

%}

%token B_ON B_OFF

%token FIELD STRING BLOCK NUMBER
%token NOT
%token AND OR
%token LIKE ILIKE

%left  '+' '-'
%left  '*' '/'
%token UMINUS

%right AND OR

%token PLUS MINUS
%token TIMES DIVIDE

%token EQ NE LT LE GT GE

%token FCT_LOWERCASE FCT_UPPERCASE FCT_SUBSTRING FCT_TRIM

%token PAIR

%token ADD_FIELD
%token APPLY_ALIAS
%token APPLY_MODIFY
%token APPLY_INCLUDE
%token BIBTEX_ENV_NAME
%token BIBTEX_SEARCH_PATH
%token CHECK_DOUBLE
%token CHECK_DOUBLE_DELETE
%token CHECK_RULE
%token CHECK_CASE_SENSITIVE
%token CLEAR_IGNORED_WORDS
%token COUNT_ALL
%token COUNT_USED
%token CROSSREF_LIMIT
%token DEFAULT_KEY
%token DELETE_FIELD
%token DIR_FILE_SEPARATOR
%token DUMP_SYMBOLS
%token ENV_SEPARATOR
%token EXTRACT_FILE
%token EXTRACT_REGEX
%token EXPAND_MACROS
%token EXPAND_CROSSREF
%token FMT_INTER_NAME
%token FMT_NAME_PRE
%token FMT_NAME_NAME
%token FMT_NAME_TITLE
%token FMT_TITLE_TITLE
%token FMT_ET_AL
%token FMT_WORD_SEPARATOR
%token FIELD_TYPE
%token INPUT
%token IGNORED_WORD
%token KEY_GENERATION
%token KEY_BASE
%token KEY_FORMAT
%token KEY_MAKE_ALIAS
%token KEY_NUMBER_SEPARATOR
%token KEY_EXPAND_MACROS
%token MACRO_FILE
%token NEW_ENTRY_TYPE
%token NEW_FIELD_TYPE
%token NEW_FORMAT_TYPE
%token OUTPUT_FILE
%token PASS_COMMENTS
%token PRESERVE_KEY_CASE
%token PRESERVE_KEYS
%token PRINT
%token PRINT_ALIGN_STRING
%token PRINT_ALIGN_COMMENT
%token PRINT_ALIGN_PREAMBLE
%token PRINT_ALIGN_KEY
%token PRINT_ALIGN
%token PRINT_ALL_STRINGS
%token PRINT_ENTRY_TYPES
%token PRINT_EQUAL_RIGHT
%token PRINT_BRACES
%token PRINT_COMMA_AT_END
%token PRINT_DELETED_PREFIX
%token PRINT_DELETED_ENTRIES
%token PRINT_INDENT
%token PRINT_LINE_LENGTH
%token PRINT_NEWLINE
%token PRINT_PARENTHESES
%token PRINT_TERMINAL_COMMA
%token PRINT_USE_TAB
%token PRINT_WIDE_EQUAL
%token QUIET
%token REGEXP_SYNTAX
%token RENAME_FIELD
%token RESOURCE
%token RESOURCE_SEARCH_PATH
%token REWRITE_RULE
%token REWRITE_CASE_SENSITIVE
%token REWRITE_LIMIT
%token SELECT
%token SELECT_BY_STRING
%token SELECT_BY_NON_STRING
%token SELECT_BY_STRING_IGNORED
%token SELECT_CASE_SENSITIVE
%token SELECT_FIELDS
%token SELECT_NON
%token SELECT_CROSSREFS
%token SORT
%token SORT_CASED
%token SORT_MACROS
%token SORT_REVERSE
%token SORT_ORDER
%token SORT_FORMAT
%token SUPPRESS_INITIAL_NEWLINE
%token SYMBOL_TYPE
%token TEX_DEFINE
%token VERBOSE
%token VERSION

%start command

%% /*------------------------------------------------------------------------*/

command  : BIBTEX_ENV_NAME opt_eq string_expr
	 | INPUT opt_eq string_expr
		{
		}
	 | QUIET opt_eq boolean
		 { rsc_quiet = TermNumber($3); }
	 | RESOURCE opt_eq string_expr
		{ load_rsc(TermString($3)); }
	 | SELECT opt_eq string_expr
	 | SELECT term
	 | SORT opt_eq boolean
	 ;

opt_eq	 :
	 | '='
	 ;
boolean  : B_ON
		{ $$ = t_true; }
	 | B_OFF
		{ $$ = t_false; }
	 ;
string_expr: STRING
	 | BLOCK
	 ;

term     : expr cmp expr
		{ $$ = $2;
		  TermTerm($$) = $1;
		  TermTerm2($$) = $3;
		}
         | '(' term ')'
		{ $$ = $2; }
	 | NOT term
		{ $$ = new_term(NOT, $2, TermNULL); }
         | term AND term
		{ $$ = new_term(AND, $1, $3); }
         | term OR term
		{ $$ = new_term(OR, $1, $3); }
         ;

cmp      : LIKE
		{ $$ = new_term(LIKE, TermNULL, TermNULL); }
    	 | ILIKE
		{ $$ = new_term(ILIKE, TermNULL, TermNULL); }
	 | '='
		{ $$ = new_term(EQ, TermNULL, TermNULL); }
     	 | '!' '='
		{ $$ = new_term(NE, TermNULL, TermNULL); }
     	 | '>'
		{ $$ = new_term(GT, TermNULL, TermNULL); }
     	 | '>' '='
		{ $$ = new_term(GE, TermNULL, TermNULL); }
     	 | '<'
		{ $$ = new_term(LT, TermNULL, TermNULL); }
     	 | '<' '='
		{ $$ = new_term(LE, TermNULL, TermNULL); }
     	 ;

op       : '+'
		{ $$ = new_term(PLUS, TermNULL, TermNULL); }
     	 | '-'
		{ $$ = new_term(MINUS, TermNULL, TermNULL); }
     	 | '*'
		{ $$ = new_term(TIMES, TermNULL, TermNULL); }
     	 | '/'
		{ $$ = new_term(DIVIDE, TermNULL, TermNULL); }
     	 ;
expr     : FIELD
	 | STRING
	 | NUMBER
	 | expr op expr
		{ $$ = $2;
		  TermTerm($$) = $1;
		  TermTerm2($$) = $3;
		}
	 | '-' expr    %prec  UMINUS
		{ $$ = new_term(UMINUS, $2, TermNULL); }
	 | '(' expr ')'
		{ $$ = $2; }
	 | FIELD '(' opt_args ')'
		{ int op = find_function_op(TermString($1));
		  if (op < 0)
		  { if ($3) free_term($3);
		    free_term($1);
		    error_msg = "unknown function";
		    YYERROR;
		  } else {
		    $$	= $1;
		    TermOp($$) = op;
		    TermTerm($$) = $3;
		  }
		}
	 ;

opt_args :
		{ $$ = TermNULL; }
	 | args
	 ;
args	 : expr
		{ $$ = new_term(PAIR, $1, TermNULL); }
	 | args ',' expr
		{ $$ = new_term(PAIR, $1, $3); }
	 ;

%% /*------------------------------------------------------------------------*/

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
  if (fgetc(in_file)  >= 0)			   /*                        */
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
  for (c = GETC; c >= 0; c = GETC)	   	   /*                        */
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
#define ON(S,T)  if (strcmp(S, s) == 0)	{ sbclose(sb); return T; }
	  switch (*s)				   /*                        */
	  { case 'a':				   /*                        */
	      ON("and", AND)			   /*                        */
	      break;				   /*                        */
	    case 'b':				   /*                        */
	      ON("bibtex.env.name", BIBTEX_ENV_NAME)/*                       */
	      break;				   /*                        */
	    case 'i':				   /*                        */
	      ON("ilike", ILIKE)		   /*                        */
	      ON("input", INPUT)		   /*                        */
	      break;				   /*                        */
	    case 'l':				   /*                        */
	      ON("like", LIKE)			   /*                        */
	      break;				   /*                        */
	    case 'n':				   /*                        */
	      ON("not", NOT)			   /*                        */
	      break;				   /*                        */
	    case 'o':				   /*                        */
	      ON("off", B_OFF)			   /*                        */
	      ON("on", B_ON)			   /*                        */
	      ON("or", OR)			   /*                        */
	      break;				   /*                        */
	    case 'p':				   /*                        */
	      break;				   /*                        */
	    case 'q':				   /*                        */
	      ON("quiet", QUIET)		   /*                        */
	      break;				   /*                        */
	    case 'r':				   /*                        */
	      ON("resource", RESOURCE)		   /*                        */
	      break;				   /*                        */
	    case 's':				   /*                        */
	      ON("select", SELECT)		   /*                        */
	      ON("sort", SORT)			   /*                        */
	      break;				   /*                        */
	    case 'v':				   /*                        */
	      ON("verbose", VERBOSE)		   /*                        */
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
  switch (*s)					   /*                        */
  { case 'l':
      if (strcmp("lowercase",s) == 0) return FCT_LOWERCASE;
      break;
    case 's':
      if (strcmp("substring",s) == 0) return FCT_SUBSTRING;
      break;
    case 't':
      if (strcmp("trim",s) == 0) return FCT_TRIM;
      break;
    case 'u':
      if (strcmp("uppercase",s) == 0) return FCT_UPPERCASE;
      break;
  }
  return -1;
}

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
