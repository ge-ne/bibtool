/*** version.c ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2018 Gerd Neugebauer
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

#include <bibtool/error.h>

/*-----------------------------------------------------------------------------
** Variable:	bibtool_version
** Type:	char *
** Purpose:	This string variable contains the version number of
**		\BibTool. Usually it is of the form
**		\textit{major.minor} where \textit{major} and
**		\textit{minor} are the major and minor version
**		numbers.  In addition a post-fix like |alpha| or a
**		patch level like |p1| can be present.
**___________________________________________________			     */
char * bibtool_version = "2.68";		   /*                        */

/*-----------------------------------------------------------------------------
** Variable:	bibtool_year
** Type:	char *
** Purpose:	This string variable contains the publication year for this
**		version. 
**___________________________________________________			     */
char * bibtool_year = "2018";			   /*                        */

/*-----------------------------------------------------------------------------
** Function:	show_version()
** Purpose:	Print the version number and a short copyright notice
**		onto the error stream.
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void show_version()				   /*                        */
{						   /*                        */
  ErrPrintF2("BibTool Vers. %s (C) 1996-%s Gerd Neugebauer\n\n",/*           */
	     bibtool_version, bibtool_year);	   /*	                     */
}						   /*------------------------*/
