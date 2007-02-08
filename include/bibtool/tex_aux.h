/******************************************************************************
** $Id: tex_aux.h,v 1.3 2007-02-08 05:35:57 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2002 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/database.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 int apply_aux _ARG((DB db));			   /* tex_aux.c              */
 int foreach_aux _ARG((int (fct)_ARG((Uchar*))));  /* tex_aux.c              */
 int aux_used _ARG((char *s));	   		   /* tex_aux.c              */
 int read_aux _ARG((char *fname,void (*fct)(char*),int verbose));/* tex_aux.c*/
 void clear_aux _ARG((void));			   /* tex_aux.c              */
