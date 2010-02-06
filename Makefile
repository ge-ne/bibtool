#******************************************************************************
#* $Id: Makefile,v 1.2 2010-02-06 10:08:10 gene Exp $
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
		Doc/version.tex		\
		Doc/c_get.pl		\
		Doc/make_version.pl	\
		MSDOS/link.dj		\
		MSDOS/link.msc		\
		MSDOS/link.wat		\
		configure		\
		configure.in		\
		install-sh		\
		mkdirchain

dist:
	@( cd ..; rm -f $(DIR).tar.gz; tar -cvf - $(DISTFILES:%=$(DIR)/%) | gzip > $(DIR).tar.gz )
	@( cd ..; rm -f $(DIR).zip; zip $(DIR).zip $(DISTFILES:%=$(DIR)/%) )

#