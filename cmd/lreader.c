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

#undef DEBUG 

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <bibtool/sbuffer.h>
#include <bibtool/symbols.h>
#include <bibtool/type.h>
#include <bibtool/error.h>
#include "lcore.h"
#include "tstack.h"
#include "binding.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

static int scan _ARG((Binding b));		   /*                        */
static Term scan_block();			   /*                        */
static Term scan_string _ARG((short int type, char c));/*                    */
static Term read_list _ARG((Binding b, Term t));   /*                        */
static Term read_builtin _ARG((Binding b, Term t));/*                        */
static TStack reduce _ARG((TStack ts));		   /*                        */
int read_loop _ARG((Binding b, char* file, int (*action)(Binding binding, Term t) ));
static Term read_cmd _ARG((Binding b));		   /*                        */
static Term read_expr _ARG((Binding b, TStack ts));/*                        */
static Term read_args _ARG((Binding b, Term t, int sep, int term));/*        */

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


 static Term yylval;				   /*                        */
 static char * filename;			   /*                        */
 static FILE * in_file;				   /*                        */
 static int  linenum;				   /*                        */
 static int  c_look_ahead = 0;		   	   /*                        */
 static Term look_ahead = NIL;			   /*                        */


#define unscan(C,T)	(c_look_ahead = (C), look_ahead = (T))
#define GetC		fgetc(in_file)
#define UnGetC(C)	ungetc(C, in_file)
#define Shift(S,T)	stack = ts_push(stack, S, T);		\
			DebugPrint2("shift ", tag_id(c))
#define NewStack(S,T)	ts_push(StackNULL, S, T)

/*-----------------------------------------------------------------------------
** Function:	scan_block()
** Type:	Term
** Purpose:	Scan a block in balanced braces.
**		
** Arguments:	none
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
  t = StringTerm((String)sbflush(sb));      	   /*                        */
  sbclose(sb);				   	   /*                        */
  return t;			   	   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	scan_string()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	type	
**	c_end	
** Returns:	
**___________________________________________________			     */
static Term scan_string(type, c_end)		   /*                        */
  short int type;				   /*                        */
  char   c_end;					   /*                        */
{ Term t;					   /*                        */
  StringBuffer *sb = sbopen();		   	   /*                        */
  register int c;				   /*                        */
  int lno = linenum;				   /*                        */
  						   /*                        */
  for (c = GetC; c != c_end; c = GetC)	   	   /*                        */
  { if (c == '\\')			   	   /*                        */
    { c = GetC;				   	   /*                        */
      switch (c)			   	   /*                        */
      { case EOF:				   /*                        */
	case 0:				   	   /*                        */
	  linenum = lno;			   /*                        */
	  Error("Missing closing delimiter ",	   /*                        */
		(c_end =='"' ? "\"": "`"), 0);	   /*                        */
	case 'n': sbputc('\n', sb); break;	   /*                        */
	case 'r': sbputc('\r', sb); break;	   /*                        */
	case 'f': sbputc('\f', sb); break;	   /*                        */
	case 't': sbputc('\t', sb); break;	   /*                        */
	case 'b': sbputc('\b', sb); break;	   /*                        */
	default:  sbputc(c, sb);		   /*                        */
      }					   	   /*                        */
    } else if (c <= 0)			   	   /*                        */
    { linenum = lno;				   /*                        */
      Error("Missing closing delimiter ",	   /*                        */
	    (c_end =='"' ? "\"": "`"), 0);	   /*                        */
    } else{				   	   /*                        */
      sbputc(c, sb);			   	   /*                        */
    }					   	   /*                        */
  }					   	   /*                        */
					       	   /*                        */
  t = new_t_string(type, symbol((String)sbflush(sb)));/*                     */
  sbclose(sb);				   	   /*                        */
  return t;			   		   /*                        */
}						   /*------------------------*/

#define Return(VAL, C)	yylval = (VAL); return C
#define ReturnTerm(C)	yylval = NewTerm(C); return C

