#******************************************************************************
#* $Id: makefile,v 0.00 2015/10/16 22:50:55 gene Exp $
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

CFLAGS= -I ../include -DREGEX

all: sel_test

sel_test: sel_test.o term.o select.o ../sbuffer.o sel.o

select.o: select.h term.h

term.o: term.h

clean:
	rm -f *.o

#
