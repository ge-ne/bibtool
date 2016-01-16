/*** tex_aux.h ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2016 Gerd Neugebauer
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
 int foreach_aux _ARG((int (fct)_ARG((String))));  /* tex_aux.c              */
 int aux_used _ARG((String s));	   		   /* tex_aux.c              */
 int read_aux _ARG((String fname,void (*fct)(char*),int verbose));/*tex_aux.c*/
 void clear_aux _ARG((void));			   /* tex_aux.c              */
