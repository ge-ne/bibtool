/*** binding.h *****************************************************************
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

#ifndef BINDING_H
#define BINDING_H

#include <stdio.h>
#include "term.h"

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

extern Binding binding _ARG((unsigned int size, Binding nextBinding));/*     */
extern Binding root_binding();			   /*                        */
extern SymDef get_bind _ARG((Binding binding, String key));/*                */
extern Term setq _ARG((Binding binding, String key, Term term));/*           */
extern Term eval_term _ARG((Binding binding, Term term));/*                  */
extern Term eval_self _ARG((Binding binding, Term term));/*                  */
extern Term eval_builtin _ARG((Binding binding, Term term));/*               */
extern void dump_binding _ARG((Binding binding, FILE* file));/*              */

extern void bind _ARG((Binding binding, SymDef sym));/*                      */

#endif
