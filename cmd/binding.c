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


Binding binding(term)			   	   /*                        */
  Term term;					   /*                        */
{						   /*                        */
  Binding bind = (Binding) malloc(sizeof(SBinding));/*                       */
  if (bind == NULL) OUT_OF_MEMORY("binding");      /*                        */



  return bind;				   	   /*                        */
}						   /*------------------------*/

Term eval_term(binding, term)
  Binding binding;
  Term term;
{
  return NIL;
}


/*---------------------------------------------------------------------------*/
