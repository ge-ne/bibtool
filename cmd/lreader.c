/*** lreader.c ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015-2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <bibtool/sbuffer.h>
#include <bibtool/symbols.h>
#include <bibtool/type.h>
#include <bibtool/error.h>
#include "tstack.h"
#include "term.h"
#include "binding.h"
#include "lcore.h"
#include "lreader.h"

#undef DEBUG_PARSER 

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

static int scan _ARG((Binding b));
static Term scan_block();			   /*                        */
static Term scan_string _ARG((SymDef s, char c));
static Term read_list _ARG((Binding b, Term t));
static Term read_builtin _ARG((Binding b, Term t));
static TStack reduce _ARG((TStack ts));
int read_loop _ARG((Binding b, char* file, int (*action)(Binding binding, Term t) ));
static Term read_cmd _ARG((Binding b));
static Term read_expr _ARG((Binding b));

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


static String END_OF_FILE = (String)"end of file";

 static Term yylval;				   /*                        */
 static char * filename;			   /*                        */
 static FILE * in_file;				   /*                        */
 static int  linenum;				   /*                        */
 static int  c_look_ahead = 0;		   	   /*                        */
 static Term look_ahead = NIL;			   /*                        */

static Uchar buffer[2];

#define unscan(C,T) (c_look_ahead = (C), look_ahead = (T))

#define Error(X,Y,Z)						\
	error(ERR_ERROR|ERR_FILE|ERR_EXIT,(String)X,		\
	      (String)Y,(String)Z,(String)0,(String)0,linenum,filename)
#define ErrorNF(X,Y)						\
	error(ERR_ERROR|ERR_EXIT,(String)X,			\
	      (String)Y,(String)0,(String)0,(String)0,0,NULL)

#define GetC fgetc(in_file)
#define UnGetC(C) ungetc(C, in_file)

