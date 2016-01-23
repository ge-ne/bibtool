/*** lcore.c ******************************************************************
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
#include <stdlib.h>
#include <string.h>
#include <bibtool/error.h>
#include <bibtool/symbols.h>
#include <ctype.h>
#include "term.h"
#include "binding.h"
#include "lcore.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/


/*---------------------------------------------------------------------------*/


#define Declare(SYM,VAL) SymDef SYM
#include "lcore.h"

SymDef* sym_char;				   /*                        */

/*-----------------------------------------------------------------------------
** Function:	print_quoted()
** Type:	static void
** Purpose:	
**		
** Arguments:
**	file	
**	 s	
** Returns:	nothing
**___________________________________________________			     */
void print_quoted(file, s)		   	   /*                        */
  FILE * file;					   /*                        */
  String s;					   /*                        */
{						   /*                        */
  for (; *s; s++)				   /*                        */
  { switch (*s)					   /*                        */
    { case '\n':				   /*                        */
	fputs("\\n", file);			   /*                        */
	break;					   /*                        */
      case '\r':				   /*                        */
	fputs("\\r", file);			   /*                        */
	break;					   /*                        */
      case '\b':				   /*                        */
	fputs("\\b", file);			   /*                        */
	break;					   /*                        */
      case '\f':				   /*                        */
	fputs("\\f", file);			   /*                        */
	break;					   /*                        */
      case '"':					   /*                        */
	fputs("\\\"", file);			   /*                        */
	break;					   /*                        */
      case '\'':				   /*                        */
	fputs("\\'", file);			   /*                        */
	break;					   /*                        */
      case '\\':				   /*                        */
	fputs("\\\\", file);			   /*                        */
	break;					   /*                        */
      default:					   /*                        */
	fputc((char)*s, file);			   /*                        */
    }						   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_self()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term g_self(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ return term;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_eq()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	term	
** Returns:	
**___________________________________________________			     */
Term g_eq(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ int val;					   /*                        */
  Term a, b;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
  { ErrorNF("Wrong number of arguments for ==",0); }/*                       */
  a = eval_term(binding, Car(term));		   /*                        */
  b = eval_term(binding, Cadr(term));		   /*                        */
 						   /*                        */
  if (a	== NIL) { val = (b == NIL ? 1 : 0); }	   /*                        */
  else if (TermIsNumber(a))			   /*                        */
  { val = (b && TermIsNumber(b) && TNumber(a) == TNumber(b) ? 1 : 0);/*      */
  }						   /*                        */
  else if (TermIsString(a))			   /*                        */
  { val = (b					   /*                        */
	   && TermIsString(b)			   /*                        */
	   && strcmp((char*)TString(a),		   /*                        */
		     (char*)TString(b)) == 0 ? 1 : 0);/*                     */
  }						   /*                        */
  else if (TermOp(a) == L_TRUE)			   /*                        */
  { val = (TermOp(b) == TermOp(a)); }		   /*                        */
  else if (TermOp(a) == L_FALSE)		   /*                        */
  { val = (TermOp(b) == TermOp(a)); }		   /*                        */
  else val = 0;					   /*                        */
 						   /*                        */
  return SymTerm(val ? sym_true : sym_false );	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_ne()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term g_ne(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ return SymTerm(TermOp(g_eq(binding, term)) == L_TRUE/*                     */
		 ? sym_false: sym_true);	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_bool()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term eval_bool(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ 						   /*                        */
  term = eval_term(binding, term);		   /*                        */
 						   /*                        */
  if (term == NIL) return SymTerm(sym_false);	   /*                        */
 						   /*                        */
  switch (TermOp(term))				   /*                        */
  { case L_CONS:				   /*                        */
      return SymTerm(sym_true);			   /*                        */
    case L_NUMBER:				   /*                        */
      return TNumber(term)			   /*                        */
	? SymTerm(sym_true)			   /*                        */
	: SymTerm(sym_false);			   /*                        */
    case L_BLOCK:				   /*                        */
    case L_STRING:				   /*                        */
      return *TString(term)			   /*                        */
	? SymTerm(sym_true)			   /*                        */
	: SymTerm(sym_false);			   /*                        */
    case L_TRUE:				   /*                        */
    case L_FALSE:				   /*                        */
      break;					   /*                        */
    default:					   /*                        */
      ErrorNF("Type error: boolean expected",0);   /*                        */
  }						   /*                        */
 						   /*                        */
  return term;	   				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_not()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	term	
** Returns:	
**___________________________________________________			     */
Term g_not(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{						   /*                        */
  term = eval_bool(binding, Cadr(term));	   /*                        */
  return SymTerm(TermOp(term) == L_TRUE		   /*                        */
		 ? sym_false: sym_true);	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_and()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term g_and(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term t;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
  { ErrorNF("Wrong number of arguments for and",0); }/*                      */
 						   /*                        */
  t = eval_bool(binding, Car(term));		   /*                        */
  if (TermIsFalse(t)) return t;		   	   /*                        */
 						   /*                        */
  return eval_bool(binding, Cadr(term));	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_or()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term g_or(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term t;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
  { ErrorNF("Wrong number of arguments for or",0); }/*                       */
 						   /*                        */
  t = eval_bool(binding, Car(term));		   /*                        */
  if (TermIsTrue(t)) return t;		   	   /*                        */
 						   /*                        */
  return eval_bool(binding, Cadr(term));	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_version()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term g_version(binding, term)		   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ extern char* bibtool_version;			   /*                        */
 						   /*                        */
  switch (list_length(Cdr(term)))		   /*                        */
  { case 0:					   /*                        */
      break;					   /*                        */
    case 1:					   /*                        */
    case 2:					   /*                        */
      ErrorNF("Parameter version is immutable",0); /*                        */
    default:					   /*                        */
      ErrorNF("Wrong number of arguments for version",0);/*                  */
  }						   /*                        */
 						   /*                        */
  return StringTerm((String)bibtool_version);	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_empty()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term g_empty(binding, term)		   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{						   /*                        */
  return StringTerm((String)"");		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_field()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term g_field(binding, term)		   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ SymDef sym = get_bind(binding, TString(term));   /*                        */
  return sym ? SymValue(sym) : NIL;		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_field()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term g_setq(binding, term)		   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{						   /*                        */
  if (Car(term) == NIL) ErrorNF("Undefined lhs",0);/*                        */
 						   /*                        */
  return setq(binding,
	      TString(Car(term)),
	      Cadr(term)
	     );					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	scanf_num()
** Type:	long
** Purpose:	
**		
** Arguments:
**	s	
** Returns:	
**___________________________________________________			     */
long scanf_num(s)				   /*                        */
  String s;					   /*                        */
{ long val  = 0;				   /*                        */
  char sign = 0;				   /*                        */
						   /*                        */
  for (; *s; s++)				   /*                        */
  { switch (*s)					   /*                        */
    { case '-':					   /*                        */
	if (!isdigit(*(s+1))) break;		   /*                        */
	sign = '-';				   /*                        */
	s++;					   /*                        */
      case '0': case '1': case '2': case '3':	   /*                        */
      case '4': case '5': case '6': case '7':	   /*                        */
      case '8': case '9':			   /*                        */
	for (; isdigit(*s); s++)		   /*                        */
	{ val = 10 * val + *s - '0'; }		   /*                        */
	return sign ? -val: val;		   /*                        */
    }						   /*                        */
  }						   /*                        */
  return val;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_num()
** Type:	long
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term eval_num(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ 						   /*                        */
  term = eval_term(binding, term);		   /*                        */
 						   /*                        */
  if (term == NIL || TermOp(term) == L_FALSE)	   /*                        */
    return NumberTerm(0L);			   /*                        */
  if (TermOp(term) == L_TRUE)	   		   /*                        */
    return NumberTerm(1L);			   /*                        */
  if (TermIsNumber(term))	   		   /*                        */
    return term;				   /*                        */
  if (TermIsList(term))				   /*                        */
    return NumberTerm((long)list_length(term));	   /*                        */
  if (TermIsString(term))			   /*                        */
    return NumberTerm(scanf_num(TString(term)));   /*                        */
 						   /*                        */
  ErrorNF("Type error: number expected",0);	   /*                        */
  return NIL;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_plus()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term g_plus(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ long val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
      ErrorNF("Wrong number of arguments for +",0);/*                        */
 						   /*                        */
  val = TNumber(eval_num(binding, Car(term)));	   /*                        */
  val += TNumber(eval_num(binding, Cadr(term)));   /*                        */
  return NumberTerm(val);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_minus()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	term	
** Returns:	
**___________________________________________________			     */
Term g_minus(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term t;					   /*                        */
  long val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  switch (list_length(term))			   /*                        */
  { case 1:					   /*                        */
      t = eval_num(binding, Car(term));		   /*                        */
      return NumberTerm(-TNumber(t));		   /*                        */
    case 2:					   /*                        */
      t	  = eval_num(binding, Car(term));	   /*                        */
      val = TNumber(t);				   /*                        */
      t	  = eval_num(binding, Cadr(term));	   /*                        */
      val -= TNumber(t);			   /*                        */
      return NumberTerm(val);			   /*                        */
    default:					   /*                        */
      ErrorNF("Wrong number of arguments for -",0);/*                        */
      return 0;	   				   /*                        */
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_times()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	term	
** Returns:	
**___________________________________________________			     */
Term g_times(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ long val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
      ErrorNF("Wrong number of arguments for *",0);/*                        */
 						   /*                        */
  val = TNumber(eval_num(binding, Car(term)));	   /*                        */
  val *= TNumber(eval_num(binding, Cadr(term)));   /*                        */
  return NumberTerm(val);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_div()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	term	
** Returns:	
**___________________________________________________			     */
Term g_div(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ long val, d;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
      ErrorNF("Wrong number of arguments for /",0);/*                        */
 						   /*                        */
  val = TNumber(eval_num(binding, Car(term)));	   /*                        */
  d   = TNumber(eval_num(binding, Cadr(term)));	   /*                        */
  if (d	== 0)					   /*                        */
      ErrorNF("Divide by 0",0);			   /*                        */
  return NumberTerm(val/d);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_mod()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	term	
** Returns:	
**___________________________________________________			     */
Term g_mod(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ long val, d;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
      ErrorNF("Wrong number of arguments for mod",0);/*                      */
 						   /*                        */
  val = TNumber(eval_num(binding, Car(term)));	   /*                        */
  d   = TNumber(eval_num(binding, Cadr(term)));	   /*                        */
  if (d	== 0)					   /*                        */
      ErrorNF("Modulo by 0",0);			   /*                        */
  return NumberTerm(val % d);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	hash()
** Type:	int
** Purpose:	
**		
** Arguments:
**	s	
**	 size	
** Returns:	
**___________________________________________________			     */
unsigned int hash(s)				   /*                        */
  register String s;				   /*                        */
{ register unsigned int hash = 0;		   /*                        */
  unsigned int i 	     = 0;		   /*                        */
 						   /*                        */
  while (*s)					   /*                        */
  { hash += (*s++) >> ((i++)&7); }		   /*                        */
  						   /*                        */
  return hash;				   	   /*                        */
}						   /*------------------------*/

#define InitSymChar(S,OP)				\
  SymChar(i) = symdef((String)S, *(S), NULL);		\
  SymTerm(SymChar(i)) = new_term(*(S), NIL, NIL)

/*-----------------------------------------------------------------------------
** Function:	init_symdef()
** Type:	void
** Purpose:	
**		
** Arguments:
**		
** Returns:	nothing
**___________________________________________________			     */
void init_lreader()				   /*                        */
{ int i;					   /*                        */
  char * s;					   /*                        */
 						   /*                        */
  sym_char = (SymDef*)calloc(256, sizeof(SymDef)); /*                        */
 						   /*                        */
  for (i = 1; i < 256; i++)			   /*                        */
  { switch (i)			   		   /*                        */
    { case ';':	InitSymChar( ";",    ';'); break;  /*                        */
      case '=':	InitSymChar( "=",  L_SET); break;  /*                        */
      case '<':	InitSymChar( "<",   L_LT); break;  /*                        */
      case '>':	InitSymChar( ">",   L_GT); break;  /*                        */
      case '#':	InitSymChar( "#",    '#'); break;  /*                        */
      case '+':	InitSymChar( "+", L_PLUS); break;  /*                        */
      case '-':	InitSymChar( "-",L_MINUS); break;  /*                        */
      case '*':	InitSymChar( "*",L_TIMES); break;  /*                        */
      case '/':	InitSymChar( "/",  L_DIV); break;  /*                        */
      case '%':	InitSymChar("mod", L_MOD); break;  /*                        */
      case '\'':InitSymChar("quote",L_QUOTE); break;/*                       */
      case '"':					   /*                        */
      case '_':					   /*                        */
      case '@':					   /*                        */
      case '$':					   /*                        */
      case '.':					   /*                        */
	break;					   /*                        */
      default:					   /*                        */
	if (isalnum(i) || isspace(i)) break;	   /*                        */
	s = malloc(2 * sizeof(char));	   	   /*                        */
	if (s == NULL) OUT_OF_MEMORY("symdef");	   /*                        */
	*s     = (char)i;			   /*                        */
	*(s+1) = '\0';				   /*                        */
	SymChar(i) = symdef(symbol((String)s), i, NULL);/*                   */
    }						   /*                        */
  }						   /*                        */
 						   /*                        */
  term_eof = NewTerm(-1);	   	   	   /*                        */
 						   /*                        */
#define Declare(SYM,VAL) SYM = VAL; MakeSymTerm(SYM)
#include "lcore.h"
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
