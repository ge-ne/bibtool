/*** cstring.c*****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015-2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


static Term m_substring(binding, s, args)
  Binding binding;
  String s;
  Term args;
{ int start, length;

  if (args == NULL )
    ErrorNF1("Missing argument for substring");	   /*                        */


  
  return NIL;
}


Term meth_string(binding, string, meth)
  Binding binding;
  Term string;
  Term meth;
{ String m = TString(meth);
  String s = TString(string);

  if (strcmp((char*)m, "length") == 0)
  { if (Cdr(meth))				   /*                        */
      ErrorNF2("Too many arguments for ", m);	   /*                        */
    return NumberTerm(strlen((char*)s));	   /*                        */
  }						   /*                        */
  else if (strcmp((char*)m, "substring") == 0)
  { return m_substring(binding, s, Cdr(meth));
  }
  else if (strcmp((char*)m, "toString") == 0)
  { LinkTerm(string);
  }
  else
    ErrorNF2("Undefined method ", s);	   	   /*                        */

  return string;				   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/
