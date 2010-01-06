#******************************************************************************
#* $Id: Makefile,v 1.2 2010-01-06 13:57:42 gene Exp $
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
	perl L2H.pl -v -dir=target  ${INFILES}

ci:
	ci -l ${FILES}

