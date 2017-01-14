/*** boolean.c *****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2017 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/error.h>
#include <bibtool/type.h>
#include <bibtool/sbuffer.h>
#include "../binding.h"
#include "../lcore.h"

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


static Term c_boolean;				   /*                        */

/*-----------------------------------------------------------------------------
** Function:	m_and()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	bool	the boolean term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_and(binding, bool, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term bool;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  if (bool == term_false) return bool;		   /*                        */
  while (args)					   /*                        */
  { if (!eval_bool(binding, Car(args)))		   /*                        */
      return term_false;			   /*                        */
    args = Cdr(args);				   /*                        */
  }						   /*                        */
  return term_true;		   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_class()
** Type:	Term
** Purpose:	Getter for the class.
** Arguments:
**	binding	the binding
**	bool	the boolean term
**	args	the arguments
** Returns:	the class
**___________________________________________________			     */
static Term m_class(binding, bool, args)	   /*                        */
  Binding binding;				   /*                        */
  Term bool;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "class");	   	   	   /*                        */
  LinkTerm(c_boolean);				   /*                        */
  return c_boolean;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_equals()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	bool	the boolean term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_equals(binding, bool, args)	   /*                        */
  Binding binding;				   /*                        */
  Term bool;					   /*                        */
  Term args;					   /*                        */
{ int val;					   /*                        */
  Term t = term_arg(binding, &args, "equals");	   /*                        */
  no_args(args, "equals");			   /*                        */
 						   /*                        */
  val = (t && (TType(t)  == TType(bool)));	   /*                        */
  UnlinkTerm(t);				   /*                        */
  return (val ? term_true: term_false);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_negate()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	bool	the boolean term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_negate(binding, bool, args)	   /*                        */
  Binding binding;				   /*                        */
  Term bool;					   /*                        */
  Term args;					   /*                        */
{ no_args(args, "equals");			   /*                        */
 						   /*                        */
  return (IsFalse(bool) ? term_true: term_false);  /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_or()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	bool	the boolean term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_or(binding, bool, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term bool;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  if (bool == term_true) return bool;		   /*                        */
  while (args)					   /*                        */
  { if (eval_bool(binding, Car(args)))		   /*                        */
      return term_true;			   	   /*                        */
    args = Cdr(args);				   /*                        */
  }						   /*                        */
  return term_false;		   		   /*                        */
}						   /*------------------------*/

#define Bind(NAME,GET)  bind(b, symdef(symbol((String)NAME),     \
				       0, 0, GET, NULL));

/*-----------------------------------------------------------------------------
** Function:	class_boolean()
** Type:	Term
** Purpose:	
**		
** Arguments:	none
** Returns:	The class
**___________________________________________________			     */
Term class_boolean()				   /*                        */
{ Binding b;					   /*                        */
 						   /*                        */
  if (c_boolean == NIL)				   /*                        */
  { c_boolean = new_class(StringTerm("Boolean"));  /*                        */
    b = TBinding(c_boolean);		   	   /*                        */
 						   /*                        */
    Bind("and", m_and);		   	   	   /*                        */
    Bind("as.boolean", m_as_boolean);		   /*                        */
    Bind("as.number", m_as_number);		   /*                        */
    Bind("as.string", m_as_string);		   /*                        */
    Bind("class", m_class);		   	   /*                        */
    Bind("equals", m_equals);		   	   /*                        */
    Bind("negate", m_negate);		   	   /*                        */
    Bind("or", m_or);		   	   	   /*                        */
  }						   /*                        */
 						   /*                        */
  return c_boolean;				   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
