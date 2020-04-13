/*** print.h ******************************************************************
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
**	This header file provides access to the functions and
**	variables defined in |print.c|. Consult also the documentation
**	of this file for details.
**
**	This header file automatically includes |record.h| and |database.h|.
**
******************************************************************************/

#include <bibtool/record.h>
#include <bibtool/database.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 char *sput_record _ARG((Record rec,DB db,String start));/* print.c          */
 void fput_record _ARG((FILE *file,Record rec,DB db,String start));/* print.c*/
 void put_record _ARG((int (*fct)_ARG((int)),Record rec,DB db, String start));/* print.c*/
 void set_key_type _ARG((String s));		   /* print.c                */
 void set_symbol_type _ARG((String s));	   	   /* print.c                */
 String get_symbol_type _ARG(());	   	   /* print.c                */
