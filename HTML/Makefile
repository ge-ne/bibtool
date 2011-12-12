#******************************************************************************
#* $Id: Makefile,v 1.8 2011-12-12 15:15:39 gene Exp $
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

DOCFILES      = ../Doc/bibtool.bbl	\
	  	../Doc/bibtool.tex

INSTFILES     = ../install.tex

CHANGESFILES  =	../Changes.tex

FLAGS         =	-v -dir=target
DOC_FLAGS     =	${FLAGS} -prefix=doc -main=doc.html -workdir=../Doc
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
