/*** tagged.h *****************************************************************
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

 typedef struct
 { char type;
   union
   { long num;
     char * str;
   } value;
 } STaggedValue, *TaggedValue;

#define TAGGED_NUM '#'
#define TAGGED_STR '"'

#define TaggedType(V) ((V)->type)
#define TaggedNum(V) ((V)->value.num)
#define TaggedStr(V) ((V)->value.str)

/*---------------------------------------------------------------------------*/
