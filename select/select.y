%{
#include <stdio.h>
#include <ctype.h>

#include <bibtool/sbuffer.h>
#include "select.h"
#include "term.h"

#define YYSTYPE Term

  Term result;
  int linenum	   = 1;
  char * error_msg = NULL;

%}

%token FIELD STRING NUMBER
%token NOT
%token AND OR
%token LIKE ILIKE
%token UMINUS

%left  '+' '-'
%left  '*' '/'

%right AND OR

%start selection

%%

selection: term
	 { result = $1; }

term     : expr cmp expr
	 { $$ = $2;
	   TermTerm($$) = $1;
	   TermArg2($$) = $3;
	 }
         | '(' term ')'
	 { $$ = $2; }
	 | NOT term
	 { $$ = new_term(T_NOT, $2, TermNULL); }
         | term AND term
	 { $$ = new_term(T_AND, $1, $3); }
         | term OR term
	 { $$ = new_term(T_OR, $1, $3); }
         ;

cmp      : LIKE
	 { $$ = new_term(T_LIKE, TermNULL, TermNULL); }
    	 | ILIKE
	 { $$ = new_term(T_ILIKE, TermNULL, TermNULL); }
	 | '='
	 { $$ = new_term(T_EQ, TermNULL, TermNULL); }
     	 | '!' '='
	 { $$ = new_term(T_NE, TermNULL, TermNULL); }
     	 | '>'
	 { $$ = new_term(T_GT, TermNULL, TermNULL); }
     	 | '>' '='
	 { $$ = new_term(T_GE, TermNULL, TermNULL); }
     	 | '<'
	 { $$ = new_term(T_LT, TermNULL, TermNULL); }
     	 | '<' '='
	 { $$ = new_term(T_LE, TermNULL, TermNULL); }
     	 ;

op       : '+'
	 { $$ = new_term(T_PLUS, TermNULL, TermNULL); }
     	 | '-'
	 { $$ = new_term(T_MINUS, TermNULL, TermNULL); }
     	 | '*'
	 { $$ = new_term(T_TIMES, TermNULL, TermNULL); }
     	 | '/'
	 { $$ = new_term(T_DIVIDE, TermNULL, TermNULL); }
     	 ;
expr     : FIELD
	 | STRING
	 | NUMBER
	 | expr op expr
	 { $$ = $2;
	   TermTerm($$) = $1;
	   TermArg2($$) = $3;
	 }
	 | '-' expr    %prec  UMINUS
	 { $$ = new_term(T_UMINUS, $2, TermNULL); }
	 | '(' expr ')'
	 { $$ = $2; }
	 | FIELD '(' opt_args ')'
	 { int op = find_function_op(TermString($1));
	   if (op == 0)
	   { free_term($3);
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
	 | expr ',' args
	 { $$ = new_term(T_PAIR, $1, $3); }
	 ;

%%

static unsigned char * in;			   /*                        */
static unsigned char * inp;			   /*                        */

/*-----------------------------------------------------------------------------
** Function:	()
** Type:	
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
  if (*inp)					   /*                        */
  { fprintf(stderr,"*** %s at line %d\n%.32s\n",   /*                        */
	    s, linenum, inp);			   /*                        */
  } else					   /*                        */
  { fprintf(stderr, "*** %s at EOF\n", s);	   /*                        */
  }						   /*                        */
}						   /*------------------------*/

#define GETC *(inp++)
#define UNGETC inp--

/*-----------------------------------------------------------------------------
** Function:	()
** Type:	
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
  for (c = GETC; c != EOF; c = GETC) 
  {
    switch (c) {
      case '\n':
	linenum++;
      case ' ':
      case '\f':
      case '\r':
      case '\b':
	continue;
      case '"':
	{ StringBuffer *sb = sbopen();
	  for (c = GETC; c && c != '"'; c = GETC) { sbputc(c, sb); }
	  
	  yylval = new_term_string(T_STRING, sbflush(sb));
	  return STRING;
	}	
      case '\'':
	{ StringBuffer *sb = sbopen();
	  for (c = GETC; c && c != '\''; c = GETC) { sbputc(c, sb); }
	  
	  yylval = new_term_string(T_FIELD, sbflush(sb));
	  return FIELD;
	}
	
      case '0':
	yylval = new_term_num(0);
	c = GETC;
	if (c == 0)
	{ return NUMBER;
	} else if (c == 'x')
	{ for (c = GETC; c; c = GETC)
	  { if (c >= '0' && c <= '9')
	    { TermNumber(yylval) = TermNumber(yylval) * 16 + c - '0';
	    } else if (c >= 'a' && c <= 'f')
	    { TermNumber(yylval) = TermNumber(yylval) * 16 + c - 'a';
	    } else if (c >= 'A' && c <= 'F')
	    { TermNumber(yylval) = TermNumber(yylval) * 16 + c - 'A';
	    } else 
	    { break; }
	  }
	} else if (c >= '0' && c <= '7')
	{ for (c = GETC; c >= '0' && c <= '7'; c = GETC)
	  { TermNumber(yylval) = TermNumber(yylval) * 8 + c - '0';
	  }
	}
	UNGETC;
	return NUMBER;

      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
	yylval = new_term_num(c - '0');
	for (c = GETC; c >= '0' && c <= '9'; c = GETC)
	{ TermNumber(yylval) = TermNumber(yylval) * 10 + c - '0';
	}
	UNGETC;
	return NUMBER;
      default:
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '$' || c == '@' || c == '_')
	{ StringBuffer *sb = sbopen();
	  char* s;
	  sbputc((char)c ,sb);
	  for (c = GETC; isalpha(c) || c == '_'; c = GETC) { sbputc((char)c ,sb); }

	  s = sbflush(sb);
	  if (strcmp("like", s) == 0)
	  { sbclose(sb);
	    return LIKE;
	  } else if (strcmp("ilike", s) == 0)
	  { sbclose(sb);
	    return ILIKE;
	  } else if (strcmp("and", s) == 0)
	  { sbclose(sb);
	    return AND;
	  } else if (strcmp("or", s) == 0)
	  { sbclose(sb);
	    return OR;
	  } else if (strcmp("not", s) == 0)
	  { sbclose(sb);
	    return NOT;
	  }
	  yylval = new_term_string(T_FIELD, s);
	  return FIELD;
	}
    }
    return c;
  }
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
int find_function_op(s)
  char * s;
{
  switch (*s)
  { case 'l':
      if (strcmp("lowercase",s) == 0) return T_FCT_LOWERCASE;
      break;
    case 's':
      if (strcmp("substring",s) == 0) return T_FCT_SUBSTRING;
      break;
    case 't':
      if (strcmp("trim",s) == 0) return T_FCT_TRIM;
      break;
    case 'u':
      if (strcmp("uppercase",s) == 0) return T_FCT_UPPERCASE;
      break;
  }
  return -1;
}

/*-----------------------------------------------------------------------------
** Function:	selection()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	s	
** Returns:	
**___________________________________________________			     */
Term selection(s)				   /*                        */
  char * s;					   /*                        */
{						   /*                        */
  in = s;					   /*                        */
  inp = in;					   /*                        */
  						   /*                        */
  return yyparse() ? TermNULL : result;		   /*                        */
}						   /*------------------------*/
