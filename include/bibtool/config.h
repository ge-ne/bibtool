/******************************************************************************
** $Id: config.h,v 1.1 2007-02-07 21:31:59 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-1997 Gerd Neugebauer
** 
** Net: gerd@informatik.uni-koblenz.de
** 
******************************************************************************/

/*-----------------------------------------------------------------------------
**  Define the following macro if this is compiled on a MS-DOS-like system.
**  (MSDOS, OS/2, Windows, Atari)
**  This is also done in the makefile. Do not define it here if you use the
**  makefile.
**  It affects the way file names are handled.
*/
#undef MSDOS

/*-----------------------------------------------------------------------------
**  Define the following macro if this is compiled on an Amiga.
**  This is also done in the makefile. Do not define it here if you use the
**  makefile.
**  It affects the way file names are handled.
*/
#undef AMIGA


/*-----------------------------------------------------------------------------
**  Define to empty if the keyword const does not work.
*/
#undef const

/*-----------------------------------------------------------------------------
**  Define to `unsigned' if not defined elsewhere.
*/
#undef size_t

/*-----------------------------------------------------------------------------
**  Define if you have the ANSI C header files.
*/
#undef STDC_HEADERS

/*-----------------------------------------------------------------------------
**  Define if you have the <string.h> header file.
*/
#undef HAVE_STRING_H

/*-----------------------------------------------------------------------------
**  Define if you have the <stdlib.h> header file.
*/
#undef HAVE_STDLIB_H

/*-----------------------------------------------------------------------------
**  Define if you have the <time.h> header file.
*/
#undef HAVE_TIME_H

/*-----------------------------------------------------------------------------
**  Define if you have the function getenv().
*/
#undef HAVE_GETENV

/*-----------------------------------------------------------------------------
**  Define if you have the function strrchr().
*/
#undef HAVE_STRRCHR

/*-----------------------------------------------------------------------------
**  Define if using alloca.c.
*/
#undef C_ALLOCA

/*-----------------------------------------------------------------------------
**  Define if you have alloca, as a function or macro.
*/
#undef HAVE_ALLOCA

#ifndef HAVE_ALLOCA
#define REGEX_MALLOC
#endif

/*-----------------------------------------------------------------------------
**  Define if you have <alloca.h> and it should be used (not on Ultrix).
*/
#undef HAVE_ALLOCA_H

/*-----------------------------------------------------------------------------
**  Define to one of _getb67, GETB67, getb67 for Cray-2 and Cray-YMP systems.
**  This function is required for alloca.c support on those systems.
*/
#undef CRAY_STACKSEG_END

/*-----------------------------------------------------------------------------
**  If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
 STACK_DIRECTION > 0 => grows toward higher addresses
 STACK_DIRECTION < 0 => grows toward lower addresses
 STACK_DIRECTION = 0 => direction of growth unknown
 */
#undef STACK_DIRECTION
