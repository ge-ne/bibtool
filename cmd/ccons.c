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


Binding cc_binding = NULL;		   	   /*                        */

#define Bind(NAME,GET)  bind(cc_binding, symdef(symbol((String)NAME),     \
						0, 0, GET, NULL));

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
    return StringTerm((String)"[]");		   /*                        */
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
  t = StringTerm((String)sbflush(buffer));	   /*                        */
  sbclose(buffer);				   /*                        */
  return t;		   			   /*                        */
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
    return StringTerm((String)"");		   /*                        */
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
  t = StringTerm((String)sbflush(buffer));	   /*                        */
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

/*-----------------------------------------------------------------------------
** Function:	class_list()
** Type:	void
** Purpose:	
**		
** Arguments:
**		
** Returns:	nothing
**___________________________________________________			     */
void class_list()				   /*                        */
{						   /*                        */
  cc_binding = binding(127, NULL);		   /*                        */
 						   /*                        */
  Bind("as.boolean", m_as_boolean);		   /*                        */
  Bind("as.number", m_length);		   	   /*                        */
  Bind("as.string", ml_as_string);		   /*                        */
  Bind("length", m_length);		   	   /*                        */
  Bind("join", m_join);		   	   	   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
