/*** tex_aux.h ****************************************************************
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
******************************************************************************/

#include <bibtool/database.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 bool read_aux _ARG((String fname,void (*fct)(Symbol),bool verbose));/*tex_aux.c*/
 bool apply_aux _ARG((DB db));			   /* tex_aux.c              */
 bool foreach_aux _ARG((bool (fct)_ARG((Symbol))));/* tex_aux.c              */
 bool aux_used _ARG((Symbol s));		   /* tex_aux.c              */
 void clear_aux _ARG((void));			   /* tex_aux.c              */

/*---------------------------------------------------------------------------*/
