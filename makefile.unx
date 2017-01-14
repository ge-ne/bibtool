# *** makefile.unx ************************************************************
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 1996-2017 Gerd Neugebauer
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
# *****************************************************************************

#  Look also in the file include/bibtool/config.h for additional
#  configuration parameters.
#  Read the file INSTALL for explanation.
# =============================================================================

#  This is the generic makefile for BibTool.
#  Especially it can be used on Unix systems and as a basis for
#  systems not directly mentioned in the distribution.

# =============================================================================
#  Configuration Section
# =============================================================================
# 
# -------------------------------------------------------
#  Destination directory for make install
#  This is usually a directory where public executables
#  are installed.

BINDIR     = /usr/local/bin

# -------------------------------------------------------
#  Destination directory for make install.man
#  This is usually a directory where public man pages
#  are installed.
#  Additionally name the section of the man pages to use.
#  This should be 1 (user commands), l (local), or n (new)
# 
MANDIR     = /usr/local/man
MANSECT    = 1

# -------------------------------------------------------
#  Destination directory for make install.lib
#  This is usually a directory where public shared files
#  are installed plus a final BibTool.
# 

LIBDIR     = /usr/local/lib/BibTool

# -------------------------------------------------------
#  Destination directory for make install.include
#  This is usually a directory where public include files
#  are installed plus a final `BibTool'.
# 

INCLUDEDIR = /usr/local/include/BibTool

# -------------------------------------------------------
#  Name the C compiler
# 

CC         = gcc
# CC       = cc

# -------------------------------------------------------
#  CFLAGS are the flags for the C compiler.
#  For debugging it should be -g. 
#  For final version you can try to activate 
#  the optimizer with -O or -O2 or whatever
#  BEWARE: Some C compiler produce erroneous code if the
# 	   optimizer is turned on.
# 

CFLAGS  =
# CFLAGS  = -O
#  GNU C
# CFLAGS  = -g -Wall
# CFLAGS  = -g -Wall -pedantic -Wpointer-arith -Wshadow -Wcast-align

# -------------------------------------------------------
#  C_INCLUDE are the flags for the C compiler pointing it
#  to the location of the header files. Usually this
#  does not need any modifications.
# 

C_INCLUDE  = -Iinclude

# -------------------------------------------------------
#  EXT is the optional extension of the final executable.
#  Various Operating Systems have their own ideas about
#  that.
# 

EXT		=

# -------------------------------------------------------
#  Extension of object files
# 

OBJ		= .o

# -------------------------------------------------------
#  Name some programs
# 
#  MV is a command to move certain files maybe to other
#  directories or drives. Only plain files are moved.

MV		= mv

#  RM is a command to remove certain files. It should not
#  be confused when trying to remove non-existent files.
#  Only plain files are removed.

RM		= rm -rf

# 
#  MAKEDEPEND is a program to find dependencies for
#  .c and .h files.
#  Not present on MS-DOS, Atari, Amiga, Next
MAKEDEPEND	= makedepend
# MAKEDEPEND	= gcc -MM
# 
#  INSTALL is a program to properly install some executable files.
#  Maybe cp should also do this job (on Unix)

INSTALL		= install
# INSTALL   = cp

# 
#  INSTALL_DATA is a command to install some data files.

INSTALL_DATA	= install -m 644
# INSTALL_DATA = mkdir

# 
#  INSTALL_DIR is a command to create a directory if not
#  already existent. If your install does not support the 
#  -d option you can try to use mkdir instead.

INSTALL_DIR	= ./mkdirchain
#  INSTALL_DIR = install -d
#  INSTALL_DIR = mkdir

#  -------------------------------------------------------
#  The ranlib program or : for nothing.
# 
RANLIB	        = ranlib

#  -------------------------------------------------------
#  The ar program invocation to add files to the archive.
# 
AR		= ar r

# 
#  PERL is the complet path to an existing perl executable.
#  Perl 4.* and Perl 5.* are both ok.
# 
PERL	      = /usr/local/bin/perl

