#******************************************************************************
#* $Id: Makefile,v 1.8 2012-02-04 04:59:16 gene Exp $
# =============================================================================
#
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 1996-2012 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

include makefile

DIR  = $(shell basename `pwd`)

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
		Test/BUnit.pm		\
		Test/makefile		\
		Test/bib/*.bib		\
		Test/*.t

lint:
	gcc  $(C_FLAGS) $(REGEX_DEF) $(DONT_LINK) -ansi -W -Wall -O2 ${CFILES}

dist:
	@( cd Doc; make)
	@( cd ..; rm -f $(DIR).tar.gz;				\
	   tar  -cvzf $(DIR).tar.gz $(DISTFILES:%=$(DIR)/%)	\
		--exclude CVS --exclude config.status )
	@( cd ..; rm -f $(DIR).zip;				\
	   zip  -r $(DIR).zip $(DISTFILES:%=$(DIR)/%)		\
		-x \*/\*/CVS/\* \*/config.status )

#
