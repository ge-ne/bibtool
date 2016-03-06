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
#include <bibtool/key.h>
#include <bibtool/rewrite.h>
#include <bibtool/symbols.h>
#include <bibtool/sbuffer.h>
#include <bibtool/database.h>
#include <bibtool/io.h>
#include <ctype.h>
#include "binding.h"
#include "lcore.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


Term term_true;					   /*                        */
Term term_false;				   /*                        */

/*-----------------------------------------------------------------------------
** Function:	g_self()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_self(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ LinkTerm(term);				   /*                        */
  return term;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	equals()
** Type:	int
** Purpose:	
**		
** Arguments:
**	a	the first term
**	b	the second term
** Returns:	
**___________________________________________________			     */
int equals(a, b)				   /*                        */
  Term a;					   /*                        */
  Term b;					   /*                        */
{						   /*                        */
  if (a	== NIL) return (b == NIL);		   /*                        */
  if (a == b) return 1;				   /*                        */
 						   /*                        */
  switch (TType(a))				   /*                        */
  { case L_NUMBER:				   /*                        */
      return (b && IsNumber(b) &&		   /*                        */
	      TNumber(a) == TNumber(b));   	   /*                        */
    case L_STRING:				   /*                        */
      return (b && IsString(b) &&		   /*                        */
	      TString(a) == TString(b) );  	   /*                        */
    case L_CONS:				   /*                        */
      if (b == NIL || !IsList(b)) return 0;	   /*                        */
      for (;a ; a = Cdr(a))			   /*                        */
      { if (b == NIL || !equals(Car(a), Car(b)) )  /*                        */
	  return 0;				   /*                        */
	b = Cdr(b);				   /*                        */
      }						   /*                        */
      return (b == NIL);			   /*                        */
    case L_TRUE:				   /*                        */
    case L_FALSE:				   /*                        */
       return (TType(b) == TType(a));		   /*                        */
  }		   				   /*                        */
  return (a == b);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_eq()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_eq(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term a, b;					   /*                        */
  term = Cdr(term);				   /*                        */
  if (list_length(term) != 2) wrong_no_args("=="); /*                        */
 						   /*                        */
  a    = evaluate(binding, Car(term));		   /*                        */
  b    = evaluate(binding, Cadr(term));		   /*                        */
  term = (equals(a, b) ? term_true : term_false);  /*                        */
 						   /*                        */
  UnlinkTerm(a);				   /*                        */
  UnlinkTerm(b);				   /*                        */
 						   /*                        */
  return term;		   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_ne()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_ne(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{						   /*                        */
  return (IsTrue(g_eq(binding, term))		   /*                        */
	  ? term_false: term_true);   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_lt()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_lt(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term a;					   /*                        */
  int val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
  if (list_length(term) != 2) wrong_no_args("<");  /*                        */
 						   /*                        */
  a = evaluate(binding, Car(term));		   /*                        */
 						   /*                        */
  if ( IsNumber(a) )			   	   /*                        */
  { val = (TNumber(a) < 			   /*                        */
	   eval_num(binding, Cadr(term)));	   /*                        */
  }						   /*                        */
  else if ( IsString(a) )			   /*                        */
  { val = (cmp(TString(a),			   /*                        */
	       eval_str(binding, Cadr(term))) < 0);/*                        */
  } else					   /*                        */
  { ErrorNF1("Type error: comparable expected"); } /*                        */
 						   /*                        */
  return (val ? term_true: term_false);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_le()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_le(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term a;					   /*                        */
  int val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
  if (list_length(term) != 2) wrong_no_args("<="); /*                        */
 						   /*                        */
  a = evaluate(binding, Car(term));		   /*                        */
 						   /*                        */
  if ( IsNumber(a) )			   	   /*                        */
  { val = (TNumber(a) <= 			   /*                        */
	   eval_num(binding, Cadr(term)));	   /*                        */
  }						   /*                        */
  else if ( IsString(a) )			   /*                        */
  { val = (cmp(TString(a),			   /*                        */
	       eval_str(binding, Cadr(term))) <= 0);/*                       */
  } else					   /*                        */
  { ErrorNF1("Type error: comparable expected"); } /*                        */
 						   /*                        */
  return (val ? term_true: term_false);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_gt()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_gt(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term a;					   /*                        */
  int val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
  if (list_length(term) != 2) wrong_no_args("<");  /*                        */
 						   /*                        */
  a = evaluate(binding, Car(term));		   /*                        */
 						   /*                        */
  if ( IsNumber(a) )			   	   /*                        */
  { val = (TNumber(a) > 			   /*                        */
	   eval_num(binding, Cadr(term)));	   /*                        */
  }						   /*                        */
  else if ( IsString(a) )			   /*                        */
  { val = (cmp(TString(a),			   /*                        */
	       eval_str(binding, Cadr(term))) > 0);/*                        */
  } else					   /*                        */
  { ErrorNF1("Type error: comparable expected"); } /*                        */
 						   /*                        */
  return (val ? term_true: term_false);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_ge()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_ge(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term a;					   /*                        */
  int val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
  if (list_length(term) != 2) wrong_no_args(">="); /*                        */
 						   /*                        */
  a = evaluate(binding, Car(term));		   /*                        */
 						   /*                        */
  if ( IsNumber(a) )			   	   /*                        */
  { val = (TNumber(a) >= 			   /*                        */
	   eval_num(binding, Cadr(term)));	   /*                        */
  }						   /*                        */
  else if ( IsString(a) )			   /*                        */
  { val = (cmp(TString(a),			   /*                        */
	       eval_str(binding, Cadr(term))) >= 0);/*                       */
  } else					   /*                        */
  { ErrorNF1("Type error: comparable expected"); } /*                        */
 						   /*                        */
  UnlinkTerm(a);				   /*                        */
  return (val ? term_true: term_false);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_bool()
** Type:	int
** Purpose:	Evaluate a term and convert the result into a boolean value.
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
int eval_bool(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ 						   /*                        */
  term = evaluate(binding, term);		   /*                        */
 						   /*                        */
  if (term == NIL) { return 0; }	   	   /*                        */
 						   /*                        */
  switch (TType(term))			   	   /*                        */
  { case L_CONS:				   /*                        */
      return 1;			   	   	   /*                        */
    case L_NUMBER:				   /*                        */
      return (TNumber(term) != 0);		   /*                        */
    case L_STRING:				   /*                        */
      return (*TString(term) ? 1 : 0);		   /*                        */
    case L_TRUE:				   /*                        */
      return 1;					   /*                        */
    case L_FALSE:				   /*                        */
      break;					   /*                        */
    default:					   /*                        */
      ErrorNF1("Type error: boolean expected");    /*                        */
  }						   /*                        */
 						   /*                        */
  return 0;	   				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_as_boolean()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
Term m_as_boolean(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "as.boolean");			   /*                        */
  return (eval_bool(binding, string)		   /*                        */
	  ? term_true				   /*                        */
	  : term_false);		   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_while()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_while(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term t = NIL;				   	   /*                        */
 						   /*                        */
  while (eval_bool(binding, Car(term)))		   /*                        */
  { t = evaluate(binding, Cdr(term)); }	   	   /*                        */
 						   /*                        */
  LinkTerm(t);					   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_not()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_not(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{						   /*                        */
  return (eval_bool(binding, Cadr(term))	   /*                        */
	  ? term_false				   /*                        */
	  : term_true);     			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_and()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_and(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
  { wrong_no_args("and"); }			   /*                        */
 						   /*                        */
  return (eval_bool(binding, Car(term))		   /*                        */
	  && eval_bool(binding, Cadr(term))	   /*                        */
	  ? term_true				   /*                        */
	  : term_false);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_or()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_or(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
  { wrong_no_args("or"); }			   /*                        */
 						   /*                        */
  return (eval_bool(binding, Car(term))		   /*                        */
	  || eval_bool(binding, Cadr(term))	   /*                        */
	  ? term_true				   /*                        */
	  : term_false);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_version()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_version(binding, term)		   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ extern char* bibtool_version;			   /*                        */
  return StringTerm(bibtool_version);	   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	s_version()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term s_version(binding, term)		   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ ErrorNF1("Parameter version is immutable"); 	   /*                        */
  return NIL;	   				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_out_file()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_out_file(binding, term)		   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ extern char *get_output_file();		   /*                        */
  String s = (String)get_output_file();		   /*                        */
  return s ? StringTerm(s) : NIL;	   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	s_out_file()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term s_out_file(binding, term)		   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ extern void save_output_file();		   /*                        */
  String s = eval_str(binding,Cadr(term));	   /*                        */
  save_output_file((char*)s);	   		   /*                        */
  return StringTerm(s);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_input()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_input(binding, term)		   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ int n, i;					   /*                        */
  Term *tp;					   /*                        */
 						   /*                        */
  term = NIL;					   /*                        */
  tp   = &term;					   /*                        */
 						   /*                        */
  for (n = get_no_inputs(), i = 0; i < n; i++)	   /*                        */
  { *tp = Cons1(StringTerm(get_input_file(i)));	   /*                        */
    tp = &Cdr(*tp);				   /*                        */
  }						   /*                        */
  return term;	   	   			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	s_input()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term s_input(binding, term)		   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ String s = eval_str(binding, Cadr(term));	   /*                        */
  save_input_file((char*)s);	   		   /*                        */
  return StringTerm(s);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_macro_file()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_macro_file(binding, term)		   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ return StringTerm((String)get_macro_file());	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	s_macro_file()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term s_macro_file(binding, term)		   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ 						   /*                        */
  String s = eval_str(binding, Cadr(term));	   /*                        */
  save_macro_file((char*)s);	   		   /*                        */
  return StringTerm(s);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_cl_ign_words()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	NIL
**___________________________________________________			     */
Term g_cl_ign_words(binding, term)		   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ extern void clear_ignored_words();		   /*                        */
 						   /*                        */
  if (list_length(Cdr(term)) != 0)		   /*                        */
      wrong_no_args("clear.ignored.words");	   /*                        */
 						   /*                        */
  clear_ignored_words();			   /*                        */
  return NIL;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_print()
** Type:	Term
** Purpose:	Print the term argument to stdout.
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	nil
**___________________________________________________			     */
Term g_print(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ 					   	   /*                        */
  for (term = Cdr(term); term ; term = Cdr(term))  /*                        */
  { Term t = evaluate(binding, Car(term));	   /*                        */
    prn_term(stdout, t, 0, 0, 1);		   /*                        */
    UnlinkTerm(t);				   /*                        */
  }		   				   /*                        */
  return NIL;			   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_field()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_field(binding, term)		   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ SymDef sym = get_bind(binding, TString(term));   /*                        */
  term 	     = sym ? SymValue(sym) : NIL;	   /*                        */
  LinkTerm(term);				   /*                        */
  return term;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_setq()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_setq(binding, term)		   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term car = Cadr(term);			   /*                        */
  if (car == NIL)				   /*                        */
    ErrorNF1("Undefined left hand side of equals");/*                        */
  term = evaluate(binding, Cdr(term));	   	   /*                        */
 						   /*                        */
  if (TType(car) == L_METHOD)			   /*                        */
  { Term t;					   /*                        */
    char* clazz;				   /*                        */
    SymDef symdef = get_class(binding, 		   /*                        */
			      car, 		   /*                        */
			      &t, 		   /*                        */
			      &clazz);		   /*                        */
    if (symdef == SymDefNULL)		   	   /*                        */
      ErrorNF3(clazz,			   	   /*                        */
	       ": Unknown attribute ",	   	   /*                        */
	       TString(Cdr(car)));		   /*                        */
    if (SymSet(symdef) == NULL)		   	   /*                        */
      ErrorNF3(clazz,			   	   /*                        */
	       ": Illegal assignment to ",	   /*                        */
	       TString(Cdr(car)));		   /*                        */
    Cdr(t) = Cdr(car);				   /*                        */
    LinkTerm(Cdr(t));				   /*                        */
    return (*SymSet(symdef))(binding,		   /*                        */
			     t,			   /*                        */
			     Cadr(term));	   /*                        */
  }						   /*                        */
 						   /*                        */
  if (!IsVar(car))				   /*                        */
    ErrorNF1("Illegal left hand side of equals");  /*                        */
  						   /*                        */
  term = Cadr(term);				   /*                        */
  LinkTerm(term);				   /*                        */
  return setq(binding, TString(car), term ); 	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	scanf_num()
** Type:	long
** Purpose:	Search in a string for a sequence of digit optionally
**		preceeded by a minus sign and return it as number.
** Arguments:
**	s	the string to be scanned
** Returns:	the number found or 0
**___________________________________________________			     */
static long scanf_num(s)			   /*                        */
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
** Variable:	temp_num
** Type:	long
** Purpose:	temporary variable
**		
**___________________________________________________			     */
static long temp_num;				   /*                        */

/*-----------------------------------------------------------------------------
** Function:	ev_db_count()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	db	
**	rec	
** Returns:	
**___________________________________________________			     */
static int ev_db_count(db, rec)			   /*                        */
  DB db;					   /*                        */
  Record rec;					   /*                        */
{ temp_num++;					   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_num()
** Type:	long
** Purpose:	Evaluate an expression and convert the result into a number.
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	the number found
**___________________________________________________			     */
long eval_num(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ long val;					   /*                        */
  term = evaluate(binding, term);		   /*                        */
 						   /*                        */
  if (term == NIL || IsFalse(term))	   	   /*                        */
    return 0L;			   		   /*                        */
 						   /*                        */
  switch (TType(term))				   /*                        */
  { case L_NUMBER:				   /*                        */
      return TNumber(term);			   /*                        */
    case L_FALSE:  val = 0L; break;		   /*                        */
    case L_TRUE:   val = 1L; break;		   /*                        */
    case L_CONS:   val = list_length(term); break; /*                        */
    case L_STRING:				   /*                        */
      val = scanf_num(TString(term)); break;	   /*                        */
    case L_DB:					   /*                        */
      temp_num = 0L;				   /*                        */
      db_forall(TDB(term), ev_db_count);	   /*                        */
      val = temp_num;				   /*                        */
      break;					   /*                        */
    default:					   /*                        */
      ErrorNF2("Type error: number expected instead of ",/*                  */
	      term_type(term));	   	   	   /*                        */
  }						   /*                        */
 						   /*                        */
  return val;			   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_as_number()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
Term m_as_number(binding, term, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "as.number");  		   	   /*                        */
 						   /*                        */
  if (term && IsNumber(term))			   /*                        */
  { LinkTerm(term);				   /*                        */
    return term;				   /*                        */
  }						   /*                        */
  return NumberTerm(eval_num(binding, term));	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_str()
** Type:	String
** Purpose:	Evaluate the term and convert the result to a string.
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	the string determined
**___________________________________________________			     */
String eval_str(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ String s;					   /*                        */
  term = evaluate(binding, term);		   /*                        */
 						   /*                        */
  if (term == NIL) return symbol((String)"");	   /*                        */
 						   /*                        */
  switch (TType(term))				   /*                        */
  { case L_STRING:				   /*                        */
      s = TString(term);			   /*                        */
      break;					   /*                        */
    case L_TRUE:				   /*                        */
      s =  symbol((String)"true");		   /*                        */
      UnlinkTerm(term);				   /*                        */
      break;					   /*                        */
    case L_FALSE:				   /*                        */
      s = symbol((String)"false");		   /*                        */
      break;					   /*                        */
    case L_CONS:				   /*                        */
      { StringBuffer *sb = sbopen();		   /*                        */
 						   /*                        */
	for ( ; term; term = Cdr(term))		   /*                        */
	{ sbputs((char*)eval_str(binding,	   /*                        */
				 Car(term)), sb);  /*                        */
	}					   /*                        */
	s = symbol((String)sbflush(sb));	   /*                        */
	sbclose(sb);				   /*                        */
      }						   /*                        */
      break;					   /*                        */
    case L_NUMBER:				   /*                        */
      { long n = TNumber(term);			   /*                        */
	StringBuffer *sb;			   /*                        */
	char *t, *r;				   /*                        */
	if (n == 0) return symbol((String)"0");	   /*                        */
	sb = sbopen(); 				   /*                        */
	if (n < 0)				   /*                        */
	{ sbputc('-', sb);			   /*                        */
	  n = -n;				   /*                        */
	}					   /*                        */
	while (n > 0)				   /*                        */
	{ sbputc((n%10) + '0', sb);		   /*                        */
	  n = n/10;				   /*                        */
	}					   /*                        */
	r = t = sbflush(sb);			   /*                        */
	while (*t) t++;				   /*                        */
	t--;					   /*                        */
	if (*r == '-') r++;			   /*                        */
	while (r < t)				   /*                        */
	{ char c = *r;				   /*                        */
	  *(r++) = *t;				   /*                        */
	  *(t--) = c;				   /*                        */
	}					   /*                        */
	s = symbol((String)sbflush(sb));	   /*                        */
	sbclose(sb);				   /*                        */
      }						   /*                        */
      break;					   /*                        */
    case L_CLASS:				   /*                        */
      s = symbol((String)"<CLASS>");		   /*                        */
      break;					   /*                        */
    case L_DB:				   	   /*                        */
      s = symbol((String)"<DB>");		   /*                        */
      break;					   /*                        */
    case L_RECORD:				   /*                        */
      s = symbol((String)"<ENTRY>");		   /*                        */
      break;					   /*                        */
    default:					   /*                        */
      ErrorNF2("Type error: string expected instead of ",/*                  */
	       term_type(term));		   /*                        */
  }						   /*                        */
 						   /*                        */
  return s;	   			   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_as_string()
** Type:	Term
** Purpose:	 Method to convert a term to a string.
** Arguments:
**	binding	the binding
**	number	the number term
**	args	the arguments
** Returns:	the string
**___________________________________________________			     */
Term m_as_string(binding, number, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term number;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "as.string");  		   	   /*                        */
  return StringTerm(eval_str(binding, number));	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_plus()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_plus(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ long val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2) wrong_no_args("+");  /*                        */
 						   /*                        */
  val  = eval_num(binding, Car(term));		   /*                        */
  val += eval_num(binding, Cadr(term));		   /*                        */
  return NumberTerm(val);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_minus()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_minus(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ long val = 0L;				   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  switch (list_length(term))			   /*                        */
  { case 1:					   /*                        */
      val = -eval_num(binding, Car(term));	   /*                        */
      break;					   /*                        */
    case 2:					   /*                        */
      val  = eval_num(binding, Car(term));	   /*                        */
      val -= eval_num(binding, Cadr(term));	   /*                        */
      break;					   /*                        */
    default:					   /*                        */
      wrong_no_args("-");			   /*                        */
      return NIL;				   /*                        */
  }						   /*                        */
  return NumberTerm(val);		   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_times()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_times(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ long val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2) wrong_no_args("*");  /*                        */
 						   /*                        */
  val = eval_num(binding, Car(term));	   	   /*                        */
  val *= eval_num(binding, Cadr(term));	   	   /*                        */
  return NumberTerm(val);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_div()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_div(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ long val, d;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2) wrong_no_args("/");  /*                        */
 						   /*                        */
  val = eval_num(binding, Car(term));	   	   /*                        */
  d   = eval_num(binding, Cadr(term));	   	   /*                        */
  if (d	== 0) ErrorNF1("Divide by 0");		   /*                        */
  return NumberTerm(val/d);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_mod()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_mod(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ long val, d;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2) wrong_no_args("mod");/*                        */
 						   /*                        */
  val = eval_num(binding, Car(term));	   	   /*                        */
  d   = eval_num(binding, Cadr(term));	   	   /*                        */
  if (d	== 0) ErrorNF1("Modulo by 0");		   /*                        */
  return NumberTerm(val % d);			   /*                        */
}						   /*------------------------*/

static Term *tp;

/*-----------------------------------------------------------------------------
** Function:	g__ign()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	s	
** Returns:	
**___________________________________________________			     */
static int g__ign(s)				   /*                        */
  String s;					   /*                        */
{ *tp = Cons1(StringTerm(s));			   /*                        */
  tp = &Cdr(*tp);				   /*                        */
  return 1;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g_ign_()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_ign_(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term t = NIL;					   /*                        */
  tp 	 = &t;					   /*                        */
  foreach_ignored_word(g__ign);			   /*                        */
  tp = NULL;					   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	g__add_f()
** Type:	static int
** Purpose:	
**		
** Arguments:
**	key	the key
**	value	the value
** Returns:	
**___________________________________________________			     */
static int g__add_f(key, value)			   /*                        */
  String key;					   /*                        */
  String value;					   /*                        */
{						   /*                        */
  *tp = Cons1(Cons(StringTerm(key),		   /*                        */
		   Cons1(StringTerm(value))));	   /*                        */
  tp = &Cdr(*tp);				   /*                        */
  return 1;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_add_fields()
** Type:	Term
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
Term get_add_fields()				   /*                        */
{ Term t = NIL;					   /*                        */
  tp 	 = &t;					   /*                        */
  foreach_addlist(g__add_f);			   /*                        */
  tp = NULL;					   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	wrong_no_args()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	name	
** Returns:	nothing
**___________________________________________________			     */
void wrong_no_args(name)			   /*                        */
  register char* name;				   /*                        */
{ ErrorNF2("Wrong number of arguments for ", name);/*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	no_args()
** Type:	void
** Purpose:	
**		
** Arguments:
**	args	
**	msg	
** Returns:	nothing
**___________________________________________________			     */
void no_args(args, msg)			   	   /*                        */
  register Term  args;				   /*                        */
  register char *msg;				   /*                        */
{ if (args)					   /*                        */
    ErrorNF2("Too many arguments for ", msg); 	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	term_arg()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	argp	the pointer to the argument array
**	msg	the varible part of the error messge
** Returns:	
**___________________________________________________			     */
Term term_arg(binding, argp, msg)		   /*                        */
  Binding binding;				   /*                        */
  register Term *argp;				   /*                        */
  register char *msg;				   /*                        */
{ Term t;					   /*                        */
  if (*argp == NIL)				   /*                        */
    ErrorNF2("Missing numeric argument for ", msg);/*                        */
  						   /*                        */
  t  = evaluate(binding, Car(*argp));		   /*                        */
  *argp = Cdr(*argp);				   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	num_arg()
** Type:	long
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	argp	the pointer to the argument array
**	msg	the varible part of the error messge
** Returns:	
**___________________________________________________			     */
long num_arg(binding, argp, msg)		   /*                        */
  Binding binding;				   /*                        */
  register Term *argp;				   /*                        */
  register char *msg;				   /*                        */
{ long val;					   /*                        */
  if (*argp == NIL)				   /*                        */
    ErrorNF2("Missing numeric argument for ", msg);/*                        */
  						   /*                        */
  val = eval_num(binding, Car(*argp));		   /*                        */
  *argp = Cdr(*argp);				   /*                        */
  return val;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	str_arg()
** Type:	String
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	argp	the pointer to the argument array
**	msg	the varible part of the error messge
** Returns:	
**___________________________________________________			     */
String str_arg(binding, argp, msg)		   /*                        */
  Binding binding;				   /*                        */
  register Term *argp;				   /*                        */
  register char *msg;				   /*                        */
{ String val;					   /*                        */
  if (*argp == NIL)				   /*                        */
    ErrorNF2("Missing string argument for ", msg); /*                        */
  						   /*                        */
  val = eval_str(binding, Car(*argp));		   /*                        */
  *argp = Cdr(*argp);				   /*                        */
  return val;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bool_arg()
** Type:	int
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	argp	the pointer to the argument array
**	msg	the varible part of the error messge
** Returns:	
**___________________________________________________			     */
int bool_arg(binding, argp, msg)		   /*                        */
  Binding binding;				   /*                        */
  register Term *argp;				   /*                        */
  register char *msg;				   /*                        */
{ int val;					   /*                        */
  if (*argp == NIL)				   /*                        */
    ErrorNF2("Missing boolean argument for ", msg);/*                        */
  						   /*                        */
  val = eval_bool(binding, Car(*argp));		   /*                        */
  *argp = Cdr(*argp);				   /*                        */
  return val;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rec_arg()
** Type:	Record
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	argp	the pointer to the argument array
**	msg	the varible part of the error messge
** Returns:	
**___________________________________________________			     */
Record rec_arg(binding, argp, msg)		   /*                        */
  Binding binding;				   /*                        */
  register Term *argp;				   /*                        */
  register char *msg;				   /*                        */
{ Term t;					   /*                        */
  Record rec;					   /*                        */
 						   /*                        */
  t = evaluate(binding, *argp);		   	   /*                        */
  if (t == NIL || !IsRecord(t))			   /*                        */
    ErrorNF2("Missing record argument for ", msg); /*                        */
 						   /*                        */
  rec = TRecord(t);				   /*                        */
  UnlinkTerm(t);				   /*                        */
  *argp = Cdr(*argp);				   /*                        */
  return rec;					   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
