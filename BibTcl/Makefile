# Generated automatically from Makefile.in by configure.
# *****************************************************************************
#  $Id: Makefile,v 1.1 2007-02-08 20:34:25 gene Exp $
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 1996-2001 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
# *****************************************************************************

prefix		= /usr/local
exec_prefix	= ${prefix}

LIBDIR		= ${exec_prefix}/lib/BibTool

CC		= gcc -pipe
CFLAGS		= -g
SHLIB_CFLAGS	= -fPIC
SHLIB_LD	= gcc -pipe -shared
SHLIB_SUFFIX	= .so
SHLIB_VERSION	= 
SRC_DIR		= .
TCLSH		= tclsh
TCL_VERSION	= 8.4
TCL_PREFIX	= /usr
TCL_INCLUDE	= /usr/include
RM		= /bin/rm -f

LATEX 		= latex
BIBTEX 		= bibtex
MAKEINDEX	= makeindex

BIBTOOLDIR = ..
OFILES	   = $(BIBTOOLDIR)/database.o	\
	     $(BIBTOOLDIR)/entry.o	\
	     $(BIBTOOLDIR)/error.o	\
	     $(BIBTOOLDIR)/expand.o	\
	     $(BIBTOOLDIR)/init.o	\
	     $(BIBTOOLDIR)/key.o	\
	     $(BIBTOOLDIR)/macros.o	\
	     $(BIBTOOLDIR)/names.o	\
	     $(BIBTOOLDIR)/parse.o	\
	     $(BIBTOOLDIR)/print.o	\
	     $(BIBTOOLDIR)/pxfile.o	\
	     $(BIBTOOLDIR)/record.o	\
	     $(BIBTOOLDIR)/rewrite.o	\
	     $(BIBTOOLDIR)/regex.o	\
	     $(BIBTOOLDIR)/rsc.o	\
	     $(BIBTOOLDIR)/s_parse.o	\
	     $(BIBTOOLDIR)/symbols.o	\
	     $(BIBTOOLDIR)/stack.o	\
	     $(BIBTOOLDIR)/sbuffer.o	\
	     $(BIBTOOLDIR)/tex_aux.o	\
	     $(BIBTOOLDIR)/tex_read.o	\
	     $(BIBTOOLDIR)/type.o	\
	     $(BIBTOOLDIR)/version.o	\
	     $(BIBTOOLDIR)/wordlist.o

all:  bibtool${SHLIB_SUFFIX} bibtool.tcl

bibtool${SHLIB_SUFFIX}: bibtool.c $(OFILES)
	$(CC) -c $(CFLAGS) -I$(BIBTOOLDIR)/include -I$(TCL_INCLUDE) $(SHLIB_CFLAGS) -o bibtool.o $<
	$(SHLIB_LD) bibtool.o $(OFILES) -o $@
	$(RM) bibtool.o

bibtool.tcl: Makefile
	@echo "#----------------------------------------------------------" >$@
	@echo "# This file is automatically created."			   >>$@
	@echo "# Any modifications will be lost the next time it is made." >>$@
	@echo "# This file is part of BibTool."				   >>$@
	@echo "# Copyright (C) 1997-1998 Gerd Neugebauer."		   >>$@
	@echo "set BIBTOOLDIR {$(LIBDIR)}"				   >>$@
	@echo 'load $$BIBTOOLDIR/$$tcl_platform(os)$$tcl_platform(osVersion)/bibtool[info sharedlibextension]' >>$@

INST_DIR = `echo 'puts $(LIBDIR)/$$tcl_platform(os)$$tcl_platform(osVersion)'|$(TCLSH)`

bibtcl.aux bibtcl.idx: bibtcl.tex bibtcl.ltx
	$(LATEX) bibtcl.ltx
bibtcl.dvi: bibtcl.tex bibtcl.ltx bibtcl.bbl bibtcl.ind
	$(LATEX) bibtcl.ltx
	$(LATEX) bibtcl.ltx
bibtcl.ind: bibtcl.idx
	$(MAKEINDEX) -s bibtool.ist bibtcl
bibtcl.bbl: bibtcl.bib bibtcl.aux
	$(BIBTEX) bibtcl

install: bibtool${SHLIB_SUFFIX} bibtool.tcl
	-mkdir $(INST_DIR)
	cp bibtool${SHLIB_SUFFIX} bibtool.tcl $(INST_DIR)

clean:
	rm -f *.o *${SHLIB_SUFFIX} config.cache config.log config.status lib.exp

distclean: clean
	rm -f Makefile

status:
	@echo $(LIBDIR)
