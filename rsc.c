/******************************************************************************
** $Id: rsc.c,v 1.6 2010-01-05 14:06:06 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2010 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
**-----------------------------------------------------------------------------
** Description:
**	This module contains functions which deal with resources.
**	Resources are commands to configure the behaviour of
**	\BibTool. They can be read either from a file or from a
**	string. 
**
**	The syntax of resources are modelled after the syntax rules
**	for \BibTeX{} files. See the user's guide for details of the syntax.
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/error.h>
#include <bibtool/symbols.h>
#include <bibtool/macros.h>
#include <bibtool/parse.h>
#include <bibtool/print.h>
#include <bibtool/tex_aux.h>
#include <bibtool/tex_read.h>
#include <bibtool/key.h>
#include <bibtool/rewrite.h>
#include <bibtool/s_parse.h>
#include <bibtool/entry.h>
#include <bibtool/type.h>
#include <bibtool/version.h>
#include "config.h"
#define RSC_INIT
#include <bibtool/rsc.h>

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 int load_rsc _ARG((char *name));
 int resource _ARG((char *name));
 int search_rsc _ARG((void));
 int set_rsc _ARG((Uchar *name,Uchar *val));
 int use_rsc _ARG((Uchar *s));
 static int test_true _ARG((Uchar * s));
 static void init_rsc _ARG((void));
 void rsc_print _ARG((char *s));

#define NoRscError(X)	      WARNING3("Resource file ",X," not found.")

/*****************************************************************************/
/* External Programs							     */
/*===========================================================================*/

 extern void save_input_file _ARG((char *file));   /* main.c		     */
 extern void save_macro_file _ARG((char * file));  /* main.c		     */
 extern void save_output_file _ARG((char * file)); /* main.c		     */

#ifndef __STDC__
#ifndef HAVE_GETENV
 extern char * getenv _ARG((char* name));	   /*			     */
#endif
#endif

/*---------------------------------------------------------------------------*/

#define RscNumeric(SYM,S,V,I) static Uchar *S = (Uchar*)NULL;
#define RscString(SYM,S,V,I)  static Uchar *S = (Uchar*)NULL;
#define RscBoolean(SYM,S,V,I) static Uchar *S = (Uchar*)NULL;
#define RscByFct(SYM,S,FCT)   static Uchar *S = (Uchar*)NULL;
#include <bibtool/resource.h>

