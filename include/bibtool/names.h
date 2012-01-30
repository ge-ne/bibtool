/******************************************************************************
** $Id: names.h,v 1.9 2012-01-30 05:08:02 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2012 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/type.h>

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
   Uchar	   *nn_pre;			   /*                        */
   Uchar	   *nn_mid;			   /*                        */
   Uchar	   *nn_post;			   /*                        */
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
**	NN	
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
**	NN	
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
**	NN	
** Returns:	
**___________________________________________________			     */
#define NameTrim(NN) ((NN)->nn_trim)

/*-----------------------------------------------------------------------------
** Macro:	NamePre()
** Type:	Uchar*
** Purpose:	
**		
**		
** Arguments:
**	NN	
** Returns:	
**___________________________________________________			     */
#define NamePre(NN)   ((NN)->nn_pre)

/*-----------------------------------------------------------------------------
** Macro:	NameMid()
** Type:	Uchar*
** Purpose:	
**		
**		
** Arguments:
**	NN	
** Returns:	
**___________________________________________________			     */
#define NameMid(NN)   ((NN)->nn_mid)

/*-----------------------------------------------------------------------------
** Macro:	NamePost()
** Type:	Uchar*
** Purpose:	
**		
**		
** Arguments:
**	NN	
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
** Returns:	The next |Namenode|.
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
 NameNode name_format _ARG((Uchar *s));		   /* names.c                */
 Uchar * pp_list_of_names _ARG((Uchar **wa,NameNode format,char *trans,int max,Uchar *comma,Uchar *and,char *namesep,char *etal));/* names.c*/
 char * pp_names _ARG((char *s,NameNode format,char *trans,int max,char *namesep,char *etal));/* names.c*/

/*---------------------------------------------------------------------------*/
