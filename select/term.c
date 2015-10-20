/*** term.c ********************************************************************
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

#include <stdio.h>
#include <stdlib.h>
#include "term.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

Term new_term _ARG((int op, Term a, Term b));
void free_term _ARG((Term t));

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	new_term()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	op	
**	 a1	
**	 a2	
** Returns:	
**___________________________________________________			     */
Term new_term(op, a1, a2)			   /*                        */
  int op;					   /*                        */
  Term a1;					   /*                        */
  Term a2;					   /*                        */
{						   /*                        */
  Term t = (Term)malloc(sizeof(STerm));		   /*                        */
 						   /*                        */
  TermOp(t) = op;				   /*                        */
  TermTerm(t) = a1;				   /*                        */
  TermArg2(t) = a2;				   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_term_num()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	n	
** Returns:	
**___________________________________________________			     */
Term new_term_num(n)				   /*                        */
  long n;					   /*                        */
{						   /*                        */
  Term t = (Term)malloc(sizeof(STerm));		   /*                        */
  TermOp(t) = T_NUMBER;				   /*                        */
  TermNumber(t) = n;				   /*                        */
  TermArg2(t) = TermNULL;			   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	new_term_string()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	op	
**	 s	
** Returns:	
**___________________________________________________			     */
Term new_term_string(op, s)			   /*                        */
  int op;					   /*                        */
  char * s;					   /*                        */
{						   /*                        */
  Term t = (Term)malloc(sizeof(STerm));		   /*                        */
  TermOp(t) = op;				   /*                        */
  TermString(t) = s;				   /*                        */
  TermArg2(t) = TermNULL;			   /*                        */
  return t;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	free_term()
** Type:	void
** Purpose:	
**		
** Arguments:
**	t	
** Returns:	nothing
**___________________________________________________			     */
void free_term(t)				   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  switch (TermOp(t))				   /*                        */
  { case T_STRING:				   /*                        */
    case T_FIELD:				   /*                        */
    case T_NUMBER:				   /*                        */
      break;					   /*                        */
    default:					   /*                        */
      if (TermTerm(t)) { free_term(TermTerm(t)); } /*                        */
  }						   /*                        */
  if (TermArg2(t)) { free_term(TermArg2(t)); }	   /*                        */
  free(t);					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	dump_t()
** Type:	static void
** Purpose:	
**		
** Arguments:
**	t	
**	 in	
** Returns:	nothing
**___________________________________________________			     */
static void dump_t(stream, t, in)		   /*                        */
  FILE * stream;				   /*                        */
  Term t;					   /*                        */
  int in;					   /*                        */
{ int i;					   /*                        */
  for (i = 0; i < in; i++) fputc(' ', stream);	   /*                        */
 						   /*                        */
  if (t == TermNULL)				   /*                        */
  { fputs("nil", stream);			   /*                        */
    return;					   /*                        */
  }						   /*                        */
 						   /*                        */
  switch (TermOp(t))
  {
    case T_FIELD:
      fputs(TermString(t), stream);
      return;
    case T_STRING:
      fprintf(stream, "\"%s\"",TermString(t));
      return;
    case T_NUMBER:
      fprintf(stream, "%ld",TermNumber(t));
      return;
    case T_NOT:
      fputc('(', stream);
      dump_t(TermTerm(t), in+1);
      fputc(' ', stream);
      return;
    case T_PAIR:
      in++;
      for (; t; t = TermArg2(t))
      { if (TermTerm(t)) dump_t(stream, TermTerm(t), in); }
      return;
  }
  fputc('(', stream);
  switch(TermOp(t))
  {
    case T_EQ:     fputs("= ", stream); break;
    case T_NE:     fputs("!= ", stream); break;
    case T_LT:     fputs("< ", stream); break;
    case T_LE:     fputs("<= ", stream); break;
    case T_GT:     fputs("> ", stream); break;
    case T_GE:     fputs(" >=", stream); break;
    case T_LIKE:   fputs("like ", stream); break;
    case T_ILIKE:  fputs("ilike ", stream); break;
    case T_PLUS:   fputs("+ ", stream); break;
    case T_MINUS:  fputs("- ", stream); break;
    case T_TIMES:  fputs("* ", stream); break;
    case T_DIVIDE: fputs("/ ", stream); break;
    case T_AND:    fputs("and ", stream); break;
    case T_OR:     fputs("or ", stream); break;
    case T_FCT_LOWERCASE: fputs("lowercase ", stream); break;
    case T_FCT_UPPERCASE: fputs("uppercase ", stream); break;
    case T_FCT_SUBSTRING: fputs("substring ", stream); break;
    case T_FCT_TRIM:      fputs("trim ", stream); break;
    default:
      fprintf(stderr, "*** UNKNOWN OP CODE: %d\n", TermOp(t));
      return;
  }						   /*                        */
  dump_t(stream, TermTerm(t), in+1);		   /*                        */
  fputc(' ', stream);				   /*                        */
  dump_t(stream, TermArg2(t), in);		   /*                        */
  fputc(')', stream);				   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	dump_term()
** Type:	void
** Purpose:	
**		
** Arguments:
**	t	
** Returns:	nothing
**___________________________________________________			     */
void dump_term(t) 				   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  dump_t(stdout,t, 0);				   /*                        */
  fputc('\n', stdout);				   /*                        */
}						   /*------------------------*/

 typedef struct
 { char type;
   union
   { long num;
     char * str;
   } value;
 } STaggedValue, *TaggedValue;
