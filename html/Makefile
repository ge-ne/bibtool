#******************************************************************************
#* Makefile
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

DOCFILES      = ../doc/bibtool.bbl	\
	  	../doc/bibtool.tex

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
