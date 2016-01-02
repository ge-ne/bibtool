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
#include <bibtool/error.h>
#include "tstack.h"
#include "term.h"
#include "symdef.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

 static SymDef scan();
 int read_loop();
 static Term read_cmd();
 static Term read_expr();
 static Term yylval;

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


 static Term yylval;				   /*                        */
 static char * filename;			   /*                        */
 static FILE * in_file;				   /*                        */
 static int linenum;				   /*                        */
 static SymDef sd_look_ahead = 0L;		   /*                        */
 static Term look_ahead = NIL;			   /*                        */

#define unscan(S,T) (sd_look_ahead = S, look_ahead = T)

#define Error(X,Y,Z)					\
	error(ERR_ERROR|ERR_FILE|ERR_EXIT,(String)X,	\
	      (String)Y,(String)Z,(String)0,(String)0,linenum,filename)
#define ErrorNF(X,Y)					\
	error(ERR_ERROR|ERR_EXIT,(String)X,		\
	      (String)Y,(String)0,(String)0,(String)0,0,NULL)

#define GetC fgetc(in_file)
#define UnGetC(C) ungetc(C, in_file)

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

#define Return(VAL) yylval = (VAL); return TSym(yylval)

/*-----------------------------------------------------------------------------
** Function:	scan()
** Type:	SymDef
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
static SymDef scan()				   /*                        */
{ int c;					   /*                        */
 						   /*                        */
  if (sd_look_ahead)			   	   /*                        */
  { SymDef sd	  = sd_look_ahead;		   /*                        */
    sd_look_ahead = SymDefNull;			   /*                        */
    yylval	  = look_ahead;			   /*                        */
    look_ahead	  = NIL;			   /*                        */
    return sd;			   		   /*                        */
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
	Return(scan_string(sym_string ,'"'));	   /*                        */
	  					   /*                        */
      case '`':				   	   /*                        */
	Return(scan_string(sym_field ,'`'));	   /*                        */
	  					   /*                        */
#ifdef NEVER
      case '{':					   /*                        */
	Return(scan_block());			   /*                        */
#endif
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
	  Return(new_term_num(num));		   /*                        */
	}					   /*                        */
	  					   /*                        */
      case '1': case '2': case '3': case '4':	   /*                        */
      case '5': case '6': case '7': case '8':	   /*                        */
      case '9':					   /*                        */
	{ long num = c - '0';			   /*                        */
	  for (c = GetC; c >= '0' && c <= '9'; c = GetC)/*                   */
	  { num = num * 10 + c - '0'; }	   	   /*                        */
	  UnGetC(c);				   /*                        */
	  Return(new_term_num(num));		   /*                        */
	}					   /*                        */
	  					   /*                        */
      case '[':					   /*                        */
	for (c = GetC; c && isspace(c); c = GetC); /*                        */
	if (c == ']') {				   /*                        */
	  yylval = NIL;				   /*                        */
	  return sym_cons;			   /*                        */
	}					   /*                        */
	UnGetC(c);				   /*                        */
	Return(Cons(NIL, NIL));   	   	   /*                        */
	  					   /*                        */
      case '=':					   /*                        */
	if ((c=GetC) == '=') {			   /*                        */
	  Return(new_term(sym_eq, NIL, NIL));	   /*                        */
	}					   /*                        */
	UnGetC(c);				   /*                        */
	Return(SymCharTerm('=')); 	   	   /*                        */
	  					   /*                        */
      case '&':					   /*                        */
	if ((c=GetC) == '&') {			   /*                        */
	  Return(new_term(sym_and, NIL, NIL));	   /*                        */
	}					   /*                        */
	UnGetC(c);				   /*                        */
	Return(SymCharTerm('&')); 	   	   /*                        */
	  					   /*                        */
      case '|':					   /*                        */
	if ((c=GetC) == '|') {			   /*                        */
	  Return(new_term(sym_or, NIL, NIL));	   /*                        */
	}					   /*                        */
	UnGetC(c);				   /*                        */
	Return(SymCharTerm('|')); 	   	   /*                        */
	  					   /*                        */
      case '!':					   /*                        */
	if ((c=GetC) == '=') {			   /*                        */
	  Return(new_term(sym_ne, NIL, NIL));	   /*                        */
	}					   /*                        */
	Return(SymTerm(sym_not));		   /*                        */
	  					   /*                        */
      case '>':					   /*                        */
	if ((c=GetC) == '=') {			   /*                        */
	  Return(new_term(sym_ge, NIL, NIL));	   /*                        */
	}					   /*                        */
	UnGetC(c);				   /*                        */
	Return(SymCharTerm('>'));		   /*                        */
	  					   /*                        */
      case '<':					   /*                        */
	if ((c=GetC) == '=') {			   /*                        */
	  Return(new_term(sym_le, NIL, NIL));	   /*                        */
	}					   /*                        */
	UnGetC(c);				   /*                        */
	Return(SymCharTerm('<'));		   /*                        */
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
	  sbputc((char)c ,sb);			   /*                        */
	  for (c = GetC;			   /*                        */
	       isalpha(c) || c == '_' || c == '.'; /*                        */
	       c = GetC) 			   /*                        */
	  { sbputc((char)c ,sb); }		   /*                        */
	  UnGetC(c);				   /*                        */
	  s = symbol((String)sbflush(sb));	   /*                        */
	  sbclose(sb);				   /*                        */
 						   /*                        */
#define RSC_FIRST(C)	    case C:
#define RSC_NEXT(C)	    break; case C:
#define ON(A)		    if (strcmp((char*)s, A) == 0)
#define RscNumeric(A,B,C,D) ON(A) {yylval = new_t_string(sym_r_n, s);}
#define RscString(A,B,C,D)  ON(A) {yylval = new_t_string(sym_r_s, s);}
#define RscBoolean(A,B,C,D) ON(A) {yylval = new_t_string(sym_r_b, s);}
#define RscByFct(A,B,C)     ON(A) {yylval = new_t_string(sym_r_f, s);}
#define RscTerm(A,B)	    ON(A) {B;}
#define RSC_INIT_NIL	    yylval = NIL;return sym_cons
#define RSC_INIT_TRUE	    yylval = term_true
#define RSC_INIT_FALSE	    yylval = term_false
#define RSC_INIT_AND	    yylval = term_and
#define RSC_INIT_OR	    yylval = term_or
#define RSC_INIT_NOT	    yylval = term_not
#define RSC_INIT_MOD	    yylval = term_mod
#define RSC_INIT_LIKE	    yylval = term_like
#define RSC_INIT_ILIKE	    yylval = term_ilike
 						   /*                        */
	  switch (*s) {				   /*                        */
#include <bibtool/resource.h>
	  }					   /*                        */
	  if (yylval == NIL)		   	   /*                        */
	  { yylval = FieldTerm(s); }		   /*                        */
	  return TSym(yylval);			   /*                        */
	}					   /*                        */
 						   /*                        */
      default:					   /*                        */
	yylval = SymCharTerm(c);		   /*                        */
	return yylval ? TSym(yylval) : SymChar(c); /*                        */
    }						   /*                        */
    return c < 0 ? SymDefNull : SymChar(c & 0xff); /*                        */
  }						   /*                        */
  return SymDefNull;				   /*                        */
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
static Term read_list(t)			   /*                        */
  Term t;					   /*                        */
{ SymDef s;					   /*                        */
  Term a;					   /*                        */
  Term *tp;					   /*                        */
  int car = 1;					   /*                        */
 						   /*                        */
  for (a = read_expr(); a != term_eof ; a = read_expr())/*                   */
  { if (car)					   /*                        */
    { car    = 0;				   /*                        */
      Car(t) = a;				   /*                        */
      tp     = &Cdr(t);				   /*                        */
    } else {					   /*                        */
      *tp = Cons(a, NIL);			   /*                        */
      tp  = &Cdr(*tp);				   /*                        */
    }						   /*                        */
    s = scan();					   /*                        */
    if (SymIs(s, ']')) { return t; }		   /*                        */
    if (!SymIs(s, ','))				   /*                        */
    { Error("Missing comma", 0, 0); }		   /*                        */
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
static Term read_builtin(Term t)		   /*                        */
{ SymDef s;					   /*                        */
  						   /*                        */
  for (s = scan(); s; s = scan())		   /*                        */
  {						   /*                        */
#ifdef DEBUG_PARSER
    fprintf(stderr, "--- %s\n", SymName(s));	   /*                        */
#endif
    if (SymIs(s, '='))				   /*                        */
    {						   /*                        */
#ifdef DEBUG_PARSER
      fputs("--- skip =", stderr);		   /*                        */
#endif
    } else if ( SymIs(s, '{'))		   	   /*                        */
    {
      Cdr(t) = scan_block();		   	   /*                        */
      break;					   /*                        */
    } else if (SymIsOperator(s)		   	   /*                        */
	       || SymIs(s, ';')			   /*                        */
	       || SymIs(s, ')')			   /*                        */
	       || SymIs(s, ']')) {		   /*                        */
      unscan(s, yylval);			   /*                        */
#ifdef DEBUG_PARSER
      fputs("break", stderr);			   /*                        */
#endif
      break;					   /*                        */
    } else {					   /*                        */
      unscan(s, yylval);			   /*                        */
      Cdr(t) = read_expr();		   	   /*                        */
      break;					   /*                        */
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
{ TStack sp;					   /*                        */
  Term t;					   /*                        */
  int n;					   /*                        */
   						   /*                        */
  for (sp = stack;				   /*                        */
       sp && StackPrev(sp);			   /*                        */
       sp = StackPrev(sp))			   /*                        */
  { TStack ts = StackPrev(sp);			   /*                        */
    if (StackSymIs(ts, '-')			   /*                        */
       && (StackPrev(ts) == NULL		   /*                        */
	   || StackSymIsOperator(StackPrev(ts))))  /*                        */
    { if ( StackSymIsNumber(sp) )		   /*                        */
      { TNumber(StackTerm(sp)) =		   /*                        */
	  -TNumber(StackTerm(sp));		   /*                        */
      } else {					   /*                        */
	StackTerm(sp) = Cons(StackTerm(ts),	   /*                        */
			  Cons(StackTerm(sp), NIL));/*                       */
	StackSym(sp)  = sym_cons;		   /*                        */
      }						   /*                        */
      StackPrev(sp) = ts_pop(StackPrev(sp));	   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  while (StackPrev(stack))			   /*                        */
  { n = 0;				   	   /*                        */
    for (sp = stack; sp; sp = StackPrev(sp))	   /*                        */
    { int op = StackSymOp(sp);		   	   /*                        */
      if (op > n) n = op;		   	   /*                        */
    }						   /*                        */
    if (n <= 0) Error("Syntax error",0,0);	   /*                        */
    						   /*                        */
    for (sp = stack;				   /*                        */
	 sp && StackPrev(sp);			   /*                        */
	 sp = StackPrev(sp))			   /*                        */
    {						   /*                        */
      if (SymOp(StackSym(StackPrev(sp))) != n) continue;/*                   */
#ifdef DEBUG_PARSER
      fputs("reduce", stderr);			   /*                        */
#endif
      t = Cons(StackTerm(StackPrev(sp)), NIL);	   /*                        */
       						   /*                        */
      if ((n & 1) == 1)				   /*                        */
      { Cdr(t) = Cons(StackTerm(sp), NIL);	   /*                        */
      } else {					   /*                        */
        Cdr(t) = Cons(NIL,			   /*                        */
		      Cons(StackTerm(sp),	   /*                        */
			   NIL));		   /*                        */
	StackPrev(sp)  = ts_pop(StackPrev(sp));	   /*                        */
	Car(Cdr(t)) = StackTerm(StackPrev(sp));	   /*                        */
      }						   /*                        */
      StackTerm(sp) = t;			   /*                        */
      StackSym(sp)  = sym_group;		   /*                        */
      StackPrev(sp) = ts_pop(StackPrev(sp));	   /*                        */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
#ifdef DEBUG_PARSER
  fputs("... reduced", stderr);			   /*                        */
#endif
  return stack;					   /*                        */
}						   /*------------------------*/

#define Shift(S,T) stack = ts_push(stack, S, T)
#ifdef DEBUG_PARSER
#undef Shift
#define Shift(S,T) stack = ts_push(stack, S, T); \
  printf("shift %s\n", SymName(S))
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
static Term read_expr()				   /*                        */
{ SymDef s;					   /*                        */
  TStack stack = StackNULL;			   /*                        */
 						   /*                        */
  for (s = scan(); s; s = scan())		   /*                        */
  {						   /*                        */
#ifdef DEBUG_PARSER
    fprintf(stderr, "--- read_expr(): '%s' %d\n",  /*                        */
	    SymName(s), SymOp(s));		   /*                        */
#endif
    if (s == sym_r_n			   	   /*                        */
	|| s == sym_r_s			   	   /*                        */
	|| s == sym_r_b			   	   /*                        */
	|| s == sym_r_f			   	   /*                        */
	|| s == sym_field			   /*                        */
	|| s == sym_string		   	   /*                        */
	|| s == sym_number		   	   /*                        */
	|| s == sym_true			   /*                        */
	|| s == sym_false) {		   	   /*                        */
      Shift(s, yylval);				   /*                        */
       						   /*                        */
    } else if (s == sym_cons) {			   /*                        */
      Shift(s, (yylval == NIL			   /*                        */
		? NIL				   /*                        */
		: read_list(yylval)));		   /*                        */
 						   /*                        */
    } else if (SymIs(s, '{')) {			   /*                        */
      int lno = linenum;			   /*                        */
      Term t  = read_expr();			   /*                        */
      s	      = scan();				   /*                        */
      if (! SymIs(s, '}'))			   /*                        */
      { linenum = lno;				   /*                        */
	Error("Missing } before ",		   /*                        */
	      s ? SymName(s) : (String)"end of file",0); }/*                 */
      Shift(sym_group, t);			   /*                        */
 						   /*                        */
    } else if (SymIs(s, '(')) {			   /*                        */
      int lno = linenum;			   /*                        */
      Term t  = read_expr();			   /*                        */
      s	      = scan();				   /*                        */
      if (! SymIs(s, ')'))			   /*                        */
      { linenum = lno;				   /*                        */
	Error("Missing ) before ",		   /*                        */
	      s ? SymName(s) : (String)"end of file",0); }/*                 */
      Shift(sym_cons, t);			   /*                        */
 						   /*                        */
    } else if (SymIs(s, '\'')) {		   /*                        */
      SymDef qs = s;				   /*                        */
      Term q	= SymTerm(s);			   /*                        */
      Term t	= read_expr();			   /*                        */
      Shift(qs, Cons(q, Cons(t, NIL)));		   /*                        */
 						   /*                        */
    } else if (SymIs(s, '-')) {			   /*                        */
      Shift(s, yylval);		   	   	   /*                        */
 						   /*                        */
    } else if (SymIsOperator(s)) {		   /*                        */
      if (stack	== StackNULL && BinarySym(s) )	   /*                        */
      { Error("Unexpected operator ", SymName(s), 0); }/*                    */
      Shift(s, yylval);				   /*                        */
 						   /*                        */
    } else {					   /*                        */
      unscan(s, yylval);			   /*                        */
      return stack ? StackTerm(reduce(stack)) : NIL;/*                       */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  if (stack)			   		   /*                        */
  { s = StackSym(stack);			   /*                        */
    if (SymIsOperator(s)) {			   /*                        */
      Error("Missing operator for ", SymName(s),0);/*                        */
    }						   /*                        */
    stack = reduce(stack);
    return StackTerm(stack);
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
static Term read_cmd()				   /*                        */
{ register SymDef s;			   	   /*                        */
 						   /*                        */
  for (s = scan(); s; s = scan())		   /*                        */
  {						   /*                        */
    if (s == sym_r_b				   /*                        */
	|| s == sym_r_s				   /*                        */
	|| s == sym_r_n				   /*                        */
	|| s == sym_r_f)			   /*                        */
    { return read_builtin(yylval); }		   /*                        */
    else if (!SymIs(s, ';'))			   /*                        */
    { unscan(s, yylval);			   /*                        */
      return read_expr();			   /*                        */
    }						   /*                        */
  }						   /*                        */

#ifdef NEVER
  if (!SymIs(s, ';'))			   	   /*                        */
  { Error("Semicolon expected instead of ",  	   /*                        */
	  (s ? (char*)SymName(s) : "end-of-file"),"");/*                     */
  }						   /*                        */
#endif
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
int read_loop(file, action)			   /*                        */
  char * file;				   	   /*                        */
  int (*action)_ARG((Term t));			   /*                        */
{ Term t;					   /*                        */
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
  for (t = read_cmd();				   /*                        */
       t != term_eof;				   /*                        */
       t = read_cmd())				   /*                        */
  { (*action)(t); }				   /*                        */
 						   /*                        */
  fclose(in_file);				   /*                        */
 						   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/
