/*** binding.h *****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#ifndef BINDING_H
#define BINDING_H

#include "term.h"

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

extern Binding binding _ARG((Term term));
extern Term eval_term _ARG((Binding binding, Term term));
extern Term eval_self _ARG((Binding binding, Term term));

#endif