/*-----------------------------------------------------------------------------
** Function:	tag_id()
** Type:	static String
** Purpose:	
**		
** Arguments:
**	c	
** Returns:	
**___________________________________________________			     */
String tag_id(c)			   	   /*                        */
  int c;					   /*                        */
{						   /*                        */
  switch (c)					   /*                        */
  { case L_STRING: return (String)"string";	   /*                        */
    case L_FIELD:  return (String)"field";	   /*                        */
    case L_NUMBER: return (String)"number";	   /*                        */
    case L_LIST:   return (String)"list";	   /*                        */
    case L_GROUP:  return (String)"group";	   /*                        */
    case L_TRUE:   return (String)"true";	   /*                        */
    case L_FALSE:  return (String)"false";	   /*                        */
    case L_QUOTE:  return (String)"'";		   /*                        */
    case L_MINUS:  return (String)"-";		   /*                        */
    case L_PLUS:   return (String)"+";		   /*                        */
    case L_TIMES:  return (String)"*";		   /*                        */
    case L_DIV:    return (String)"/";		   /*                        */
    case L_MOD:    return (String)"mod";	   /*                        */
    case L_SET:    return (String)"=";		   /*                        */
    case L_LIKE:   return (String)"like";	   /*                        */
    case L_ILIKE:  return (String)"ilike";	   /*                        */
    case L_EQ:     return (String)"==";		   /*                        */
    case L_NE:     return (String)"!=";		   /*                        */
    case L_GT:     return (String)">";		   /*                        */
    case L_GE:     return (String)">=";		   /*                        */
    case L_LT:     return (String)"<";		   /*                        */
    case L_LE:     return (String)"<=";		   /*                        */
    case L_NOT:    return (String)"not";	   /*                        */
    case L_AND:    return (String)"and";	   /*                        */
    case L_OR:     return (String)"or";		   /*                        */
    case 0:					   /*                        */
    case EOF:      return END_OF_FILE;		   /*                        */
  }						   /*                        */
  buffer[0] = c;				   /*                        */
  buffer[1] = 0;				   /*                        */
  return buffer;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	scan_block()
** Type:	Term
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
static Term scan_block()			   /*                        */
{ StringBuffer *sb = sbopen();		   	   /*                        */
  int n = 1;				   	   /*                        */
  int c;					   /*                        */
  Term t;					   /*                        */
 						   /*                        */
  for (c = GetC; c; c = GetC)		   	   /*                        */
  { if      (c == '{') { n++; }			   /*                        */
    else if (c == '}') { if (--n < 1) break; }	   /*                        */
    sbputc(c, sb);			   	   /*                        */
  }					   	   /*                        */
					       	   /*                        */
  t = BlockTerm((String)sbflush(sb));      	   /*                        */
  sbclose(sb);				   	   /*                        */
  return t;			   	   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	scan_string()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	s	
** Returns:	
**___________________________________________________			     */
static Term scan_string(s, c_end)		   /*                        */
  SymDef s;					   /*                        */
  char   c_end;					   /*                        */
{ Term t;					   /*                        */
  StringBuffer *sb = sbopen();		   	   /*                        */
  register int c;				   /*                        */
  int lno = linenum;				   /*                        */
  						   /*                        */
  for (c = GetC; c != c_end; c = GetC)	   	   /*                        */
  { if ( c == '\\')			   	   /*                        */
    { c = GetC;				   	   /*                        */
      switch (c)			   	   /*                        */
      { case EOF:				   /*                        */
	case 0:				   	   /*                        */
	  linenum = lno;			   /*                        */
	  Error("Missing closing delimiter ",	   /*                        */
		(c_end =='"' ? "\"": "`"), 0);	   /*                        */
	case 'n':			   	   /*                        */
	  sbputc('\n', sb);		   	   /*                        */
	  break;			   	   /*                        */
	case 'r':			   	   /*                        */
	  sbputc('\r', sb);		   	   /*                        */
	  break;			   	   /*                        */
	case 'f':			   	   /*                        */
	  sbputc('\f', sb);		   	   /*                        */
	  break;			   	   /*                        */
	case 'b':			   	   /*                        */
	  sbputc('\b', sb);		   	   /*                        */
	  break;			   	   /*                        */
	default:			   	   /*                        */
	  sbputc(c, sb);		   	   /*                        */
      }					   	   /*                        */
    } else if ( c <= 0)			   	   /*                        */
    { linenum = lno;				   /*                        */
      Error("Missing closing delimiter ",	   /*                        */
	    (c_end =='"' ? "\"": "`"), 0);	   /*                        */
    } else{				   	   /*                        */
      sbputc(c, sb);			   	   /*                        */
    }					   	   /*                        */
  }					   	   /*                        */
					       	   /*                        */
  t = new_t_string(s, symbol((String)sbflush(sb)));/*                        */
  sbclose(sb);				   	   /*                        */
  return t;			   		   /*                        */
}						   /*------------------------*/

#define Return(VAL, C) yylval = (VAL); return C

/*-----------------------------------------------------------------------------
** Function:	scan()
** Type:	SymDef
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
static int scan(b)			   	   /*                        */
  Binding b;					   /*                        */
{ register int c;				   /*                        */
 						   /*                        */
  if (c_look_ahead)			   	   /*                        */
  { c		 = c_look_ahead;		   /*                        */
    yylval	 = look_ahead;			   /*                        */
    c_look_ahead = 0;			   	   /*                        */
    look_ahead	 = NIL;			   	   /*                        */
    return c;			   		   /*                        */
  }						   /*                        */
    						   /*                        */
  yylval = NIL;				   	   /*                        */
 						   /*                        */
  for (c = GetC; c >= 0; c = GetC)	   	   /*                        */
  {						   /*                        */
#ifdef DEBUG_PARSER
    fprintf(stderr, "--- scan %c %d\n",c,c);	   /*                        */
#endif
    switch (c) {				   /*                        */
      case '\n':				   /*                        */
	linenum++;				   /*                        */
      case ' ':					   /*                        */
      case '\f':				   /*                        */
      case '\r':				   /*                        */
      case '\b':				   /*                        */
	continue;				   /*                        */
 						   /*                        */
      case '%':					   /*                        */
	for (c = GetC; c && c != '\n'; c = GetC) ; /*                        */
	continue;				   /*                        */
						   /*                        */
      case '"':					   /*                        */
	Return(scan_string(sym_string ,'"'),	   /*                        */
	       L_STRING);			   /*                        */
	  					   /*                        */
      case '`':				   	   /*                        */
	Return(scan_string(sym_field ,'`'),	   /*                        */
	       L_FIELD);  			   /*                        */
 	  					   /*                        */
      case '+':					   /*                        */
	Return(SymCharTerm('+'), L_PLUS);	   /*                        */
	  					   /*                        */
      case '-':					   /*                        */
	Return(SymCharTerm('-'), L_MINUS);	   /*                        */
	  					   /*                        */
      case '*':					   /*                        */
	Return(SymCharTerm('*'), L_TIMES);	   /*                        */
	  					   /*                        */
      case '/':					   /*                        */
	Return(SymCharTerm('/'), L_DIV);	   /*                        */
	  					   /*                        */
      case '\'':				   /*                        */
	Return(SymCharTerm('\''), L_QUOTE);	   /*                        */
	  					   /*                        */
      case '0':					   /*                        */
	{ register long num = 0;		   /*                        */
	  c = GetC;				   /*                        */
	  if (c == 'x')			   	   /*                        */
	  { for (c = GetC; c; c = GetC)		   /*                        */
	    { if (c >= '0' && c <= '9')		   /*                        */
	      { num = num * 16 + c - '0';	   /*                        */
	      } else if (c >= 'a' && c <= 'f')	   /*                        */
	      { num = num * 16 + 10 + c - 'a';	   /*                        */
	      } else if (c >= 'A' && c <= 'F')	   /*                        */
	      { num = num * 16 + 10 + c - 'A';	   /*                        */
	      } else 				   /*                        */
	      { break; }			   /*                        */
	    }					   /*                        */
	  } else				   /*                        */
	  { for (; c >= '0' && c <= '7'; c = GetC) /*                        */
	    { num = num * 8 + c - '0'; }	   /*                        */
	  }					   /*                        */
	  if (c > 0) UnGetC(c);			   /*                        */
	  Return(new_term_num(num), L_NUMBER);	   /*                        */
	}					   /*                        */
	  					   /*                        */
      case '1': case '2': case '3': case '4':	   /*                        */
      case '5': case '6': case '7': case '8':	   /*                        */
      case '9':					   /*                        */
	{ long num = c - '0';			   /*                        */
	  for (c = GetC; c >= '0' && c <= '9'; c = GetC)/*                   */
	  { num = num * 10 + c - '0'; }	   	   /*                        */
	  UnGetC(c);				   /*                        */
	  Return(new_term_num(num), L_NUMBER);	   /*                        */
	}					   /*                        */
	  					   /*                        */
      case '[':					   /*                        */
	for (c = GetC; c && isspace(c); c = GetC); /*                        */
	if (c == ']') {				   /*                        */
	  yylval = NIL;				   /*                        */
	  return L_LIST;			   /*                        */
	}					   /*                        */
	UnGetC(c);				   /*                        */
	Return(Cons(NIL, NIL), L_LIST);		   /*                        */
	  					   /*                        */
      case '=':					   /*                        */
	if ((c=GetC) == '=') {			   /*                        */
	  Return(new_term(sym_eq, NIL, NIL),	   /*                        */
		 L_EQ);	   		   	   /*                        */
	}					   /*                        */
	UnGetC(c);				   /*                        */
	Return(SymCharTerm('='), L_SET);	   /*                        */
	  					   /*                        */
      case '&':					   /*                        */
	if ((c=GetC) == '&') {			   /*                        */
	  Return(new_term(sym_and, NIL, NIL),	   /*                        */
		 L_AND);	   		   /*                        */
	}					   /*                        */
	UnGetC(c);				   /*                        */
	Return(SymCharTerm('&'), '&'); 	   	   /*                        */
	  					   /*                        */
      case '|':					   /*                        */
	if ((c=GetC) == '|') {			   /*                        */
	  Return(new_term(sym_or, NIL, NIL),	   /*                        */
		 L_OR);	   			   /*                        */
	}					   /*                        */
	UnGetC(c);				   /*                        */
	Return(SymCharTerm('|'), '|'); 	   	   /*                        */
	  					   /*                        */
      case '!':					   /*                        */
	if ((c=GetC) == '=') {			   /*                        */
	  Return(new_term(sym_ne, NIL, NIL), L_NE);/*                        */
	}					   /*                        */
	Return(SymTerm(sym_not), L_NOT);	   /*                        */
	  					   /*                        */
      case '>':					   /*                        */
	if ((c=GetC) == '=') {			   /*                        */
	  Return(new_term(sym_ge, NIL, NIL), L_GE);/*                        */
	}					   /*                        */
	UnGetC(c);				   /*                        */
	Return(SymCharTerm('>'), L_GT);		   /*                        */
	  					   /*                        */
      case '<':					   /*                        */
	if ((c=GetC) == '=') {			   /*                        */
	  Return(new_term(sym_le, NIL, NIL), L_LE);/*                        */
	}					   /*                        */
	UnGetC(c);				   /*                        */
	Return(SymCharTerm('<'), L_LT);		   /*                        */
	  					   /*                        */
      case 'a': case 'b': case 'c': case 'd':	   /*                        */
      case 'e': case 'f': case 'g': case 'h':	   /*                        */
      case 'i': case 'j': case 'k': case 'l':	   /*                        */
      case 'm': case 'n': case 'o': case 'p':	   /*                        */
      case 'q': case 'r': case 's': case 't':	   /*                        */
      case 'u': case 'v': case 'w': case 'x':	   /*                        */
      case 'y': case 'z':			   /*                        */
      case 'A': case 'B': case 'C': case 'D':	   /*                        */
      case 'E': case 'F': case 'G': case 'H':	   /*                        */
      case 'I': case 'J': case 'K': case 'L':	   /*                        */
      case 'M': case 'N': case 'O': case 'P':	   /*                        */
      case 'Q': case 'R': case 'S': case 'T':	   /*                        */
      case 'U': case 'V': case 'W': case 'X':	   /*                        */
      case 'Y': case 'Z':			   /*                        */
      case '$': case '@': case '_': case '.':	   /*                        */
	{ StringBuffer *sb = sbopen();		   /*                        */
	  String s;				   /*                        */
	  SymDef sym;				   /*                        */
	  sbputc((char)c ,sb);			   /*                        */
	  for (c = GetC;			   /*                        */
	       isalpha(c) || isdigit(c) || c == '_' || c == '.';/*           */
	       c = GetC) 			   /*                        */
	  { sbputc((char)c ,sb); }		   /*                        */
	  UnGetC(c);				   /*                        */
	  s = symbol((String)sbflush(sb));	   /*                        */
	  sbclose(sb);				   /*                        */
 						   /*                        */
	  sym = get_bind(b, s);			   /*                        */
	  if (sym)
	  { yylval = SymTerm(sym);	   	   /*                        */
	    c 	   = SymOp(sym);		   /*                        */
	  } else {
	    c = L_FIELD;
	  }
	  if (yylval == NIL)			   /*                        */
	  { yylval = FieldTerm(s);		   /*                        */
	  }
#ifdef DEBUG_PARSER
	  printf("--- scan: word %s 0x%x\n",	   /*                        */
		 (char*)s, c);	   		   /*                        */
#endif
	  return c;	   			   /*                        */
	}					   /*                        */
 						   /*                        */
      default:					   /*                        */
	yylval = SymCharTerm(c);		   /*                        */
	return c; 				   /*                        */
    }						   /*                        */
    return c < 0 ? EOF : c; 			   /*                        */
  }						   /*                        */
  return EOF;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_list()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	t	
** Returns:	
**___________________________________________________			     */
static Term read_list(b, t)			   /*                        */
  Binding b;					   /*                        */
  Term t;					   /*                        */
{ int c;					   /*                        */
  Term a;					   /*                        */
  Term *tp;					   /*                        */
  int car = 1;					   /*                        */
 						   /*                        */
  for (a = read_expr(b);			   /*                        */
       a != term_eof;				   /*                        */
       a = read_expr(b))			   /*                        */
  { if (car)					   /*                        */
    { car    = 0;				   /*                        */
      Car(t) = a;				   /*                        */
      tp     = &Cdr(t);				   /*                        */
    } else {					   /*                        */
      *tp = Cons(a, NIL);			   /*                        */
      tp  = &Cdr(*tp);				   /*                        */
    }						   /*                        */
    c = scan(b);				   /*                        */
    if (c == ']') return t;		   	   /*                        */
    if (c != ',') Error("Missing comma", 0, 0);	   /*                        */
  }						   /*                        */
  Error("Unclosed list", 0, 0);	   	   	   /*                        */
  return NIL;					   /* This will never happen */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_builtin()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	Term t	
** Returns:	
**___________________________________________________			     */
static Term read_builtin(b, t)	   		   /*                        */
  Binding b;					   /*                        */
  Term t;					   /*                        */
{ int c;					   /*                        */
  						   /*                        */
  for (c = scan(b); c > 0; c = scan(b))	   	   /*                        */
  {						   /*                        */
#ifdef DEBUG_PARSER
    fprintf(stderr, "--- read_builtin %s %x\n", tag_id(c), c);/*             */
#endif
    if (c == '=' || c == L_SET)		   	   /*                        */
    {						   /*                        */
#ifdef DEBUG_PARSER
      fputs("--- skip =\n", stderr);		   /*                        */
#endif
    } else if (c == '{')		   	   /*                        */
    { return Cons(t, Cons(scan_block(), NIL));	   /*                        */
    } else if (L_IS_OPERATOR(c)		   	   /*                        */
	       || c == ';'			   /*                        */
	       || c == ')'			   /*                        */
	       || c == ']') {		   	   /*                        */
      unscan(c, yylval);			   /*                        */
      return t;					   /*                        */
    } else {					   /*                        */
      unscan(c, yylval);			   /*                        */
      return Cons(t, Cons(read_expr(b),NIL));	   /*                        */
    }						   /*                        */
  }						   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	reduce()
** Type:	static TStack
** Purpose:	Analyze the stack and make a tree of the sequential
**		operators and terms.
**		
** Arguments:
**	stack	
** Returns:	
**___________________________________________________			     */
static TStack reduce(stack)			   /*                        */
  TStack stack;					   /*                        */
{ TStack current, prev;				   /*                        */
  Term t;					   /*                        */
  int n, op;					   /*                        */
   						   /*                        */
#ifdef DEBUG_PARSER
  fputs("--- reduce\n", stderr);		   /*                        */
#endif
  for (current = stack;				   /*                        */
       current && StackPrev(current);		   /*                        */
       current = StackPrev(current))		   /*                        */
  { prev = StackPrev(current);		   	   /*                        */
    if (StackChar(prev) == L_MINUS		   /*                        */
	&& (StackPrev(prev) == NULL		   /*                        */
	    || L_IS_OPERATOR(StackChar(StackPrev(prev)))))/*                 */
    { if ( TSym(StackTerm(current)) == sym_number )/*                        */
      { TNumber(StackTerm(current)) =		   /*                        */
	  -TNumber(StackTerm(current));		   /*                        */
      } else {					   /*                        */
	StackTerm(current) = Cons(StackTerm(prev), /*                        */
				  Cons(StackTerm(current),/*                 */
				       NIL));	   /*                        */
	StackChar(current) = L_LIST;		   /*                        */
      }						   /*                        */
      StackPrev(current) = ts_pop(StackPrev(current));/*                     */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
#ifdef DEBUG_PARSER
      fputs("--- minus processed\n", stderr);	   /*                        */
      dump_tstack(stderr, stack);		   /*                        */
#endif
  while (StackPrev(stack))			   /*                        */
  { n = 0x400;				   	   /*                        */
    for (current = StackPrev(stack);		   /*                        */
	 current;				   /*                        */
	 current = StackPrev(current))		   /*                        */
    { op = StackChar(current);		   	   /*                        */
#ifdef DEBUG_PARSER
      fprintf(stderr,"--- op = 0x%x\n", op);   	   /*                        */
#endif
      if (op > n) n = op;		   	   /*                        */
    }						   /*                        */
#ifdef DEBUG_PARSER
    fprintf(stderr,"--- n = 0x%x\n", n);   	   /*                        */
#endif
    if (n <= 0x400)				   /*                        */
      Error("Missing operator after ",		   /*                        */
	    TermName(StackTerm(stack)), 0);	   /*                        */
    						   /*                        */
    for (current = stack;			   /*                        */
	 current && StackPrev(current);		   /*                        */
	 current = StackPrev(current))		   /*                        */
    { prev = StackPrev(current);		   /*                        */
      if (StackChar(prev) != n) continue;	   /*                        */
#ifdef DEBUG_PARSER
      fprintf(stderr,"--- reducing at 0x%x\n", n); /*                        */
      dump_tstack(stderr, stack);		   /*                        */
#endif
      t = Cons(StackTerm(prev), NIL);		   /*                        */
       						   /*                        */
      if (L_IS_BINARY(n))			   /*                        */
      {						   /*                        */
	if (L_IS_BINARY(StackChar(StackPrev(prev))))/*                       */
	{ Error("First operator for ",		   /*                        */
		TermName(StackTerm(prev)),	   /*                        */
		" missing");			   /*                        */
	}					   /*                        */
 						   /*                        */
	Cdr(t) = Cons(NIL,			   /*                        */
		      Cons(StackTerm(current),	   /*                        */
			   NIL));		   /*                        */
	StackPrev(current) = ts_pop(prev);	   /*                        */
	Car(Cdr(t)) = StackTerm(StackPrev(current));/*                       */
      } else {					   /*                        */
        Cdr(t) = Cons(StackTerm(current), NIL);	   /*                        */
      }						   /*                        */
      StackTerm(current) = t;			   /*                        */
      StackChar(current) = L_LIST;		   /*                        */
      StackPrev(current) = ts_pop(StackPrev(current));/*                     */
#ifdef DEBUG_PARSER
      fputs("--- pop\n", stderr);		   /*                        */
      dump_tstack(stderr, stack);		   /*                        */
#endif
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
#ifdef DEBUG_PARSER
  fputs("... reduced\n", stderr);		   /*                        */
#endif
  return stack;					   /*                        */
}						   /*------------------------*/

#define Shift(S,T) stack = ts_push(stack, S, T)
#ifdef DEBUG_PARSER
#undef Shift
#define Shift(S,T) stack = ts_push(stack, S, T);	\
  fprintf(stderr, "--- shift %s\n", tag_id(c))
#endif

/*-----------------------------------------------------------------------------
** Function:	read_expr()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
static Term read_expr(b)			   /*                        */
  Binding b;					   /*                        */
{ int c;					   /*                        */
  TStack stack = StackNULL;			   /*                        */
 						   /*                        */
  for (c = scan(b); c && c != EOF; c = scan(b))	   /*                        */
  {						   /*                        */
#ifdef DEBUG_PARSER
    fprintf(stderr, "--- read_expr: '%s' 0x%x\n",  /*                        */
	    tag_id(c), c);		   	   /*                        */
#endif
    switch (c)					   /*                        */
    { case '{':					   /*                        */
	{					   /*                        */
	  int lno = linenum;			   /*                        */
	  Term t = read_expr(b);		   /*                        */
	  c	 = scan(b);		   	   /*                        */
	  if (c != '}')			   	   /*                        */
	  { linenum = lno;			   /*                        */
	    Error("Missing } before ",		   /*                        */
		  tag_id(c), 0); }		   /*                        */
	  Shift(L_GROUP, t);		   	   /*                        */
	}					   /*                        */
	break;					   /*                        */
 						   /*                        */
      case '(':					   /*                        */
	{					   /*                        */
	  int lno = linenum;			   /*                        */
	  Term t  = read_expr(b);		   /*                        */
	  c	  = scan(b);		   	   /*                        */
	  if (c != ')')			   	   /*                        */
	  { linenum = lno;			   /*                        */
	    Error("Missing ) before ",		   /*                        */
		  tag_id(c), 0); }		   /*                        */
	  Shift(L_LIST, t);		   	   /*                        */
	}					   /*                        */
	break;					   /*                        */
 						   /*                        */
      case L_LIST:				   /*                        */
	Shift(L_LIST, (yylval == NIL	   	   /*                        */
		       ? NIL			   /*                        */
		       : read_list(b, yylval)));   /*                        */
	break;					   /*                        */
 						   /*                        */
      case '\'':				   /*                        */
	{ Term t = read_expr(b);		   /*                        */
	  Shift(L_QUOTE,			   /*                        */
		Cons(SymTerm(sym_quote),	   /*                        */
		     Cons(t, NIL)));    	   /*                        */
	}					   /*                        */
	break;					   /*                        */
						   /*                        */
      case L_STRING:				   /*                        */
      case L_NUMBER:				   /*                        */
      case L_FIELD:				   /*                        */
      case L_QUOTE:				   /*                        */
      case L_TRUE:				   /*                        */
      case L_FALSE:				   /*                        */
      case L_NOT:				   /*                        */
	Shift(c, yylval);		   	   /*                        */
	break;					   /*                        */
 						   /*                        */
      case L_MINUS:				   /*                        */
      case '-':					   /*                        */
	Shift(L_MINUS, yylval);		   	   /*                        */
	break;					   /*                        */
	  					   /*                        */
      default:					   /*                        */
	if (L_IS_OPERATOR(c)) {  		   /*                        */
	  if (L_IS_BINARY(c) && stack == StackNULL)/*                        */
	  { Error("Unexpected operator ",	   /*                        */
		  tag_id(c), 0); }		   /*                        */
	  Shift(c, yylval);			   /*                        */
						   /*                        */
	} else {				   /*                        */
	  unscan(c, yylval);			   /*                        */
	  return stack				   /*                        */
	    ? StackTerm(reduce(stack))		   /*                        */
	    : NIL;				   /*                        */
	}					   /*                        */
    }						   /*                        */
  }						   /*                        */
					   	   /*                        */
  if (stack)			   		   /*                        */
  { c = StackChar(stack);			   /*                        */
    if (L_IS_OPERATOR(c)) {			   /*                        */
      Error("Missing operator for ", tag_id(c), 0);/*                        */
    }						   /*                        */
    stack = reduce(stack);			   /*                        */
    return StackTerm(stack);			   /*                        */
  }	   					   /*                        */
  return term_eof;				   /*                        */
}						   /*------------------------*/
#undef Shift

/*-----------------------------------------------------------------------------
** Function:	read_cmd()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
static Term read_cmd(b)				   /*                        */
  Binding b;					   /*                        */
{ register int c;			   	   /*                        */
 						   /*                        */
  for (c = scan(b); c >= 0; c = scan(b))	   /*                        */
  { 						   /*                        */
    if (c == L_FIELD) {				   /*                        */
      SymDef sym = TSym(yylval);		   /*                        */
      String s = (sym == sym_field		   /*                        */
		  ? TString(yylval)		   /*                        */
		  : SymName(sym));		   /*                        */
      if (get_bind(b, s))			   /*                        */
      { return read_builtin(b, yylval); }	   /*                        */
    }						   /*                        */
 						   /*                        */
    if (c != ';')			   	   /*                        */
    { unscan(c, yylval);			   /*                        */
      return read_expr(b);			   /*                        */
    }						   /*                        */
  }						   /*                        */
   						   /*                        */
  return term_eof;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_loop()
** Type:	int
** Purpose:	
**		
** Arguments:
**	filename	
** Returns:	
**___________________________________________________			     */
int read_loop(b, file, action)		   	   /*                        */
  Binding b;				   	   /*                        */
  char * file;				   	   /*                        */
  int (*action)_ARG((Binding b, Term t));	   /*                        */
{ Term term;					   /*                        */
 						   /*                        */
  if (file == NULL) {			   	   /*                        */
    Error("No input file given", 0, 0);	   	   /*                        */
  }						   /*                        */
  linenum    = 1;				   /*                        */
  filename   = file;				   /*                        */
  look_ahead = NIL;				   /*                        */
  in_file    = fopen(file, "r");		   /*                        */
  if (in_file == NULL) {			   /*                        */
    ErrorNF("File could not be opened: ", file);   /*                        */
  }						   /*                        */
   						   /*                        */
  for (term = read_cmd(b);			   /*                        */
       term != term_eof;			   /*                        */
       term = read_cmd(b))			   /*                        */
  { (*action)(b, term); }			   /*                        */
 						   /*                        */
  fclose(in_file);				   /*                        */
 						   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
