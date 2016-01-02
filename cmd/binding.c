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

#include <string.h>
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
Binding binding _ARG((unsigned int size));
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
Binding binding(size)			   	   /*                        */
  unsigned int size;				   /*                        */
{						   /*                        */
  Binding bind = (Binding) malloc(sizeof(SBinding));/*                       */
  if (bind == BindingNULL) OUT_OF_MEMORY("binding");/*                       */
 						   /*                        */
  BJunks(bind) = (BJunk*) calloc(size, sizeof(BJunk));/*                     */
  if (BJunks(bind) == NULL) OUT_OF_MEMORY("binding");/*                      */
 						   /*                        */
  BSize(bind) = size;				   /*                        */
  NextBinding(bind) = BindingNULL;		   /*                        */
  return bind;				   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	hash()
** Type:	int
** Purpose:	
**		
** Arguments:
**	s	
**	 size	
** Returns:	
**___________________________________________________			     */
int hash(s, size)				   /*                        */
  register String s;				   /*                        */
  unsigned int size;				   /*                        */
{ register unsigned int hash = 0;		   /*                        */
  unsigned int i 	     = 0;		   /*                        */
 						   /*                        */
  while (*s)					   /*                        */
  { hash += (*s++) >> ((i++)&7); }		   /*                        */
  						   /*                        */
  return hash % size;				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_bind()
** Type:	BJunk
** Purpose:	
**		
** Arguments:
**	binding	
**	 key	
** Returns:	
**___________________________________________________			     */
BJunk get_bind(binding, key)			   /*                        */
  Binding binding;				   /*                        */
  String key;					   /*                        */
{ unsigned int h = hash(key, BSize(binding));
  BJunk junk;
  
  for (;;)
  {
    for (junk = BJunks(binding)[h];
	 junk;
	 junk = NextJunk(junk))
    { if (strcmp((char*)JKey(junk), (char*)key) == 0)
      { return junk; }
    }
    binding = NextBinding(binding);
    if (binding == BindingNULL) return NULL;
  }						   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	bind()
** Type:	void
** Purpose:	
**		
** Arguments:
**	b	
**	 key	
**	 term	
**	 get	
**	 set	
** Returns:	nothing
**___________________________________________________			     */
void bind(b, key, term, get, set)		   /*                        */
  Binding b;				   	   /*                        */
  String key;					   /*                        */
  Term term;					   /*                        */
  Term (*get)();				   /*                        */
  void (*set)();				   /*                        */
{ unsigned int h = hash(key, BSize(b));
  BJunk junk;
  
  for (junk = BJunks(b)[h]; junk; junk = NextJunk(junk))
  { if (strcmp((char*)JKey(junk), (char*)key) == 0)
    {
      JValue(junk) = term;
      JGet(junk)   = get;
      JSet(junk)   = set;
      return;
    }
  }

  junk = (BJunk) malloc(sizeof(SBJunk));	   /*                        */
  if (junk == NULL) OUT_OF_MEMORY("binding");	   /*                        */
  JKey(junk)     = key;
  JValue(junk)   = term;
  JGet(junk)     = get;
  JSet(junk)     = set;
  NextJunk(junk) = BJunks(b)[h];
  BJunks(b)[h]   = junk;
}						   /*------------------------*/

Term g_print(binding, term)			   /*                        */
  Binding binding;				   /*                        */
  Term term;					   /*                        */
{
  print_term(stdout, Cdr(term));

  return NIL;			   		   /*                        */
}						   /*------------------------*/



/*-----------------------------------------------------------------------------
** Function:	def_binding()
** Type:	Binding
** Purpose:	
**		
** Arguments:
**		
** Returns:	
**___________________________________________________			     */
Binding def_binding()				   /*                        */
{ Binding b = binding(511);			   /*                        */

  bind(b, "true", term_true, NULL, NULL);
  bind(b, "false", term_false, NULL, NULL);

#define RSC_INIT_AND   term_and,   NULL
#define RSC_INIT_FALSE term_false, eval_self
#define RSC_INIT_ILIKE term_ilike, NULL
#define RSC_INIT_LIKE  term_like,  NULL
#define RSC_INIT_MOD   term_mod,   NULL
#define RSC_INIT_NOT   term_not,   NULL
#define RSC_INIT_NIL   NIL,        NULL
#define RSC_INIT_OR    term_or,    NULL
#define RSC_INIT_TRUE  term_true,  eval_self
#define RSC_FIRST(C)
#define RSC_NEXT(C)
#define RscTerm(NAME,VALUE)	bind(b, NAME, VALUE, NULL);
#define RscBoolean(NAME,B,C,D)	bind(b, NAME, NIL, NULL, NULL);
#define RscString(NAME,B,C,D)	bind(b, NAME, NIL, NULL, NULL);
#define RscNumeric(NAME,B,C,D)	bind(b, NAME, NIL, NULL, NULL);
#define RscByFct(NAME,B,FCT)	bind(b, NAME, NIL, NULL, NULL);

#include <bibtool/resource.h>

  bind(b, "print", NIL, g_print, NULL);

  return b;				   	   /*                        */
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
{ BJunk junk;					   /*                        */
 						   /*                        */
  if (term == NIL) return NIL;			   /*                        */
 						   /*                        */
  junk = get_bind(binding, TermName(term));	   /*                        */
 						   /*                        */
  if (junk == NULL)	   			   /*                        */
  { Error("Undefined function ", TermName(term)); }/*                        */
  if (JGet(junk) == NULL)	   		   /*                        */
  { Error("Undefined getter for ", TermName(term)); }/*                      */
 						   /*                        */
  return (*JGet(junk))(binding, term);	   	   /*                        */
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

/*-----------------------------------------------------------------------------
** Function:	eval_cons()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 term	
** Returns:	
**___________________________________________________			     */
Term eval_builtin(binding, term)		   /*                        */
  Binding binding;				   /*                        */
  register Term term;				   /*                        */
{						   /*                        */

  if (strcmp((char*)TString(term), "print") == 0) {
    print_term(stdout,
	       eval_term(binding, Cdr(term)));
  }

  return NIL;					   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
