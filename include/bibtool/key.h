/******************************************************************************
** $Id: key.h,v 1.9 2012-01-29 17:04:08 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2012 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
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

#include <bibtool/database.h>
#include <bibtool/sbuffer.h>
#include <bibtool/keynode.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Uchar *get_field _ARG((DB db,Record rec,Uchar *name));/* key.c              */
 Uchar* fmt_expand _ARG((StringBuffer *sb,Uchar *cp,DB db,Record rec));/* key.c*/
 int apply_fmt _ARG((StringBuffer *sb,char *fmt,Record rec,DB db));/* key.c  */
 int foreach_ignored_word _ARG((int (*fct)_ARG((Uchar*))));/* key.c          */
 int mark_key _ARG((DB db,Record rec));		   /* key.c                  */
 int set_field _ARG((DB db,Record rec,Uchar *name,Uchar *value));/* key.c    */
 void add_format _ARG((char *s));		   /* key.c                  */
 void add_ignored_word _ARG((Uchar *s));	   /* key.c                  */
 void add_sort_format _ARG((char *s));		   /* key.c                  */
 void clear_ignored_words _ARG((void));		   /* key.c                  */
 void def_format_type _ARG((char *s));		   /* key.c                  */
 void end_key_gen _ARG((void));			   /* key.c                  */
 void free_key_node _ARG((KeyNode kn));		   /* key.c                  */
 void make_key _ARG((DB db,Record rec));	   /* key.c                  */
 void make_sort_key _ARG((DB db,Record rec));	   /* key.c                  */
 void set_base _ARG((Uchar *value));		   /* key.c                  */
 void set_separator _ARG((int n,Uchar *s));	   /* key.c                  */
 void start_key_gen _ARG((void));		   /* key.c                  */

