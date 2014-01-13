/*** tex_read.h ***************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2014 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
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
 int TeX_read _ARG((Uchar * cp,Uchar **sp));	   /* tex-read.c             */
 void TeX_active _ARG((int c,int arity,unsigned char * s));/* tex_read.c     */
 void TeX_close _ARG((void));			   /* tex_read.c             */
 void TeX_def _ARG((unsigned char *s));		   /* tex_read.c             */
 void TeX_define _ARG((char *name,int arity,char *body));/* tex_read.c       */
 void TeX_open_file _ARG((FILE * file));	   /* tex_read.c             */
 void TeX_open_string _ARG((unsigned char * s));   /* tex_read.c             */
 void TeX_reset _ARG((void));			   /* tex_read.c             */
