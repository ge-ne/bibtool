/******************************************************************************
** $Id: macros.h,v 1.2 2007-02-08 05:27:32 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2001 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
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

#include <bibtool/type.h>

/*-----------------------------------------------------------------------------
** Typedef:	Macro
** Purpose:	This is a pointer type to represent a mapping from a
**		string to another string.  This mapping is accompanied
**		by a counter which can be used as a reference count.
**___________________________________________________			     */
 typedef struct mACRO				   /*			     */
 { Uchar	*mc_name;		   	   /* Name of the macro.     */
   Uchar	*mc_value;		   	   /* Value of the macro.    */
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
** Type:	Uchar *
** Purpose:	This is the functional representation of the name
**		component of a |Macro|. It can be used to extract this
**		information. It can also be used as a lvalue.
** Arguments:
**	M	|Macro| to consider
**___________________________________________________			     */
#define MacroName(M)	((M)->mc_name)

/*-----------------------------------------------------------------------------
** Macro:	MacroValue()
** Type:	Uchar *
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
 Macro new_macro _ARG((Uchar *name,Uchar *val,Macro next,int count));/* macros.c*/
 Uchar * get_item _ARG((Uchar * name,int type));   /* macros.c               */
 Uchar * get_key_name _ARG((Uchar *s));		   /* macros.c               */
 Uchar * look_macro _ARG((Uchar *name,int add));   /* macros.c               */
 int def_macro _ARG((Uchar *name,Uchar *val,int count));/* macros.c          */
 void def_field_type _ARG((Uchar * s));		   /* macros.c               */
 void dump_mac _ARG((char *fname,int allp));	   /* macros.c               */
 void foreach_macro _ARG((int (*fct) _ARG((Uchar *,Uchar *))));/* macros.c   */
 void free_macro _ARG((Macro mac));		   /* macros.c               */
 void init_macros _ARG((void));			   /* macros.c               */
 void save_key _ARG((char * s,char * key));	   /* macros.c               */
