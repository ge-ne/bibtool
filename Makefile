#*** Makefile ******************************************************************
#
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 1996-2015 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
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
		configure		\
		configure.in		\
		install-sh		\
		mkdirchain		\
		test/BUnit.pm		\
		test/makefile		\
		test/bib/*.bib		\
		test/*.t

CTANFILES =	README			\
		doc/bibtool.pdf		\
		doc/ref_card.pdf	\
		doc/c_lib.pdf

lint:
	gcc  $(C_FLAGS) $(REGEX_DEF) $(DONT_LINK) -ansi -W -Wall -O2 ${CFILES}

dist:
	@( cd doc; make)
	@( cd ..; rm -f $(DIR).tar.gz;				\
	   tar  -cvzf $(DIRNO).tar.gz $(DISTFILES:%=$(DIR)/%)	\
		--exclude CVS --exclude config.status )
	@gpg -a -b ../$(DIRNO).tar.gz
	@( cd ..; rm -f $(DIR).zip;				\
	   zip  -r $(DIRNO).zip $(DISTFILES:%=$(DIR)/%)		\
		-x \*/\*/CVS/\* \*/config.status )

ctan: dist
	@rm -rf ../bibtool ../bibtool.zip
	@mkdir ../bibtool
	@cp $(CTANFILES) ../$(DIRNO).tar.gz ../$(DIRNO).tar.gz.asc ../bibtool
	@(cd ..; zip bibtool.zip bibtool/*)
	@rm -rf ../bibtool
#
