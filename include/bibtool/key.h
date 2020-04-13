/*** key.h ********************************************************************
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
**	This header file provides functions to deal with keys as they
**	are defined in |keys.h|. 
**
**	This header file automaticall includes the header files
**	|database.h| and |sbuffer.h| since datatypes defined there are
**	required. 
**
******************************************************************************/

#include <bibtool/symbols.h>
#include <bibtool/database.h>
#include <bibtool/sbuffer.h>
#include <bibtool/keynode.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Symbol get_field _ARG((DB db, Record rec, Symbol name));/* key.c            */
 String fmt_expand _ARG((StringBuffer *sb, String cp, DB db, Record rec));/* key.c*/
 bool foreach_ignored_word _ARG((bool (*fct)_ARG((Symbol))));/* key.c        */
 bool mark_key _ARG((DB db,Record rec));	   /* key.c                  */
 bool set_field _ARG((DB db,Record rec,Symbol name,Symbol value));/* key.c   */
 int apply_fmt _ARG((StringBuffer *sb,char *fmt,Record rec,DB db));/* key.c  */
 void add_format _ARG((char *s));		   /* key.c                  */
 void add_ignored_word _ARG((Symbol s));	   /* key.c                  */
 void add_sort_format _ARG((char *s));		   /* key.c                  */
 void clear_ignored_words _ARG((void));		   /* key.c                  */
 void def_format_type _ARG((String s));		   /* key.c                  */
 void end_key_gen _ARG((void));			   /* key.c                  */
 void free_key_node _ARG((KeyNode kn));		   /* key.c                  */
 void make_key _ARG((DB db,Record rec));	   /* key.c                  */
 void make_sort_key _ARG((DB db,Record rec));	   /* key.c                  */
 void set_base _ARG((String value));		   /* key.c                  */
 String get_base _ARG(());		   	   /* key.c                  */
 void set_separator _ARG((int n,String s));	   /* key.c                  */
 Symbol get_separator _ARG((int n));	   	   /* key.c                  */
 void start_key_gen _ARG((void));		   /* key.c                  */

