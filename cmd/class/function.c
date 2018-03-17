/*** function.c ***************************************************************
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


static Term c_function;				   /*                        */

/*-----------------------------------------------------------------------------
** Function:	m_class()
** Type:	Term
** Purpose:	Getter for the class.
** Arguments:
**	binding	the binding
**	fct	the function term
**	args	the arguments
** Returns:	the class
**___________________________________________________			     */
static Term m_class(binding, fct, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term fct;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "class");	   	   	   /*                        */
  LinkTerm(c_function);				   /*                        */
  return c_function;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_apply()
** Type:	Term
** Purpose:	Run the function.
** Arguments:
**	binding	the binding
**	fct	the function term
**	args	the arguments
** Returns:	the class
**___________________________________________________			     */
static Term m_apply(binding, fct, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term fct;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  return funcall(binding, (String)"", fct, args);  /*                        */
}						   /*------------------------*/

#define Bind(NAME,GET)  bind(b, symdef(symbol((String)NAME),     \
				       0, 0, GET, NULL));

/*-----------------------------------------------------------------------------
** Function:	m_code()
** Type:	Term
** Purpose:	Getter for the code.
** Arguments:
**	binding	the binding
**	fct	the function term
**	args	the arguments
** Returns:	the class
**___________________________________________________			     */
static Term m_code(binding, fct, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term fct;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "code");	   	   	   /*                        */
  fct = Cddr(fct);				   /*                        */
  if (fct) LinkTerm(fct);			   /*                        */
  return fct;				   	   /*                        */
}						   /*------------------------*/

#define Bind(NAME,GET)  bind(b, symdef(symbol((String)NAME),     \
				       0, 0, GET, NULL));

/*-----------------------------------------------------------------------------
** Function:	class_function()
** Type:	Term
** Purpose:	
**		
** Arguments:	none
** Returns:	The class
**___________________________________________________			     */
Term class_function()				   /*                        */
{ Binding b;					   /*                        */
 						   /*                        */
  if (c_function == NIL)			   /*                        */
  { c_function = new_class(StringTerm("Function"));/*                        */
    b = TBinding(c_function);		   	   /*                        */
 						   /*                        */
    Bind("apply", m_apply);		   	   /*                        */
    Bind("class", m_class);		   	   /*                        */
    Bind("code", m_code);			   /*                        */
  }						   /*                        */
 						   /*                        */
  return c_function;				   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
