#******************************************************************************
#* $Id: Makefile,v 1.5 2010-02-06 10:09:28 gene Exp $
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

INFILES = 	../Doc/config.tex	\
	  	../Doc/bibtool.bbl	\
	  	../Doc/bibtool.tex


FLAGS   =	-v -dir=target -prefix=doc -main=doc.html

all:
	perl L2H.pl ${FLAGS} ${INFILES}


#
