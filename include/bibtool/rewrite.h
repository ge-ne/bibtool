/******************************************************************************
** $Id: rewrite.h,v 1.1 2007-02-07 21:31:56 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-1997 Gerd Neugebauer
** 
** Net: gerd@informatik.uni-koblenz.de
** 
******************************************************************************/

#include <bibtool/record.h>
#include <bibtool/database.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 int is_selected _ARG((DB db,Record rec));	   /* rewrite.c              */
 void add_check_rule _ARG((char *s));		   /* rewrite.c              */
 void add_extract _ARG((char *s));		   /* rewrite.c              */
 void add_field _ARG((char *spec));		   /* rewrite.c              */
 void add_rewrite_rule _ARG((char *s));		   /* rewrite.c              */
 void add_s_extract _ARG((char *s));		   /* rewrite.c              */
 void clear_addlist _ARG((void));		   /* rewrite.c              */
 void remove_field _ARG((char *field,Record rec)); /* rewrite.c              */
 void rewrite_record _ARG((DB db,Record rec));	   /* rewrite.c              */
 void save_regex _ARG((char *s));		   /* rewrite.c              */

