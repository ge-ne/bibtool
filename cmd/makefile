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

CFLAGS  = -g -Wall -I $(BASEDIR)include -DREGEX

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

L_OFILES = binding.o		\
	   class/boolean.o	\
	   class/class.o	\
	   class/db.o		\
	   class/function.o	\
	   class/list.o		\
	   class/number.o	\
	   class/record.o	\
	   class/string.o	\
	   lcore.o		\
	   linereader.o		\
	   literate.o		\
	   lreader.o		\
	   rec_sort.o		\
	   term.o		\
	   tstack.o

#------------------------------------------------------------------------------

all: tester

binding.o:	binding.c binding.h literate.h term.h lcore.h lreader.h builtin.h
class/boolean.o:  class/boolean.c term.h binding.h
class/class.o:	  class/class.c term.h binding.h
class/function.o: class/function.c term.h binding.h
class/list.o:	  class/list.c term.h binding.h
class/db.o:	  class/db.c term.h binding.h lcore.h rec_sort.h
class/number.o:	  class/number.c term.h binding.h
class/record.o:	  class/record.c term.h binding.h
class/string.o:	  class/string.c term.h binding.h
lcore.o:	  lcore.c lcore.h term.h
linereader.o:	  linereader.c linereader.h
literate.o:	  literate.c literate.h term.h
lreader.o:	  lreader.c lreader.h lreader.h term.h linereader.h lcore.h tstack.h binding.h
rec_sort.o:	  rec_sort.c rec_sort.h term.h binding.h # lcore.h
term.o:		  term.c term.h
tester.o:	  tester.c term.h lcore.h lreader.h binding.h tstack.h
tstack.o:	  tstack.c tstack.h lcore.h term.h binding.h

tester: tester.o $(L_OFILES) $(OFILES)
	@$(CC) -g -O2 -o $@ $^ -lkpathsea

_: tester
	@tester -e _.ttt

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