# 
#  LINT is a program to check the C source for problems.
#  
LINT	      = lint
# 
#  CXREF is a C cross reference program.
#  
CXREF	      = cxref

# -------------------------------------------------------
#  Defines to support (non-ANSI) C compilers.
#  For Solaris 2 you may have to define HAVE_STRING_H
#  For ANSI C compilers they should be empty.
#  Mostly needed for the GNU regex library.
#  Include
#  -DHAVE_STRING_H	if your C compiler has string.h
# 			(e.g. on Solaris 2)
# 			Maybe you have to enlarge the
# 			include search path.
#  -DREGEX_MALLOC	if you have NO alloca() library
# 			function
#  -DHAVE_ALLOCA_H	if you need alloca.h for alloca()
# 
#  -DHAVE_CONFIG_H	if you want to use the file REGEX_DIR/config.h
# 			this file has to be created then.
# 

NON_ANSI_DEFS =

# -------------------------------------------------------
#  GNU Regular Expression Library support.
#  First of all the (sub)directory containing the 
#  necessary files (excluding trailing slash).
# 
#  This directory is contained in the BibTool distribution.
#  I have tried newer versions of this library without
#  positive results. (Try it if you don't believe me:-)
# 
REGEX_DIR     = regex-0.12
# 

REGEX_DEF     = -DREGEX -I$(REGEX_DIR)

REGEX         = regex$(OBJ)

# -------------------------------------------------------
#  Kpathsea Library support.
#  This library provides means to specify a search path 
#  with recursive search in subdirectories.
#  The library is NOT contained in the BibTool distribution.
#  This routines are expected to work with Kpathsea-2.6 or
#  above.
# 
#  See the file INSTALL for details.
# 
#  Kpathsea is not known to work yet on anything else but
#  Unix platforms.
#  This item is purely experimental.
#  Maybe you are better off not trying it!
# 
#  The value of KPATHSEA_DIR is the directory containing
#  the distribution of kpathsea. I.e. the directory
#  containing the subdirectory kpathsea.
#  The value of KPATHSEA is the name of the kpathsea library.
#  if kpathsea should not be used then it has to be empty.
#  The value of KPATHSEA_DEF are the additional flags for the
#  C compiler. It should arrange things that the macro
#  KPATHSEA is defined and the directory beneath kpathsea
#  is in the include search path.

KPATHSEA_DIR  = ../kpse2-6
KPATHSEA      = 
KPATHSEA_DEF  = 
#  KPATHSEA     = $(KPATHSEA_DIR)/kpathsea/kpathsea.a
#  KPATHSEA_DEF = -DHAVE_LIBKPATHSEA -I$(KPATHSEA_DIR)

# -------------------------------------------------------
#  Default search paths
#  The values are NULL or a string containing a colon
#  separated list of directories.
#  DON'T FORGET THE CURRENT DIRECTORY!
# 
#  The character ENV_SEP separates the directories in
#  environment search paths.
# 

BIBINPUTS_DEFAULT = NULL
BIBTOOL_DEFAULT   = \".:$(LIBDIR)\"
ENV_SEP           = \":\"

# -------------------------------------------------------
#  Declare the file naming conventions.
#  FILE_TYPES contains optionally a macro definition
#  determining the file naming conventions.
#  -DMSDOS denotes MSDOG-like file names. (Also for Atari)
#  -DAMIGA denotes the Amiga file names.
#  The default (empty) are UN*X-like file names.
# 
#  DIR_SEP is the directory-file separator.

FILE_TYPES        = 
DIR_SEP		  = /

# =============================================================================
#  End of Configuration Section
# =============================================================================

MAKEFILE      = makefile

SHELL         = /bin/sh

RSC_DEF	      = -DRSC_BIBINPUTS_DEFAULT=$(BIBINPUTS_DEFAULT)		\
		-DRSC_BIBTOOL_DEFAULT=$(BIBTOOL_DEFAULT)		\
		-DENV_SEP=$(ENV_SEP)

DONT_LINK     = -c
LINK_TO       = -o
STANDALONE    = -DSTANDALONE

