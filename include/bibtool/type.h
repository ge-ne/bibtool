/*** type.h *******************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2020 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2, or (at your option)
** any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
**-----------------------------------------------------------------------------
** Description:
**	This module is a replacement for the system header file
**	|ctype.h|. In contrast to some implementations of the |isalpha|
**	and friends the macros in this header are stable. This means
**	that the argument is evaluated exactly once and each macro
**	consists of exactly one C statement. Thus these macros can
**	be used even at those places where only a single statement is
**	allowed (conditionals without braces) or with arguments
**	containing side effects.
**
**	In addition this is a starting point to implement an xord
**	array like \TeX{} has one (some day\dots)
**
**	This header file requires the initialization function
**	|init_type()| to be called before the macros will work as
**	described. 
**
**	This header file also provides the functions and varaibles
**	defined in |type.c|
**
******************************************************************************/

#ifndef TYPE_H_LOADED
#define TYPE_H_LOADED

#include <bibtool/general.h>

 typedef unsigned char Uchar;
 typedef Uchar* String;

#define StringNULL (String)NULL

#define T__None      0
#define T__Upper     1
#define T__Lower     2
#define T__Allowed   4
#define T__Number    8
#define T__Space    16
#define T__Extended 32
#define T__WordSep  64

#ifdef INIT_TYPE

 int type__allowed[257] = {
  /*0   */ T__None,
  /*1   */ T__Space|T__WordSep,
  /*2   */ T__Space|T__WordSep,
  /*3   */ T__Space|T__WordSep,
  /*4   */ T__Space|T__WordSep,
  /*5   */ T__Space|T__WordSep,
  /*6   */ T__Space|T__WordSep,
  /*7   */ T__Space|T__WordSep,
  /*8   */ T__Space|T__WordSep,
  /*9   */ T__Space|T__WordSep,
  /*a   */ T__Space|T__WordSep,
  /*b   */ T__Space|T__WordSep,
  /*c   */ T__Space|T__WordSep,
  /*d   */ T__Space|T__WordSep,
  /*e   */ T__Space|T__WordSep,
  /*f   */ T__Space|T__WordSep,
  /*0   */ T__Space|T__WordSep,
  /*1   */ T__Space|T__WordSep,
  /*2   */ T__Space|T__WordSep,
  /*3   */ T__Space|T__WordSep,
  /*4   */ T__Space|T__WordSep,
  /*5   */ T__Space|T__WordSep,
  /*6   */ T__Space|T__WordSep,
  /*7   */ T__Space|T__WordSep,
  /*8   */ T__Space|T__WordSep,
  /*9   */ T__Space|T__WordSep,
  /*a   */ T__Space|T__WordSep,
  /*b   */ T__Space|T__WordSep,
  /*c   */ T__Space|T__WordSep,
  /*d   */ T__Space|T__WordSep,
  /*e   */ T__Space|T__WordSep,
  /*f   */ T__Space|T__WordSep,
  /*0   */ T__Space|T__WordSep,
  /*1 ! */ T__Allowed|T__WordSep,
  /*2 " */ T__None,
  /*3 # */ T__None,
  /*4 $ */ T__Allowed,
  /*5 % */ T__None,
  /*6 & */ T__Allowed,
  /*7 ' */ T__None,
  /*8 ( */ T__None,
  /*9 ) */ T__None,
  /*a * */ T__Allowed,
  /*b + */ T__Allowed,
  /*c , */ T__None|T__WordSep,
  /*d - */ T__Allowed,
  /*e . */ T__Allowed|T__WordSep,
  /*f / */ T__Allowed,
  /*0 0 */ T__Allowed|T__Number,
  /*1 1 */ T__Allowed|T__Number,
  /*2 2 */ T__Allowed|T__Number,
  /*3 3 */ T__Allowed|T__Number,
  /*4 4 */ T__Allowed|T__Number,
  /*5 5 */ T__Allowed|T__Number,
  /*6 6 */ T__Allowed|T__Number,
  /*7 7 */ T__Allowed|T__Number,
  /*8 8 */ T__Allowed|T__Number,
  /*9 9 */ T__Allowed|T__Number,
  /*a : */ T__Allowed|T__WordSep,
  /*b ; */ T__Allowed|T__WordSep,
  /*c < */ T__Allowed,
  /*d = */ T__None,
  /*e > */ T__Allowed,
  /*f ? */ T__Allowed,
  /*0 @ */ T__Allowed|T__WordSep,
  /*1 A */ T__Allowed|T__Upper,
  /*2 B */ T__Allowed|T__Upper,
  /*3 C */ T__Allowed|T__Upper,
  /*4 D */ T__Allowed|T__Upper,
  /*5 E */ T__Allowed|T__Upper,
  /*6 F */ T__Allowed|T__Upper,
  /*7 G */ T__Allowed|T__Upper,
  /*8 H */ T__Allowed|T__Upper,
  /*9 I */ T__Allowed|T__Upper,
  /*a J */ T__Allowed|T__Upper,
  /*b K */ T__Allowed|T__Upper,
  /*c L */ T__Allowed|T__Upper,
  /*d M */ T__Allowed|T__Upper,
  /*e N */ T__Allowed|T__Upper,
  /*f O */ T__Allowed|T__Upper,
  /*0 P */ T__Allowed|T__Upper,
  /*1 Q */ T__Allowed|T__Upper,
  /*2 R */ T__Allowed|T__Upper,
  /*3 S */ T__Allowed|T__Upper,
  /*4 T */ T__Allowed|T__Upper,
  /*5 U */ T__Allowed|T__Upper,
  /*6 V */ T__Allowed|T__Upper,
  /*7 W */ T__Allowed|T__Upper,
  /*8 X */ T__Allowed|T__Upper,
  /*9 Y */ T__Allowed|T__Upper,
  /*a Z */ T__Allowed|T__Upper,
  /*b [ */ T__Allowed,
  /*c \ */ T__Allowed,
  /*d ] */ T__Allowed,
  /*e ^ */ T__Allowed,
  /*f _ */ T__Allowed,
  /*0 ` */ T__Allowed,
  /*1 a */ T__Allowed|T__Lower,
  /*2 b */ T__Allowed|T__Lower,
  /*3 c */ T__Allowed|T__Lower,
  /*4 d */ T__Allowed|T__Lower,
  /*5 e */ T__Allowed|T__Lower,
  /*6 f */ T__Allowed|T__Lower,
  /*7 g */ T__Allowed|T__Lower,
  /*8 h */ T__Allowed|T__Lower,
  /*9 i */ T__Allowed|T__Lower,
  /*a j */ T__Allowed|T__Lower,
  /*b k */ T__Allowed|T__Lower,
  /*c l */ T__Allowed|T__Lower,
  /*d m */ T__Allowed|T__Lower,
  /*e n */ T__Allowed|T__Lower,
  /*f o */ T__Allowed|T__Lower,
  /*0 p */ T__Allowed|T__Lower,
  /*1 q */ T__Allowed|T__Lower,
  /*2 r */ T__Allowed|T__Lower,
  /*3 s */ T__Allowed|T__Lower,
  /*4 t */ T__Allowed|T__Lower,
  /*5 u */ T__Allowed|T__Lower,
  /*6 v */ T__Allowed|T__Lower,
  /*7 w */ T__Allowed|T__Lower,
  /*8 x */ T__Allowed|T__Lower,
  /*9 y */ T__Allowed|T__Lower,
  /*a z */ T__Allowed|T__Lower,
  /*b { */ T__None,
  /*c | */ T__Allowed,
  /*d } */ T__None,
  /*e ~ */ T__WordSep,
  /*f  */ T__Allowed,
  /*0  */ T__Allowed|T__Extended,
  /*1  */ T__Allowed|T__Extended,
  /*2  */ T__Allowed|T__Extended,
  /*3  */ T__Allowed|T__Extended,
  /*4  */ T__Allowed|T__Extended,
  /*5  */ T__Allowed|T__Extended,
  /*6  */ T__Allowed|T__Extended,
  /*7  */ T__Allowed|T__Extended,
  /*8  */ T__Allowed|T__Extended,
  /*9  */ T__Allowed|T__Extended,
  /*a  */ T__Allowed|T__Extended,
  /*b  */ T__Allowed|T__Extended,
  /*c  */ T__Allowed|T__Extended,
  /*d  */ T__Allowed|T__Extended,
  /*e  */ T__Allowed|T__Extended,
  /*f  */ T__Allowed|T__Extended,
  /*0  */ T__Allowed|T__Extended,
  /*1  */ T__Allowed|T__Extended,
  /*2  */ T__Allowed|T__Extended,
  /*3  */ T__Allowed|T__Extended,
  /*4  */ T__Allowed|T__Extended,
  /*5  */ T__Allowed|T__Extended,
  /*6  */ T__Allowed|T__Extended,
  /*7  */ T__Allowed|T__Extended,
  /*8  */ T__Allowed|T__Extended,
  /*9  */ T__Allowed|T__Extended,
  /*a  */ T__Allowed|T__Extended,
  /*b  */ T__Allowed|T__Extended,
  /*c  */ T__Allowed|T__Extended,
  /*d  */ T__Allowed|T__Extended,
  /*e  */ T__Allowed|T__Extended,
  /*f  */ T__Allowed|T__Extended,
  /*0  */ T__Allowed|T__Extended,
  /*1  */ T__Allowed|T__Extended,
  /*2  */ T__Allowed|T__Extended,
  /*3  */ T__Allowed|T__Extended,
  /*4  */ T__Allowed|T__Extended,
  /*5  */ T__Allowed|T__Extended,
  /*6  */ T__Allowed|T__Extended,
  /*7  */ T__Allowed|T__Extended,
  /*8  */ T__Allowed|T__Extended,
  /*9  */ T__Allowed|T__Extended,
  /*a  */ T__Allowed|T__Extended,
  /*b  */ T__Allowed|T__Extended,
  /*c  */ T__Allowed|T__Extended,
  /*d  */ T__Allowed|T__Extended,
  /*e  */ T__Allowed|T__Extended,
  /*f  */ T__Allowed|T__Extended,
  /*0  */ T__Allowed|T__Extended,
  /*1  */ T__Allowed|T__Extended,
  /*2  */ T__Allowed|T__Extended,
  /*3  */ T__Allowed|T__Extended,
  /*4  */ T__Allowed|T__Extended,
  /*5  */ T__Allowed|T__Extended,
  /*6  */ T__Allowed|T__Extended,
  /*7  */ T__Allowed|T__Extended,
  /*8  */ T__Allowed|T__Extended,
  /*9  */ T__Allowed|T__Extended,
  /*a  */ T__Allowed|T__Extended,
  /*b  */ T__Allowed|T__Extended,
  /*c  */ T__Allowed|T__Extended,
  /*d  */ T__Allowed|T__Extended,
  /*e  */ T__Allowed|T__Extended,
  /*f  */ T__Allowed|T__Extended,
  /*0  */ T__Allowed|T__Extended,
  /*1  */ T__Allowed|T__Extended,
  /*2  */ T__Allowed|T__Extended,
  /*3  */ T__Allowed|T__Extended,
  /*4  */ T__Allowed|T__Extended,
  /*5  */ T__Allowed|T__Extended,
  /*6  */ T__Allowed|T__Extended,
  /*7  */ T__Allowed|T__Extended,
  /*8  */ T__Allowed|T__Extended,
  /*9  */ T__Allowed|T__Extended,
  /*a  */ T__Allowed|T__Extended,
  /*b  */ T__Allowed|T__Extended,
  /*c  */ T__Allowed|T__Extended,
  /*d  */ T__Allowed|T__Extended,
  /*e  */ T__Allowed|T__Extended,
  /*f  */ T__Allowed|T__Extended,
  /*0  */ T__Allowed|T__Extended,
  /*1  */ T__Allowed|T__Extended,
  /*2  */ T__Allowed|T__Extended,
  /*3  */ T__Allowed|T__Extended,
  /*4  */ T__Allowed|T__Extended,
  /*5  */ T__Allowed|T__Extended,
  /*6  */ T__Allowed|T__Extended,
  /*7  */ T__Allowed|T__Extended,
  /*8  */ T__Allowed|T__Extended,
  /*9  */ T__Allowed|T__Extended,
  /*a  */ T__Allowed|T__Extended,
  /*b  */ T__Allowed|T__Extended,
  /*c  */ T__Allowed|T__Extended,
  /*d  */ T__Allowed|T__Extended,
  /*e  */ T__Allowed|T__Extended,
  /*f  */ T__Allowed|T__Extended,
  /*0  */ T__Allowed|T__Extended,
  /*1  */ T__Allowed|T__Extended,
  /*2  */ T__Allowed|T__Extended,
  /*3  */ T__Allowed|T__Extended,
  /*4  */ T__Allowed|T__Extended,
  /*5  */ T__Allowed|T__Extended,
  /*6  */ T__Allowed|T__Extended,
  /*7  */ T__Allowed|T__Extended,
  /*8  */ T__Allowed|T__Extended,
  /*9  */ T__Allowed|T__Extended,
  /*a  */ T__Allowed|T__Extended,
  /*b  */ T__Allowed|T__Extended,
  /*c  */ T__Allowed|T__Extended,
  /*d  */ T__Allowed|T__Extended,
  /*e  */ T__Allowed|T__Extended,
  /*f  */ T__Allowed|T__Extended,
  /*0  */ T__Allowed|T__Extended,
  /*1  */ T__Allowed|T__Extended,
  /*2  */ T__Allowed|T__Extended,
  /*3  */ T__Allowed|T__Extended,
  /*4  */ T__Allowed|T__Extended,
  /*5  */ T__Allowed|T__Extended,
  /*6  */ T__Allowed|T__Extended,
  /*7  */ T__Allowed|T__Extended,
  /*8  */ T__Allowed|T__Extended,
  /*9  */ T__Allowed|T__Extended,
  /*a  */ T__Allowed|T__Extended,
  /*b  */ T__Allowed|T__Extended,
  /*c  */ T__Allowed|T__Extended,
  /*d  */ T__Allowed|T__Extended,
  /*e  */ T__Allowed|T__Extended,
  /*f  */ T__Allowed|T__Extended
 };

