/* regex-0.12/config.h.  Generated from reconfig.h.in by configure.  */
/******************************************************************************
** $Id: config.h,v 1.11 2013-11-24 21:40:14 gene Exp $
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
