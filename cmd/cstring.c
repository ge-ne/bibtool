/*** cstring.c*****************************************************************
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


Binding cs_binding = NULL;		   	   /*                        */

#define Bind(NAME,GET)  bind(cs_binding, symdef(symbol((String)NAME),     \
						0, 0, GET, NULL));

/*-----------------------------------------------------------------------------
** Function:	m_length()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_length(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "length");	   	   	   /*                        */
  return NumberTerm(strlen((char*)TString(string)));/*                       */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_as_string()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_as_string(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "as.string");  		   	   /*                        */
  LinkTerm(string);				   /*                        */
  return string;	   	   		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_as_number()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_as_number(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "as.number");  		   	   /*                        */
 						   /*                        */
  return eval_num(binding, string);		   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_trim()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_trim(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{ String s = TString(string);			   /*                        */
  StringBuffer *sb;			   	   /*                        */
  char *cp, *str;				   /*                        */
  Term t;					   /*                        */
  no_args(args, "trim");	   	   	   /*                        */
 						   /*                        */
  sb = sbopen();				   /*                        */
  sbputs((char*)s, sb);				   /*                        */
  str = sbflush(sb);				   /*                        */
  while (is_space(*str)) str++;			   /*                        */
  cp = str;					   /*                        */
  while (*cp) cp++;				   /*                        */
  for (cp--; cp	>= str && is_space(*cp) ;cp--)	   /*                        */
    *cp = '\0';					   /*                        */
 						   /*                        */
  t = StringTerm((String)str);			   /*                        */
  sbclose(sb);					   /*                        */
  return t;	   	   		   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_substring()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_substring(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{ String s = TString(string);			   /*                        */
  int start, len;				   /*                        */
  StringBuffer *sb;			   	   /*                        */
  char *cp;				   	   /*                        */
  Term t;					   /*                        */
 						   /*                        */
  if (args == NULL )				   /*                        */
    ErrorNF1("Missing argument for substring");	   /*                        */
 						   /*                        */
  t	= eval_num(binding, Car(args));		   /*                        */
  start = TNumber(t);				   /*                        */
  UnlinkTerm(t);				   /*                        */
 						   /*                        */
  sb = sbopen();				   /*                        */
  for (cp = (char*)s; *cp && start-- > 0 ; cp++);  /*                        */
 						   /*                        */
  if (Cdr(args))				   /*                        */
  { t   = eval_num(binding, Cadr(args));	   /*                        */
    len = TNumber(t);				   /*                        */
    UnlinkTerm(t);				   /*                        */
    for (; *cp && len-- > 0 ; cp++)		   /*                        */
    { sbputchar(*cp, sb); }			   /*                        */
  }						   /*                        */
  else						   /*                        */
  { for (; *cp; cp++)				   /*                        */
    { sbputchar(*cp, sb); }			   /*                        */
  }						   /*                        */
 						   /*                        */
  t = StringTerm((String)sbflush(sb));		   /*                        */
  sbclose(sb);					   /*                        */
  return t;	   	   		   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	class_string()
** Type:	void
** Purpose:	
**		
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void class_string()				   /*                        */
{						   /*                        */
  cs_binding = binding(127, NULL);		   /*                        */
 						   /*                        */
  Bind("as.string", m_as_string);		   /*                        */
  Bind("as.number", m_as_number);		   /*                        */
  Bind("length", m_length);			   /*                        */
  Bind("substring", m_substring);		   /*                        */
  Bind("trim", m_trim);		   		   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
