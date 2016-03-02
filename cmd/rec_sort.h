/*** rec_sort.h ***************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/record.h>
#include "term.h"
#include "binding.h"

/*---------------------------------------------------------------------------*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

typedef int (* FunPtr)_ARG((Record r1, Record r2));

extern FunPtr get_sorter _ARG((int cased,
			       int desc,
			       Binding b,
			       Term f));

/*---------------------------------------------------------------------------*/
