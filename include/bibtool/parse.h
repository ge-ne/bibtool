/*** parse.h ******************************************************************
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
**	This header file contains functions which deal with the
**	parsing of \BibTeX{} files. They are defined in |parse.c| and
**	declared in this file.
**	
******************************************************************************/

#include <bibtool/record.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 bool read_rsc _ARG((String name));		   /* parse.c                */
 bool see_bib _ARG((String fname));		   /* parse.c                */
 bool seen _ARG((void));			   /* parse.c                */
 int parse_bib _ARG((Record rec));		   /* parse.c                */
 void init_read _ARG((void));			   /* parse.c                */
 void set_rsc_path _ARG((String val));		   /* parse.c                */