/*-----------------------------------------------------------------------------
** Function:	init_rsc()
** Purpose:	This function performs resource initializations.  It
**		is necessary to call this function before the other
**		functions in this module can be expected to work
**		properly. Thus it is called at the beginning of the
**		functions is question.
** Details:
**		Initialize the key words.
**		Tricky use of CPP. The header file resource.h is included 
**		for the second time. To avoid confusion in makedepend the 
**		hader file is only included if MAKEDPEND is not defined.
**		The same trick can be found again later.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
static void init_rsc()				   /*			     */
{						   /*			     */
#define RscNumeric(SYM,S,V,I)  S = symbol((Uchar*)SYM);
#define RscString(SYM,S,V,I)   S = symbol((Uchar*)SYM);
#define RscBoolean(SYM,S,V,I)  S = symbol((Uchar*)SYM);
#define RscByFct(SYM,S,FCT)    S = symbol((Uchar*)SYM);
#ifndef MAKEDEPEND
#include <bibtool/resource.h>
#endif
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	search_rsc()
** Purpose:	Try to open the resource file at different places:
**		\begin{itemize}
**		\item In the place indicated by the environment variable
**		  |RSC_ENV_VAR|. This step is skipped if the macro
**		  |RSC_ENV_VAR| is not defined (at compile time of the
**		  module).
**		\item In the home directory.  The home directory is
**		  determined by an environment variable.  The macro
**		  |HOME_ENV_VAR| contains the name of this environment
**		  variable. If this macro is not defined (at
**		  compile time of the module) then this step is skipped.
**		\item In the usual place for resource files.
**		\end{itemize}
**		For each step |load_rsc()| is called until it
**		succeeds.
**
**		The files sought is determined by the macro
**		|DefaultResourceFile| at compile time of the
**		module. (see |bibtool.h|)
** Arguments:	none
** Returns:	|TRUE| iff the resource loading succeeds somewhere.
**___________________________________________________			     */
int search_rsc()				   /*			     */
{ static char	*def = DefaultResourceFile;	   /*			     */
  register char *ap;				   /*			     */
  register char *fn;				   /*			     */
  int		l;				   /*			     */
						   /*			     */
#ifdef RSC_ENV_VAR
  if ( (ap=getenv(RSC_ENV_VAR)) != NULL		   /* Try to get the name    */
      && load_rsc(ap) ) return TRUE;		   /*  from the environment. */
#endif
						   /*			     */
#ifdef HOME_ENV_VAR
  if ( (ap=getenv(HOME_ENV_VAR)) != NULL )	   /* Try to get the resource*/
  { l = strlen(ap)+strlen(DIR_SEP)+strlen(def)+1;  /*  file from the home    */
    if ( (fn=malloc(l)) != NULL )		   /*  directory	     */
    { (void)strcpy(fn,ap);			   /*			     */
      (void)strcat(fn,DIR_SEP);			   /*			     */
      (void)strcat(fn,def);			   /*			     */
      l = load_rsc(fn);				   /*			     */
      free(fn);					   /*			     */
      if ( l ) return TRUE;			   /*			     */
    }						   /*			     */
  }						   /*			     */
#endif
						   /* if all fails then try  */
  return load_rsc(def);				   /*  to use a default.     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	load_rsc()
** Purpose:	This function tries to load a resource file. 
** Details:
** 		Perform initialization if required.
** 		The main job is done by |read_rsc()|. This function is located
** 		in |parse.c| since it shares subroutines with the parser.
** Arguments:
**	name	The name of the resource file to read.
** Returns:	|FALSE| iff the reading failed.
**___________________________________________________			     */
int load_rsc(name)			   	   /*			     */
  register char *name;				   /*			     */
{						   /*			     */
  if ( r_v == NULL ) { init_rsc(); }		   /*			     */
  return ( name != NULL ? read_rsc(name) : 0 );	   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	resource()
** Type:	int
** Purpose:	
**		
** Arguments:
**	name	
**	 warnp	
** Returns:	
**___________________________________________________			     */
int resource(name)			   	   /*			     */
  register char *name;				   /*			     */
{						   /*			     */
  int ret = load_rsc(name);			   /*                        */
  if ( !ret )
  { NoRscError(name); }
  return ret;	   				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	test_true()
** Purpose:	A boolean resource can be set to true in different ways:
**		|true|, |t|, |yes|, |on|, |1|
**		which represent ``true''.  Each other value is
**		interpreted as ``false''. 
**		The comparison is done case insensitive.
** Arguments:
**	s	String to check for the boolean value.
** Returns:	|TRUE| iff the string represents true.
**___________________________________________________			     */
static int test_true(s)				   /*			     */
  Uchar * s;				   	   /*			     */
{						   /*			     */
  switch ( *s )					   /*                        */
  { case '1':		return (s[1] == '\0');
    case 'o': case 'O':
      return ((s[1] == 'n' || s[1] == 'N') &&
	      s[2] == '\0' );
    case 'y': case 'Y':
      return ((s[1] == 'e' || s[1] == 'E') &&
	      (s[2] == 's' || s[2] == 'S') &&
	      s[3] == '\0' );
    case 't': case 'T':
      return (s[1] == '\0' ||
	      ((s[1] == 'r' || s[1] == 'R') &&
	       (s[2] == 'u' || s[2] == 'U') &&
	       (s[3] == 'e' || s[3] == 'E') &&
	       s[4] == '\0'));
  }						   /*                        */
  return 0;					   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	use_rsc()
** Purpose:	This function can be used to evaluate a single
**		resource instruction. The argument is a string which
**		is parsed to extract the resource command.
**
**		This is an entry point for command line options which
**		set resources. 
** Arguments:
**	s	String containg a resource command.
** Returns:	|FALSE| iff no error has occurred.
**___________________________________________________			     */
int use_rsc(s)					   /*			     */
  Uchar		*s;				   /*			     */
{ register Uchar *name,				   /*			     */
		 *value;			   /*			     */
						   /*			     */
  (void)sp_open(s);				   /*			     */
  if ( (name = SParseSymbol(&s)) == NULL ) return 1; /*			     */
						   /*			     */
  (void)SParseSkip(&s);				   /*                        */
						   /*			     */
  if ( (value = SParseValue(&s)) == NULL )	   /*                        */
  { ReleaseSymbol(name);			   /*                        */
    return 1; 					   /*			     */
  }						   /*                        */
						   /*			     */
  if ( r_v == NULL ) { init_rsc(); }		   /*			     */
						   /*			     */
  return set_rsc(name,value);			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	set_rsc()
** Purpose:	Set the resource to a given value. Here the assignment
**		is divided into two parts: the name and the value.
**		Both arguments are assumed to be symbols.
** Arguments:
**	name	Name of the resource to set.
**	val	The new value of the resource.
** Returns:	|FALSE| iff everything went right.
**___________________________________________________			     */
int set_rsc(name,val)				   /*			     */
  Uchar *name;				   	   /*			     */
  Uchar *val;				   	   /*			     */
{						   /*			     */
  if ( rsc_verbose )				   /*			     */
  { VerbosePrint4("Resource ",			   /*                        */
		  (char*)name,			   /*                        */
		  " = ",			   /*                        */
		  (val==NULL?"*NULL*":(char*)val));/*	                     */
  }						   /*                        */
						   /*			     */
#define SETQ(V,T) V=T; ReleaseSymbol(name);
#define RscNumeric(SYM,S,V,I)		\
  if( name==S ) { SETQ(V,atoi((char*)val));  ReleaseSymbol(val); return 0; }
#define RscString(SYM,S,V,I)		\
  if( name==S ) { ReleaseSymbol(V); V = val; ReleaseSymbol(name); return 0; }
#define RscBoolean(SYM,S,V,I)		\
  if( name==S ) { SETQ(V,test_true(val));    ReleaseSymbol(val); return 0; }
#define RscByFct(SYM,S,FCT)		\
  if( name==S ) { (void)FCT; ReleaseSymbol(name); 	  return 0; }
#define RSC_FIRST(C)	      case C:
#define RSC_NEXT(C)	      break; case C:
						   /*			     */
  switch( *name )				   /*			     */
  {						   /*			     */
#ifndef MAKEDEPEND
#include <bibtool/resource.h>
#endif
  }						   /*			     */
						   /*			     */
  ERROR3("Resource ",name," unknown.");		   /*			     */
  return 1;					   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	rsc_print()
** Purpose:	Print a string to the error stream as defined in
**		|error.h|. The string is automatically augmented by a
**		trailing newline.
**		This wrapper function is used for the resource |print|.
** Arguments:
**	s	String to print.
** Returns:	nothing
**___________________________________________________			     */
void rsc_print(s)				   /*			     */
  char *s;				   	   /*			     */
{ ErrPrintF("%s\n",s);				   /* print the string itself*/
			   			   /* followed by a newline  */
}						   /*------------------------*/
