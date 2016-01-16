/*** rewrite.h ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2016 Gerd Neugebauer
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

#include <bibtool/record.h>
#include <bibtool/database.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 int is_selected _ARG((DB db, Record rec));
 int set_regex_syntax _ARG((char* name));
 void add_check_rule _ARG((String s));
 void add_extract _ARG((String s, int regexp, int notp));
 void add_field _ARG((String spec));
 void add_rewrite_rule _ARG((String s));
 void clear_addlist _ARG((void));
 void remove_field _ARG((String field, Record rec));
 void rename_field _ARG((String spec));
 void rewrite_record _ARG((DB db, Record rec));
 void save_regex _ARG((String s));
