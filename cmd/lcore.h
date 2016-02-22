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
#include <bibtool/record.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

/*---------------------------------------------------------------------------*/

extern unsigned int hash _ARG((String s));	   /*                        */
extern void print_quoted _ARG((FILE*f, String s)); /*                        */

extern void wrong_no_args _ARG((char* name));	   /*                        */
extern void no_args _ARG((Term  args, char *msg)); /*                        */
extern long num_arg _ARG((Binding binding, Term *argp, char *msg));/*        */
extern String str_arg _ARG((Binding binding, Term *argp, char *msg));/*      */

extern Record rec_arg _ARG((Binding binding, Term *argp, char *msg));/*      */

extern Term eval_bool _ARG((Binding b, Term t));   /*                        */
extern Term eval_num _ARG((Binding b, Term t));    /*                        */
extern Term eval_str _ARG((Binding b, Term t));    /*                        */

extern Term g_and _ARG((Binding b, Term t));       /*                        */
extern Term g_div _ARG((Binding b, Term t));	   /*                        */
extern Term g_eq _ARG((Binding b, Term t));	   /*                        */
extern Term g_field _ARG((Binding b, Term t));	   /*                        */
extern Term s_field _ARG((Binding b, Term t));	   /*                        */
extern Term g_ge _ARG((Binding b, Term t));	   /*                        */
extern Term g_gt _ARG((Binding b, Term t));	   /*                        */
extern Term g_ign_ _ARG((Binding b, Term t));	   /*                        */
extern Term g_input _ARG((Binding b, Term t));	   /*                        */
extern Term s_input _ARG((Binding b, Term t));	   /*                        */
extern Term g_le _ARG((Binding b, Term t));	   /*                        */
extern Term g_lt _ARG((Binding b, Term t));	   /*                        */
extern Term g_macro_file _ARG((Binding b, Term t));/*                        */
extern Term s_macro_file _ARG((Binding b, Term t));/*                        */
extern Term g_minus _ARG((Binding b, Term t));	   /*                        */
extern Term g_mod _ARG((Binding b, Term t));	   /*                        */
extern Term g_ne _ARG((Binding b, Term t));	   /*                        */
extern Term g_not _ARG((Binding b, Term t));       /*                        */
extern Term g_or _ARG((Binding b, Term t));        /*                        */
extern Term g_plus _ARG((Binding b, Term t));	   /*                        */
extern Term g_print _ARG((Binding b, Term t));	   /*                        */
extern Term g_read _ARG((Binding b, Term t));	   /*                        */
extern Term s_read _ARG((Binding b, Term t));	   /*                        */
extern Term g_self _ARG((Binding b, Term t));	   /*                        */
extern Term g_setq _ARG((Binding b, Term t));	   /*                        */
extern Term g_times _ARG((Binding b, Term t));	   /*                        */
extern Term g_version _ARG((Binding b, Term t));   /*                        */
extern Term s_version _ARG((Binding b, Term t));   /*                        */
extern Term g_out_file _ARG((Binding b, Term t));  /*                        */
extern Term s_out_file _ARG((Binding b, Term t));  /*                        */
extern Term g_cl_ign_words _ARG((Binding b, Term t));/*                      */

extern Term get_add_fields();			   /*                        */

extern Term m_as_boolean _ARG((Binding binding,
			       Term string,
			       Term args));
extern Term m_as_string _ARG((Binding binding,
			      Term string,
			      Term args));
extern Term m_as_number _ARG((Binding binding,
			      Term string,
			      Term args));

extern void init_lcore();			   /*                        */

extern SymDef sym_true;			   	   /*                        */
extern SymDef sym_false;			   /*                        */

extern Term term_true;				   /*                        */
extern Term term_false;				   /*                        */

/*---------------------------------------------------------------------------*/

#define ErrorNF1(X)						\
	error(ERR_ERROR|ERR_EXIT,(String)X,			\
	      (String)0,(String)0,(String)0,(String)0,0,NULL)

#define ErrorNF2(X,Y)						\
	error(ERR_ERROR|ERR_EXIT,(String)X,			\
	      (String)Y,(String)0,(String)0,(String)0,0,NULL)

#define ErrorNF3(X,Y,Z)						\
	error(ERR_ERROR|ERR_EXIT,(String)X,			\
	      (String)Y,(String)Z,(String)0,(String)0,0,NULL)

/*---------------------------------------------------------------------------*/
