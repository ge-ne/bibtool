/*** string.c *****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2018 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/error.h>
#include <bibtool/type.h>
#include <bibtool/sbuffer.h>
#include "../binding.h"
#include "../lcore.h"

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


static Term c_string;				   /*                        */

/*-----------------------------------------------------------------------------
** Function:	m_class()
** Type:	Term
** Purpose:	Getter for the class.
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	the class
**___________________________________________________			     */
static Term m_class(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "class");	   	   	   /*                        */
  LinkTerm(c_string);				   /*                        */
  return c_string;				   /*                        */
}						   /*------------------------*/

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
  t = StringTerm(str);			   	   /*                        */
  sbclose(sb);					   /*                        */
  return t;	   	   		   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_concat()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_concat(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{ Term t;					   /*                        */
  StringBuffer *sb = sbopen();			   /*                        */
  						   /*                        */
  sbputs((char*)TString(string), sb);		   /*                        */
 						   /*                        */
  for ( ; args; args = Cdr(args))		   /*                        */
  { sbputs((char*)eval_str(binding, Car(args)), sb);/*                       */
  }						   /*                        */
 						   /*                        */
  t = StringTerm((String)sbflush(sb));		   /*                        */
  sbclose(sb);					   /*                        */
  return t;	   	   		   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_equals()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	
**	 string	
**	 args	
** Returns:	
**___________________________________________________			     */
static Term m_equals(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{ int val;					   /*                        */
  Term t = term_arg(binding, &args, "equals");	   /*                        */
  no_args(args, "equals");			   /*                        */
 						   /*                        */
  val = (t &&  IsString(t)			   /*                        */
	 && TString(string) == TString(t));	   /*                        */
  UnlinkTerm(t);				   /*                        */
  return (val ? term_true: term_false);		   /*                        */
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
{ int start, len;				   /*                        */
  StringBuffer *sb;			   	   /*                        */
  char *cp;				   	   /*                        */
  Term t;					   /*                        */
 						   /*                        */
  start = num_arg(binding, &args, "substring");	   /*                        */
    						   /*                        */
  sb = sbopen();				   /*                        */
  for (cp = (char*)TString(string);		   /*                        */
       *cp && start-- > 0;			   /*                        */
       cp++);  					   /*                        */
 						   /*                        */
  if (args)				   	   /*                        */
  { len = num_arg(binding, &args, "substring");	   /*                        */
    no_args(args, "substring");			   /*                        */
 						   /*                        */
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

#define Bind(NAME,GET)  bind(b, symdef(symbol((String)NAME),     \
				       0, 0, GET, NULL));

/*-----------------------------------------------------------------------------
** Function:	class_string()
** Type:	Term
** Purpose:	
**		
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
Term class_string()				   /*                        */
{ Binding b;					   /*                        */
 						   /*                        */
  if (c_string == NIL)			   	   /*                        */
  { c_string = new_class(StringTerm("String"));	   /*                        */
    b = TBinding(c_string);			   /*                        */
 						   /*                        */
    Bind("as.boolean", m_as_boolean);		   /*                        */
    Bind("as.string", m_as_string);		   /*                        */
    Bind("as.number", m_as_number);		   /*                        */
    Bind("class", m_class);			   /*                        */
    Bind("concat", m_concat);			   /*                        */
    Bind("equals", m_equals);			   /*                        */
    Bind("length", m_length);			   /*                        */
    Bind("substring", m_substring);		   /*                        */
    Bind("trim", m_trim);			   /*                        */
  }						   /*                        */
 						   /*                        */
  return c_string;				   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
