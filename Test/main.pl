#!/bin/perl -W
#******************************************************************************
# $Id: main.pl,v 1.1 2011-09-25 13:41:53 gene Exp $
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

main.pl - Test suite for BibTool main.

=head1 SYNOPSIS

main.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
my $out = 'main_out_1.bib';
BUnit::run(name => 'main_out_1',
    args         => "-q -o $out x1",
    expected_out => '',
    expected_err => '',
    prepare      => sub { unlink($out) if -e $out; },
    check        => sub { if (-e $out)  {
                            unlink($out);
			    return 0;
			  }
			  print STDERR "missing $out\t";
			  return 1});

#------------------------------------------------------------------------------
BUnit::run(name => 'main_quiet_1',
	 args	      => '-q xyzzy',
	 expected_out => '',
	 expected_err => '');

#------------------------------------------------------------------------------
BUnit::run(name => 'main_000',
	 args	      => '',
	 expected_out => '',
	 expected_err => '');

#------------------------------------------------------------------------------
BUnit::run(name => 'main_001',
	 args	      => 'xyzzy',
	 expected_out => '',
	 expected_err => <<EOF);

*** BibTool WARNING: File xyzzy not found.
EOF

#------------------------------------------------------------------------------
BUnit::run(name => 'main_002',
	 args	      => 'x1.bib',
	 expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011
}
EOF
	 expected_err => '');

#------------------------------------------------------------------------------
BUnit::run(name => 'main_003',
	 args	      => 'x1',
	 expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011
}
EOF
	 expected_err => '');

