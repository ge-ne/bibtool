/*** symdef.h ******************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015-2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include "lreader.h"
#include <stdio.h>
#include <bibtool/type.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

/*---------------------------------------------------------------------------*/

extern void init_symdef();			   /*                        */
extern SymDef symdef();
extern unsigned int hash _ARG((String s));	   /*                        */
extern void print_quoted _ARG((FILE*f, String s)); /*                        */
extern void wrong_no_args _ARG((char* name));	   /*                        */
extern Term eval_bool _ARG((Binding b, Term t));   /*                        */
extern Term eval_num _ARG((Binding b, Term t));    /*                        */
extern Term eval_str _ARG((Binding b, Term t));    /*                        */

extern Term g_and _ARG((Binding b, Term t));       /*                        */
extern Term g_div _ARG((Binding b, Term t));	   /*                        */
extern Term g_eq _ARG((Binding b, Term t));	   /*                        */
extern Term g_field _ARG((Binding b, Term t));	   /*                        */
extern Term g_lt _ARG((Binding b, Term t));	   /*                        */
extern Term g_minus _ARG((Binding b, Term t));	   /*                        */
extern Term g_mod _ARG((Binding b, Term t));	   /*                        */
extern Term g_ne _ARG((Binding b, Term t));	   /*                        */
extern Term g_not _ARG((Binding b, Term t));       /*                        */
extern Term g_or _ARG((Binding b, Term t));        /*                        */
extern Term g_plus _ARG((Binding b, Term t));	   /*                        */
extern Term g_print _ARG((Binding b, Term t));	   /*                        */
extern Term g_self _ARG((Binding b, Term t));	   /*                        */
extern Term g_setq _ARG((Binding b, Term t));	   /*                        */
extern Term g_times _ARG((Binding b, Term t));	   /*                        */
extern Term g_version _ARG((Binding b, Term t));   /*                        */
extern Term g_out_file _ARG((Binding b, Term t));  /*                        */
extern Term g_cl_ign_words _ARG((Binding b, Term t));/*                      */

extern SymDef sym_true;			   	   /*                        */
extern SymDef sym_false;			   /*                        */

extern Term term_true;
extern Term term_false;

/*---------------------------------------------------------------------------*/
