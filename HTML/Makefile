#******************************************************************************
#* $Id: Makefile,v 1.7 2011-12-04 13:23:14 gene Exp $
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

DOCFILES      = ../Doc/config.tex	\
	  	../Doc/bibtool.bbl	\
	  	../Doc/bibtool.tex

INSTFILES     = ../Doc/config.tex	\
	  	../install.tex

CHANGESFILES  =	../Doc/config.tex	\
	  	../Changes.tex

FLAGS         =	-v -dir=target
DOC_FLAGS     =	${FLAGS} -prefix=doc -main=doc.html
INST_FLAGS    =	${FLAGS} -prefix=install -main=install.html
CHANGES_FLAGS =	${FLAGS} -prefix=changes -main=changes.html

all:	doc inst changelog

doc:
	perl L2H.pl ${DOC_FLAGS} ${DOCFILES}

inst:
	perl L2H.pl ${INST_FLAGS} ${INSTFILES}

changelog changes:
	perl L2H.pl ${CHANGES_FLAGS} ${CHANGESFILES}

#
