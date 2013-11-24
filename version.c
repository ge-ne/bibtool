/******************************************************************************
** $Id: version.c,v 1.16 2013-11-24 21:40:13 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2013 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/error.h>

/*-----------------------------------------------------------------------------
** Variable:	bibtool_version
** Type:	char *
** Purpose:	This string variable contains the version number of
**		\BibTool. Usually it is of the form
**		\textit{major.minor} where \textit{major} and
**		\textit{minor} are the major and minor version
**		numbers.  In addition a postfix like |alpha| or a
**		patchlevel like |p1| can be present.
**___________________________________________________			     */
 char * bibtool_version = "2.56-alpha";		   /*                        */

/*-----------------------------------------------------------------------------
** Function:	show_version()
** Purpose:	Print the version number and a short copyright notice
**		onto the error stream.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void show_version()				   /*                        */
{						   /*                        */
  ErrPrintF("BibTool Vers. %s (C) 1996-2012 Gerd Neugebauer\n\n",/*          */
	    bibtool_version);			   /*	                     */
}						   /*------------------------*/
