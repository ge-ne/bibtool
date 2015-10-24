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
char* eval2string(db, rec, t)			   /*                        */
  DB db;					   /*                        */
  Record rec;					   /*                        */
  Term t;					   /*                        */
{ char * s;					   /*                        */
  if (t == TermNULL) return NULL;		   /*                        */

  switch(TermOp(t))
  { case T_FIELD:
      s = get_field(db, rec, TermString(t));
      return s;
    case T_STRING:
      return TermString(t);
    case T_FCT_LOWERCASE:
      { char *cp;
	for (s=cp=eval2string(db, rec, TermTerm(t));*cp;cp++)
	{ *cp = tolower(*cp); }
        return s;
      }
    case T_FCT_UPPERCASE:
      { char *cp;
	for (s=cp=eval2string(db, rec, TermTerm(t));*cp;cp++)
	{ *cp = toupper(*cp); }
        return s;
      }
    case T_FCT_TRIM:
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
long eval2number(db, rec, t)			   /*                        */
  DB db;					   /*                        */
  Record rec;					   /*                        */
  Term t;					   /*                        */
{						   /*                        */
  if (t == TermNULL) return 0L;			   /*                        */
 						   /*                        */
  switch(TermOp(t))				   /*                        */
  { case T_FIELD:
      { char *s = get_field(db, rec, TermString(t));
        return s ? atol(s) : 0L;
      }
    case T_NUMBER:
      return TermNumber(t);
    case T_UMINUS:
      return - eval2number(db, rec, TermTerm(t));
    case T_PLUS:
      return eval2number(db, rec, TermTerm(t)) +
	eval2number(db, rec, TermTerm2(t));
    case T_MINUS:
      return eval2number(db, rec, TermTerm(t)) -
	eval2number(db, rec, TermTerm2(t));
    case T_TIMES:
      return eval2number(db, rec, TermTerm(t)) *
	eval2number(db, rec, TermTerm2(t));
    case T_DIVIDE:
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
  { case T_NUMBER:
      switch (TermOp(t2))
      { case T_NUMBER:
	  return TermNumber(t1) == TermNumber(t2);
	case T_FIELD:
	  s2 = get_field(db, rec, TermString(t2));
	  break;
	case T_STRING:
	case T_BLOCK:
	  s2 = TermString(t2);
	  break;
	default:
	  return FALSE;
      }
      sprintf(s,"%d",TermNumber(t1));
      return strcmp(s2, s);
      break;
    case T_FIELD:
      s1 = get_field(db, rec, TermString(t1));
      break;
    case T_STRING:
    case T_BLOCK:
      s1 = TermString(t1);
      break;
    default:
      return FALSE;
  }

  switch (TermOp(t2))
  { case T_FIELD:
      s2 = get_field(db, rec, TermString(t2));
      break;
    case T_NUMBER:
      sprintf(s,"%d",TermNumber(t2));
      s2 = s;
      break;
    case T_STRING:
    case T_BLOCK:
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
    case T_AND:
      return eval_select(TermTerm(t)) && eval_select(TermTerm2(t));
    case T_OR:
      return eval_select(TermTerm(t)) || eval_select(TermTerm2(t));
    case T_NOT:
      return ! eval_select(TermTerm(t));
    case T_EQ:
      return eval_eq(db, rec, TermTerm(t), TermTerm2(t));
    case T_NE:
      return ! eval_eq(db, rec, TermTerm(t), TermTerm2(t));
      /*
    case T_LT:
    case T_LE:
    case T_GT:
    case T_GE:
      */
#ifdef REGEX
    case T_LIKE:
    case T_ILIKE:
      { char * v = eval2string(TermTerm(t));
	char * pattern = eval2string(TermTerm2(t));
      }
#endif
  }						   /*                        */
 						   /*                        */
  return FALSE;					   /*                        */
}						   /*------------------------*/
