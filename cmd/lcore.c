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

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

extern void class_boolean();
extern void class_db();
extern void class_record();
extern void class_list();
extern void class_number();
extern void class_string();

/*---------------------------------------------------------------------------*/


Term term_true;					   /*                        */
Term term_false;				   /*                        */

SymDef sym_true;				   /*                        */
SymDef sym_false;				   /*                        */

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
{ int val;					   /*                        */
  Term a, b;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
  { wrong_no_args("=="); }			   /*                        */
  a = evaluate(binding, Car(term));		   /*                        */
  b = evaluate(binding, Cadr(term));		   /*                        */
 						   /*                        */
  if (a	== NIL) { val = (b == NIL ? 1 : 0); }	   /*                        */
  else if (IsNumber(a))			   	   /*                        */
  { val = (b 					   /*                        */
	   && IsNumber(b)			   /*                        */
	   && TNumber(a) == TNumber(b) ? 1 : 0);   /*                        */
  }						   /*                        */
  else if (IsString(a))			   	   /*                        */
  { val = (b					   /*                        */
	   && IsString(b)			   /*                        */
	   && cmp(TString(a), TString(b)) == 0 ? 1 : 0);/*                   */
  }						   /*                        */
  else if (IsTrue(a))			   	   /*                        */
  { val = (TType(b) == TType(a)); }		   /*                        */
  else if (IsFalse(a))		   	   	   /*                        */
  { val = (TType(b) == TType(a)); }		   /*                        */
  else val = 0;					   /*                        */
 						   /*                        */
  return (val ? term_true: term_false);		   /*                        */
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
  term = g_eq(binding, term);			   /*                        */
  return (IsTrue(term) ? term_false: term_true);   /*                        */
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
{ Term a, b;					   /*                        */
  int val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
  if (list_length(term) != 2) wrong_no_args("<");  /*                        */
 						   /*                        */
  a = evaluate(binding, Car(term));		   /*                        */
  b = evaluate(binding, Cadr(term));		   /*                        */
 						   /*                        */
  if ( IsNumber(a) )			   	   /*                        */
  { if ( !IsNumber(b) )			   	   /*                        */
      b = eval_num(binding, b);			   /*                        */
    val = (TNumber(a) < TNumber(b));		   /*                        */
  } else if ( IsString(a) )			   /*                        */
  { if ( !IsString(b) )			   	   /*                        */
      b = eval_str(binding, b);			   /*                        */
    val = (cmp(TString(a), TString(b)) < 0);	   /*                        */
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
{ Term a, b;					   /*                        */
  int val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
  if (list_length(term) != 2) wrong_no_args("<="); /*                        */
 						   /*                        */
  a = evaluate(binding, Car(term));		   /*                        */
  b = evaluate(binding, Cadr(term));		   /*                        */
 						   /*                        */
  if ( IsNumber(a) )			   	   /*                        */
  { if ( !IsNumber(b) )			   	   /*                        */
      b = eval_num(binding, b);			   /*                        */
    val = (TNumber(a) <= TNumber(b));		   /*                        */
  } else if ( IsString(a) )			   /*                        */
  { if ( !IsString(b) )			   	   /*                        */
      b = eval_str(binding, b);			   /*                        */
    val = (cmp(TString(a), TString(b)) <= 0);	   /*                        */
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
{ Term a, b;					   /*                        */
  int val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
  if (list_length(term) != 2) wrong_no_args("<");  /*                        */
 						   /*                        */
  a = evaluate(binding, Car(term));		   /*                        */
  b = evaluate(binding, Cadr(term));		   /*                        */
 						   /*                        */
  if ( IsNumber(a) )			   	   /*                        */
  { if ( !IsNumber(b) )			   	   /*                        */
      b = eval_num(binding, b);			   /*                        */
    val = (TNumber(a) > TNumber(b));		   /*                        */
  } else if ( IsString(a) )			   /*                        */
  { if ( !IsString(b) )			   	   /*                        */
      b = eval_str(binding, b);			   /*                        */
    val = (cmp(TString(a), TString(b)) > 0);	   /*                        */
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
{ Term a, b;					   /*                        */
  int val;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
  if (list_length(term) != 2) wrong_no_args(">="); /*                        */
 						   /*                        */
  a = evaluate(binding, Car(term));		   /*                        */
  b = evaluate(binding, Cadr(term));		   /*                        */
 						   /*                        */
  if ( IsNumber(a) )			   	   /*                        */
  { if ( !IsNumber(b) )			   	   /*                        */
      b = eval_num(binding, b);			   /*                        */
    val = (TNumber(a) >= TNumber(b));		   /*                        */
  } else if ( IsString(a) )			   /*                        */
  { if ( !IsString(b) )			   	   /*                        */
      b = eval_str(binding, b);			   /*                        */
    val = (cmp(TString(a), TString(b)) >= 0);	   /*                        */
  } else					   /*                        */
  { ErrorNF1("Type error: comparable expected"); } /*                        */
 						   /*                        */
  return (val ? term_true: term_false);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_bool()
** Type:	Term
** Purpose:	Evaluate a term and convert the result into a boolean value.
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term eval_bool(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ 						   /*                        */
  term = evaluate(binding, term);		   /*                        */
 						   /*                        */
  if (term == NIL) { return term_false; }	   /*                        */
 						   /*                        */
  switch (TType(term))			   	   /*                        */
  { case L_CONS:				   /*                        */
      return term_true;			   	   /*                        */
    case L_NUMBER:				   /*                        */
      return (TNumber(term) ? term_true : term_false);/*                     */
    case L_STRING:				   /*                        */
      return (*TString(term) ? term_true : term_false);/*                    */
    case L_TRUE:				   /*                        */
    case L_FALSE:				   /*                        */
      break;					   /*                        */
    default:					   /*                        */
      ErrorNF1("Type error: boolean expected");    /*                        */
  }						   /*                        */
 						   /*                        */
  LinkTerm(term);				   /*                        */
  return term;	   				   /*                        */
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
  return eval_bool(binding, string);		   /*                        */
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
Term g_while(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term t = NIL;				   	   /*                        */
 						   /*                        */
  while (eval_bool(binding, Car(term)) == term_true)/*                       */
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
  term = eval_bool(binding, Cadr(term));	   /*                        */
  LinkTerm(term);				   /*                        */
  return IsTrue(term) ? term_false: term_true;     /*                        */
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
{ Term t;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
  { wrong_no_args("and"); }			   /*                        */
 						   /*                        */
  t = eval_bool(binding, Car(term));		   /*                        */
  LinkTerm(t);					   /*                        */
  return (IsFalse(t)				   /*                        */
	  ? t					   /*                        */
	  : eval_bool(binding, Cadr(term)));	   /*                        */
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
{ Term t;					   /*                        */
 						   /*                        */
  term = Cdr(term);				   /*                        */
 						   /*                        */
  if (list_length(term) != 2)			   /*                        */
  { wrong_no_args("or"); }			   /*                        */
 						   /*                        */
  t = eval_bool(binding, Car(term));		   /*                        */
  LinkTerm(t);					   /*                        */
  return (IsTrue(t)				   /*                        */
	  ? t					   /*                        */
	  : eval_bool(binding, Cadr(term)));	   /*                        */
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
  return StringTerm((String)bibtool_version);	   /*                        */
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
 						   /*                        */
  term = eval_str(binding,Cadr(term));	   	   /*                        */
  save_output_file((char*)TString(term));	   /*                        */
  return term;				   	   /*                        */
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
  { *tp = Cons1(StringTerm((String)get_input_file(i)));/*                    */
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
{						   /*                        */
  term = eval_str(binding, Cadr(term));	   	   /*                        */
  save_input_file((char*)TString(term));	   /*                        */
  return term;				   	   /*                        */
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
  term = eval_str(binding, Cadr(term));	   	   /*                        */
  save_macro_file((char*)TString(term));	   /*                        */
  return term;				   	   /*                        */
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
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term g_print(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ 					   	   /*                        */
  for (term = Cdr(term); term ; term = Cdr(term))  /*                        */
  { Term t = evaluate(binding, Car(term));	   /*                        */
    prn_term(stdout, t, 0, 0);			   /*                        */
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
  term	   = evaluate(binding, Cdr(term));	   /*                        */
  if (car == NIL) ErrorNF1("Undefined LHS");	   /*                        */
  if (!IsVar(car)) ErrorNF1("Illegal LHS");    	   /*                        */
  						   /*                        */
  term = Cadr(term);				   /*                        */
  LinkTerm(term);				   /*                        */
  return setq(binding, TString(car), term ); 	   /*                        */
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
** Returns:	
**___________________________________________________			     */
Term eval_num(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ long val;					   /*                        */
  term = evaluate(binding, term);		   /*                        */
 						   /*                        */
  if (term == NIL || IsFalse(term))	   	   /*                        */
    return NumberTerm(0L);			   /*                        */
 						   /*                        */
  switch (TType(term))				   /*                        */
  { case L_NUMBER: return term;			   /*                        */
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
  return NumberTerm(val);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_as_number()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	term	
**	args	
** Returns:	
**___________________________________________________			     */
Term m_as_number(binding, term, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "as.number");  		   	   /*                        */
  return eval_num(binding, term);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_str()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	term	the term
** Returns:	
**___________________________________________________			     */
Term eval_str(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ Term t;					   /*                        */
  term = evaluate(binding, term);		   /*                        */
 						   /*                        */
  if (term == NIL) return StringTerm((String)"");  /*                        */
 						   /*                        */
  switch (TType(term))				   /*                        */
  {						   /*                        */
    case L_STRING:				   /*                        */
      LinkTerm(term);				   /*                        */
      break;					   /*                        */
    case L_TRUE:				   /*                        */
      term = StringTerm((String)"true");	   /*                        */
      break;					   /*                        */
    case L_FALSE:				   /*                        */
      term = StringTerm((String)"false");	   /*                        */
      break;					   /*                        */
    case L_CONS:				   /*                        */
      { StringBuffer *sb = sbopen();		   /*                        */
 						   /*                        */
	for ( ; term; term = Cdr(term))		   /*                        */
	{ t = eval_str(binding, Car(term));	   /*                        */
	  sbputs((char*)TString(t), sb);	   /*                        */
	  UnlinkTerm(t);			   /*                        */
	}					   /*                        */
	term = StringTerm((String)sbflush(sb));	   /*                        */
	sbclose(sb);				   /*                        */
      }						   /*                        */
    case L_NUMBER:				   /*                        */
      { long n = TNumber(term);			   /*                        */
	StringBuffer *sb;			   /*                        */
	char *s, *t;				   /*                        */
	if (n == 0) return StringTerm((String)"0");/*                        */
	sb = sbopen(); 				   /*                        */
	if (n < 0)				   /*                        */
	{ sbputc('-', sb);			   /*                        */
	  n = -n;				   /*                        */
	}					   /*                        */
	while (n > 0)				   /*                        */
	{ sbputc((n%10) + '0', sb);		   /*                        */
	  n = n/10;				   /*                        */
	}					   /*                        */
	s = t = sbflush(sb);			   /*                        */
	while (*t) t++;				   /*                        */
	t--;					   /*                        */
	if (*s == '-') s++;			   /*                        */
	while (s < t)				   /*                        */
	{ char c = *s;				   /*                        */
	  *(s++) = *t;				   /*                        */
	  *(t--) = c;				   /*                        */
	}					   /*                        */
	term = StringTerm((String)sbflush(sb));	   /*                        */
	sbclose(sb);				   /*                        */
      }						   /*                        */
      break;					   /*                        */
    case L_DB:				   	   /*                        */
      term = StringTerm((String)"<DB>");
      break;
    case L_RECORD:				   /*                        */
      term = StringTerm((String)"<RECORD>");
      break;
    default:					   /*                        */
      ErrorNF2("Type error: string expected instead of ",/*                  */
	       term_type(term));		   /*                        */
  }						   /*                        */
 						   /*                        */
  return term;	   			   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_as_string()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	number	the number term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
Term m_as_string(binding, number, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term number;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "as.string");  		   	   /*                        */
  return eval_str(binding, number);		   /*                        */
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
  if (list_length(term) != 2)			   /*                        */
    wrong_no_args("+");	   			   /*                        */
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
**	binding	the binding
**	term	the term
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
      wrong_no_args("-");			   /*                        */
      return 0;	   				   /*                        */
  }						   /*                        */
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
  if (list_length(term) != 2)			   /*                        */
    wrong_no_args("*");			   	   /*                        */
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
  if (list_length(term) != 2)			   /*                        */
    wrong_no_args("/");			   	   /*                        */
 						   /*                        */
  val = TNumber(eval_num(binding, Car(term)));	   /*                        */
  d   = TNumber(eval_num(binding, Cadr(term)));	   /*                        */
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
  if (list_length(term) != 2)			   /*                        */
    wrong_no_args("mod");			   /*                        */
 						   /*                        */
  val = TNumber(eval_num(binding, Car(term)));	   /*                        */
  d   = TNumber(eval_num(binding, Cadr(term)));	   /*                        */
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
**	key	
**	 value	
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
** Function:	num_arg()
** Type:	long
** Purpose:	
**		
** Arguments:
**	binding	
**	argp	
**	msg	
** Returns:	
**___________________________________________________			     */
long num_arg(binding, argp, msg)		   /*                        */
  Binding binding;				   /*                        */
  register Term *argp;				   /*                        */
  register char *msg;				   /*                        */
{ Term t;					   /*                        */
  long val;					   /*                        */
  if (*argp == NIL)				   /*                        */
    ErrorNF2("Missing numeric argument for ", msg);/*                        */
  						   /*                        */
  t   = eval_num(binding, Car(*argp));		   /*                        */
  val = TNumber(t);				   /*                        */
  UnlinkTerm(t);				   /*                        */
  *argp = Cdr(*argp);				   /*                        */
  return val;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	str_arg()
** Type:	String
** Purpose:	
**		
** Arguments:
**	binding	
**	argp	
**	msg	
** Returns:	
**___________________________________________________			     */
String str_arg(binding, argp, msg)		   /*                        */
  Binding binding;				   /*                        */
  register Term *argp;				   /*                        */
  register char *msg;				   /*                        */
{ Term t;					   /*                        */
  String val;					   /*                        */
  if (*argp == NIL)				   /*                        */
    ErrorNF2("Missing string argument for ", msg); /*                        */
  						   /*                        */
  t   = eval_str(binding, Car(*argp));		   /*                        */
  val = TString(t);				   /*                        */
  UnlinkTerm(t);				   /*                        */
  *argp = Cdr(*argp);				   /*                        */
  return val;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bool_arg()
** Type:	int
** Purpose:	
**		
** Arguments:
**	binding	
**	argp	
**	msg	
** Returns:	
**___________________________________________________			     */
int bool_arg(binding, argp, msg)		   /*                        */
  Binding binding;				   /*                        */
  register Term *argp;				   /*                        */
  register char *msg;				   /*                        */
{ Term t;					   /*                        */
  int val;					   /*                        */
  if (*argp == NIL)				   /*                        */
    ErrorNF2("Missing boolean argument for ", msg);/*                        */
  						   /*                        */
  t = eval_bool(binding, Car(*argp));		   /*                        */
  val = (t == term_true);			   /*                        */
  UnlinkTerm(t);				   /*                        */
  *argp = Cdr(*argp);				   /*                        */
  return val;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rec_arg()
** Type:	Record
** Purpose:	
**		
** Arguments:
**	binding	
**	 argp	
**	 msg	
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

/*-----------------------------------------------------------------------------
** Function:	init_lcore()
** Type:	void
** Purpose:	
**		
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void init_lcore()				   /*                        */
{						   /*                        */
  sym_true  = symdef((String)"true",  L_TRUE,  SYM_LOCKED, g_self, NULL);/*  */
  sym_false = symdef((String)"false", L_FALSE, SYM_LOCKED, g_self, NULL);/*  */
 						   /*                        */
  term_true  = SymTerm(sym_true)  = NewTerm(L_TRUE);/*                       */
  term_false = SymTerm(sym_false) = NewTerm(L_FALSE);/*                      */
 						   /*                        */
  class_boolean();				   /*                        */
  class_db();					   /*                        */
  class_record();
  class_list();					   /*                        */
  class_number();				   /*                        */
  class_string();				   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
