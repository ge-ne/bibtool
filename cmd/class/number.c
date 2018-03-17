/*** number.c *****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2018 Gerd Neugebauer
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


static Term c_number;				   /*                        */

/*-----------------------------------------------------------------------------
** Function:	m_class()
** Type:	Term
** Purpose:	Getter for the class.
** Arguments:
**	binding	the binding
**	number	the number term
**	args	the arguments
** Returns:	the class
**___________________________________________________			     */
static Term m_class(binding, number, args)	   /*                        */
  Binding binding;				   /*                        */
  Term number;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "class");	   	   	   /*                        */
  LinkTerm(c_number);				   /*                        */
  return c_number;				   /*                        */
}						   /*------------------------*/


/*-----------------------------------------------------------------------------
** Function:	m_equals()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	num	the number term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_equals(binding, num, args)	   /*                        */
  Binding binding;				   /*                        */
  Term num;					   /*                        */
  Term args;					   /*                        */
{ int val;					   /*                        */
  Term t = term_arg(binding, &args, "equals");	   /*                        */
  no_args(args, "equals");			   /*                        */
 						   /*                        */
  val = (t && (TType(t) == L_NUMBER		   /*                        */
	       && TNumber(t) == TNumber(num)));	   /*                        */
  UnlinkTerm(t);				   /*                        */
  return (val ? term_true: term_false);		   /*                        */
}						   /*------------------------*/

#define Bind(NAME,GET)  bind(b, symdef(symbol((String)NAME),     \
				       0, 0, GET, NULL));

/*-----------------------------------------------------------------------------
** Function:	class_number()
** Type:	Term
** Purpose:	
**		
** Arguments:	none
** Returns:	the class
**___________________________________________________			     */
Term class_number()				   /*                        */
{ Binding b;					   /*                        */
 						   /*                        */
  if (c_number == NIL)			   	   /*                        */
  { c_number = new_class(StringTerm("Number"));	   /*                        */
    b = TBinding(c_number);		   	   /*                        */
 						   /*                        */
    Bind("as.boolean", m_as_boolean);		   /*                        */
    Bind("as.string", m_as_string);		   /*                        */
    Bind("as.number", m_as_number);		   /*                        */
    Bind("equals", m_equals);		   	   /*                        */
    Bind("class", m_class);		   	   /*                        */
  }						   /*                        */
 						   /*                        */
  return c_number;				   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
