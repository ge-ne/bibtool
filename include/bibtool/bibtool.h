/******************************************************************************
** $Id: bibtool.h,v 1.9 2013-11-24 22:07:52 gene Exp $
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
**-----------------------------------------------------------------------------
** Description:
**	This header file contains includes for all other header files
**	belonging to the \BibTool{} C library. It is here for the
**	convenience of the C programmer who does not have to include
**	two dozen header files but can use this single file. Thus any
**	C program which utilizes the \BibTool{} C library can start as
**	follows:
**
**	\verb|#include <bibtool/bibtool.h>|
**
**      Note that this include file also contains includes to system
**	specific header files. They are determined during configuration.
**
******************************************************************************/

#include <bibtool/config.h>
#include <bibtool/entry.h>
#include <bibtool/error.h>
#include <bibtool/expand.h>
#include <bibtool/general.h>
#include <bibtool/init.h>
#include <bibtool/key.h>
#include <bibtool/macros.h>
#include <bibtool/names.h>
#include <bibtool/parse.h>
#include <bibtool/print.h>
#include <bibtool/pxfile.h>
#include <bibtool/regex.h>
#include <bibtool/rewrite.h>
#include <bibtool/rsc.h>
#include <bibtool/s_parse.h>
#include <bibtool/stack.h>
#include <bibtool/symbols.h>
#include <bibtool/tex_aux.h>
#include <bibtool/tex_read.h>
#include <bibtool/type.h>
#include <bibtool/version.h>
