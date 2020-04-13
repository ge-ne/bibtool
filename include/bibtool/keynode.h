/*** keynode.h ****************************************************************
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
**	This header file provides the datatype of a keynode.  This is
**	an internal structure which is used to built parse trees from
**	format specifications. Usually this is done in |key.c| and
**	should not be visible outside.
**
******************************************************************************/

#include <bibtool/symbols.h>
#include <bibtool/type.h>

/*-----------------------------------------------------------------------------
** Typedef:	KeyNode
** Purpose:	
**		
**		
**___________________________________________________			     */
 typedef struct kEYnODE				   /*                        */
 { short int	  kn_type;			   /*                        */
   short int      kn_pre;			   /*                        */
   short int      kn_post;			   /*                        */
   Symbol	  kn_symbol;			   /*                        */
   String	  kn_from;			   /*                        */
   String	  kn_to;			   /*                        */
   struct kEYnODE *kn_next;			   /*                        */
   struct kEYnODE *kn_then;			   /*                        */
   struct kEYnODE *kn_else;			   /*                        */
 } *KeyNode, SKeyNode;				   /*                        */

#define NodeType(X)   ((X)->kn_type)
#define NodePre(X)    ((X)->kn_pre)
#define NodePost(X)   ((X)->kn_post)
#define NodeSymbol(X) ((X)->kn_symbol)
#define NodeNext(X)   ((X)->kn_next)
#define NodeThen(X)   ((X)->kn_then)
#define NodeElse(X)   ((X)->kn_else)
#ifdef REGEX
#define NodeFrom(X)   ((X)->kn_from)
#define NodeTo(X)     ((X)->kn_to)
#endif

#define NodeCountMask 0x100
#define NodePlusMask  0x200
#define NodeMinusMask 0x400
#define NodeSTRING    0x800
#define NodeTEST      0x801
#define NodeTESTneg   0x802
#define NodeOR        0x803
#define NodeSPECIAL   0x804
