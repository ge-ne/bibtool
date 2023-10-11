/*** pxfile.h *****************************************************************
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
**	This module provides access to the functions and
**	variables defined in |pxfile.c|. Consult also the documentation
**	of this file for details.
**
**	This header file automatically includes |bibtool.h| and |<stdio.h>|.
**
******************************************************************************/

#include <stdio.h>

extern char * px_filename;

extern FILE * px_fopen(
#ifdef __STDC__
	char  * name,
	char  * mode,
	char  **pattern,
	char  **path,
	int   (*show)(char*)
#endif
	);

extern char **px_s2p(
#ifdef __STDC__
	char  * s,
	int   sep
#endif
	);