C_FLAGS	      = $(C_INCLUDE) $(CFLAGS) $(FILE_TYPES)

CFILES	      = main.c		\
		$(CLIBFILES)
CLIBFILES     = database.c	\
		crossref.c	\
		entry.c		\
		error.c		\
		expand.c	\
		init.c		\
		io.c		\
		key.c		\
		macros.c	\
		names.c		\
		parse.c		\
		print.c		\
		pxfile.c	\
		record.c	\
		rewrite.c	\
		rsc.c		\
		s_parse.c	\
		symbols.c	\
		stack.c		\
		sbuffer.c	\
		tex_aux.c	\
		tex_read.c	\
		version.c	\
		type.c		\
		wordlist.c

HPATH	      = include${DIR_SEP}bibtool${DIR_SEP}
HFILES	      = config.h		\
		${HPATH}database.h	\
		${HPATH}crossref.h	\
		${HPATH}bibtool.h	\
		${HPATH}config.h	\
		${HPATH}entry.h		\
		${HPATH}error.h		\
		${HPATH}expand.h	\
		${HPATH}general.h	\
		${HPATH}init.h		\
		${HPATH}io.h		\
		${HPATH}key.h		\
		${HPATH}keynode.h	\
		${HPATH}macros.h	\
		${HPATH}names.h		\
		${HPATH}parse.h		\
		${HPATH}print.h		\
		${HPATH}pxfile.h	\
		${HPATH}record.h	\
		${HPATH}regex.h		\
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

OFILES	      = main$(OBJ)	\
		$(OLIBFILES)
OLIBFILES     = database$(OBJ)	\
		crossref$(OBJ)	\
		entry$(OBJ)	\
		error$(OBJ)	\
		expand$(OBJ)	\
		init$(OBJ)	\
		io$(OBJ)	\
		key$(OBJ)	\
		macros$(OBJ)	\
		names$(OBJ)	\
		parse$(OBJ)	\
		print$(OBJ)	\
		pxfile$(OBJ)	\
		record$(OBJ)	\
		rewrite$(OBJ)	\
		rsc$(OBJ)	\
		s_parse$(OBJ)	\
		symbols$(OBJ)	\
		stack$(OBJ)	\
		sbuffer$(OBJ)	\
		tex_aux$(OBJ)	\
		tex_read$(OBJ)	\
		type$(OBJ)	\
		version$(OBJ)	\
		wordlist$(OBJ)

DOCFILES      = doc$(DIR_SEP)bibtool.1		\
		doc$(DIR_SEP)bibtool.tex	\
		doc$(DIR_SEP)bibtool.bib	\
		doc$(DIR_SEP)bibtool.bbl	\
		doc$(DIR_SEP)bibtool.aux	\
		doc$(DIR_SEP)bibtool.ind	\
		doc$(DIR_SEP)bibtool.idx	\
		doc$(DIR_SEP)bibtool.ist	\
		doc$(DIR_SEP)config.tex		\
		doc$(DIR_SEP)version.tex	\
		doc$(DIR_SEP)ref_card.tex	\
		doc$(DIR_SEP)Makefile		\
		doc$(DIR_SEP)c_get.pl		\
		doc$(DIR_SEP)c_lib.tex

LIBFILES      = lib$(DIR_SEP)biblatex.rsc	\
		lib$(DIR_SEP)braces.rsc		\
		lib$(DIR_SEP)check_y.rsc	\
		lib$(DIR_SEP)default.rsc	\
		lib$(DIR_SEP)field.rsc		\
		lib$(DIR_SEP)improve.rsc	\
		lib$(DIR_SEP)iso2tex.rsc	\
		lib$(DIR_SEP)keep_bibtex.rsc	\
		lib$(DIR_SEP)keep_biblatex.rsc	\
		lib$(DIR_SEP)month.rsc		\
		lib$(DIR_SEP)opt.rsc		\
		lib$(DIR_SEP)sort_fld.rsc	\
		lib$(DIR_SEP)tex_def.rsc

