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

L_OFILES = term.o symdef.o binding.o tstack.o lreader.o

#------------------------------------------------------------------------------

all: tester

term.o:    term.c term.h symdef.h
symdef.o:  symdef.c term.h symdef.h
tstack.o:  tstack.c tstack.h term.h symdef.h
lreader.o: lreader.c term.h symdef.h
tester.o:  tester.c term.h symdef.h binding.h
binding.o: binding.c binding.h term.h symdef.h

tester: tester.o $(L_OFILES) $(OFILES)
	@$(CC) -g -O2 -o $@ $^ -lkpathsea

test:    run_tests

run_tests: tester test/*/*.t
	(cd test; make)

#------------------------------------------------------------------------------

clean:
	rm -f *.o

distclean: clean

#

