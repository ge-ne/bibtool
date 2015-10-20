/*** tagged.c *****************************************************************
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

#include <stdio.h>
#include "tagged.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


TaggedValue new_s_tagged(s)
  char* s;
{
  TaggedValue v	= (TaggedValue)malloc(sizeof(STaggedValue));
  TaggedType(v) = TAGGED_STR;
  TaggedStr(v) = s;
  return v;					   /*                        */
}						   /*------------------------*/

TaggedValue new_n_tagged(n)
  long n;
{
  TaggedValue v = (TaggedValue)malloc(sizeof(STaggedValue));
  TaggedType(v) = TAGGED_NUM;
  TaggedStr(v) = s;
  return v;					   /*                        */
}						   /*------------------------*/

void free_tagged(t)
  TaggedValue t;
{
  if (TaggedType(t)  == TAGGED_STR)
  { free(TaggedStr(t)); }
  (void)free(t);				   /*                        */
}						   /*------------------------*/