PROGFILES     = Perl$(DIR_SEP)bibtool.pl	\
		Tcl$(DIR_SEP)bibtool.tcl
ETCFILES      = README.md			\
		INSTALL				\
		COPYING				\
		Changes.tex			\
		makefile.unx			\
		makefile.dos			\
		makefile.ata			\
		makefile.ami			\
		ToDo				\
		THANKS				\
		pxfile.man			\
		sbuffer.man			\
		doc$(DIR_SEP)c.tex		\
		doc$(DIR_SEP)c_main.tex		\
		doc$(DIR_SEP)c_lib.ind		\
		$(MSDOS_targets)		\
		$(PROGFILES)			\
		$(AUTOCONFFILES)		\
		$(BIBTCLFILES)

AUTOCONFFILES = configure			\
		configure.ac			\
		install-sh			\
		mkdirchain			\
		AutoConf$(DIR_SEP)config.h.in	\
		AutoConf$(DIR_SEP)makefile.in	\
		AutoConf$(DIR_SEP)reconfig.h.in

BIBTCLFILES   = BibTcl$(DIR_SEP)Makefile.in	\
		BibTcl$(DIR_SEP)README		\
		BibTcl$(DIR_SEP)bibtool.c	\
		BibTcl$(DIR_SEP)bibtcl.tex	\
		BibTcl$(DIR_SEP)bibtcl.ltx	\
		BibTcl$(DIR_SEP)bibtcl.bib	\
		BibTcl$(DIR_SEP)version.tex	\
		BibTcl$(DIR_SEP)configure.in	\
		BibTcl$(DIR_SEP)configure	\
		BibTcl$(DIR_SEP)dina4.sty	\
		BibTcl$(DIR_SEP)bibtool.ist	\
		BibTcl$(DIR_SEP)main.tcl

DISTFILES     = $(ETCFILES)			\
		$(CFILES)			\
		$(HFILES)			\
		$(LIBFILES)			\
		$(DOCFILES)			\
		$(REGEX_DIR)

# -----------------------------------------------------------------------------
#  The main target
# -----------------------------------------------------------------------------

default all: bibtool$(EXT)

bibtool$(EXT): $(OFILES) $(REGEX) $(KPATHSEA)
	$(CC) $(C_FLAGS) $(LINK_TO) $@ $(OFILES) $(REGEX) $(KPATHSEA)

tex_read$(EXT): tex_read.c
	$(CC) $(C_FLAGS) $(STANDALONE) tex_read.c $(LINK_TO) tex_read$(EXT)

tex_aux$(OBJ): tex_aux.c
	$(CC) $(C_FLAGS) $(REGEX_DEF) $(DONT_LINK) tex_aux.c

main$(OBJ): main.c
	$(CC) $(C_FLAGS) $(REGEX_DEF) $(KPATHSEA_DEF) $(DONT_LINK) main.c

init$(OBJ): init.c
	$(CC) $(C_FLAGS) $(KPATHSEA_DEF) $(DONT_LINK) init.c

io$(OBJ): io.c
	$(CC) $(C_FLAGS) $(KPATHSEA_DEF) $(DONT_LINK) io.c

parse$(OBJ): parse.c
	$(CC) $(C_FLAGS) $(KPATHSEA_DEF) $(DONT_LINK) parse.c

rewrite$(OBJ): rewrite.c
	$(CC) $(C_FLAGS) $(REGEX_DEF) $(DONT_LINK) rewrite.c

rsc$(OBJ): rsc.c
	$(CC) $(C_FLAGS) $(RSC_DEF) $(DONT_LINK) rsc.c

