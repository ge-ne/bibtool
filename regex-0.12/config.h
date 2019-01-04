/* regex-0.12/config.h.  Generated from reconfig.h.in by configure.  */
/*** reconfig.h ***************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2019 Gerd Neugebauer
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

/*-----------------------------------------------------------------------------
**  Define if you have the <string.h> header file.
*/
#define HAVE_STRING_H 1

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/*-----------------------------------------------------------------------------
**  Define if you have alloca, as a function or macro.
*/
#define HAVE_ALLOCA 1
#ifndef HAVE_ALLOCA
#define REGEX_MALLOC
#endif

/*-----------------------------------------------------------------------------
**  Define if you have <alloca.h> and it should be used (not on Ultrix).
*/
#define HAVE_ALLOCA_H 1

/*-----------------------------------------------------------------------------
**  Define to one of _getb67, GETB67, getb67 for Cray-2 and Cray-YMP systems.
**  This function is required for alloca.c support on those systems.
*/
/* #undef CRAY_STACKSEG_END */

/*-----------------------------------------------------------------------------
**  If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
 STACK_DIRECTION > 0 => grows toward higher addresses
 STACK_DIRECTION < 0 => grows toward lower addresses
 STACK_DIRECTION = 0 => direction of growth unknown
 */
/* #undef STACK_DIRECTION */
