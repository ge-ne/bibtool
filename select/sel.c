/*** sel.c ********************************************************************
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

#include <bibtool/bibtool.h>
#include "term.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/
 char* eval2string();

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
** Function:	eval2string()
** Type:	char*
** Purpose:	
**		
** Arguments:
**	t	
** Returns:	
**___________________________________________________			     */
char* eval2string(t)				   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  if (t == TermNULL) return NULL;		   /*                        */

  switch(TermOp(t))
  { case T_FIELD:
						   /* TODO*/
      break;
    case T_STRING:
      return TermString(t);
    case T_FCT_LOWERCASE:
      { char *s, *cp;
	for(s=cp=eval2string(TermTerm(t));*cp;cp++)
	{ *cp = tolower(*cp); }
        return s;
      }
    case T_FCT_UPPERCASE:
      { char *s, *cp;
	for(s=cp=eval2string(TermTerm(t));*cp;cp++)
	{ *cp = toupper(*cp); }
        return s;
      }
    case T_FCT_TRIM:
      { char *s, *cp;
	s = cp = eval2string(TermTerm(t));
	if (isspace(*s)) {
	  char* x = s;
	  for (x++;isspace(*x);x++);
	  while (*x) *(cp++) = *(x++);
	  cp = s;
	}
	while (*cp) { cp++; }
	while (cp >= s && isspace(*cp)) cp--;
        return s;
      }
      /*
    case T_FCT_SUBSTRING:
      */
  }
  return NULL;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval2number()
** Type:	long
** Purpose:	
**		
** Arguments:
**	t	
** Returns:	
**___________________________________________________			     */
long eval2number(t)				   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  if (t == TermNULL) return 0L;			   /*                        */
 						   /*                        */
  switch(TermOp(t))				   /*                        */
  { case T_FIELD:
						   /* TODO*/
      break;
    case T_NUMBER:
      return TermNumber(t);
    case T_UMINUS:
      return - eval2number(TermTerm(t));
    case T_PLUS:
      return eval2number(TermTerm(t)) + eval2number(TermArg2(t));
    case T_MINUS:
      return eval2number(TermTerm(t)) - eval2number(TermArg2(t));
    case T_TIMES:
      return eval2number(TermTerm(t)) * eval2number(TermArg2(t));
    case T_DIVIDE:
      return eval2number(TermTerm(t)) / eval2number(TermArg2(t));
  }						   /*                        */
  return 0L;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	eval_select()
** Type:	int
** Purpose:	
**		
** Arguments:
**	t	
** Returns:	
**___________________________________________________			     */
int eval_select(rec, db, t)			   /*                        */
  Term t;					   /*                        */
  DB db;					   /*                        */
  Record rec;					   /*                        */
{						   /*                        */
  if (t == TermNULL) return FALSE;		   /*                        */
 						   /*                        */
  switch(TermOp(t))				   /*                        */
  {						   /*                        */
    case T_AND:
      return eval_select(TermTerm(t)) && eval_select(TermArg2(t));
    case T_OR:
      return eval_select(TermTerm(t)) || eval_select(TermArg2(t));
    case T_NOT:
      return ! eval_select(TermTerm(t));
      /*
    case T_EQ:
    case T_NE:
    case T_LT:
    case T_LE:
    case T_GT:
    case T_GE:
      */
#ifdef REGEX
    case T_LIKE:
    case T_ILIKE:
      { char * v = eval2string(TermTerm(t));
	char * pattern = eval2string(TermArg2(t));
      }
#endif
  }						   /*                        */
 						   /*                        */
  return FALSE;					   /*                        */
}						   /*------------------------*/