/*-----------------------------------------------------------------------------
** Variable:	trans_lower
** Type:	char*
** Purpose:	Translation table mapping upper case letters to lower
**		case. Such a translation table can be used as argument
**		to the regular expression functions.
**___________________________________________________			     */
Uchar trans_lower[256];			   	   /*                        */

/*-----------------------------------------------------------------------------
** Variable:	trans_upper
** Type:	char*
** Purpose:	Translation table mapping lower case letters to upper
**		case. Such a translation table can be used as argument
**		to the regular expression functions.
**___________________________________________________			     */
Uchar trans_upper[256];			   	   /*                        */

/*-----------------------------------------------------------------------------
** Variable:	trans_id
** Type:	char*
** Purpose:	Translation table performing no translation. Thus it
**		implements the identity a translation table can be
**		used as argument to the regular expression functions.
**___________________________________________________			     */
Uchar trans_id[256];			   	   /*                        */

#else

 extern int  type__allowed[];
 extern Uchar trans_lower[256];
 extern Uchar trans_upper[256];
 extern Uchar trans_id[256];
#endif

/*-----------------------------------------------------------------------------
** Macro:	is_allowed()
** Type:	bool
** Purpose:	Decide whether the character given as argument is an
**		allowed character in the sense of \BibTeX.
** Arguments:
**	C	Character to consider
** Returns:	|TRUE| iff the argument is an allowed character.
**___________________________________________________			     */
#define is_allowed(C)	  (type__allowed[(Uchar)C]&T__Allowed)

