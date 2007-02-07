/******************************************************************************
** $Id: tex_read.h,v 1.1 2007-02-07 21:31:53 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-1997 Gerd Neugebauer
** 
** Net: gerd@informatik.uni-koblenz.de
** 
**-----------------------------------------------------------------------------
** Description:
**	This header file provides definitions for the use of functions
**	to immitate the reading apparatus of \TeX{} which are defined
**	in |tex_read.c|. 
**	    
******************************************************************************/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 int TeX_read _ARG((char * cp,char **sp));	   /* tex-read.c             */
 void TeX_active _ARG((int c,int arity,char * s)); /* tex-read.c             */
 void TeX_close _ARG((void));			   /* tex-read.c             */
 void TeX_def _ARG((char *s));			   /* tex-read.c             */
 void TeX_define _ARG((char *name,int arity,char *body));/* tex-read.c       */
 void TeX_open_file _ARG((FILE * file));	   /* tex-read.c             */
 void TeX_open_string _ARG((char * s));		   /* tex-read.c             */
 void TeX_reset _ARG((void));			   /* tex_read.c             */

