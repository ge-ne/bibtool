# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2016 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2, or (at your option)
#  any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#*=============================================================================
# 
# This is the makefile to run the test suite for BibTool. It should
# work at least for Unix-like systems with GNUmake and bash.
# For instance Linux and Windows with cygwin fulfill this pre-condition.
#
# Note that portability hasn't been an issue for this makefile yet.
#

# -------------------------------------------------------
#  EXT is the optional extension of the final executable.
#  Various operating systems have their own ideas about
#  that.
# 

EXT =

# -----------------------------------------------------------------------------
BIBTOOL_PRG   = ../bibtool$(EXT)
PERL          = perl$(EXT)

DIR_SEP       =/
CPATH	      = ..${DIR_SEP}
CFILES	      = ${CPATH}main.c		\
		${CPATH}crossref.c	\
		${CPATH}database.c	\
		${CPATH}entry.c		\
		${CPATH}error.c		\
		${CPATH}expand.c	\
		${CPATH}init.c		\
		${CPATH}key.c		\
		${CPATH}macros.c	\
		${CPATH}names.c		\
		${CPATH}parse.c		\
		${CPATH}print.c		\
		${CPATH}pxfile.c	\
		${CPATH}record.c	\
		${CPATH}rewrite.c	\
		${CPATH}rsc.c		\
		${CPATH}s_parse.c	\
		${CPATH}symbols.c	\
		${CPATH}stack.c		\
		${CPATH}sbuffer.c	\
		${CPATH}tex_aux.c	\
		${CPATH}tex_read.c	\
		${CPATH}type.c		\
		${CPATH}version.c	\
		${CPATH}wordlist.c
HPATH	      = ${CPATH}include${DIR_SEP}bibtool${DIR_SEP}
HFILES	      = ${CPATH}config.h	\
		${HPATH}crossref.h	\
		${HPATH}database.h	\
		${HPATH}bibtool.h	\
		${HPATH}config.h	\
		${HPATH}entry.h		\
		${HPATH}error.h		\
		${HPATH}expand.h	\
		${HPATH}general.h	\
		${HPATH}init.h		\
		${HPATH}key.h		\
		${HPATH}keynode.h	\
		${HPATH}macros.h	\
		${HPATH}names.h		\
		${HPATH}parse.h		\
		${HPATH}print.h		\
		${HPATH}pxfile.h	\
		${HPATH}regex.h		\
		${HPATH}record.h	\
		${HPATH}resource.h	\
		${HPATH}rewrite.h	\
		${HPATH}rsc.h		\
		${HPATH}s_parse.h	\
		${HPATH}sbuffer.h	\
		${HPATH}stack.h		\
		${HPATH}symbols.h	\
		${HPATH}tex_aux.h	\
		${HPATH}tex_read.h	\
		${HPATH}type.h		\
		${HPATH}version.h	\
		${HPATH}wordlist.h

default check all: $(BIBTOOL_PRG) $(SUITES)
	@BIBTOOL_PRG=$(BIBTOOL_PRG) ${PERL} -Ilib -MBUnit -e "exit all()"

$(BIBTOOL_PRG): $(CFILES) $(HFILES)
	(cd ..; make)

clean:
	${RM} *.log *.err *.???-expected *.out *~ *.bak

distclean: clean

# -----------------------------------------------------------------------------

.SUFFIXES: .t .test $(SUFFIXES)

.t.test: $(BIBTOOL_PRG)
	@BIBTOOL_PRG=$(BIBTOOL_PRG) $(PERL) -Ilib $<

#
