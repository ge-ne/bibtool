dnl ***************************************************************************
dnl 
dnl This file is part of BibTool.
dnl It is distributed under the GNU General Public License.
dnl See the file COPYING for details.
dnl 
dnl (c) 1996-2019 Gerd Neugebauer
dnl 
dnl Net: gene@gerd-neugebauer.de
dnl 
dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2, or (at your option)
dnl any later version.
dnl 
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl 
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software
dnl Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
dnl 
dnl ***************************************************************************

AC_REVISION($Revision: 1.12 $)
AC_COPYRIGHT(Copyright (C) 2017-2019 Gerd Neugebauer
This configure script is part of BibTool.
Revision 1.12)
AC_PREREQ(2.69)

dnl ---------------------------------------------------------------------------
dnl Process this file with autoconf to produce a configure script.
AC_INIT(BibTool,2.*)

dnl ---------------------------------------------------------------------------
AC_PREREQ(2.69)

dnl ---------------------------------------------------------------------------
dnl Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB

dnl AC_PATH_PROGS(PERL,perl perl5.003 perl4.036 /usr/local/bin/perl)
dnl AC_PATH_PROGS(TCLSH,tclsh tclsh-8.0 tclsh-8.1 tclsh-8.2 tclx,/usr/local/bin/tclsh)

dnl ---------------------------------------------------------------------------
dnl for regexp
AC_USE_SYSTEM_EXTENSIONS
AC_SEARCH_LIBS([strerror],[cposix])
AC_USE_SYSTEM_EXTENSIONS

dnl ---------------------------------------------------------------------------
dnl Checks for compile flags.
AX_APPEND_COMPILE_FLAGS(-Wno-old-style-definition)

dnl ---------------------------------------------------------------------------
dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T

dnl ---------------------------------------------------------------------------
dnl Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_MEMCMP

dnl ---------------------------------------------------------------------------
dnl Check for headers.
AC_CHECK_HEADERS(string.h)
AC_CHECK_HEADERS(stdlib.h)
AC_CHECK_HEADERS(stdbool.h)
AC_CHECK_HEADERS(stdint.h)
AC_CHECK_HEADERS(time.h)
AC_CHECK_FUNCS(getenv)
AC_CHECK_FUNCS(strrchr)

dnl ---------------------------------------------------------------------------
AC_ARG_WITH(kpathsea,Use the KPATHSEA library.,,with_kpathsea=yes)

if test $with_kpathsea = no; then
	kpathsea_dir=
	kpathsea_lib=
	kpathsea_def=
else
	AC_MSG_CHECKING(for kpathsea library)
	kpathsea_dir=
	kpathsea_lib=
	kpathsea_lib_static=
	kpathsea_def=
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
		#include <stdio.h>
		#include <kpathsea/tex-file.h>
	]], [[]])],[
		kpathsea_dir=/usr/include
		kpathsea_lib=-lkpathsea
		kpathsea_def=-DHAVE_LIBKPATHSEA
	],[
	for cand in .. ../kpse3-2 kpse3-2 . /usr/include /usr/local/include
	do
	  if test -f $cand/kpathsea/tex-file.h ; then
	    if test -f $cand/../lib/libkpathsea.a; then
	      kpathsea_dir=$cand
	      kpathsea_def="-DHAVE_LIBKPATHSEA -I$cand"
	      kpathsea_lib_static=$cand/../lib/libkpathsea.a
	    else
	      if test -f $cand/kpathsea/STATIC/libkpathsea.a; then
	        kpathsea_lib_static=$cand/kpathsea/STATIC/libkpathsea.a
		kpathsea_dir=$cand
		kpathsea_def="-DHAVE_LIBKPATHSEA -I$cand"
	      fi
	    fi
	  fi
	done
	])
	if test -z "$kpathsea_dir"; then
		AC_MSG_WARN(not found)
	else
		AC_MSG_RESULT($kpathsea_dir)
	fi
fi
AC_SUBST(kpathsea_dir)dnl
AC_SUBST(kpathsea_lib)dnl
AC_SUBST(kpathsea_lib_static)dnl
AC_SUBST(kpathsea_def)dnl

dnl ---------------------------------------------------------------------------
dnl AC_CONFIG_SUBDIRS(regex-0.12)
dnl ---------------------------------------------------------------------------

dnl AC_CONFIG_SUBDIRS(BibTcl)

AC_CONFIG_HEADERS([include/bibtool/config.h:AutoConf/config.h.in regex-0.12/config.h:AutoConf/reconfig.h.in])

AC_CONFIG_FILES([makefile:AutoConf/makefile.in])
AC_OUTPUT
dnl ---------------------------------------------------------------------------
