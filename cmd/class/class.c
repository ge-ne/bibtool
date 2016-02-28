/*** class.c *****************************************************************
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


Term c_class;				   	   /*                        */

/*-----------------------------------------------------------------------------
** Function:	m_class()
** Type:	Term
** Purpose:	Getter for the class.
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	the class
**___________________________________________________			     */
static Term m_class(binding, clazz, args)	   /*                        */
  Binding binding;				   /*                        */
  Term clazz;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "class");	   	   	   /*                        */
  LinkTerm(c_class);				   /*                        */
  return c_class;				   /*                        */
}						   /*------------------------*/

#define Bind(NAME,GET)  bind(b, symdef(symbol((String)NAME),     \
				       0, 0, GET, NULL));

/*-----------------------------------------------------------------------------
** Function:	class_class()
** Type:	Term
** Purpose:	
**		
** Arguments:	none
** Returns:	The class
**___________________________________________________			     */
Term class_class()				   /*                        */
{ Binding b;					   /*                        */
  c_class = new_class(StringTerm("Class"));	   /*                        */
  b = TBinding(c_class);		   	   /*                        */
 						   /*                        */
  Bind("class", m_class);		   	   /*                        */
 						   /*                        */
  return c_class;				   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
