/*** binding.c *****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <stdlib.h>
#include <bibtool/error.h>
#include "binding.h"
#include "term.h"
#include "symdef.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
Binding binding _ARG((Term term));
Term eval_term _ARG((Binding binding, Term term));
Term eval_self _ARG((Binding binding, Term term));

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/

#define Error(X,Y)					\
	error(ERR_ERROR|ERR_EXIT,(String)X,		\
	      (String)Y,(String)0,(String)0,(String)0,0,NULL)
/*-----------------------------------------------------------------------------
** Function:	binding()
** Type:	Binding
** Purpose:	
**		
** Arguments:
**	term	
** Returns:	
**___________________________________________________			     */
Binding binding(term)			   	   /*                        */
  Term term;					   /*                        */
{						   /*                        */
  Binding bind = (Binding) malloc(sizeof(SBinding));/*                       */
  if (bind == NULL) OUT_OF_MEMORY("binding");      /*                        */



  return bind;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_term()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term eval_term(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{ SymDef symdef;				   /*                        */
  if (term == NIL) return NIL;			   /*                        */
 						   /*                        */
  symdef = TSym(term);				   /*                        */
  if (SymEval(symdef) == NULL)			   /*                        */
  { Error("Undefined function ",		   /*                        */
	   SymName(symdef)); }		   	   /*                        */
 						   /*                        */
  return (*SymEval(symdef))(binding, term);	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_self()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term eval_self(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  register Term term;				   /*                        */
{						   /*                        */
  return term;					   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