/*-----------------------------------------------------------------------------
** Function:	scan()
** Type:	SymDef
** Purpose:	Scan the input stream in_file for the next token.
**		The token code is returned and the token value is stored in
**		the global variable yylval.
** Arguments:
**	b	the bindings in effect
** Returns:	the token code
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
  { DebugPrintF3("scan %c %d\n",c,c);	   	   /*                        */
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
	Return(scan_string(L_STRING ,'"'),	   /*                        */
	       L_STRING);			   /*                        */
	  					   /*                        */
      case '`':				   	   /*                        */
	Return(scan_string(L_FIELD ,'`'),	   /*                        */
	       L_FIELD);  			   /*                        */
 	  					   /*                        */
      case '+':					   /*                        */
	ReturnTerm(L_PLUS);  	   		   /*                        */
	  					   /*                        */
      case '-':					   /*                        */
	ReturnTerm(L_MINUS);			   /*                        */
	  					   /*                        */
      case '*':					   /*                        */
	ReturnTerm(L_TIMES);	   		   /*                        */
	  					   /*                        */
      case '/':					   /*                        */
	ReturnTerm(L_DIV);    	   		   /*                        */
	  					   /*                        */
      case '\'':				   /*                        */
	ReturnTerm(L_QUOTE);	   		   /*                        */
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
	  Return(NumberTerm(num), L_NUMBER);	   /*                        */
	}					   /*                        */
	  					   /*                        */
      case '1': case '2': case '3': case '4':	   /*                        */
      case '5': case '6': case '7': case '8':	   /*                        */
      case '9':					   /*                        */
	{ long num = c - '0';			   /*                        */
	  for (c = GetC; c >= '0' && c <= '9'; c = GetC)/*                   */
	  { num = num * 10 + c - '0'; }	   	   /*                        */
	  UnGetC(c);				   /*                        */
	  Return(NumberTerm(num), L_NUMBER);	   /*                        */
	}					   /*                        */
	  					   /*                        */
      case '[':					   /*                        */
	for (c = GetC; c && isspace(c); c = GetC); /*                        */
	if (c == ']') {	Return(NIL, L_CONS); }	   /*                        */
	UnGetC(c);				   /*                        */
	Return(Cons1(NIL), L_CONS);		   /*                        */
	  					   /*                        */
      case '=':					   /*                        */
	if ((c=GetC) == '=') { ReturnTerm(L_EQ); } /*                        */
	UnGetC(c);				   /*                        */
	ReturnTerm(L_SET);	   	   	   /*                        */
	  					   /*                        */
      case '&':					   /*                        */
	if ((c=GetC) == '&') { ReturnTerm(L_AND); }/*                        */
	UnGetC(c);				   /*                        */
	return '&'; 	   	   		   /*                        */
	  					   /*                        */
      case '|':					   /*                        */
	if ((c=GetC) == '|') { ReturnTerm(L_OR); } /*                        */
	UnGetC(c);				   /*                        */
	return '|'; 	   	   		   /*                        */
	  					   /*                        */
      case '!':					   /*                        */
	if ((c=GetC) == '=') { ReturnTerm(L_NE); } /*                        */
	ReturnTerm(L_NOT);	   		   /*                        */
	  					   /*                        */
      case '>':					   /*                        */
	if ((c=GetC) == '=') { ReturnTerm(L_GE); } /*                        */
	UnGetC(c);				   /*                        */
	ReturnTerm(L_GT);	   	   	   /*                        */
	  					   /*                        */
      case '<':					   /*                        */
	if ((c=GetC) == '=') { ReturnTerm(L_LE); } /*                        */
	UnGetC(c);				   /*                        */
	ReturnTerm(L_LT);	   	   	   /*                        */
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
	  sym = get_bind(b, s);			   /*                        */
	  if (sym)				   /*                        */
	  { c 	   = SymOp(sym);		   /*                        */
	    yylval = SymTerm(sym);	   	   /*                        */
	    if (yylval == NIL && c != L_CONS)	   /*                        */
	      yylval = (c == L_FIELD		   /*                        */
			? FieldTerm(s)		   /*                        */
			: NewTerm(c));		   /*                        */
	    DebugPrintF3("scan: word %s 0x%x\n",   /*                        */
		   (char*)s, c);		   /*                        */
	    return c;	   			   /*                        */
	  }					   /*                        */
	  Return(FieldTerm(s), L_FIELD);	   /*                        */
	}					   /*                        */
 						   /*                        */
    }						   /*                        */
    DebugPrintF3("scan: default %s 0x%x\n",	   /*                        */
		 tag_id(c), c);		   	   /*                        */
    return c <= 0 ? EOF : c; 			   /*                        */
  }						   /*                        */
  return EOF;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_list()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term tamplate
