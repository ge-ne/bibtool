/*** boolean.c *****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2016 Gerd Neugebauer
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
    Bind("as.boolean", m_as_boolean);		   /*                        */
    Bind("as.number", m_as_number);		   /*                        */
    Bind("as.string", m_as_string);		   /*                        */
    Bind("equals", m_equals);		   	   /*                        */
    Bind("class", m_class);		   	   /*                        */
  }						   /*                        */
 						   /*                        */
  return c_boolean;				   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
