#*** makefile ******************************************************************
#
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2015 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

CFLAGS = -Wall -I ../include -DREGEX

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

all: tester

term.o: term.c term.h symdef.h
symdef.o: symdef.c term.h symdef.h
tstack.o: tstack.c tstack.h term.h symdef.h
lreader.o: lreader.c term.h symdef.h
tester.o: tester.c term.h symdef.h binding.h
binding.o: binding.c binding.h

tester: tester.o lreader.o tstack.o term.o symdef.o binding.o $(OFILES)
	@$(CC) -g -O2 -o $@ $^ -lkpathsea

test: do_test
do_test: tester test/*/*.t
	(cd test; make)

clean:
	rm -f *.o

distclean: clean

#

