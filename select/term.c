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
#include "commands.h"

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
  TermTerm2(t) = a2;				   /*                        */
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
  TermOp(t) = NUMBER;				   /*                        */
  TermNumber(t) = n;				   /*                        */
  TermTerm2(t) = TermNULL;			   /*                        */
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
  TermTerm2(t) = TermNULL;			   /*                        */
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
  { case STRING:				   /*                        */
    case FIELD:				   /*                        */
    case NUMBER:				   /*                        */
      break;					   /*                        */
    default:					   /*                        */
      if (TermTerm(t)) { free_term(TermTerm(t)); } /*                        */
  }						   /*                        */
  if (TermTerm2(t)) { free_term(TermTerm2(t)); }	   /*                        */
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
    case FIELD:
      fputs(TermString(t), stream);
      return;
    case STRING:
      fprintf(stream, "\"%s\"",TermString(t));
      return;
    case BLOCK:
      fprintf(stream, "{%s}",TermString(t));
      return;
    case NUMBER:
      fprintf(stream, "%ld",TermNumber(t));
      return;
    case NOT:
      fputc('(', stream);
      dump_t(TermTerm(t), in+1);
      fputc(' ', stream);
      return;
    case PAIR:
      in++;
      for (; t; t = TermTerm(t))
      { if (TermTerm2(t)) dump_t(stream, TermTerm2(t), in); }
      return;
  }
  fputc('(', stream);
  switch(TermOp(t))
  {
    case EQ:     fputs("= ", stream); break;
    case NE:     fputs("!= ", stream); break;
    case LT:     fputs("< ", stream); break;
    case LE:     fputs("<= ", stream); break;
    case GT:     fputs("> ", stream); break;
    case GE:     fputs(" >=", stream); break;
    case LIKE:   fputs("like ", stream); break;
    case ILIKE:  fputs("ilike ", stream); break;
    case PLUS:   fputs("+ ", stream); break;
    case MINUS:  fputs("- ", stream); break;
    case TIMES:  fputs("* ", stream); break;
    case DIVIDE: fputs("/ ", stream); break;
    case AND:    fputs("and ", stream); break;
    case OR:     fputs("or ", stream); break;
    case FCT_LOWERCASE: fputs("lowercase ", stream); break;
    case FCT_UPPERCASE: fputs("uppercase ", stream); break;
    case FCT_SUBSTRING: fputs("substring ", stream); break;
    case FCT_TRIM:      fputs("trim ", stream); break;
    default:
      fprintf(stderr, "*** UNKNOWN OP CODE: %d\n", TermOp(t));
      return;
  }						   /*                        */
  dump_t(stream, TermTerm(t), in + 1);		   /*                        */
  fputc(' ', stream);				   /*                        */
  dump_t(stream, TermTerm2(t), in);		   /*                        */
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
