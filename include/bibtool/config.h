/* include/bibtool/config.h.  Generated from config.h.in by configure.  */
/******************************************************************************
** $Id: config.h,v 1.8 2011-06-07 20:01:06 gene Exp $
**=============================================================================
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2011 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

/*-----------------------------------------------------------------------------
**  Define the following macro if this is compiled on a MS-DOS-like system.
**  (MSDOS, OS/2, Windows, Atari)
**  This is also done in the makefile. Do not define it here if you use the
**  makefile.
**  It affects the way file names are handled.
*/
/* #undef MSDOS */

/*-----------------------------------------------------------------------------
**  Define the following macro if this is compiled on an Amiga.
**  This is also done in the makefile. Do not define it here if you use the
**  makefile.
**  It affects the way file names are handled.
*/
/* #undef AMIGA */


/*-----------------------------------------------------------------------------
**  Define to empty if the keyword const does not work.
*/
/* #undef const */

/*-----------------------------------------------------------------------------
**  Define to `unsigned' if not defined elsewhere.
*/
/* #undef size_t */

/*-----------------------------------------------------------------------------
**  Define if you have the ANSI C header files.
*/
#define STDC_HEADERS 1

/*-----------------------------------------------------------------------------
**  Define if you have the <string.h> header file.
*/
#define HAVE_STRING_H 1

/*-----------------------------------------------------------------------------
**  Define if you have the <stdlib.h> header file.
*/
#define HAVE_STDLIB_H 1

/*-----------------------------------------------------------------------------
**  Define if you have the <time.h> header file.
*/
#define HAVE_TIME_H 1

/*-----------------------------------------------------------------------------
**  Define if you have the function getenv().
*/
#define HAVE_GETENV 1

/*-----------------------------------------------------------------------------
**  Define if you have the function strrchr().
*/
#define HAVE_STRRCHR 1

/*-----------------------------------------------------------------------------
**  Define if using alloca.c.
*/
/* #undef C_ALLOCA */

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
