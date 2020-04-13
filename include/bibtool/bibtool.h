/*** bibtool.h ****************************************************************
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
**	This header file contains includes for all other header files
**	belonging to the \BibTool{} C library. It is here for the
**	convenience of the C programmer who does not have to include
**	two dozen header files but can use this single file. Thus any
**	C program which utilizes the \BibTool{} C library can start as
**	follows:
**
**	\verb|#include <bibtool/bibtool.h>|
**
**      Note that this include file also contains includes to system
**	specific header files. They are determined during configuration.
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>

#include <bibtool/entry.h>
#include <bibtool/error.h>
#include <bibtool/expand.h>
#include <bibtool/init.h>
#include <bibtool/key.h>
#include <bibtool/macros.h>
#include <bibtool/names.h>
#include <bibtool/parse.h>
#include <bibtool/print.h>
#include <bibtool/pxfile.h>
#include <bibtool/regex.h>
#include <bibtool/rewrite.h>
#include <bibtool/rsc.h>
#include <bibtool/s_parse.h>
#include <bibtool/stack.h>
#include <bibtool/tex_aux.h>
#include <bibtool/tex_read.h>
#include <bibtool/version.h>
