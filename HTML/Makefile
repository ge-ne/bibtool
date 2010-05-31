#******************************************************************************
#* $Id: Makefile,v 1.6 2010-05-31 04:02:43 gene Exp $
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

DOCFILES      = ../Doc/version.tex	\
	  	../Doc/bibtool.bbl	\
	  	../Doc/bibtool.tex

INSTFILES     = ../Doc/version.tex	\
	  	../install.tex

CHANGESFILES  =	../Doc/version.tex	\
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
