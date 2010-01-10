#******************************************************************************
#* $Id: Makefile,v 1.3 2010-01-10 09:38:20 gene Exp $
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

INFILES = 	../Doc/config.tex	\
	  	../Doc/bibtool.bbl	\
	  	../Doc/bibtool.tex


FLAGS   =	-v -dir=target

all:
	perl L2H.pl ${FLAGS} ${INFILES}
	cp GPL.html *.png *.gif target



