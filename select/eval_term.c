/*** eval_term.c ***************************************************************
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

#include "eval_term.h"
#include "commands.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

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
char* eval2string(db, rec, t)			   /*                        */
  DB db;					   /*                        */
  Record rec;					   /*                        */
  Term t;					   /*                        */
{ char * s;					   /*                        */
  if (t == TermNULL) return NULL;		   /*                        */

  switch(TermOp(t))
  { case FIELD:
      s = get_field(db, rec, TermString(t));
      return s;
    case STRING:
      return TermString(t);
    case FCT_LOWERCASE:
      { char *cp;
	for (s=cp=eval2string(db, rec, TermTerm(t));*cp;cp++)
	{ *cp = tolower(*cp); }
        return s;
      }
    case FCT_UPPERCASE:
      { char *cp;
	for (s=cp=eval2string(db, rec, TermTerm(t));*cp;cp++)
	{ *cp = toupper(*cp); }
        return s;
      }
    case FCT_TRIM:
      { char *cp;
	s = cp = eval2string(db, rec, TermTerm(t));
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
    case FCT_SUBSTRING:
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
long eval2number(db, rec, t)			   /*                        */
  DB db;					   /*                        */
  Record rec;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  if (t == TermNULL) return 0L;			   /*                        */
 						   /*                        */
  switch(TermOp(t))				   /*                        */
  { case FIELD:
      { char *s = get_field(db, rec, TermString(t));
        return s ? atol(s) : 0L;
      }
    case NUMBER:
      return TermNumber(t);
    case UMINUS:
      return - eval2number(db, rec, TermTerm(t));
    case PLUS:
      return eval2number(db, rec, TermTerm(t)) +
	eval2number(db, rec, TermTerm2(t));
    case MINUS:
      return eval2number(db, rec, TermTerm(t)) -
	eval2number(db, rec, TermTerm2(t));
    case TIMES:
      return eval2number(db, rec, TermTerm(t)) *
	eval2number(db, rec, TermTerm2(t));
    case DIVIDE:
      return eval2number(db, rec, TermTerm(t)) /
	eval2number(db, rec, TermTerm2(t));
  }						   /*                        */
  return 0L;					   /*                        */
}						   /*------------------------*/

int eval_eq(db, rec, t1, t2)
  DB db;					   /*                        */
  Record rec;					   /*                        */
  Term t1;
  Term t2;
{ static char s[64];
  char *s1, *s2;

  if (t1 == NULL) { return (t2 == NULL); }
  if (t2 == NULL) { return FALSE; }

  switch (TermOp(t1))
  { case NUMBER:
      switch (TermOp(t2))
      { case NUMBER:
	  return TermNumber(t1) == TermNumber(t2);
	case FIELD:
	  s2 = get_field(db, rec, TermString(t2));
	  break;
	case STRING:
	case BLOCK:
	  s2 = TermString(t2);
	  break;
	default:
	  return FALSE;
      }
      sprintf(s,"%d",TermNumber(t1));
      return strcmp(s2, s);
      break;
    case FIELD:
      s1 = get_field(db, rec, TermString(t1));
      break;
    case STRING:
    case BLOCK:
      s1 = TermString(t1);
      break;
    default:
      return FALSE;
  }

  switch (TermOp(t2))
  { case FIELD:
      s2 = get_field(db, rec, TermString(t2));
      break;
    case NUMBER:
      sprintf(s,"%d",TermNumber(t2));
      s2 = s;
      break;
    case STRING:
    case BLOCK:
      s2 = TermString(t2);
      break;
    default:
      return FALSE;
  }
  return strcmp(s1, s2);			   /*                        */
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
int eval_select(db, rec, t)			   /*                        */
  Term t;					   /*                        */
  DB db;					   /*                        */
  Record rec;					   /*                        */
{						   /*                        */
  if (t == TermNULL) return FALSE;		   /*                        */
 						   /*                        */
  switch(TermOp(t))				   /*                        */
  {						   /*                        */
    case AND:
      return eval_select(TermTerm(t)) && eval_select(TermTerm2(t));
    case OR:
      return eval_select(TermTerm(t)) || eval_select(TermTerm2(t));
    case NOT:
      return ! eval_select(TermTerm(t));
    case EQ:
      return eval_eq(db, rec, TermTerm(t), TermTerm2(t));
    case NE:
      return ! eval_eq(db, rec, TermTerm(t), TermTerm2(t));
      /*
    case LT:
    case LE:
    case GT:
    case GE:
      */
#ifdef REGEX
    case LIKE:
    case ILIKE:
      { char * v = eval2string(TermTerm(t));
	char * pattern = eval2string(TermTerm2(t));
      }
#endif
  }						   /*                        */
 						   /*                        */
  return FALSE;					   /*                        */
}						   /*------------------------*/