/*-----------------------------------------------------------------------------
** Macro:	is_upper()
** Type:	bool
** Purpose:	Decide whether the character given as argument is a
**		upper case letter.
**		(Characters outside the ASCII range are not considered
**		letters yet)
** Arguments:
**	C	Character to consider
** Returns:	|TRUE| iff the character is an uppercase letter.
**___________________________________________________			     */
#define is_upper(C)	  (type__allowed[(Uchar)C]&T__Upper)

/*-----------------------------------------------------------------------------
** Macro:	is_lower()
** Type:	bool
** Purpose:	Decide whether the character given as argument is a
**		lower case letter.
**		(Characters outside the ASCII range are not considered
**		letters yet)
** Arguments:
**	C	Character to consider
** Returns:	|TRUE| iff the character is a lowercase letter.
**___________________________________________________			     */
#define is_lower(C)	  (type__allowed[(Uchar)C]&T__Lower)

/*-----------------------------------------------------------------------------
** Macro:	is_alpha()
** Type:	bool
** Purpose:	Decide whether the character given as argument is a
**		letter.
**		(Characters outside the ASCII range are not considered
**		letters yet)
** Arguments:
**	C	Character to consider
** Returns:	|TRUE| iff the character is a letter.
**___________________________________________________			     */
#define is_alpha(C)	  (type__allowed[(Uchar)C]&(T__Upper|T__Lower))

