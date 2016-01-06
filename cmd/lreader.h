/*** lreader.h *****************************************************************
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

#ifndef LREADER_H
#define LREADER_H

#include <stdio.h>
#include "term.h"

#define L_STRING	0x200
#define L_BLOCK		0x201
#define L_FIELD		0x202
#define L_NUMBER	0x203
#define L_LIST		0x204
#define L_GROUP		0x205
#define L_TRUE		0x206
#define L_FALSE		0x207

#define L_QUOTE		0x401
#define L_MINUS		0x412
#define L_PLUS		0x414
#define L_TIMES		0x416
#define L_DIV		0x418
#define L_MOD		0x420
#define L_SET		0x422
#define L_LIKE		0x424
#define L_ILIKE		0x426
#define L_EQ		0x428
#define L_NE		0x430
#define L_GT		0x432
#define L_GE		0x434
#define L_LT		0x436
#define L_LE		0x438
#define L_AND		0x440
#define L_OR		0x442
#define L_NOT		0x451

#define L_IS_OPERATOR(C) ((C) >= 0x400)
#define L_IS_BINARY(C)   (((C) & 1) == 0)

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

extern void init_lreader();

#endif