.c$(OBJ):
	$(CC) $(C_FLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $< -o $@

# __________________________________________________________________
#  Include the makefile into the dependencies to force updates
#  when the makefile is modified.
$(OFILES): $(MAKEFILE)

# __________________________________________________________________
#  Targets from the GNU Regular Expression Library.

regex$(OBJ): $(REGEX_DIR)$(DIR_SEP)regex.c $(MAKEFILE)
	$(CC) $(C_FLAGS) -I$(REGEX_DIR) $(NON_ANSI_DEFS) $(REGEX_DIR)$(DIR_SEP)regex.c $(DONT_LINK) -o $@

# -----------------------------------------------------------------------------
#  General development targets
# -----------------------------------------------------------------------------

CLEAN_TARGETS	= *$(OBJ) xref *.bak core #* *~ ; cd doc; $(MAKE) clean

clean:
	-$(RM) $(CLEAN_TARGETS)

veryclean: clean
	-$(RM) bibtool

doc: d-o-c
d-o-c:
	cd doc; $(MAKE) DIR_SEP=$(DIR_SEP)

test check: Test
Test:
	(cd test; $(MAKE))

libbib.a: $(OLIBFILES)
	$(AR) $@ $(OLIBFILES) regex.o
	$(RANLIB) $@

depend:
	-$(MAKEDEPEND) -fmakefile -DMAKEDEPEND  $(C_INCLUDE) $(CFILES)

install: install.bin install.lib

install.bin: bibtool$(EXT)
	-$(INSTALL_DIR) $(BINDIR)
	$(INSTALL) bibtool$(EXT) $(BINDIR)

INSTALL_LIB_FILES = lib$(DIR_SEP)*.*

install.lib: 
	-$(INSTALL_DIR) $(LIBDIR)
	for lib in $(INSTALL_LIB_FILES); do	\
	  $(INSTALL_DATA) $$lib $(LIBDIR);	\
	done

install.include: 
	-$(INSTALL_DIR) $(INCLUDEDIR)
	for lib in $(INSTALL_INCLUDE_FILES); do	\
	  $(INSTALL_DATA) $$lib $(INCLUDEDIR);	\
	done

install.man: 
	-$(INSTALL_DIR) $(MANDIR)$(DIR_SEP)man$(MANSECT)
	$(INSTALL) doc$(DIR_SEP)bibtool.1 \
		$(MANDIR)$(DIR_SEP)man$(MANSECT)$(DIR_SEP)bibtool.$(MANSECT)

uninstall.bin:
	-$(RM) $(BINDIR)$(DIR_SEP)bibtool$(EXT)

uninstall.lib:
	-$(RM) $(LIBDIR)

uninstall.include:
	-$(RM) $(INCLUDEDIR)

uninstall.man:
	-$(RM) $(MANDIR)$(DIR_SEP)man$(MANSECT)$(DIR_SEP)bibtool.$(MANSECT)

status:
	@echo $(LIBDIR)

# =============================================================================
# DO NOT DELETE THIS LINE -- make depend depends on it.
main.o database.o entry.o error.o expand.o init.o io.o key.o macros.o names.o parse.o print.o pxfile.o record.o rewrite.o rsc.o s_parse.o symbols.o stack.o sbuffer.o tex_aux.o tex_read.o type.o version.o wordlist.o: config.h include/bibtool/database.h include/bibtool/bibtool.h include/bibtool/config.h include/bibtool/entry.h include/bibtool/error.h include/bibtool/expand.h include/bibtool/general.h include/bibtool/init.h include/bibtool/io.h include/bibtool/key.h include/bibtool/keynode.h include/bibtool/macros.h include/bibtool/names.h include/bibtool/parse.h include/bibtool/print.h include/bibtool/pxfile.h include/bibtool/record.h include/bibtool/regex.h include/bibtool/resource.h include/bibtool/rewrite.h include/bibtool/rsc.h include/bibtool/s_parse.h include/bibtool/sbuffer.h include/bibtool/stack.h include/bibtool/symbols.h include/bibtool/tex_aux.h include/bibtool/tex_read.h include/bibtool/type.h include/bibtool/version.h include/bibtool/wordlist.h main.c database.c entry.c error.c expand.c init.c io.c key.c macros.c names.c parse.c print.c pxfile.c record.c rewrite.c rsc.c s_parse.c symbols.c stack.c sbuffer.c tex_aux.c tex_read.c version.c type.c wordlist.c

