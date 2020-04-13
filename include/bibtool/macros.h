/*** macros.h *****************************************************************
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
**	This header file contains definitions for the |Macro|
**	structure. |Macro| is the pointer type corresponding to the
**	structure |SMacro|. All C macros and functions provided
**	through this header file deal with the pointer type. The
**	structure itself is used in the allocation function only.
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>

/*-----------------------------------------------------------------------------
** Typedef:	Macro
** Purpose:	This is a pointer type to represent a mapping from a
**		string to another string.  This mapping is accompanied
**		by a counter which can be used as a reference count.
**___________________________________________________			     */
 typedef struct mACRO				   /*			     */
 { Symbol	mc_name;		   	   /* Name of the macro.     */
   Symbol	mc_value;		   	   /* Value of the macro.    */
   int		mc_used;			   /* Reference count.	     */
   struct mACRO *mc_next;			   /* Pointer the next macro.*/
 } SMacro, *Macro;				   /*			     */


/*-----------------------------------------------------------------------------
** Constant:	MacroNULL()
** Type:	Macro
** Purpose:	This is the |NULL| pointer for the |Macro| type. It
**		can be used as a special or illlegal macro.
**___________________________________________________			     */
#define MacroNULL (Macro)0

/*-----------------------------------------------------------------------------
** Macro:	MacroName()
** Type:	String 
** Purpose:	This is the functional representation of the name
**		component of a |Macro|. It can be used to extract this
**		information. It can also be used as a lvalue.
** Arguments:
**	M	|Macro| to consider
**___________________________________________________			     */
#define MacroName(M)	((M)->mc_name)

/*-----------------------------------------------------------------------------
** Macro:	MacroValue()
** Type:	String 
** Purpose:	This is the functional representation of the value
**		component of a |Macro|. It can be used to extract this
**		information. It can also be used as a lvalue.
** Arguments:
**	M	|Macro| to consider
**___________________________________________________			     */
#define MacroValue(M)	((M)->mc_value)

/*-----------------------------------------------------------------------------
** Macro:	MacroCount()
** Type:	int
** Purpose:	This is the functional representation of the counter
**		component of a |Macro|. It can be used to extract this
**		information. It can also be used as a lvalue.
** Arguments:
**	M	|Macro| to consider
**___________________________________________________			     */
#define MacroCount(M)	((M)->mc_used)

/*-----------------------------------------------------------------------------
** Macro:	NextMacro()
** Type:	Macro
** Purpose:	This is the functional representation of the next
**		|Macro|. It can be used to extract this information.
**		It can also be used as a lvalue.
** Arguments:
**	M	|Macro| to consider
**___________________________________________________			     */
#define NextMacro(M)	((M)->mc_next)

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 Macro new_macro _ARG((Symbol name,Symbol val,Macro next,int cnt));/*macros.c*/
 Symbol get_item _ARG((Symbol  name,int type));    /* macros.c               */
 Symbol get_key _ARG((Symbol name));		   /* macros.c               */
 Symbol look_macro _ARG((Symbol name, int add));   /* macros.c               */
 bool each_macro _ARG((Macro m,bool (*fct)(Symbol,Symbol)));/* macros.c      */
 int def_macro _ARG((Symbol name,Symbol val,int count));/* macros.c          */
 void def_field_type _ARG((String  s));		   /* macros.c               */
 void dump_mac _ARG((char *fname,int allp));	   /* macros.c               */
 void foreach_macro _ARG((bool (*fct)(Symbol,Symbol)));/* macros.c           */
 void free_macro _ARG((Macro mac));		   /* macros.c               */
 void init_macros _ARG((void));			   /* macros.c               */
 void save_key _ARG((Symbol name, Symbol key));	   /* macros.c               */

/*---------------------------------------------------------------------------*/
