#******************************************************************************
#* $Id: Makefile,v 1.1 2010-01-05 23:09:56 gene Exp $
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

INFILES = 	../Doc/config.tex	\
	  	../Doc/bibtool.bbl	\
	  	../Doc/bibtool.tex

FILES   = 	L2H.pl		\
	  	L2H.pm		\
	  	L2H_file.pm	\
	  	GPL.html	\
	  	LaTeX.lh	\
	  	Makefile

all:
	perl L2H.pl -v ${INFILES}

ci:
	ci -l ${FILES}

