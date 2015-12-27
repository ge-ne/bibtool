#******************************************************************************
#* $Id: makefile,v 0.00 2015/12/22 10:51:45 gene Exp $
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

all: test_t

term.o: term.c term.h symdef.h
symdef.o: symdef.c term.h symdef.h
t_stack.o: t_stack.c t_stack.h term.h symdef.h
t_parser.o: t_parser.c term.h symdef.h
test_t.o: term.h symdef.h

test_t: test_t.o t_parser.o t_stack.o term.o symdef.o $(OFILES)
	@$(CC) -g -O2 -o $@ $^ -lkpathsea

clean:
	rm -f *.o

distclean: clean

# -----------------------------------------------------------------------------

TEST_PRG=test_t
.SUFFIXES: .t .test $(SUFFIXES)

.t.test: $(TEST_PRG)
	@TEST_PRG=$(TEST_PRG) $(PERL) -I. $<

#

