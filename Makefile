#*** Makefile ******************************************************************
#
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 1996-2016 Gerd Neugebauer
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
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

include makefile

DIR  = $(shell basename `pwd`)
DIRNO  = $(shell basename `pwd`-`sed -e '/bibtool_version =/s/.*"\(.*\)".*/\1/p' -e d version.c`)

DISTFILES += 	AutoConf/config.h.in 	\
		AutoConf/makefile.in	\
		AutoConf/reconfig.h.in	\
		BibTcl/bibtcl.bib	\
		BibTcl/bibtcl.ltx	\
		BibTcl/bibtcl.tex	\
		BibTcl/bibtool.c	\
		BibTcl/bibtool.ist	\
		BibTcl/Makefile.in	\
		BibTcl/configure	\
		BibTcl/configure.in	\
		BibTcl/dina4.sty	\
		BibTcl/main.tcl		\
		BibTcl/README		\
		BibTcl/version.tex	\
		BibTcl/Makefile		\
		MSDOS/link.dj		\
		MSDOS/link.msc		\
		MSDOS/link.wat		\
		Linux/ld-version-script	\
		configure		\
		configure.ac		\
		install-sh		\
		mkdirchain		\
		test/lib/BUnit.pm	\
		test/makefile		\
		test/bib/*.bib		\
		test/*.t

CTANFILES =	README.md		\
		doc/bibtool.pdf		\
		doc/ref_card.pdf	\
		doc/c_lib.pdf

LATEX	=	lualatex

configure: configure.ac
	autoconf

lint:
	gcc  $(C_FLAGS) $(REGEX_DEF) $(DONT_LINK) -ansi -W -Wall -O2 ${CFILES}

dist:   Changes.pdf install.pdf
	@( cd doc; make)
	@( cd ..; rm -f $(DIRNO).tar.gz;			\
	   tar  -cvzf $(DIRNO).tar.gz $(DISTFILES:%=$(DIR)/%)	\
		--owner bibtool --group bibtool			\
		--exclude CVS --exclude config.status )
	@gpg -a -b ../$(DIRNO).tar.gz
	@( cd ..; rm -f $(DIRNO).zip;				\
	   zip  -r $(DIRNO).zip $(DISTFILES:%=$(DIR)/%)		\
		-x \*/\*/CVS/\* \*/config.status )

ctan: dist
	@rm -rf ../bibtool ../bibtool.zip
	@mkdir ../bibtool
	@cp $(CTANFILES) ../$(DIRNO).tar.gz ../$(DIRNO).tar.gz.asc ../bibtool
	@( cd ..; zip bibtool.zip bibtool/* )
	@rm -rf ../bibtool

%.pdf: %.tex
	@$(LATEX) $*

#