#------------------------------------------------------------------------------
BUnit::run(name => 'main_010',
	 args	      => 'xampl.bib',
	 expected_out => <<EOF,
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

\@Article{	  article-minimal,
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  journal	= {\\mbox{G-Animal's} Journal},
  year		= 1986
}

\@Article{	  article-full,
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  journal	= {\\mbox{G-Animal's} Journal},
  year		= 1986,
  volume	= 41,
  number	= 7,
  pages		= "73+",
  month		= jul,
  note		= "This is a full ARTICLE entry"
}

\@Article{	  article-crossref,
  crossref	= {WHOLE-JOURNAL},
  key		= "",
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  pages		= "73+",
  note		= "This is a cross-referencing ARTICLE entry"
}

\@Article{	  whole-journal,
  key		= "GAJ",
  journal	= {\\mbox{G-Animal\'s} Journal},
  year		= 1986,
  volume	= 41,
  number	= 7,
  month		= jul,
  note		= {The entire issue is devoted to gnats and gnus (this entry
		  is a cross-referenced ARTICLE (journal))}
}

\@InBook{	  inbook-minimal,
  author	= "Donald E. Knuth",
  title		= "Fundamental Algorithms",
  publisher	= "Addison-Wesley",
  year		= "{\\noopsort{1973b}}1973",
  chapter	= "1.2"
}

\@InBook{	  inbook-full,
  author	= "Donald E. Knuth",
  title		= "Fundamental Algorithms",
  volume	= 1,
  series	= "The Art of Computer Programming",
  publisher	= "Addison-Wesley",
  address	= "Reading, Massachusetts",
  edition	= "Second",
  month		= "10~"  # jan,
  year		= "{\\noopsort{1973b}}1973",
  type		= "Section",
  chapter	= "1.2",
  pages		= "10--119",
  note		= "This is a full INBOOK entry"
}

\@InBook{	  inbook-crossref,
  crossref	= "whole-set",
  title		= "Fundamental Algorithms",
  volume	= 1,
  series	= "The Art of Computer Programming",
  edition	= "Second",
  year		= "{\\noopsort{1973b}}1973",
  type		= "Section",
  chapter	= "1.2",
  note		= "This is a cross-referencing INBOOK entry"
}

\@Book{		  book-minimal,
  author	= "Donald E. Knuth",
  title		= "Seminumerical Algorithms",
  publisher	= "Addison-Wesley",
  year		= "{\\noopsort{1973c}}1981"
}

\@Book{		  book-full,
  author	= "Donald E. Knuth",
  title		= "Seminumerical Algorithms",
  volume	= 2,
  series	= "The Art of Computer Programming",
  publisher	= "Addison-Wesley",
  address	= "Reading, Massachusetts",
  edition	= "Second",
  month		= "10~"  # jan,
  year		= "{\\noopsort{1973c}}1981",
  note		= "This is a full BOOK entry"
}

\@Book{		  book-crossref,
  crossref	= "whole-set",
  title		= "Seminumerical Algorithms",
  volume	= 2,
  series	= "The Art of Computer Programming",
  edition	= "Second",
  year		= "{\\noopsort{1973c}}1981",
  note		= "This is a cross-referencing BOOK entry"
}

\@Book{		  whole-set,
  author	= "Donald E. Knuth",
  publisher	= "Addison-Wesley",
  title		= "The Art of Computer Programming",
  series	= "Four volumes",
  year		= "{\\noopsort{1973a}}{\\switchargs{--90}{1968}}",
  note		= "Seven volumes planned (this is a cross-referenced set of
		  BOOKs)"
}

\@Booklet{	  booklet-minimal,
  key		= "Kn{\\printfirst{v}{1987}}",
  title		= "The Programming of Computer Art"
}

\@Booklet{	  booklet-full,
  author	= "Jill C. Knvth",
  title		= "The Programming of Computer Art",
  howpublished	= "Vernier Art Center",
  address	= "Stanford, California",
  month		= feb,
  year		= 1988,
  note		= "This is a full BOOKLET entry"
}

\@InCollection{	  incollection-minimal,
  author	= "Daniel D. Lincoll",
  title		= "Semigroups of Recurrences",
  booktitle	= "High Speed Computer and Algorithm Organization",
  publisher	= "Academic Press",
  year		= 1977
}

\@InCollection{	  incollection-full,
  author	= "Daniel D. Lincoll",
  title		= "Semigroups of Recurrences",
  editor	= "David J. Lipcoll and D. H. Lawrie and A. H. Sameh",
  booktitle	= "High Speed Computer and Algorithm Organization",
  number	= 23,
  series	= "Fast Computers",
  chapter	= 3,
  type		= "Part",
  pages		= "179--183",
  publisher	= "Academic Press",
  address	= "New York",
  edition	= "Third",
  month		= sep,
  year		= 1977,
  note		= "This is a full INCOLLECTION entry"
}

\@InCollection{	  incollection-crossref,
  crossref	= "whole-collection",
  author	= "Daniel D. Lincoll",
  title		= "Semigroups of Recurrences",
  pages		= "179--183",
  note		= "This is a cross-referencing INCOLLECTION entry"
}

\@Book{		  whole-collection,
  editor	= "David J. Lipcoll and D. H. Lawrie and A. H. Sameh",
  title		= "High Speed Computer and Algorithm Organization",
  booktitle	= "High Speed Computer and Algorithm Organization",
  number	= 23,
  series	= "Fast Computers",
  publisher	= "Academic Press",
  address	= "New York",
  edition	= "Third",
  month		= sep,
  year		= 1977,
  note		= "This is a cross-referenced BOOK (collection) entry"
}

\@Manual{	  manual-minimal,
  key		= "Manmaker",
  title		= "The Definitive Computer Manual"
}

\@Manual{	  manual-full,
  author	= "Larry Manmaker",
  title		= "The Definitive Computer Manual",
  organization	= "Chips-R-Us",
  address	= "Silicon Valley",
  edition	= "Silver",
  month		= apr # "-"  # may,
  year		= 1986,
  note		= "This is a full MANUAL entry"
}

\@MastersThesis{	  mastersthesis-minimal,
  author	= "{\\'{E}}douard Masterly",
  title		= "Mastering Thesis Writing",
  school	= "Stanford University",
  year		= 1988
}

\@MastersThesis{	  mastersthesis-full,
  author	= "{\\'{E}}douard Masterly",
  title		= "Mastering Thesis Writing",
  school	= "Stanford University",
  type		= "Master's project",
  address	= "English Department",
  month		= jun # "-"  # aug,
  year		= 1988,
  note		= "This is a full MASTERSTHESIS entry"
}

\@Misc{		  misc-minimal,
  key		= "Missilany",
  note		= "This is a minimal MISC entry"
}

\@Misc{		  misc-full,
  author	= "Joe-Bob Missilany",
  title		= "Handing out random pamphlets in airports",
  howpublished	= "Handed out at O'Hare",
  month		= oct,
  year		= 1984,
  note		= "This is a full MISC entry"
}

\@InProceedings{	  inproceedings-minimal,
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  booktitle	= "Proc. Fifteenth Annual ACM"  # stoc,
  year		= 1983
}

\@InProceedings{	  inproceedings-full,
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  editor	= "Wizard V. Oz and Mihalis Yannakakis",
  booktitle	= "Proc. Fifteenth Annual ACM"  # stoc,
  number	= 17,
  series	= "All ACM Conferences",
  pages		= "133--139",
  month		= mar,
  year		= 1983,
  address	= "Boston",
  organization	= acm,
  publisher	= "Academic Press",
  note		= "This is a full INPROCEDINGS entry"
}

\@InProceedings{	  inproceedings-crossref,
  crossref	= "whole-proceedings",
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  organization	= "",
  pages		= "133--139",
  note		= "This is a cross-referencing INPROCEEDINGS entry"
}

\@Proceedings{	  proceedings-minimal,
  key		= stoc-key,
  title		= "Proc. Fifteenth Annual"  # stoc,
  year		= 1983
}

\@Proceedings{	  proceedings-full,
  editor	= "Wizard V. Oz and Mihalis Yannakakis",
  title		= "Proc. Fifteenth Annual"  # stoc,
  number	= 17,
  series	= "All ACM Conferences",
  month		= mar,
  year		= 1983,
  address	= "Boston",
  organization	= acm,
  publisher	= "Academic Press",
  note		= "This is a full PROCEEDINGS entry"
}

\@Proceedings{	  whole-proceedings,
  key		= stoc-key,
  organization	= acm,
  title		= "Proc. Fifteenth Annual"  # stoc,
  address	= "Boston",
  year		= 1983,
  booktitle	= "Proc. Fifteenth Annual ACM"  # stoc,
  note		= "This is a cross-referenced PROCEEDINGS"
}

\@PhDThesis{	  phdthesis-minimal,
  author	= "F. Phidias Phony-Baloney",
  title		= "Fighting Fire with Fire: Festooning {F}rench Phrases",
  school	= "Fanstord University",
  year		= 1988
}

\@PhDThesis{	  phdthesis-full,
  author	= "F. Phidias Phony-Baloney",
  title		= "Fighting Fire with Fire: Festooning {F}rench Phrases",
  school	= "Fanstord University",
  type		= "{PhD} Dissertation",
  address	= "Department of French",
  month		= jun # "-"  # aug,
  year		= 1988,
  note		= "This is a full PHDTHESIS entry"
}

\@TechReport{	  techreport-minimal,
  author	= "Tom Terrific",
  title		= "An {\$O(n \\log n / \\! \\log\\log n)\$} Sorting Algorithm",
  institution	= "Fanstord University",
  year		= 1988
}

\@TechReport{	  techreport-full,
  author	= "Tom T{\\'{e}}rrific",
  title		= "An {\$O(n \\log n / \\! \\log\\log n)\$} Sorting Algorithm",
  institution	= "Fanstord University",
  type		= "Wishful Research Result",
  number	= "7",
  address	= "Computer Science Department, Fanstord, California",
  month		= oct,
  year		= 1988,
  note		= "This is a full TECHREPORT entry"
}

\@Unpublished{	  unpublished-minimal,
  author	= "Ulrich {\\"{U}}nderwood and Ned {\\~N}et and Paul {\\={P}}ot",
  title		= "Lower Bounds for Wishful Research Results",
  note		= "Talk at Fanstord University (this is a minimal UNPUBLISHED
		  entry)"
}

\@Unpublished{	  unpublished-full,
  author	= "Ulrich {\\"{U}}nderwood and Ned {\\~N}et and Paul {\\={P}}ot",
  title		= "Lower Bounds for Wishful Research Results",
  month		= nov # ", "  # dec,
  year		= 1988,
  note		= "Talk at Fanstord University (this is a full UNPUBLISHED
		  entry)"
}

\@Misc{		  random-note-crossref,
  key		= {Volume-2},
  note		= "Volume~2 is listed under Knuth \\cite{book-full}"
}
EOF
	expected_err => <<EOF);

*** BibTool WARNING:  (line 29 in ./xampl.bib): 125 non-space characters ignored.
EOF

#------------------------------------------------------------------------------
BUnit::run(name => 'main_help_1',
	 args	      => '-h',
	 expected_out => '',
	 expected_err => <<EOF ,
BibTool Vers. 2.xxx (C) 1996-2xxx Gerd Neugebauer

bibtool [options] [-o outfile] [[-i] infile] ...

	Options:
	-A<c>		Kind of disambiguating key strings: <c>=0|a|A
	-c		Include crossreferenced entries into the output (toggle)
	-d		Check double entries (toggle)
	-f <format>	Key generation enabled (formated key)
	-F		Key generation enabled with formated key
	-h		Print this help info and exit
	[-i] infile	Specify input file. If -i omitted it may not start
			with a -. If absent stdin is taken to read from.
			Multiple input files may be given.
	-k		Key generation enabled.
	-K		Key generation enabled (long key).
	-m macfile	Dump macros to macfile. - is stdout
	-M macfile	Dump used macros to macfile. - is stdout
	-o outfile	Specify output file as next argument
			If absent stdout is taken to write to.
	-q		Quiet mode. No warnings.
	-r resource	Load resource file (several are possible).
	-R		Load default resource file here.
	-s		Sort.
	-S		Sort reverse.
	-v		Enable verbose mode
	-V		Print version
	-x file		Extract from aux file.
	-X <regex>	Extract regular expression.
	-- <rsc>	Evaluate one resource command <rsc>.
	-\@		Print statistics (short).
	-#		Print statistics.

Library path: xxx
Special configuration options: xxx
EOF
	 fct_err =>
		 sub{local $_	 = shift;
		     s/Vers. 2.[0-9]+/Vers. 2.xxx/;
		     s/1996-2.../1996-2xxx/;
		     s/Library path: .*/Library path: xxx/;
		     s/Special configuration options: .*/Special configuration options: xxx/;
		     return $_
		 } );

#------------------------------------------------------------------------------
BUnit::run(name => 'main_version_1',
	 args	      => '-V',
	 expected_out => '',
	 expected_err => <<EOF ,
BibTool Vers. 2.xxx (C) 1996-2xxx Gerd Neugebauer


Library path: xxx
Special configuration options: xxx
EOF
	 fct_err =>
		 sub{local $_ = shift;
		     s/Vers. 2.[0-9]+/Vers. 2.xxx/;
		     s/1996-2.../1996-2xxx/;
		     s/Library path: .*/Library path: xxx/;
		     s/Special configuration options: .*/Special configuration options: xxx/;
		     return $_
		 } );

#------------------------------------------------------------------------------
BUnit::run(name => 'main_ressource_1',
	 args	      => '-- xyzzy=on',
	 expected_err => "\n*** BibTool ERROR: Resource xyzzy unknown.\n");

#------------------------------------------------------------------------------
BUnit::run(name => 'main_@_1',
	 args	      => '-@ x1',
	 expected_err => "\n---  Manual              1 read      1 written\n");

#------------------------------------------------------------------------------
BUnit::run(name => 'main_count_1',
	 args	      => '-- count.used=on x1',
	 expected_err		  => "\n---  Manual              1 read      1 written\n");

#------------------------------------------------------------------------------
BUnit::run(name => 'main_count_2',
	 args	      => '-- count.used=off x1',
	 expected_err => '');

#------------------------------------------------------------------------------
BUnit::run(name => 'main_@_2',
	 args	      => '-@ xampl',
	 expected_err => <<EOF);

*** BibTool WARNING:  (line 29 in ./xampl.bib): 125 non-space characters ignored.

---  STRING              3 read      3 written
---  PREAMBLE            1 read      1 written
---  Article             4 read      4 written
---  Book                5 read      5 written
---  Booklet             2 read      2 written
---  InBook              3 read      3 written
---  InCollection        3 read      3 written
---  InProceedings       3 read      3 written
---  Manual              2 read      2 written
---  MastersThesis       2 read      2 written
---  Misc                3 read      3 written
---  PhDThesis           2 read      2 written
---  Proceedings         3 read      3 written
---  TechReport          2 read      2 written
---  Unpublished         2 read      2 written
EOF

#------------------------------------------------------------------------------
BUnit::run(name => 'main_#_1',
	 args	      => '-# x1',
	 expected_err => <<EOF);

---  STRING              0 read      0 written
---  PREAMBLE            0 read      0 written
---  COMMENT             0 read      0 written
---  ALIAS               0 read      0 written
---  MODIFY              0 read      0 written
---  INCLUDE             0 read      0 written
---  Article             0 read      0 written
---  Book                0 read      0 written
---  Booklet             0 read      0 written
---  Conference          0 read      0 written
---  InBook              0 read      0 written
---  InCollection        0 read      0 written
---  InProceedings       0 read      0 written
---  Manual              1 read      1 written
---  MastersThesis       0 read      0 written
---  Misc                0 read      0 written
---  PhDThesis           0 read      0 written
---  Proceedings         0 read      0 written
---  TechReport          0 read      0 written
---  Unpublished         0 read      0 written
EOF

#------------------------------------------------------------------------------
BUnit::run(name => 'main_#_2',
	 args	      => '-# xampl.bib',
	 expected_err => <<EOF);

*** BibTool WARNING:  (line 29 in ./xampl.bib): 125 non-space characters ignored.

---  STRING              3 read      3 written
---  PREAMBLE            1 read      1 written
---  COMMENT             0 read      0 written
---  ALIAS               0 read      0 written
---  MODIFY              0 read      0 written
---  INCLUDE             0 read      0 written
---  Article             4 read      4 written
---  Book                5 read      5 written
---  Booklet             2 read      2 written
---  Conference          0 read      0 written
---  InBook              3 read      3 written
---  InCollection        3 read      3 written
---  InProceedings       3 read      3 written
---  Manual              2 read      2 written
---  MastersThesis       2 read      2 written
---  Misc                3 read      3 written
---  PhDThesis           2 read      2 written
---  Proceedings         3 read      3 written
---  TechReport          2 read      2 written
---  Unpublished         2 read      2 written
EOF

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