/*-----------------------------------------------------------------------------
** Macro:	is_digit()
** Type:	bool
** Purpose:	Decide whether the character given as argument is a
**		digit.
**		(Characters outside the ASCII range are not considered
**		letters yet)
** Arguments:
**	C	Character to consider
** Returns:	|TRUE| iff the character is a digit.
**___________________________________________________			     */
#define is_digit(C)	  (type__allowed[(Uchar)C]&T__Number)

/*-----------------------------------------------------------------------------
** Macro:	is_space()
** Type:	bool
** Purpose:	Decide whether the character given as argument is a
**		space character. |'\0'| is not a space character.
** Arguments:
**	C	Character to consider
** Returns:	|TRUE| iff the character is a space character.
**___________________________________________________			     */
#define is_space(C)	  (type__allowed[(Uchar)C]&T__Space)

/*-----------------------------------------------------------------------------
** Macro:	is_extended()
** Type:	bool
** Purpose:	Decide whether the character given as argument is an
**		extended character outside the ASCII range.
** Arguments:
**	C	Character to consider
** Returns:	|TRUE| iff the character is an extended character.
**___________________________________________________			     */
#define is_extended(C)	  (type__allowed[(Uchar)C]&T__Extended)

/*-----------------------------------------------------------------------------
** Macro:	is_wordsep()
** Type:	bool
** Purpose:	Decide whether the character given as argument is a
**		word separator which denotes no word constituent.
** Arguments:
**	C	Character to consider
** Returns:	|TRUE| iff the character is a word separator.
**___________________________________________________			     */
#define is_wordsep(C)	  (type__allowed[(Uchar)C]&T__WordSep)

