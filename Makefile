#******************************************************************************
#* $Id: Makefile,v 1.6 2012-01-26 19:54:20 gene Exp $
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
		Doc/c.tex		\
		Doc/c_main.tex		\
		Doc/config.tex		\
		Doc/c_get.pl		\
		Doc/make_version.pl	\
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

dist:
	@( cd ..; rm -f $(DIR).tar.gz; \
	   tar  -cvzf $(DIR).tar.gz $(DISTFILES:%=$(DIR)/%)	\
		--exclude CVS --exclude config.status )
	@( cd ..; rm -f $(DIR).zip; \
	   zip  -r $(DIR).zip $(DISTFILES:%=$(DIR)/%)		\
		-x \*/\*/CVS/\* \*/config.status )

#