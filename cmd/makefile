#*** makefile ******************************************************************
#
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2015-2016 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

BASEDIR = ../

CFLAGS  = -Wall -I $(BASEDIR)include -DREGEX

OFILES  = $(BASEDIR)crossref.o	\
	  $(BASEDIR)database.o	\
	  $(BASEDIR)entry.o	\
	  $(BASEDIR)error.o	\
	  $(BASEDIR)expand.o	\
	  $(BASEDIR)init.o	\
	  $(BASEDIR)io.o	\
	  $(BASEDIR)key.o	\
	  $(BASEDIR)macros.o	\
	  $(BASEDIR)names.o	\
	  $(BASEDIR)parse.o	\
	  $(BASEDIR)print.o	\
	  $(BASEDIR)pxfile.o	\
	  $(BASEDIR)record.o	\
	  $(BASEDIR)rewrite.o	\
	  $(BASEDIR)rsc.o	\
	  $(BASEDIR)s_parse.o	\
	  $(BASEDIR)symbols.o	\
	  $(BASEDIR)stack.o	\
	  $(BASEDIR)sbuffer.o	\
	  $(BASEDIR)tex_aux.o	\
	  $(BASEDIR)tex_read.o	\
	  $(BASEDIR)type.o	\
	  $(BASEDIR)version.o	\
	  $(BASEDIR)wordlist.o	\
	  $(BASEDIR)regex.o

L_OFILES = term.o		\
	   binding.o		\
	   lcore.o		\
	   tstack.o		\
	   lreader.o		\
	   linereader.o		\
	   cstring.o		\
	   cnumber.o		\
	   ccons.o		\
	   cdb.o		\
	   cboolean.o		\
	   literate.o

#------------------------------------------------------------------------------

all: tester

term.o:		term.c term.h
lcore.o:	lcore.c lcore.h term.h
tstack.o:	tstack.c tstack.h lcore.h term.h binding.h
linereader.o:	linereader.c linereader.h
lreader.o:	lreader.c lreader.h lreader.h term.h linereader.h lcore.h tstack.h binding.h
binding.o:	binding.c binding.h literate.h term.h lcore.h lreader.h builtin.h
literate.o:	literate.c literate.h term.h
tester.o:	tester.c term.h lcore.h lreader.h binding.h tstack.h
ccons.o:	ccons.c term.h binding.h
cnumber.o:	cnumber.c term.h binding.h
cstring.o:	cstring.c term.h binding.h
cboolean.o:	cboolean.c term.h binding.h
cdb.o:		cdb.c term.h binding.h

tester: tester.o $(L_OFILES) $(OFILES)
	@$(CC) -g -O2 -o $@ $^ -lkpathsea

test:    run_tests

run_tests: tester test/*/*.t
	(cd test; make)

depend:
	makedepend -I $(BASEDIR)include *.c

#------------------------------------------------------------------------------

clean:
	rm -f *.o

distclean: clean

#
# DO NOT DELETE