** Returns:	
**___________________________________________________			     */
static Term read_list(binding, term)		   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term *tp = &term;				   /*                        */
  register int c;				   /*                        */
  register Term a;				   /*                        */
  						   /*                        */
  for (a = read_expr(binding, StackNULL);	   /*                        */
       a != term_eof;				   /*                        */
       a  = read_expr(binding, StackNULL))	   /*                        */
  { if (tp == &term) { Car(term) = a;  }	   /*                        */
    else {	       *tp = Cons1(a); }	   /*                        */
    tp = &Cdr(*tp);				   /*                        */
    c  = scan(binding);				   /*                        */
    if (c == ']') return term;		   	   /*                        */
    if (c != ',') Error("Missing comma instead of ",/*                       */
			tag_id(c), 0);	   	   /*                        */
  }						   /*                        */
  Error("Unclosed list", 0, 0);	   	   	   /*                        */
  return NIL;					   /* This will never happen */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_args()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
**	separator	the separating character
**	terminal	ther terminating character
** Returns:	
**___________________________________________________			     */
static Term read_args(binding, term, separator, terminal)/*                  */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
  int separator;				   /*                        */
  int terminal;					   /*                        */
{ int lno = linenum;				   /*                        */
  int c	  = scan(binding);			   /*                        */
  Term x  = term;				   /*                        */
  Term a;					   /*                        */
 						   /*                        */
  for (;;)					   /*                        */
  {						   /*                        */
    while (c == separator) { c = scan(binding); }  /*                        */
    if (c == terminal) return term;		   /*                        */
    unscan(c, yylval);				   /*                        */
    a = read_expr(binding, StackNULL);		   /*                        */
    if (a == term_eof)				   /*                        */
    { linenum = lno;				   /*                        */
      Error("Missing ", tag_id(terminal), 0);	   /*                        */
    }						   /*                        */
 						   /*                        */
    Cdr(x) = Cons1(a);			   	   /*                        */
    x = Cdr(x);				   	   /*                        */
    c = scan(binding);				   /*                        */
    if (c == terminal) return term;		   /*                        */
    if (c != separator)				   /*                        */
      Error("Missing separator instead of ",	   /*                        */
	    tag_id(c), 0);			   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_builtin()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	b	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
static Term read_builtin(b, term)		   /*                        */
  Binding b;					   /*                        */
  Term term;					   /*                        */
{ register int c;				   /*                        */
  						   /*                        */
  TType(term) = L_FUNCALL;			   /*                        */
  DebugPrintF2("read_builtin (%s)\n",		   /*                        */
	       (char*)TString(term));		   /*                        */
  for (c = scan(b); c > 0; c = scan(b))	   	   /*                        */
  {						   /*                        */
    DebugPrintF3("read_builtin %s %x\n", tag_id(c), c);/*                    */
    if (c == '=' || c == L_SET)		   	   /*                        */
    { DebugPrint1("--- skip =\n");		   /*                        */
      continue;					   /*                        */
    } else if (c == '{')		   	   /*                        */
    { Cdr(term) = Cons1(scan_block());		   /*                        */
    } else if ((c != L_MINUS && L_IS_OPERATOR(c))  /*                        */
	       || c == ';'			   /*                        */
	       || c == ')'			   /*                        */
	       || c == ']') {		   	   /*                        */
      unscan(c, yylval);			   /*                        */
    } else {					   /*                        */
      unscan(c, yylval);			   /*                        */
      Cdr(term) = Cons1(read_expr(b, StackNULL));  /*                        */
    }						   /*                        */
    break;				   	   /*                        */
  }						   /*                        */
  return term;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	reduce()
** Type:	static TStack
** Purpose:	Analyze the stack and make a tree of the sequential
**		operators and terms.
**		
** Arguments:
**	stack	the term stack
** Returns:	
**___________________________________________________			     */
static TStack reduce(stack)			   /*                        */
  TStack stack;					   /*                        */
{ TStack current, prev;				   /*                        */
  Term t;					   /*                        */
  int n, op;					   /*                        */
   						   /*                        */
  DebugPrint1("reduce\n");		   	   /*                        */
 						   /*                        */
  for (current = stack;				   /*                        */
       current && StackPrev(current);		   /*                        */
       current = StackPrev(current))		   /*                        */
  { prev = StackPrev(current);		   	   /*                        */
    if (StackChar(prev) == L_MINUS		   /*                        */
	&& (StackPrev(prev) == NULL		   /*                        */
	    || L_IS_OPERATOR(StackChar(StackPrev(prev)))))/*                 */
    { if ( TType(StackTerm(current)) == L_NUMBER ) /*                        */
      { TNumber(StackTerm(current)) =		   /*                        */
	  -TNumber(StackTerm(current));		   /*                        */
      } else {					   /*                        */
	Term t	 = StackTerm(prev);		   /*                        */
	TType(t) = L_UMINUS;			   /*                        */
	Cdr(t)   = Cons1(StackTerm(current)); 	   /*                        */
						   /*                        */
	StackTerm(current) = t;	   		   /*                        */
	StackChar(current) = L_UMINUS;		   /*                        */
      }						   /*                        */
      StackPrev(current) = ts_pop(StackPrev(current));/*                     */
      DebugPrint1("--- minus processed\n");	   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
#ifdef DEBUG
  dump_tstack(stderr, stack);		   	   /*                        */
  fputs("---\n", stderr);	   		   /*                        */
#endif
  while (StackPrev(stack))			   /*                        */
  { n = 0x400;				   	   /*                        */
    for (current = StackPrev(stack);		   /*                        */
	 current;				   /*                        */
	 current = StackPrev(current))		   /*                        */
    { op = StackChar(current);		   	   /*                        */
      DebugPrintF2("op = 0x%x\n", op);   	   /*                        */
      if (op > n) n = op;		   	   /*                        */
    }						   /*                        */
    DebugPrintF2("n = 0x%x\n", n);   	   	   /*                        */
    if (n <= 0x400)				   /*                        */
      Error("Missing operator after ",		   /*                        */
	    TermIsField(StackTerm(stack)) 	   /*                        */
	    ? TString(StackTerm(stack))		   /*                        */
	    : tag_id(TType(StackTerm(stack))), 0); /*                        */
					       	   /*                        */
    for (current = stack;			   /*                        */
	 current && StackPrev(current);		   /*                        */
	 current = StackPrev(current))		   /*                        */
    { prev = StackPrev(current);		   /*                        */
      if (StackChar(prev) != n) continue;	   /*                        */
      DebugPrintF2("reducing at 0x%x\n", n); 	   /*                        */
      t = StackTerm(prev);		   	   /*                        */
       						   /*                        */
      if (L_IS_BINARY(n))			   /*                        */
      {						   /*                        */
	if (L_IS_BINARY(StackChar(StackPrev(prev))))/*                       */
	{ Error("First operator for ",		   /*                        */
		tag_id(TType(StackTerm(prev))),    /*                        */
		" missing");			   /*                        */
	}					   /*                        */
 						   /*                        */
	Cdr(t) = Cons(NIL,			   /*                        */
		      Cons1(StackTerm(current)));  /*                        */
	StackPrev(current) = ts_pop(prev);	   /*                        */
	Car(Cdr(t)) = StackTerm(StackPrev(current));/*                       */
      } else {					   /*                        */
        Cdr(t) = Cons1(StackTerm(current));	   /*                        */
      }						   /*                        */
      StackTerm(current) = t;			   /*                        */
      StackChar(current) = L_CONS;		   /*                        */
      StackPrev(current) = ts_pop(StackPrev(current));/*                     */
#ifdef DEBUG
      fputs("--- pop\n", stderr);		   /*                        */
      dump_tstack(stderr, stack);		   /*                        */
#endif
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  DebugPrint1("... reduced\n");		   	   /*                        */

  return stack;					   /*                        */
}						   /*------------------------*/

#define Expect(C, MSG)	\
  if ((c=scan(binding)) != C) { Error(MSG, " instead of ", tag_id(c)); }

/*-----------------------------------------------------------------------------
** Function:	read_group()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
** Returns:	
**___________________________________________________			     */
static Term read_group(binding, msg)		   /*                        */
  Binding binding;				   /*                        */
  char * msg;					   /*                        */
{ int c;			   		   /*                        */
  Expect('{', "Missing {");			   /*                        */
  return read_args(binding,			   /*                        */
		   NewTerm(L_GROUP), 	   	   /*                        */
		   ';',		   		   /*                        */
		   '}');			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_condition()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	
**	msg	
** Returns:	
**___________________________________________________			     */
static Term read_condition(binding, msg)	   /*                        */
  Binding binding;				   /*                        */
  char * msg;					   /*                        */
{ int c;			   		   /*                        */
  Expect('(', "Missing (");			   /*                        */
  return read_args(binding,			   /*                        */
		   NewTerm(L_GROUP), 	   	   /*                        */
		   -666,			   /*                        */
		   ')');			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_mapping()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	msg	the name of the primitive
** Returns:	
**___________________________________________________			     */
static Term read_mapping(binding, msg)		   /*                        */
  Binding binding;				   /*                        */
  char *msg;					   /*                        */
{ int c;			   		   /*                        */
  Term term = NIL;				   /*                        */
  Term *tp  = &term;				   /*                        */
 						   /*                        */
  for (;;)					   /*                        */
  { Term v;					   /*                        */
    c = scan(binding);				   /*                        */
    if (c == ')') return term;			   /*                        */
    if (c != L_FIELD)				   /*                        */
      Error(msg, ": Missing variable instead of ", /*                        */
	    tag_id(c));				   /*                        */
    v	= yylval;				   /*                        */
    *tp = Cons1(v);				   /*                        */
    tp = &Cdr(*tp);				   /*                        */
 						   /*                        */
    c = scan(binding);				   /*                        */
    if (c == ')' || c == ',')			   /*                        */
    { unscan(c, yylval);			   /*                        */
      Cdr(v) = NIL;				   /*                        */
    }						   /*                        */
    else if (c 	!= ':')				   /*                        */
    { Error(msg, ": Missing : instead of ",	   /*                        */
	    tag_id(c));				   /*                        */
    }						   /*                        */
    else					   /*                        */
    { Cdr(v) = read_expr(binding, StackNULL);	   /*                        */
    }						   /*                        */
    c = scan(binding);				   /*                        */
    if (c == ')') return term;			   /*                        */
    if (c != ',')				   /*                        */
      Error(msg, ": Missing , instead of ",	   /*                        */
	    tag_id(c));				   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	read_expr()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	
**	stack	
** Returns:	
**___________________________________________________			     */
static Term read_expr(binding, stack)		   /*                        */
  Binding binding;				   /*                        */
  TStack stack;					   /*                        */
{ int c;					   /*                        */
 						   /*                        */
  for (c = scan(binding);			   /*                        */
       c > 0;				   	   /*                        */
       c = scan(binding))			   /*                        */
  {						   /*                        */
    DebugPrintF3("read_expr: '%s' 0x%x\n",  	   /*                        */
		 tag_id(c), c);		   	   /*                        */
    switch (c)					   /*                        */
    { case '{':					   /*                        */
	Shift(L_GROUP,				   /*                        */
	      read_args(binding,		   /*                        */
			NewTerm(L_GROUP), 	   /*                        */
			';',		   	   /*                        */
			'}'));	   	   	   /*                        */
	break;					   /*                        */
 						   /*                        */
      case '(':					   /*                        */
	{ int lno = linenum;			   /*                        */
	  Term t  = read_expr(binding, StackNULL); /*                        */
	  c	  = scan(binding);		   /*                        */
	  if (c != ')')			   	   /*                        */
	  { linenum = lno;			   /*                        */
	    Error("Missing ) before ",		   /*                        */
		  tag_id(c), 0); }		   /*                        */
	  Shift(L_CONS, t);		   	   /*                        */
	}					   /*                        */
	break;					   /*                        */
 						   /*                        */
      case L_CONS:				   /*                        */
	Shift(L_CONS, (yylval == NIL	   	   /*                        */
		       ? NIL			   /*                        */
		       : read_list(binding, yylval)));/*                     */
	break;					   /*                        */
 						   /*                        */
      case L_QUOTE:				   /*                        */
	Shift(L_QUOTE,				   /*                        */
	      new_term(L_QUOTE,			   /*                        */
		       NIL,			   /*                        */
		       Cons1(read_expr(binding, StackNULL))));/*             */
	break;					   /*                        */
						   /*                        */
      case L_FIELD:				   /*                        */
	{ Term t = yylval;			   /*                        */
	  c = scan(binding);			   /*                        */
	  if (c != '(')				   /*                        */
	  { unscan(c, yylval);			   /*                        */
 	    Shift(L_FIELD, t);		   	   /*                        */
	    break;				   /*                        */
	  }					   /*                        */
	  t = read_args(binding,		   /*                        */
			new_t_string(L_FUNCALL,    /*                        */
				     TString(t)),  /*                        */
			',',			   /*                        */
			')');			   /*                        */
	  Shift(L_FUNCALL, t);		   	   /*                        */
	}					   /*                        */
	break;					   /*                        */
 						   /*                        */
      case L_DEFUN:				   /*                        */
	{ Term t = yylval;		   	   /*                        */
	  Expect(L_FIELD, "Missing function name");/*                        */
	  TString(t) = TString(yylval);		   /*                        */
	  free_term(yylval);			   /*                        */
	  Expect('(', "Missing ( for defun");	   /*                        */
	  Cdr(t)  = NewTerm(L_FUNCTION);	   /*                        */
	  Cadr(t) = read_mapping(binding, "defun");/*                        */
	  Cddr(t) = read_group(binding, "defun");  /*                        */
	  Shift(L_DEFUN, t);		   	   /*                        */
	}					   /*                        */
	break;					   /*                        */
 						   /*                        */
      case L_FUNCTION:				   /*                        */
	{ Term t = yylval;		   	   /*                        */
	  Expect('(', "Missing ( for function");   /*                        */
	  Cdr(t)  = NewTerm(L_FUNCTION);	   /*                        */
	  Cadr(t) = read_mapping(binding, "function");/*                     */
	  Cddr(t) = read_group(binding, "function");/*                       */
	  Shift(L_FUNCTION, t);		   	   /*                        */
	}					   /*                        */
	break;					   /*                        */
 						   /*                        */
      case L_IF:				   /*                        */
	{ Term t = yylval;		   	   /*                        */
	  Car(t) = read_condition(binding, "if");  /*                        */
	  Cdr(t) = Cons1(read_group(binding, "if"));/*                       */
	  c = scan(binding);			   /*                        */
	  if (c	== L_ELSE)			   /*                        */
	  { Cddr(t) = read_group(binding, "else"); }/*                       */
	  else				   	   /*                        */
	  { unscan(c, yylval); }		   /*                        */
	  Shift(L_IF, t);		   	   /*                        */
	}					   /*                        */
	break;					   /*                        */
 						   /*                        */
      case L_WHILE:				   /*                        */
	{ Term t = yylval;		   	   /*                        */
	  Car(t) = read_condition(binding, "while");/*                       */
	  Cdr(t) = read_group(binding, "while");   /*                        */
	  Shift(L_WHILE, t);		   	   /*                        */
	}					   /*                        */
	break;					   /*                        */
 						   /*                        */
      case L_WITH:				   /*                        */
	{ Term t = yylval;		   	   /*                        */
	  Expect('(', "Missing ( for with");	   /*                        */
	  Car(t) = read_mapping(binding, "with");  /*                        */
	  Cdr(t) = read_group(binding, "with");	   /*                        */
	  Shift(L_WITH, t);		   	   /*                        */
	}					   /*                        */
	break;					   /*                        */
 						   /*                        */
      case L_ELSE:				   /*                        */
	Error("isolated else encountered",0,0);	   /*                        */
 						   /*                        */
      case L_STRING:				   /*                        */
      case L_NUMBER:				   /*                        */
      case L_NOT:				   /*                        */
	Shift(c, yylval);		   	   /*                        */
	break;					   /*                        */
 						   /*                        */
      case L_TRUE:				   /*                        */
	Shift(c, term_true);	   	   	   /*                        */
	break;					   /*                        */
 						   /*                        */
      case L_FALSE:				   /*                        */
	Shift(c, term_false);	   	   	   /*                        */
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

/*-----------------------------------------------------------------------------
** Function:	read_cmd()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
** Returns:	
**___________________________________________________			     */
static Term read_cmd(binding)			   /*                        */
  Binding binding;				   /*                        */
{ register int c;			   	   /*                        */
  TStack stack = StackNULL;			   /*                        */
 						   /*                        */
  for (c = scan(binding); c >= 0; c = scan(binding))/*                       */
  { 						   /*                        */
    switch (c)					   /*                        */
    { case ';':					   /*                        */
	continue;				   /*                        */
      case L_FIELD:				   /*                        */
	{ Term val = yylval;			   /*                        */
	  SymDef sym = get_bind(binding,	   /*                        */
				TString(val));	   /*                        */
	  c = scan(binding);			   /*                        */
	  if (c == '(')				   /*                        */
	  { val = read_args(binding,		   /*                        */
			    new_t_string(L_FUNCALL,/*                        */
					 TString(val)),/*                    */
			    ',',		   /*                        */
			    ')');		   /*                        */
	    Shift(TType(val), val);	   	   /*                        */
	  }					   /*                        */
	  else					   /*                        */
	  { unscan(c, yylval);			   /*                        */
	    if (sym && (SymFlags(sym)&SYM_BUILTIN))/*                        */
	    { return read_builtin(binding, val); } /*                        */
	    Shift(L_FIELD, val);		   /*                        */
	  }					   /*                        */
	}					   /*                        */
	break;					   /*                        */
      case '(':					   /*                        */
      case '{':					   /*                        */
	unscan(c, yylval);			   /*                        */
	break;					   /*                        */
      default:					   /*                        */
	if ( c >= 0 && c <= 0xff		   /*                        */
	     && yylval == NIL)		   	   /*                        */
	  Error("Unexpected character '",	   /*                        */
		tag_id(c),			   /*                        */
		"' found");			   /*                        */
	unscan(c, yylval);			   /*                        */
    }					   	   /*                        */
    return read_expr(binding, stack);	   	   /*                        */
  }						   /*                        */
   						   /*                        */
  return term_eof;				   /*                        */
}						   /*------------------------*/
#undef Shift

/*-----------------------------------------------------------------------------
** Function:	read_loop()
** Type:	int
** Purpose:	
**		
** Arguments:
**	binding	
**	file	
**	action	
** Returns:	
**___________________________________________________			     */
int read_loop(binding, file, action)		   /*                        */
  Binding binding;				   /*                        */
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
  for (term = read_cmd(binding);		   /*                        */
       term != term_eof;			   /*                        */
       term = read_cmd(binding))		   /*                        */
  { (*action)(binding, term); }			   /*                        */
 						   /*                        */
  fclose(in_file);				   /*                        */
 						   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
