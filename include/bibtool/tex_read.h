/*** tex_read.h ***************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2020 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2, or (at your option)
** any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
**-----------------------------------------------------------------------------
** Description:
**	This header file provides definitions for the use of functions
**	to immitate the reading apparatus of \TeX{} which are defined
**	in |tex_read.c|. 
**	    
******************************************************************************/

#include <stdio.h>
#include <bibtool/type.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 bool TeX_read _ARG((String cp, String *sp));	   /* tex-read.c             */
 void TeX_active _ARG((int c,int arity, String s));/* tex_read.c             */
 void TeX_close _ARG((void));			   /* tex_read.c             */
 void TeX_def _ARG((String s));		   	   /* tex_read.c             */
 void TeX_define _ARG((char *name,int arity,char *body));/* tex_read.c       */
 void TeX_open_file _ARG((FILE * file));	   /* tex_read.c             */
 void TeX_open_string _ARG((String s));   	   /* tex_read.c             */
 void TeX_reset _ARG((void));			   /* tex_read.c             */

/*---------------------------------------------------------------------------*/
