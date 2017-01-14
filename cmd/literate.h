/*** literate.h ***************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2017 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include "term.h"

typedef struct s_iterator
{
  void *state;
  int (*hasNext) _ARG((void*));
  Term (*next) _ARG((void*));
  void (*finish) _ARG((void*));
} *Iterator, SIterator;

#define ItHasNext(I)	((I)->hasNext)
#define ItNext(I)	((I)->next)
#define ItFinish(I)	((I)->finish)
#define ItState(I)	((I)->state)

#define DoItHasNext(I)	(*((I)->hasNext))(I)
#define DoItNext(I)	(*((I)->next))(I)
#define DoItFinish(I)	(*((I)->finish))(I)

/*---------------------------------------------------------------------------*/

extern Iterator get_iterator _ARG((Term t));

/*---------------------------------------------------------------------------*/
