/*** print.h ******************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2015 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
**-----------------------------------------------------------------------------
** Description:
**	This header file provides access to the functions and
**	variables defined in |print.c|. Consult also the documentation
**	of this file for details.
**
**	This header file automatically includes |record.h| and |database.h|.
**
******************************************************************************/

#include <bibtool/record.h>
#include <bibtool/database.h>

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 char * sput_record _ARG((Record rec,DB db,Uchar *start));/* print.c         */
 void fput_record _ARG((FILE *file,Record rec,DB db,Uchar *start));/* print.c*/
 void put_record _ARG((int (*fct)_ARG((int)),Record rec,DB db,Uchar *start));/* print.c*/
 void set_key_type _ARG((Uchar * s));		   /* print.c                */
 void set_symbol_type _ARG((Uchar * s));	   /* print.c                */
