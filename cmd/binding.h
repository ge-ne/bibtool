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

#ifndef BINDINGS_H
#define BINDINGS_H

#include <bibtool/type.h>
#include "term.h"

typedef struct S_BJUNK
{ String key;
  Term value;
  struct S_BJUNK * next;
} SBJunk, *BJunk;

typedef struct S_BINDING
{ int junk_size;
  BJunk junks;
  struct S_BINDING *next;
} SBinding, *Binding;


#endif
