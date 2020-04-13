/*** names.h ******************************************************************
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
******************************************************************************/

#include <bibtool/type.h>
#include <bibtool/symbols.h>

/*-----------------------------------------------------------------------------
** Typedef:	SNameNode
** Purpose:	The name format is translated internally into a list
**		of nodes which are easier to evaluate since they avoid
**		the reparsing of the format. This structure contains
**		such a node.
**___________________________________________________			     */
 typedef struct nameNODE			   /*                        */
 { int		   nn_type;			   /*                        */
   int		   nn_strip;			   /*                        */
   int		   nn_trim;			   /*                        */
   Symbol	   nn_pre;			   /*                        */
   Symbol	   nn_mid;			   /*                        */
   Symbol	   nn_post;			   /*                        */
   struct nameNODE *nn_next;			   /* Pointer to the next    */
 						   /*  name node             */
 } SNameNode, *NameNode;			   /*                        */

/*-----------------------------------------------------------------------------
** Constant:	NameNULL()
** Type:	NameNode
** Purpose:	The |NULL| pointer to a |NameNode| which can be used
**		as a special value to indicate the end of a |NameNode|
**		list.
** Returns:	The |NULL| pointer to a |NameNode|.
**___________________________________________________			     */
#define NameNULL      ((NameNode)0)

/*-----------------------------------------------------------------------------
** Macro:	NameType()
** Type:	int
** Purpose:	
**		
**		
** Arguments:
**	NN	the name node
** Returns:	
**___________________________________________________			     */
#define NameType(NN)  ((NN)->nn_type)

/*-----------------------------------------------------------------------------
** Macro:	NameStrip()
** Type:	int
** Purpose:	
**		
**		
** Arguments:
**	NN	the name node
** Returns:	
**___________________________________________________			     */
#define NameStrip(NN) ((NN)->nn_strip)

/*-----------------------------------------------------------------------------
** Macro:	NameTrim()
** Type:	int
** Purpose:	
**		
**		
** Arguments:
**	NN	the name node
** Returns:	
**___________________________________________________			     */
#define NameTrim(NN) ((NN)->nn_trim)

/*-----------------------------------------------------------------------------
** Macro:	NamePre()
** Type:	String
** Purpose:	
**		
**		
** Arguments:
**	NN	the name node
** Returns:	
**___________________________________________________			     */
#define NamePre(NN)   ((NN)->nn_pre)

/*-----------------------------------------------------------------------------
** Macro:	NameMid()
** Type:	String
** Purpose:	
**		
**		
** Arguments:
**	NN	the name node
** Returns:	
**___________________________________________________			     */
#define NameMid(NN)   ((NN)->nn_mid)

/*-----------------------------------------------------------------------------
** Macro:	NamePost()
** Type:	String
** Purpose:	
**		
**		
** Arguments:
**	NN	the name node
** Returns:	
**___________________________________________________			     */
#define NamePost(NN)  ((NN)->nn_post)

/*-----------------------------------------------------------------------------
** Macro:	NextName()
** Type:	NameNode
** Purpose:	Functional representation of the pointer to the next
**		|NameNode|.
** Arguments:
**	NN	|NameNode| to consider.
** Returns:	The next |NameNode|.
**___________________________________________________			     */
#define NextName(NN)  ((NN)->nn_next)


#define NoName		0x00
#define NameFirst	0x01
#define NameLast	0x02
#define NameVon		0x03
#define NameJr		0x04
#define NameString	0x05

#define NameNone	0x00
#define NameLower	0x10
#define NameUpper	0x20
#define NameExternal	0x30

#define NameTypeMask		0x0f
#define NameTranslationMask	0xf0

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 NameNode name_format _ARG((String s));		   /* names.c                */
 String  pp_list_of_names _ARG((String *wa,NameNode format,String trans,int max,String comma,String and,char *namesep,char *etal));/* names.c*/
 char * pp_names _ARG((char *s,NameNode format,String trans,int max,char *namesep,char *etal));/* names.c*/

/*---------------------------------------------------------------------------*/
