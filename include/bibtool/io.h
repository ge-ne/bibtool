/*** io.h *********************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2018-2020 Gerd Neugebauer
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
**	This header file provides functions to deal with file I/O.
**
******************************************************************************/

#include <bibtool/symbols.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

 extern void save_input_file _ARG((Symbol file));  /*                        */
 extern void save_macro_file _ARG((Symbol file));  /*                        */
 extern void save_output_file _ARG((Symbol file)); /*                        */
 extern int get_no_inputs();			   /*                        */
 extern Symbol get_input_file _ARG((int i));	   /*                        */
 extern Symbol get_macro_file();   		   /*                        */
 extern Symbol get_output_file(); 		   /*                        */
