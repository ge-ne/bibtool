/*** ccons.c*******************************************************************
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


Term c_list;					   /*                        */

/*-----------------------------------------------------------------------------
** Function:	m_class()
** Type:	Term
** Purpose:	Getter for the class.
** Arguments:
**	binding	the binding
**	list	the list term
**	args	the arguments
** Returns:	the class
**___________________________________________________			     */
static Term m_class(binding, list, args)	   /*                        */
  Binding binding;				   /*                        */
  Term list;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "class");	   	   	   /*                        */
  LinkTerm(c_list);				   /*                        */
  return c_list;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_as_string()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	list	the list term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term ml_as_string(binding, list, args)	   /*                        */
  Binding binding;				   /*                        */
  Term list;					   /*                        */
  Term args;					   /*                        */
{ StringBuffer *buffer;				   /*                        */
  Term t;					   /*                        */
  no_args(args, "as.string");  		   	   /*                        */
  if (list == NIL)				   /*                        */
    return StringTerm("[]");		   	   /*                        */
 						   /*                        */
  buffer = sbopen();				   /*                        */
  sbputc('[', buffer);				   /*                        */
  t = eval_str(binding, Car(list));		   /*                        */
  sbputs((char*)TString(t), buffer);		   /*                        */
  UnlinkTerm(t);				   /*                        */
  for (list = Cdr(list); list; list = Cdr(list))   /*                        */
  { sbputs(", ", buffer);			   /*                        */
    t = eval_str(binding, Car(list));		   /*                        */
    sbputs((char*)TString(t), buffer);		   /*                        */
    UnlinkTerm(t);				   /*                        */
  }						   /*                        */
  sbputc(']', buffer);				   /*                        */
  t = StringTerm(sbflush(buffer));	   	   /*                        */
  sbclose(buffer);				   /*                        */
  return t;		   			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	ml_car()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	list	the list term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_car(binding, list, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term list;					   /*                        */
  Term args;					   /*                        */
{ Term t = list ? Car(list) : NIL;		   /*                        */
  no_args(args, "car");  		   	   /*                        */
  if (list) LinkTerm(t);			   /*                        */
  return t;		   			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	ml_cdr()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	list	the list term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_cdr(binding, list, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term list;					   /*                        */
  Term args;					   /*                        */
{ Term t = list ? Cdr(list) : NIL;		   /*                        */
  no_args(args, "cdr");  		   	   /*                        */
  if (list) LinkTerm(t);			   /*                        */
  return t;		   			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_empty()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	list	the list term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_empty(binding, list, args)	   /*                        */
  Binding binding;				   /*                        */
  Term list;					   /*                        */
  Term args;					   /*                        */
{ no_args(args, "empty");  		   	   /*                        */
  return list ? term_false : term_true;		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_join()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	list	the list term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_join(binding, list, args)	   	   /*                        */
  Binding binding;				   /*                        */
  Term list;					   /*                        */
  Term args;					   /*                        */
{ StringBuffer *buffer;				   /*                        */
  char * sep = "";				   /*                        */
  Term t;					   /*                        */
  if (args)				   	   /*                        */
  { sep = (char*)str_arg(binding, &args, "join"); }/*                        */
 						   /*                        */
  no_args(args, "join");			   /*                        */
 						   /*                        */
  if (list == NIL)				   /*                        */
    return StringTerm("");		   	   /*                        */
 						   /*                        */
  buffer = sbopen();				   /*                        */
  t 	 = eval_str(binding, Car(list));	   /*                        */
  sbputs((char*)TString(t), buffer);		   /*                        */
  UnlinkTerm(t);				   /*                        */
 						   /*                        */
  for (list = Cdr(list); list; list = Cdr(list))   /*                        */
  { sbputs(sep, buffer);			   /*                        */
    t = eval_str(binding, Car(list));		   /*                        */
    sbputs((char*)TString(t), buffer);		   /*                        */
    UnlinkTerm(t);				   /*                        */
  }						   /*                        */
  t = StringTerm(sbflush(buffer));	   	   /*                        */
  sbclose(buffer);				   /*                        */
  return t;		   			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_length()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	list	the list term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_length(binding, list, args)	   /*                        */
  Binding binding;				   /*                        */
  Term list;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "length");     		   	   /*                        */
 						   /*                        */
  return NumberTerm(list_length(list));		   /*                        */
}						   /*------------------------*/


#define Bind(NAME,GET)  bind(b, symdef(symbol((String)NAME),     \
				       0, 0, GET, NULL));

/*-----------------------------------------------------------------------------
** Function:	class_list()
** Type:	Term
** Purpose:	
**		
** Arguments:	none
** Returns:	the class
**___________________________________________________			     */
Term class_list()				   /*                        */
{ Binding b;					   /*                        */
  c_list = new_class(StringTerm("List"));	   /*                        */
  b = TBinding(c_list);		   	   	   /*                        */
 						   /*                        */
  Bind("as.boolean", m_as_boolean);		   /*                        */
  Bind("as.number", m_length);		   	   /*                        */
  Bind("as.string", ml_as_string);		   /*                        */
  Bind("car", m_car);		   	   	   /*                        */
  Bind("cdr", m_cdr);		   	   	   /*                        */
  Bind("class", m_class);			   /*                        */
  Bind("empty", m_empty);			   /*                        */
  Bind("length", m_length);		   	   /*                        */
  Bind("join", m_join);		   	   	   /*                        */
 						   /*                        */
  return c_list;				   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
