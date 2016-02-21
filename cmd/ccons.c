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


static Binding cc_binding = NULL;		   /*                        */

#define Bind(NAME,GET)  bind(cc_binding, symdef(symbol((String)NAME),     \
						0, 0, GET, NULL));

/*-----------------------------------------------------------------------------
** Function:	m_as_string()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	list	
**	args	
** Returns:	
**___________________________________________________			     */
static Term m_as_string(binding, list, args)	   /*                        */
  Binding binding;				   /*                        */
  Term list;					   /*                        */
  Term args;					   /*                        */
{ StringBuffer *buffer;				   /*                        */
  Term t;					   /*                        */
  if (args)				   	   /*                        */
    ErrorNF1("Too many arguments for as.string");  /*                        */
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
**	binding	
**	list	
**	args	
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
  { if (Cdr(args))				   /*                        */
      ErrorNF1("Too many arguments for join");	   /*                        */
    t	= eval_str(binding, Car(args));		   /*                        */
    sep = (char*)TString(t);			   /*                        */
    UnlinkTerm(t);				   /*                        */
  }						   /*                        */
  if (list == NIL)				   /*                        */
    return StringTerm((String)"");		   /*                        */
 						   /*                        */
  buffer = sbopen();				   /*                        */
  t = eval_str(binding, Car(list));		   /*                        */
  sbputs((char*)TString(t), buffer);		   /*                        */
  UnlinkTerm(t);				   /*                        */
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
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	
**	list	
**	args	
** Returns:	
**___________________________________________________			     */
static Term m_length(binding, list, args)	   /*                        */
  Binding binding;				   /*                        */
  Term list;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  if (args)				   	   /*                        */
    ErrorNF1("Too many arguments for length");     /*                        */
 						   /*                        */
  return NumberTerm(list_length(list));		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	init_clist()
** Type:	void
** Purpose:	
**		
** Arguments:
**		
** Returns:	nothing
**___________________________________________________			     */
void init_clist()				   /*                        */
{						   /*                        */
  cc_binding = binding(127, NULL);		   /*                        */
 						   /*                        */
  Bind("as.number", m_length);		   	   /*                        */
  Bind("as.string", m_as_string);		   /*                        */
  Bind("length", m_length);		   	   /*                        */
  Bind("join", m_join);		   	   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	meth_list()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	list	
**	meth	
** Returns:	
**___________________________________________________			     */
Term meth_list(binding, list, meth)		   /*                        */
  Binding binding;				   /*                        */
  Term list;					   /*                        */
  Term meth;					   /*                        */
{ SymDef symdef = get_bind(cc_binding,		   /*                        */
			   TString(meth));	   /*                        */
 						   /*                        */
  if (symdef == SymDefNULL			   /*                        */
      || SymGet(symdef) == NULL)		   /*                        */
    ErrorNF2("Unknown method for list: ",	   /*                        */
	     TString(meth));	   		   /*                        */
 						   /*                        */
  return (*SymGet(symdef))(binding, list, Cdr(meth));/*                      */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
