#******************************************************************************
#* $Id: makefile,v 0.00 2015/10/16 22:50:55 gene Exp $
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

CFLAGS = -I ../include -DREGEX

OFILES  = ../crossref.o	\
	  ../database.o	\
	  ../entry.o	\
	  ../error.o	\
	  ../expand.o	\
	  ../init.o	\
	  ../key.o	\
	  ../macros.o	\
	  ../names.o	\
	  ../parse.o	\
	  ../print.o	\
	  ../pxfile.o	\
	  ../record.o	\
	  ../rewrite.o	\
	  ../rsc.o	\
	  ../s_parse.o	\
	  ../symbols.o	\
	  ../stack.o	\
	  ../sbuffer.o	\
	  ../tex_aux.o	\
	  ../tex_read.o	\
	  ../type.o	\
	  ../version.o	\
	  ../wordlist.o	\
	  ../regex.o

all: sel_test

sel_test: sel_test.o term.o select.o $(OFILES) sel.o
	$(CC) -g -O2 -o $@ sel_test.o term.o select.o $(OFILES) sel.o -lkpathsea 

select.o: select.h term.h

term.o: term.h

clean:
	rm -f *.o

#