/*-----------------------------------------------------------------------------
** Macro:	ToLower()
** Type:	char
** Purpose:	Translate a character to it's lower case dual. If the
**		character is no upper case letter then the character
**		is returned unchanged.
** Arguments:
**	C	Character to translate
** Returns:	The lower case letter or the character itself.
**___________________________________________________			     */
#define ToLower(C)	  trans_lower[(Uchar)(C)]

/*-----------------------------------------------------------------------------
** Macro:	ToUpper()
** Type:	char
** Purpose:	Translate a character to it's upper case dual. If the
**		character is no lower case letter then the character
**		is returned unchanged.
** Arguments:
**	C	Character to translate
** Returns:	The upper case letter or the character itself.
**___________________________________________________			     */
#define ToUpper(C)	  trans_upper[(Uchar)(C)]

#define SYMBOL_TYPE_LOWER 0
#define SYMBOL_TYPE_UPPER 1
#define SYMBOL_TYPE_CASED 2

#endif

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 String lower _ARG((String s));		   	   /* type.c                 */
 bool case_eq _ARG((String s, String t));	   /* type.c                 */
 int cmp _ARG((String s, String t));	   	   /* type.c                 */
 void add_word_sep _ARG((String s));		   /* type.c                 */
 void init_type _ARG((void));			   /* type.c                 */

/*---------------------------------------------------------------------------*/
