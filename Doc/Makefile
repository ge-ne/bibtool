##*****************************************************************************
## $Id: Makefile,v 1.10 2011-06-08 17:26:03 gene Exp $
##=============================================================================
## 
## This file is part of BibTool.
## It is distributed under the GNU General Public License.
## See the file COPYING for details.
## 
## (c) 1997-2010 Gerd Neugebauer
## 
## Net: gene@gerd-neugebauer.de
## 
##*****************************************************************************

LATEX     = latex
PDFLATEX  = pdflatex
BIBTEX    = bibtex
MAKEINDEX = makeindex

DIR_SEP   = /

.SUFFIXES: .tex .toc .dvi .pdf .aux .bbl .ind .idx $(SUFFIXES)

.tex.pdf:
	$(PDFLATEX) $<
.tex.dvi:
	$(LATEX) $<
.tex.toc:
	$(PDFLATEX) $<
.tex.idx:
	$(PDFLATEX) $<
.tex.aux:
	$(PDFLATEX) $<
.aux.bbl:
	$(BIBTEX) $*

TARGETS = bibtool.pdf ref_card.pdf c_lib.pdf

##-----------------------------------------------------------------------------

all: $(TARGETS)

##-----------------------------------------------------------------------------

bibtool.dvi: bibtool.tex bibtool.bbl bibtool.ind version.tex
	$(LATEX) bibtool
	$(LATEX) bibtool

bibtool.pdf: bibtool.tex bibtool.bbl bibtool.ind version.tex
	$(PDFLATEX) bibtool
	$(PDFLATEX) bibtool

bibtool.ind ind index: bibtool.idx
	$(MAKEINDEX) -s bibtool.ist bibtool

##-----------------------------------------------------------------------------

config.tex: ..$(DIR_SEP)Makefile ..$(DIR_SEP)config.h
	cd ..; $(MAKE) Doc$(DIR_SEP)config.tex

version.tex: ../version.c
	./make_version.pl ../version.c > version.tex

##-----------------------------------------------------------------------------

ref_card.dvi: ref_card.tex version.tex
	$(LATEX) ref_card.tex

ref_card.pdf: ref_card.tex version.tex
	$(PDFLATEX) ref_card.tex

##-----------------------------------------------------------------------------

CDIR	= ..$(DIR_SEP)
HDIR	= ..$(DIR_SEP)include$(DIR_SEP)bibtool$(DIR_SEP)
CFILES	= $(HDIR)bibtool.h	\
	  $(HDIR)database.h	\
	  $(CDIR)database.c	\
	  $(HDIR)entry.h	\
	  $(CDIR)entry.c	\
	  $(HDIR)error.h	\
	  $(CDIR)error.c	\
	  $(HDIR)expand.h	\
	  $(CDIR)expand.c	\
	  $(HDIR)init.h		\
	  $(CDIR)init.c		\
	  $(HDIR)keynode.h	\
	  $(HDIR)key.h		\
	  $(CDIR)key.c		\
	  $(HDIR)macros.h	\
	  $(CDIR)macros.c	\
	  $(HDIR)names.h	\
	  $(CDIR)names.c	\
	  $(HDIR)parse.h	\
	  $(CDIR)parse.c	\
	  $(HDIR)print.h	\
	  $(CDIR)print.c	\
	  $(HDIR)pxfile.h	\
	  $(CDIR)pxfile.c	\
	  $(HDIR)record.h	\
	  $(CDIR)record.c	\
	  $(HDIR)rewrite.h	\
	  $(CDIR)rewrite.c	\
	  $(HDIR)resource.h	\
	  $(HDIR)rsc.h		\
	  $(CDIR)rsc.c		\
	  $(HDIR)s_parse.h	\
	  $(CDIR)s_parse.c	\
	  $(HDIR)stack.h	\
	  $(CDIR)stack.c	\
	  $(HDIR)sbuffer.h	\
	  $(CDIR)sbuffer.c	\
	  $(HDIR)symbols.h	\
	  $(CDIR)symbols.c	\
	  $(HDIR)tex_aux.h	\
	  $(CDIR)tex_aux.c	\
	  $(HDIR)tex_read.h	\
	  $(CDIR)tex_read.c	\
	  $(HDIR)type.h		\
	  $(CDIR)type.c		\
	  $(HDIR)version.h	\
	  $(CDIR)version.c	\
	  $(HDIR)wordlist.h	\
	  $(CDIR)wordlist.c

c_lib:
	$(LATEX) c_lib.tex
	$(MAKEINDEX) -s bibtool.ist c_lib
	$(LATEX) c_lib.tex

c_lib.dvi: c_lib.tex c_main.tex c.tex config.tex
	$(LATEX) c_lib.tex
	$(MAKEINDEX) -s bibtool.ist c_lib
	$(LATEX) c_lib.tex

c_lib.pdf: c_lib.tex c_main.tex c.tex config.tex
	$(PDFLATEX) c_lib.tex
	$(MAKEINDEX) -s bibtool.ist c_lib
	$(PDFLATEX) c_lib.tex

c_main.tex: $(CDIR)main.c c_get.pl
	perl c_get.pl $(CDIR)main.c > $@
c.tex: $(CFILES) c_get.pl
	perl c_get.pl $(CFILES) >  $@

##-----------------------------------------------------------------------------

clean:
	$(RM) *.bak *.BAK *~ *.log *.ilg *.blg

veryclean: clean
	$(RM) *.toc *.aux *.idx *.ind *.ilg *.bbl

distclean: veryclean
	$(RM) $(TARGETS)


