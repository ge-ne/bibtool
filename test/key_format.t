#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2014 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

key.t - Test suite for BibTool key.

=head1 SYNOPSIS

key.t 

=head1 DESCRIPTION

This module contains some test cases. Running this module as program
will run all test cases and print a summary for each. Optionally files
*.out and *.err are left if the expected result does not match the
actual result.

=head1 OPTIONS

none 

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name => '_k_1',
	 args	      => '-k bib/xampl.bib',
	 expected_out => <<EOF,
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} "
	 # "\\newcommand{\\printfirst}[2]{#1} "
	 # "\\newcommand{\\singleletter}[1]{#1} "
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

\@Article{	  aamport:gnats,
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  journal	= {\\mbox{G-Animal's} Journal},
  year		= 1986
}

\@Article{	  aamport:gnats*1,
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

\@Article{	  aamport:gnats*2,
  crossref	= {gaj},
  key		= "",
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  pages		= "73+",
  note		= "This is a cross-referencing ARTICLE entry"
}

\@Article{	  gaj,
  key		= "GAJ",
  journal	= {\\mbox{G-Animal\'s} Journal},
  year		= 1986,
  volume	= 41,
  number	= 7,
  month		= jul,
  note		= {The entire issue is devoted to gnats and gnus (this entry
		  is a cross-referenced ARTICLE (journal))}
}

\@InBook{	  knuth:fundamental,
  author	= "Donald E. Knuth",
  title		= "Fundamental Algorithms",
  publisher	= "Addison-Wesley",
  year		= "{\\noopsort{1973b}}1973",
  chapter	= "1.2"
}

\@InBook{	  knuth:fundamental*1,
  author	= "Donald E. Knuth",
  title		= "Fundamental Algorithms",
  volume	= 1,
  series	= "The Art of Computer Programming",
  publisher	= "Addison-Wesley",
  address	= "Reading, Massachusetts",
  edition	= "Second",
  month		= "10~" # jan,
  year		= "{\\noopsort{1973b}}1973",
  type		= "Section",
  chapter	= "1.2",
  pages		= "10--119",
  note		= "This is a full INBOOK entry"
}

\@InBook{	  knuth:fundamental*2,
  crossref	= "knuth:art",
  title		= "Fundamental Algorithms",
  volume	= 1,
  series	= "The Art of Computer Programming",
  edition	= "Second",
  year		= "{\\noopsort{1973b}}1973",
  type		= "Section",
  chapter	= "1.2",
  note		= "This is a cross-referencing INBOOK entry"
}

\@Book{		  knuth:seminumerical,
  author	= "Donald E. Knuth",
  title		= "Seminumerical Algorithms",
  publisher	= "Addison-Wesley",
  year		= "{\\noopsort{1973c}}1981"
}

\@Book{		  knuth:seminumerical*1,
  author	= "Donald E. Knuth",
  title		= "Seminumerical Algorithms",
  volume	= 2,
  series	= "The Art of Computer Programming",
  publisher	= "Addison-Wesley",
  address	= "Reading, Massachusetts",
  edition	= "Second",
  month		= "10~" # jan,
  year		= "{\\noopsort{1973c}}1981",
  note		= "This is a full BOOK entry"
}

\@Book{		  knuth:seminumerical*2,
  crossref	= "knuth:art",
  title		= "Seminumerical Algorithms",
  volume	= 2,
  series	= "The Art of Computer Programming",
  edition	= "Second",
  year		= "{\\noopsort{1973c}}1981",
  note		= "This is a cross-referencing BOOK entry"
}

\@Book{		  knuth:art,
  author	= "Donald E. Knuth",
  publisher	= "Addison-Wesley",
  title		= "The Art of Computer Programming",
  series	= "Four volumes",
  year		= "{\\noopsort{1973a}}{\\switchargs{--90}{1968}}",
  note		= "Seven volumes planned (this is a cross-referenced set of
		  BOOKs)"
}

\@Booklet{	  :programming,
  key		= "Kn{\\printfirst{v}{1987}}",
  title		= "The Programming of Computer Art"
}

\@Booklet{	  knvth:programming,
  author	= "Jill C. Knvth",
  title		= "The Programming of Computer Art",
  howpublished	= "Vernier Art Center",
  address	= "Stanford, California",
  month		= feb,
  year		= 1988,
  note		= "This is a full BOOKLET entry"
}

\@InCollection{	  lincoll:semigroups,
  author	= "Daniel D. Lincoll",
  title		= "Semigroups of Recurrences",
  booktitle	= "High Speed Computer and Algorithm Organization",
  publisher	= "Academic Press",
  year		= 1977
}

\@InCollection{	  lincoll:semigroups*1,
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

\@InCollection{	  lincoll:semigroups*2,
  crossref	= "lipcoll.lawrie.ea:high",
  author	= "Daniel D. Lincoll",
  title		= "Semigroups of Recurrences",
  pages		= "179--183",
  note		= "This is a cross-referencing INCOLLECTION entry"
}

\@Book{		  lipcoll.lawrie.ea:high,
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

\@Manual{	  :definitive,
  key		= "Manmaker",
  title		= "The Definitive Computer Manual"
}

\@Manual{	  manmaker:definitive,
  author	= "Larry Manmaker",
  title		= "The Definitive Computer Manual",
  organization	= "Chips-R-Us",
  address	= "Silicon Valley",
  edition	= "Silver",
  month		= apr # "-" # may,
  year		= 1986,
  note		= "This is a full MANUAL entry"
}

\@MastersThesis{	  masterly:mastering,
  author	= "{\\'{E}}douard Masterly",
  title		= "Mastering Thesis Writing",
  school	= "Stanford University",
  year		= 1988
}

\@MastersThesis{	  masterly:mastering*1,
  author	= "{\\\'{E}}douard Masterly",
  title		= "Mastering Thesis Writing",
  school	= "Stanford University",
  type		= "Master\'s project",
  address	= "English Department",
  month		= jun # "-" # aug,
  year		= 1988,
  note		= "This is a full MASTERSTHESIS entry"
}

\@Misc{		  missilany,
  key		= "Missilany",
  note		= "This is a minimal MISC entry"
}

\@Misc{		  missilany:handing,
  author	= "Joe-Bob Missilany",
  title		= "Handing out random pamphlets in airports",
  howpublished	= "Handed out at O\'Hare",
  month		= oct,
  year		= 1984,
  note		= "This is a full MISC entry"
}

\@InProceedings{	  oaho.ullman.ea:on,
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  booktitle	= "Proc. Fifteenth Annual ACM" # stoc,
  year		= 1983
}

\@InProceedings{	  oaho.ullman.ea:on*1,
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  editor	= "Wizard V. Oz and Mihalis Yannakakis",
  booktitle	= "Proc. Fifteenth Annual ACM" # stoc,
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

\@InProceedings{	  oaho.ullman.ea:on*2,
  crossref	= ":proc*1",
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  organization	= "",
  pages		= "133--139",
  note		= "This is a cross-referencing INPROCEEDINGS entry"
}

\@Proceedings{	  :proc,
  key		= stoc-key,
  title		= "Proc. Fifteenth Annual" # stoc,
  year		= 1983
}

\@Proceedings{	  oz.yannakakis:proc,
  editor	= "Wizard V. Oz and Mihalis Yannakakis",
  title		= "Proc. Fifteenth Annual" # stoc,
  number	= 17,
  series	= "All ACM Conferences",
  month		= mar,
  year		= 1983,
  address	= "Boston",
  organization	= acm,
  publisher	= "Academic Press",
  note		= "This is a full PROCEEDINGS entry"
}

\@Proceedings{	  :proc*1,
  key		= stoc-key,
  organization	= acm,
  title		= "Proc. Fifteenth Annual" # stoc,
  address	= "Boston",
  year		= 1983,
  booktitle	= "Proc. Fifteenth Annual ACM" # stoc,
  note		= "This is a cross-referenced PROCEEDINGS"
}

\@PhDThesis{	  phony-baloney:fighting,
  author	= "F. Phidias Phony-Baloney",
  title		= "Fighting Fire with Fire: Festooning {F}rench Phrases",
  school	= "Fanstord University",
  year		= 1988
}

\@PhDThesis{	  phony-baloney:fighting*1,
  author	= "F. Phidias Phony-Baloney",
  title		= "Fighting Fire with Fire: Festooning {F}rench Phrases",
  school	= "Fanstord University",
  type		= "{PhD} Dissertation",
  address	= "Department of French",
  month		= jun # "-" # aug,
  year		= 1988,
  note		= "This is a full PHDTHESIS entry"
}

\@TechReport{	  terrific:on--n----n,
  author	= "Tom Terrific",
  title		= "An {\$O(n \\log n / \\! \\log\\log n)\$} Sorting Algorithm",
  institution	= "Fanstord University",
  year		= 1988
}

\@TechReport{	  terrific:on--n----n*1,
  author	= "Tom T{\\\'{e}}rrific",
  title		= "An {\$O(n \\log n / \\! \\log\\log n)\$} Sorting Algorithm",
  institution	= "Fanstord University",
  type		= "Wishful Research Result",
  number	= "7",
  address	= "Computer Science Department, Fanstord, California",
  month		= oct,
  year		= 1988,
  note		= "This is a full TECHREPORT entry"
}

\@Unpublished{	  underwood.net.ea:lower,
  author	= "Ulrich {\\"{U}}nderwood and Ned {\\~N}et and Paul {\\={P}}ot",
  title		= "Lower Bounds for Wishful Research Results",
  note		= "Talk at Fanstord University (this is a minimal UNPUBLISHED
		  entry)"
}

\@Unpublished{	  underwood.net.ea:lower*1,
  author	= "Ulrich {\\"{U}}nderwood and Ned {\\~N}et and Paul {\\={P}}ot",
  title		= "Lower Bounds for Wishful Research Results",
  month		= nov # ", " # dec,
  year		= 1988,
  note		= "Talk at Fanstord University (this is a full UNPUBLISHED
		  entry)"
}

\@Misc{		  volume-2,
  key		= {Volume-2},
  note		= "Volume~2 is listed under Knuth \\cite{book-full}"
}
EOF
	expected_err => <<EOF);

*** BibTool WARNING:  (line 29 in ./bib/xampl.bib): 125 non-space characters ignored.
EOF

#------------------------------------------------------------------------------
BUnit::run(name => '_f_short_1',
	 args	      => '-f short bib/xampl.bib',
	 expected_out => <<EOF,
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} "
	 # "\\newcommand{\\printfirst}[2]{#1} "
	 # "\\newcommand{\\singleletter}[1]{#1} "
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

\@Article{	  aamport:gnats,
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  journal	= {\\mbox{G-Animal's} Journal},
  year		= 1986
}

\@Article{	  aamport:gnats*1,
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

\@Article{	  aamport:gnats*2,
  crossref	= {gaj},
  key		= "",
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  pages		= "73+",
  note		= "This is a cross-referencing ARTICLE entry"
}

\@Article{	  gaj,
  key		= "GAJ",
  journal	= {\\mbox{G-Animal\'s} Journal},
  year		= 1986,
  volume	= 41,
  number	= 7,
  month		= jul,
  note		= {The entire issue is devoted to gnats and gnus (this entry
		  is a cross-referenced ARTICLE (journal))}
}

\@InBook{	  knuth:fundamental,
  author	= "Donald E. Knuth",
  title		= "Fundamental Algorithms",
  publisher	= "Addison-Wesley",
  year		= "{\\noopsort{1973b}}1973",
  chapter	= "1.2"
}

\@InBook{	  knuth:fundamental*1,
  author	= "Donald E. Knuth",
  title		= "Fundamental Algorithms",
  volume	= 1,
  series	= "The Art of Computer Programming",
  publisher	= "Addison-Wesley",
  address	= "Reading, Massachusetts",
  edition	= "Second",
  month		= "10~" # jan,
  year		= "{\\noopsort{1973b}}1973",
  type		= "Section",
  chapter	= "1.2",
  pages		= "10--119",
  note		= "This is a full INBOOK entry"
}

\@InBook{	  knuth:fundamental*2,
  crossref	= "knuth:art",
  title		= "Fundamental Algorithms",
  volume	= 1,
  series	= "The Art of Computer Programming",
  edition	= "Second",
  year		= "{\\noopsort{1973b}}1973",
  type		= "Section",
  chapter	= "1.2",
  note		= "This is a cross-referencing INBOOK entry"
}

\@Book{		  knuth:seminumerical,
  author	= "Donald E. Knuth",
  title		= "Seminumerical Algorithms",
  publisher	= "Addison-Wesley",
  year		= "{\\noopsort{1973c}}1981"
}

\@Book{		  knuth:seminumerical*1,
  author	= "Donald E. Knuth",
  title		= "Seminumerical Algorithms",
  volume	= 2,
  series	= "The Art of Computer Programming",
  publisher	= "Addison-Wesley",
  address	= "Reading, Massachusetts",
  edition	= "Second",
  month		= "10~" # jan,
  year		= "{\\noopsort{1973c}}1981",
  note		= "This is a full BOOK entry"
}

\@Book{		  knuth:seminumerical*2,
  crossref	= "knuth:art",
  title		= "Seminumerical Algorithms",
  volume	= 2,
  series	= "The Art of Computer Programming",
  edition	= "Second",
  year		= "{\\noopsort{1973c}}1981",
  note		= "This is a cross-referencing BOOK entry"
}

\@Book{		  knuth:art,
  author	= "Donald E. Knuth",
  publisher	= "Addison-Wesley",
  title		= "The Art of Computer Programming",
  series	= "Four volumes",
  year		= "{\\noopsort{1973a}}{\\switchargs{--90}{1968}}",
  note		= "Seven volumes planned (this is a cross-referenced set of
		  BOOKs)"
}

\@Booklet{	  :programming,
  key		= "Kn{\\printfirst{v}{1987}}",
  title		= "The Programming of Computer Art"
}

\@Booklet{	  knvth:programming,
  author	= "Jill C. Knvth",
  title		= "The Programming of Computer Art",
  howpublished	= "Vernier Art Center",
  address	= "Stanford, California",
  month		= feb,
  year		= 1988,
  note		= "This is a full BOOKLET entry"
}

\@InCollection{	  lincoll:semigroups,
  author	= "Daniel D. Lincoll",
  title		= "Semigroups of Recurrences",
  booktitle	= "High Speed Computer and Algorithm Organization",
  publisher	= "Academic Press",
  year		= 1977
}

\@InCollection{	  lincoll:semigroups*1,
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

\@InCollection{	  lincoll:semigroups*2,
  crossref	= "lipcoll.lawrie.ea:high",
  author	= "Daniel D. Lincoll",
  title		= "Semigroups of Recurrences",
  pages		= "179--183",
  note		= "This is a cross-referencing INCOLLECTION entry"
}

\@Book{		  lipcoll.lawrie.ea:high,
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

\@Manual{	  :definitive,
  key		= "Manmaker",
  title		= "The Definitive Computer Manual"
}

\@Manual{	  manmaker:definitive,
  author	= "Larry Manmaker",
  title		= "The Definitive Computer Manual",
  organization	= "Chips-R-Us",
  address	= "Silicon Valley",
  edition	= "Silver",
  month		= apr # "-" # may,
  year		= 1986,
  note		= "This is a full MANUAL entry"
}

\@MastersThesis{	  masterly:mastering,
  author	= "{\\'{E}}douard Masterly",
  title		= "Mastering Thesis Writing",
  school	= "Stanford University",
  year		= 1988
}

\@MastersThesis{	  masterly:mastering*1,
  author	= "{\\\'{E}}douard Masterly",
  title		= "Mastering Thesis Writing",
  school	= "Stanford University",
  type		= "Master\'s project",
  address	= "English Department",
  month		= jun # "-" # aug,
  year		= 1988,
  note		= "This is a full MASTERSTHESIS entry"
}

\@Misc{		  missilany,
  key		= "Missilany",
  note		= "This is a minimal MISC entry"
}

\@Misc{		  missilany:handing,
  author	= "Joe-Bob Missilany",
  title		= "Handing out random pamphlets in airports",
  howpublished	= "Handed out at O\'Hare",
  month		= oct,
  year		= 1984,
  note		= "This is a full MISC entry"
}

\@InProceedings{	  oaho.ullman.ea:on,
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  booktitle	= "Proc. Fifteenth Annual ACM" # stoc,
  year		= 1983
}

\@InProceedings{	  oaho.ullman.ea:on*1,
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  editor	= "Wizard V. Oz and Mihalis Yannakakis",
  booktitle	= "Proc. Fifteenth Annual ACM" # stoc,
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

\@InProceedings{	  oaho.ullman.ea:on*2,
  crossref	= ":proc*1",
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  organization	= "",
  pages		= "133--139",
  note		= "This is a cross-referencing INPROCEEDINGS entry"
}

\@Proceedings{	  :proc,
  key		= stoc-key,
  title		= "Proc. Fifteenth Annual" # stoc,
  year		= 1983
}

\@Proceedings{	  oz.yannakakis:proc,
  editor	= "Wizard V. Oz and Mihalis Yannakakis",
  title		= "Proc. Fifteenth Annual" # stoc,
  number	= 17,
  series	= "All ACM Conferences",
  month		= mar,
  year		= 1983,
  address	= "Boston",
  organization	= acm,
  publisher	= "Academic Press",
  note		= "This is a full PROCEEDINGS entry"
}

\@Proceedings{	  :proc*1,
  key		= stoc-key,
  organization	= acm,
  title		= "Proc. Fifteenth Annual" # stoc,
  address	= "Boston",
  year		= 1983,
  booktitle	= "Proc. Fifteenth Annual ACM" # stoc,
  note		= "This is a cross-referenced PROCEEDINGS"
}

\@PhDThesis{	  phony-baloney:fighting,
  author	= "F. Phidias Phony-Baloney",
  title		= "Fighting Fire with Fire: Festooning {F}rench Phrases",
  school	= "Fanstord University",
  year		= 1988
}

\@PhDThesis{	  phony-baloney:fighting*1,
  author	= "F. Phidias Phony-Baloney",
  title		= "Fighting Fire with Fire: Festooning {F}rench Phrases",
  school	= "Fanstord University",
  type		= "{PhD} Dissertation",
  address	= "Department of French",
  month		= jun # "-" # aug,
  year		= 1988,
  note		= "This is a full PHDTHESIS entry"
}

\@TechReport{	  terrific:on--n----n,
  author	= "Tom Terrific",
  title		= "An {\$O(n \\log n / \\! \\log\\log n)\$} Sorting Algorithm",
  institution	= "Fanstord University",
  year		= 1988
}

\@TechReport{	  terrific:on--n----n*1,
  author	= "Tom T{\\\'{e}}rrific",
  title		= "An {\$O(n \\log n / \\! \\log\\log n)\$} Sorting Algorithm",
  institution	= "Fanstord University",
  type		= "Wishful Research Result",
  number	= "7",
  address	= "Computer Science Department, Fanstord, California",
  month		= oct,
  year		= 1988,
  note		= "This is a full TECHREPORT entry"
}

\@Unpublished{	  underwood.net.ea:lower,
  author	= "Ulrich {\\"{U}}nderwood and Ned {\\~N}et and Paul {\\={P}}ot",
  title		= "Lower Bounds for Wishful Research Results",
  note		= "Talk at Fanstord University (this is a minimal UNPUBLISHED
		  entry)"
}

\@Unpublished{	  underwood.net.ea:lower*1,
  author	= "Ulrich {\\"{U}}nderwood and Ned {\\~N}et and Paul {\\={P}}ot",
  title		= "Lower Bounds for Wishful Research Results",
  month		= nov # ", " # dec,
  year		= 1988,
  note		= "Talk at Fanstord University (this is a full UNPUBLISHED
		  entry)"
}

\@Misc{		  volume-2,
  key		= {Volume-2},
  note		= "Volume~2 is listed under Knuth \\cite{book-full}"
}
EOF
	expected_err => <<EOF);

*** BibTool WARNING:  (line 29 in ./bib/xampl.bib): 125 non-space characters ignored.
EOF

#------------------------------------------------------------------------------
BUnit::run(name         => '_K_1',
	   args	        => '-K bib/xampl.bib',
	   expected_put => <<EOF,
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

\@Article{	  aamport.la:gnats,
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  journal	= {\\mbox{G-Animal's} Journal},
  year		= 1986
}

\@Article{	  aamport.la:gnats*1,
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

\@Article{	  aamport.la:gnats*2,
  crossref	= {gaj},
  key		= "",
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  pages		= "73+",
  note		= "This is a cross-referencing ARTICLE entry"
}

\@Article{	  gaj,
  key		= "GAJ",
  journal	= {\\mbox{G-Animal\'s} Journal},
  year		= 1986,
  volume	= 41,
  number	= 7,
  month		= jul,
  note		= {The entire issue is devoted to gnats and gnus (this entry
		  is a cross-referenced ARTICLE (journal))}
}

\@InBook{	  knuth.de:fundamental,
  author	= "Donald E. Knuth",
  title		= "Fundamental Algorithms",
  publisher	= "Addison-Wesley",
  year		= "{\\noopsort{1973b}}1973",
  chapter	= "1.2"
}

\@InBook{	  knuth.de:fundamental*1,
  author	= "Donald E. Knuth",
  title		= "Fundamental Algorithms",
  volume	= 1,
  series	= "The Art of Computer Programming",
  publisher	= "Addison-Wesley",
  address	= "Reading, Massachusetts",
  edition	= "Second",
  month		= "10~" # jan,
  year		= "{\\noopsort{1973b}}1973",
  type		= "Section",
  chapter	= "1.2",
  pages		= "10--119",
  note		= "This is a full INBOOK entry"
}

\@InBook{	  knuth.de:fundamental*2,
  crossref	= "knuth.de:art",
  title		= "Fundamental Algorithms",
  volume	= 1,
  series	= "The Art of Computer Programming",
  edition	= "Second",
  year		= "{\\noopsort{1973b}}1973",
  type		= "Section",
  chapter	= "1.2",
  note		= "This is a cross-referencing INBOOK entry"
}

\@Book{		  knuth.de:seminumerical,
  author	= "Donald E. Knuth",
  title		= "Seminumerical Algorithms",
  publisher	= "Addison-Wesley",
  year		= "{\\noopsort{1973c}}1981"
}

\@Book{		  knuth.de:seminumerical*1,
  author	= "Donald E. Knuth",
  title		= "Seminumerical Algorithms",
  volume	= 2,
  series	= "The Art of Computer Programming",
  publisher	= "Addison-Wesley",
  address	= "Reading, Massachusetts",
  edition	= "Second",
  month		= "10~" # jan,
  year		= "{\\noopsort{1973c}}1981",
  note		= "This is a full BOOK entry"
}

\@Book{		  knuth.de:seminumerical*2,
  crossref	= "knuth.de:art",
  title		= "Seminumerical Algorithms",
  volume	= 2,
  series	= "The Art of Computer Programming",
  edition	= "Second",
  year		= "{\\noopsort{1973c}}1981",
  note		= "This is a cross-referencing BOOK entry"
}

\@Book{		  knuth.de:art,
  author	= "Donald E. Knuth",
  publisher	= "Addison-Wesley",
  title		= "The Art of Computer Programming",
  series	= "Four volumes",
  year		= "{\\noopsort{1973a}}{\\switchargs{--90}{1968}}",
  note		= "Seven volumes planned (this is a cross-referenced set of
		  BOOKs)"
}

\@Booklet{	  :programming,
  key		= "Kn{\\printfirst{v}{1987}}",
  title		= "The Programming of Computer Art"
}

\@Booklet{	  knvth.jc:programming,
  author	= "Jill C. Knvth",
  title		= "The Programming of Computer Art",
  howpublished	= "Vernier Art Center",
  address	= "Stanford, California",
  month		= feb,
  year		= 1988,
  note		= "This is a full BOOKLET entry"
}

\@InCollection{	  lincoll.dd:semigroups,
  author	= "Daniel D. Lincoll",
  title		= "Semigroups of Recurrences",
  booktitle	= "High Speed Computer and Algorithm Organization",
  publisher	= "Academic Press",
  year		= 1977
}

\@InCollection{	  lincoll.dd:semigroups*1,
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

\@InCollection{	  lincoll.dd:semigroups*2,
  crossref	= "lipcoll.dj.lawrie.dh.ea:high",
  author	= "Daniel D. Lincoll",
  title		= "Semigroups of Recurrences",
  pages		= "179--183",
  note		= "This is a cross-referencing INCOLLECTION entry"
}

\@Book{		  lipcoll.dj.lawrie.dh.ea:high,
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

\@Manual{	  :definitive,
  key		= "Manmaker",
  title		= "The Definitive Computer Manual"
}

\@Manual{	  manmaker.l:definitive,
  author	= "Larry Manmaker",
  title		= "The Definitive Computer Manual",
  organization	= "Chips-R-Us",
  address	= "Silicon Valley",
  edition	= "Silver",
  month		= apr # "-" # may,
  year		= 1986,
  note		= "This is a full MANUAL entry"
}

\@MastersThesis{	  masterly.e:mastering,
  author	= "{\\'{E}}douard Masterly",
  title		= "Mastering Thesis Writing",
  school	= "Stanford University",
  year		= 1988
}

\@MastersThesis{	  masterly.e:mastering*1,
  author	= "{\\\'{E}}douard Masterly",
  title		= "Mastering Thesis Writing",
  school	= "Stanford University",
  type		= "Master\'s project",
  address	= "English Department",
  month		= jun # "-" # aug,
  year		= 1988,
  note		= "This is a full MASTERSTHESIS entry"
}

\@Misc{		  missilany,
  key		= "Missilany",
  note		= "This is a minimal MISC entry"
}

\@Misc{		  missilany.j:handing,
  author	= "Joe-Bob Missilany",
  title		= "Handing out random pamphlets in airports",
  howpublished	= "Handed out at O\'Hare",
  month		= oct,
  year		= 1984,
  note		= "This is a full MISC entry"
}

\@InProceedings{	  oaho.av.ullman.jd.ea:on,
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  booktitle	= "Proc. Fifteenth Annual ACM" # stoc,
  year		= 1983
}

\@InProceedings{	  oaho.av.ullman.jd.ea:on*1,
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  editor	= "Wizard V. Oz and Mihalis Yannakakis",
  booktitle	= "Proc. Fifteenth Annual ACM" # stoc,
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

\@InProceedings{	  oaho.av.ullman.jd.ea:on*2,
  crossref	= ":proc*1",
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  organization	= "",
  pages		= "133--139",
  note		= "This is a cross-referencing INPROCEEDINGS entry"
}

\@Proceedings{	  :proc,
  key		= stoc-key,
  title		= "Proc. Fifteenth Annual" # stoc,
  year		= 1983
}

\@Proceedings{	  oz.wv.yannakakis.m:proc,
  editor	= "Wizard V. Oz and Mihalis Yannakakis",
  title		= "Proc. Fifteenth Annual" # stoc,
  number	= 17,
  series	= "All ACM Conferences",
  month		= mar,
  year		= 1983,
  address	= "Boston",
  organization	= acm,
  publisher	= "Academic Press",
  note		= "This is a full PROCEEDINGS entry"
}

\@Proceedings{	  :proc*1,
  key		= stoc-key,
  organization	= acm,
  title		= "Proc. Fifteenth Annual" # stoc,
  address	= "Boston",
  year		= 1983,
  booktitle	= "Proc. Fifteenth Annual ACM" # stoc,
  note		= "This is a cross-referenced PROCEEDINGS"
}

\@PhDThesis{	  phony-baloney.fp:fighting,
  author	= "F. Phidias Phony-Baloney",
  title		= "Fighting Fire with Fire: Festooning {F}rench Phrases",
  school	= "Fanstord University",
  year		= 1988
}

\@PhDThesis{	  phony-baloney.fp:fighting*1,
  author	= "F. Phidias Phony-Baloney",
  title		= "Fighting Fire with Fire: Festooning {F}rench Phrases",
  school	= "Fanstord University",
  type		= "{PhD} Dissertation",
  address	= "Department of French",
  month		= jun # "-" # aug,
  year		= 1988,
  note		= "This is a full PHDTHESIS entry"
}

\@TechReport{	  terrific.t:on--n----n,
  author	= "Tom Terrific",
  title		= "An {\$O(n \\log n / \\! \\log\\log n)\$} Sorting Algorithm",
  institution	= "Fanstord University",
  year		= 1988
}

\@TechReport{	  terrific.t:on--n----n*1,
  author	= "Tom T{\\\'{e}}rrific",
  title		= "An {\$O(n \\log n / \\! \\log\\log n)\$} Sorting Algorithm",
  institution	= "Fanstord University",
  type		= "Wishful Research Result",
  number	= "7",
  address	= "Computer Science Department, Fanstord, California",
  month		= oct,
  year		= 1988,
  note		= "This is a full TECHREPORT entry"
}

\@Unpublished{	  underwood.u.net.n.ea:lower,
  author	= "Ulrich {\\"{U}}nderwood and Ned {\\~N}et and Paul {\\={P}}ot",
  title		= "Lower Bounds for Wishful Research Results",
  note		= "Talk at Fanstord University (this is a minimal UNPUBLISHED
		  entry)"
}

\@Unpublished{	  underwood.u.net.n.ea:lower*1,
  author	= "Ulrich {\\"{U}}nderwood and Ned {\\~N}et and Paul {\\={P}}ot",
  title		= "Lower Bounds for Wishful Research Results",
  month		= nov # ", " # dec,
  year		= 1988,
  note		= "Talk at Fanstord University (this is a full UNPUBLISHED
		  entry)"
}

\@Misc{		  volume-2,
  key		= {Volume-2},
  note		= "Volume~2 is listed under Knuth \\cite{book-full}"
}
EOF
	expected_err => <<EOF);

*** BibTool WARNING:  (line 29 in ./bib/xampl.bib): 125 non-space characters ignored.
EOF

#------------------------------------------------------------------------------
BUnit::run(name         => '_f_long_1',
	   args	        => '-f long bib/xampl.bib',
	   expected_put => <<EOF,
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

\@Article{	  aamport.la:gnats,
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  journal	= {\\mbox{G-Animal's} Journal},
  year		= 1986
}

\@Article{	  aamport.la:gnats*1,
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

\@Article{	  aamport.la:gnats*2,
  crossref	= {gaj},
  key		= "",
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  pages		= "73+",
  note		= "This is a cross-referencing ARTICLE entry"
}

\@Article{	  gaj,
  key		= "GAJ",
  journal	= {\\mbox{G-Animal\'s} Journal},
  year		= 1986,
  volume	= 41,
  number	= 7,
  month		= jul,
  note		= {The entire issue is devoted to gnats and gnus (this entry
		  is a cross-referenced ARTICLE (journal))}
}

\@InBook{	  knuth.de:fundamental,
  author	= "Donald E. Knuth",
  title		= "Fundamental Algorithms",
  publisher	= "Addison-Wesley",
  year		= "{\\noopsort{1973b}}1973",
  chapter	= "1.2"
}

\@InBook{	  knuth.de:fundamental*1,
  author	= "Donald E. Knuth",
  title		= "Fundamental Algorithms",
  volume	= 1,
  series	= "The Art of Computer Programming",
  publisher	= "Addison-Wesley",
  address	= "Reading, Massachusetts",
  edition	= "Second",
  month		= "10~" # jan,
  year		= "{\\noopsort{1973b}}1973",
  type		= "Section",
  chapter	= "1.2",
  pages		= "10--119",
  note		= "This is a full INBOOK entry"
}

\@InBook{	  knuth.de:fundamental*2,
  crossref	= "knuth.de:art",
  title		= "Fundamental Algorithms",
  volume	= 1,
  series	= "The Art of Computer Programming",
  edition	= "Second",
  year		= "{\\noopsort{1973b}}1973",
  type		= "Section",
  chapter	= "1.2",
  note		= "This is a cross-referencing INBOOK entry"
}

\@Book{		  knuth.de:seminumerical,
  author	= "Donald E. Knuth",
  title		= "Seminumerical Algorithms",
  publisher	= "Addison-Wesley",
  year		= "{\\noopsort{1973c}}1981"
}

\@Book{		  knuth.de:seminumerical*1,
  author	= "Donald E. Knuth",
  title		= "Seminumerical Algorithms",
  volume	= 2,
  series	= "The Art of Computer Programming",
  publisher	= "Addison-Wesley",
  address	= "Reading, Massachusetts",
  edition	= "Second",
  month		= "10~" # jan,
  year		= "{\\noopsort{1973c}}1981",
  note		= "This is a full BOOK entry"
}

\@Book{		  knuth.de:seminumerical*2,
  crossref	= "knuth.de:art",
  title		= "Seminumerical Algorithms",
  volume	= 2,
  series	= "The Art of Computer Programming",
  edition	= "Second",
  year		= "{\\noopsort{1973c}}1981",
  note		= "This is a cross-referencing BOOK entry"
}

\@Book{		  knuth.de:art,
  author	= "Donald E. Knuth",
  publisher	= "Addison-Wesley",
  title		= "The Art of Computer Programming",
  series	= "Four volumes",
  year		= "{\\noopsort{1973a}}{\\switchargs{--90}{1968}}",
  note		= "Seven volumes planned (this is a cross-referenced set of
		  BOOKs)"
}

\@Booklet{	  :programming,
  key		= "Kn{\\printfirst{v}{1987}}",
  title		= "The Programming of Computer Art"
}

\@Booklet{	  knvth.jc:programming,
  author	= "Jill C. Knvth",
  title		= "The Programming of Computer Art",
  howpublished	= "Vernier Art Center",
  address	= "Stanford, California",
  month		= feb,
  year		= 1988,
  note		= "This is a full BOOKLET entry"
}

\@InCollection{	  lincoll.dd:semigroups,
  author	= "Daniel D. Lincoll",
  title		= "Semigroups of Recurrences",
  booktitle	= "High Speed Computer and Algorithm Organization",
  publisher	= "Academic Press",
  year		= 1977
}

\@InCollection{	  lincoll.dd:semigroups*1,
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

\@InCollection{	  lincoll.dd:semigroups*2,
  crossref	= "lipcoll.dj.lawrie.dh.ea:high",
  author	= "Daniel D. Lincoll",
  title		= "Semigroups of Recurrences",
  pages		= "179--183",
  note		= "This is a cross-referencing INCOLLECTION entry"
}

\@Book{		  lipcoll.dj.lawrie.dh.ea:high,
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

\@Manual{	  :definitive,
  key		= "Manmaker",
  title		= "The Definitive Computer Manual"
}

\@Manual{	  manmaker.l:definitive,
  author	= "Larry Manmaker",
  title		= "The Definitive Computer Manual",
  organization	= "Chips-R-Us",
  address	= "Silicon Valley",
  edition	= "Silver",
  month		= apr # "-" # may,
  year		= 1986,
  note		= "This is a full MANUAL entry"
}

\@MastersThesis{	  masterly.e:mastering,
  author	= "{\\'{E}}douard Masterly",
  title		= "Mastering Thesis Writing",
  school	= "Stanford University",
  year		= 1988
}

\@MastersThesis{	  masterly.e:mastering*1,
  author	= "{\\\'{E}}douard Masterly",
  title		= "Mastering Thesis Writing",
  school	= "Stanford University",
  type		= "Master\'s project",
  address	= "English Department",
  month		= jun # "-" # aug,
  year		= 1988,
  note		= "This is a full MASTERSTHESIS entry"
}

\@Misc{		  missilany,
  key		= "Missilany",
  note		= "This is a minimal MISC entry"
}

\@Misc{		  missilany.j:handing,
  author	= "Joe-Bob Missilany",
  title		= "Handing out random pamphlets in airports",
  howpublished	= "Handed out at O\'Hare",
  month		= oct,
  year		= 1984,
  note		= "This is a full MISC entry"
}

\@InProceedings{	  oaho.av.ullman.jd.ea:on,
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  booktitle	= "Proc. Fifteenth Annual ACM" # stoc,
  year		= 1983
}

\@InProceedings{	  oaho.av.ullman.jd.ea:on*1,
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  editor	= "Wizard V. Oz and Mihalis Yannakakis",
  booktitle	= "Proc. Fifteenth Annual ACM" # stoc,
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

\@InProceedings{	  oaho.av.ullman.jd.ea:on*2,
  crossref	= ":proc*1",
  author	= "Alfred V. Oaho and Jeffrey D. Ullman and Mihalis
		  Yannakakis",
  title		= "On Notions of Information Transfer in {VLSI} Circuits",
  organization	= "",
  pages		= "133--139",
  note		= "This is a cross-referencing INPROCEEDINGS entry"
}

\@Proceedings{	  :proc,
  key		= stoc-key,
  title		= "Proc. Fifteenth Annual" # stoc,
  year		= 1983
}

\@Proceedings{	  oz.wv.yannakakis.m:proc,
  editor	= "Wizard V. Oz and Mihalis Yannakakis",
  title		= "Proc. Fifteenth Annual" # stoc,
  number	= 17,
  series	= "All ACM Conferences",
  month		= mar,
  year		= 1983,
  address	= "Boston",
  organization	= acm,
  publisher	= "Academic Press",
  note		= "This is a full PROCEEDINGS entry"
}

\@Proceedings{	  :proc*1,
  key		= stoc-key,
  organization	= acm,
  title		= "Proc. Fifteenth Annual" # stoc,
  address	= "Boston",
  year		= 1983,
  booktitle	= "Proc. Fifteenth Annual ACM" # stoc,
  note		= "This is a cross-referenced PROCEEDINGS"
}

\@PhDThesis{	  phony-baloney.fp:fighting,
  author	= "F. Phidias Phony-Baloney",
  title		= "Fighting Fire with Fire: Festooning {F}rench Phrases",
  school	= "Fanstord University",
  year		= 1988
}

\@PhDThesis{	  phony-baloney.fp:fighting*1,
  author	= "F. Phidias Phony-Baloney",
  title		= "Fighting Fire with Fire: Festooning {F}rench Phrases",
  school	= "Fanstord University",
  type		= "{PhD} Dissertation",
  address	= "Department of French",
  month		= jun # "-" # aug,
  year		= 1988,
  note		= "This is a full PHDTHESIS entry"
}

\@TechReport{	  terrific.t:on--n----n,
  author	= "Tom Terrific",
  title		= "An {\$O(n \\log n / \\! \\log\\log n)\$} Sorting Algorithm",
  institution	= "Fanstord University",
  year		= 1988
}

\@TechReport{	  terrific.t:on--n----n*1,
  author	= "Tom T{\\\'{e}}rrific",
  title		= "An {\$O(n \\log n / \\! \\log\\log n)\$} Sorting Algorithm",
  institution	= "Fanstord University",
  type		= "Wishful Research Result",
  number	= "7",
  address	= "Computer Science Department, Fanstord, California",
  month		= oct,
  year		= 1988,
  note		= "This is a full TECHREPORT entry"
}

\@Unpublished{	  underwood.u.net.n.ea:lower,
  author	= "Ulrich {\\"{U}}nderwood and Ned {\\~N}et and Paul {\\={P}}ot",
  title		= "Lower Bounds for Wishful Research Results",
  note		= "Talk at Fanstord University (this is a minimal UNPUBLISHED
		  entry)"
}

\@Unpublished{	  underwood.u.net.n.ea:lower*1,
  author	= "Ulrich {\\"{U}}nderwood and Ned {\\~N}et and Paul {\\={P}}ot",
  title		= "Lower Bounds for Wishful Research Results",
  month		= nov # ", " # dec,
  year		= 1988,
  note		= "Talk at Fanstord University (this is a full UNPUBLISHED
		  entry)"
}

\@Misc{		  volume-2,
  key		= {Volume-2},
  note		= "Volume~2 is listed under Knuth \\cite{book-full}"
}
EOF
	expected_err => <<EOF);

*** BibTool WARNING:  (line 29 in ./bib/xampl.bib): 125 non-space characters ignored.
EOF

#------------------------------------------------------------------------------
BUnit::run(name => 'f_empty_1',
	 args	      => '-f empty',
	 bib 	      => <<EOF,
\@Article{	  aamport:1,
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  journal	= {\\mbox{G-Animal's} Journal},
  year		= 1986
}
\@Article{	  gaj,
  key		= "GAJ",
  journal	= {\\mbox{G-Animal\'s} Journal},
  year		= 1986,
  volume	= 41,
  number	= 7,
  month		= jul,
  note		= {The entire issue is devoted to gnats and gnus (this entry
		  is a cross-referenced ARTICLE (journal))}
}
EOF
	 expected_out => <<EOF,

\@Article{,
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System},
  journal	= {\\mbox{G-Animal's} Journal},
  year		= 1986
}

\@Article{,
  key		= "GAJ",
  journal	= {\\mbox{G-Animal\'s} Journal},
  year		= 1986,
  volume	= 41,
  number	= 7,
  month		= jul,
  note		= {The entire issue is devoted to gnats and gnus (this entry
		  is a cross-referenced ARTICLE (journal))}
}
EOF
	expected_err => <<EOF);
EOF


use constant DATA => <<__EOF__;
\@Unpublished{unpublished-key,
  author   = "First A. U. Thor and Seco N. D. Author and Third A. Uthor
              and others",
  title    = "This is a rather long title of an unpublished entry which
              exceeds one line"
}
\@Article{,
  author = {L[eslie] A. Aamport},
  title = {The Gnats and Gnus Document Preparation System}
}
\@BOOK{whole-collection,
    editor = "David J. Lipcoll and D. H. Lawrie and A. H. Sameh",
    title = "High Speed Computer and Algorithm Organization"
}
\@MISC{misc-minimal,
    key = "Missilany",
    note = "This is a minimal MISC entry"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name       => 'key_format_1',
	   args	      => '-- key.format={short}',
	   bib 	      => DATA,
	   expected_out => <<__EOF__);

\@Unpublished{	  thor.author.ea:this,
  author	= "First A. U. Thor and Seco N. D. Author and Third A. Uthor
		  and others",
  title		= "This is a rather long title of an unpublished entry which
		  exceeds one line"
}

\@Article{	  aamport:gnats,
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System}
}

\@Book{		  lipcoll.lawrie.ea:high,
  editor	= "David J. Lipcoll and D. H. Lawrie and A. H. Sameh",
  title		= "High Speed Computer and Algorithm Organization"
}

\@Misc{		  missilany,
  key		= "Missilany",
  note		= "This is a minimal MISC entry"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name       => 'key_format_2',
	   args	      => '-- key.format={long}',
	   bib 	      => DATA,
	   expected_out => <<__EOF__);

\@Unpublished{	  thor.fau.author.snd.ea:this,
  author	= "First A. U. Thor and Seco N. D. Author and Third A. Uthor
		  and others",
  title		= "This is a rather long title of an unpublished entry which
		  exceeds one line"
}

\@Article{	  aamport.la:gnats,
  author	= {L[eslie] A. Aamport},
  title		= {The Gnats and Gnus Document Preparation System}
}

\@Book{		  lipcoll.dj.lawrie.dh.ea:high,
  editor	= "David J. Lipcoll and D. H. Lawrie and A. H. Sameh",
  title		= "High Speed Computer and Algorithm Organization"
}

\@Misc{		  missilany,
  key		= "Missilany",
  note		= "This is a minimal MISC entry"
}
__EOF__

use constant SAMPLE => <<__EOF__;
\@MISC{misc,
    author = "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_p1',
	   resource	=> 'key.format={%p(author)}',
	   bib		=> SAMPLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  Thor.Meone.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_p2',
	   resource	=> 'key.format={%1p(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  Thor.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_p3',
	   resource	=> 'key.format={%-2p(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  thor.meone.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_p4',
	   resource	=> 'key.format={%+1p(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  THOR.EA,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_n1',
	   resource	=> 'key.format={%n(author)}',
	   bib		=> SAMPLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  Thor.Meone.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_n2',
	   resource	=> 'key.format={%1n(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  Thor.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_n3',
	   resource	=> 'key.format={%-2n(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  thor.meone.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_n4',
	   resource	=> 'key.format={%+1n(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  THOR.EA,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_n5',
	   resource	=> 'key.format={%.3n(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  Tho.Meo.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_N1',
	   resource	=> 'key.format={%N(author)}',
	   bib		=> SAMPLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  Thor.AU.Meone.SO.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_N2',
	   resource	=> 'key.format={%1N(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  Thor.AU.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_N3',
	   resource	=> 'key.format={%-2N(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  thor.au.meone.so.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_N4',
	   resource	=> 'key.format={%+1N(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  THOR.AU.EA,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_N5',
	   resource	=> 'key.format={%.3N(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  Tho.AU.Meo.SO.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

use constant SAMPLE_NUM => <<__EOF__;
\@MISC{misc,
       pages = {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_d1',
	   resource	=> 'key.format={x%d(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x89,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_d2',
	   resource	=> 'key.format={x%1d(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x9,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_d3',
	   resource	=> 'key.format={x%4d(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x89,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_d4',
	   resource	=> 'key.format={x%-4d(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x0089,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_d5',
	   resource	=> 'key.format={x%-5.2d(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x00123,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_d6',
	   resource	=> 'key.format={x%+.3d(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x0,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_d7',
	   resource	=> 'key.format={x%0d(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_d8',
	   resource	=> 'key.format={x%.3d(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  **key*,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_D1',
	   resource	=> 'key.format={x%D(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x89,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_D2',
	   resource	=> 'key.format={x%1D(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x89,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_D3',
	   resource	=> 'key.format={x%4D(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x89,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_D4',
	   resource	=> 'key.format={x%-4D(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x0089,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_D5',
	   resource	=> 'key.format={x%-5.2D(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x00123,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_D6',
	   resource	=> 'key.format={x%+.3D(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x0,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_D7',
	   resource	=> 'key.format={x%0D(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  x89,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_D8',
	   resource	=> 'key.format={x%.3D(pages)}',
	   bib		=> SAMPLE_NUM,
	   expected_out	=> <<__EOF__);

\@Misc{		  **key*,
  pages		= {89--123}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_s1',
	   resource	=> 'key.format={%s(author)}',
	   bib		=> SAMPLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  A.-U.-Thor-and-S.-O.-Meone-and-others,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_s2',
	   resource	=> 'key.format={%8s(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  A.-U.-Th,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_s3',
	   resource	=> 'key.format={%-8s(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  a.-u.-th,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_s4',
	   resource	=> 'key.format={%+8s(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  A.-U.-TH,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_s5',
	   resource	=> 'key.format={x%0s(author)}',
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

use constant SAMPLE_TITLE => <<__EOF__;
\@MISC{csim,
    title = "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_T1',
	   resource	=> 'key.format={%T(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  Whole,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_T2',
	   resource	=> 'key.format={%2T(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  Whole-Title,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_T3',
	   resource	=> 'key.format={%2.1T(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  W-T,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_T4',
	   resource	=> 'key.format={%-T(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  whole,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_T5',
	   resource	=> 'key.format={%+T(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  WHOLE,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_t1',
	   resource	=> 'key.format={%t(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  The,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_t2',
	   resource	=> 'key.format={%2t(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  The-Whole,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_t3',
	   resource	=> 'key.format={%2.1t(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  T-W,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_t4',
	   resource	=> 'key.format={%-t(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  the,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_t5',
	   resource	=> 'key.format={%+t(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  THE,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_W1',
	   resource	=> 'key.format={%W(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  Whole,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_W2',
	   resource	=> 'key.format={%2W(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  WholeTitle,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_W3',
	   resource	=> 'key.format={%2.1W(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  WT,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_W4',
	   resource	=> 'key.format={%-W(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  whole,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_W5',
	   resource	=> 'key.format={%+W(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  WHOLE,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_w1',
	   resource	=> 'key.format={%w(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  The,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_w2',
	   resource	=> 'key.format={%2w(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  TheWhole,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_w3',
	   resource	=> 'key.format={%2.1w(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  TW,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_w4',
	   resource	=> 'key.format={%-w(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  the,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_format_w5',
	   resource	=> 'key.format={%+w(title)}',
	   bib		=> SAMPLE_TITLE,
	   expected_out	=> <<__EOF__);

\@Misc{		  THE,
  title		= "The Whole Title"
}
__EOF__

foreach $_ (qw/p n N/) {
#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}1",
	   resource	=> "key.format={x%2#$_(author)}",
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}2",
	   resource	=> "key.format={x%4#$_(author)}",
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  **key*,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}3",
	   resource	=> "key.format={x%-4#$_(author)}",
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}4",
	   resource	=> "key.format={x%3.4#$_(author)}",
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}5",
	   resource	=> "key.format={x%-3.4#$_(author)}",
	   bib 	        => SAMPLE,
	   expected_out => <<__EOF__);

\@Misc{		  **key*,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

}

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_s1",
	   resource	=> "key.format={x%#s(title)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_s2",
	   resource	=> "key.format={x%13.13#s(title)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_s3",
	   resource	=> "key.format={x%10.16#s(title)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_s4",
	   resource	=> "key.format={x%-10.16#s(title)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  **key*,
  title		= "The Whole Title"
}
__EOF__


foreach $_ (qw/w t/) {
#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}1",
	   resource	=> "key.format={x%#$_(title)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}2",
	   resource	=> "key.format={x%3.3#$_(title)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}3",
	   resource	=> "key.format={x%1.6#$_(title)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}4",
	   resource	=> "key.format={x%-1.6#$_(title)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  **key*,
  title		= "The Whole Title"
}
__EOF__
}

foreach $_ (qw/W T/) {
#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}1",
	   resource	=> "key.format={x%#$_(title)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}2",
	   resource	=> "key.format={x%2.2#$_(title)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}3",
	   resource	=> "key.format={x%1.6#$_(title)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_hash_${_}4",
	   resource	=> "key.format={x%-1.6#$_(title)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  **key*,
  title		= "The Whole Title"
}
__EOF__
}

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_dollar_key1",
	   resource	=> "key.format={x%s(\$key)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  xcsim,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
#BUnit::run(name         => "key_format_dollar_sortkey1",
#	   resource	=> "key.format={x%s(\$sortkey)}",
#	   bib 	        => SAMPLE_TITLE,
#	   expected_out => <<__EOF__);
#
#\@Misc{		  xcsim,
#  title		= "The Whole Title"
#}
#__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_dollar_type1",
	   resource	=> "key.format={x%s(\$type)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  xMisc,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_at_type1",
	   resource	=> "key.format={x%s(\@Book)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  **key*,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_at_type2",
	   resource	=> "key.format={x%s(\@Misc)}",
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  xMisc,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_at_type3",
	   resource	=> 'key.format={x%s(@MISC)}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  xMisc,
  title		= "The Whole Title"
}
__EOF__


my ($sec,$minute,$hour,$day,$month,$year,$wday,$yday,$isdst) = localtime(time);
$day = "0$day" if $day <= 9;
$month++;
$month = "0$month" if $month <= 9;
$year += 1900;
$hour = "0$hour" if $hour <= 9;
$minute = "0$minute" if $minute <= 9;

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_dollar_day1",
	   resource	=> 'key.format={x%s($day)}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x$day,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_dollar_month1",
	   resource	=> 'key.format={x%s($month)}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x$month,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_dollar_year1",
	   resource	=> 'key.format={x%s($year)}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x$year,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_dollar_hour1",
	   resource	=> 'key.format={x%s($hour)}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x$hour,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_dollar_minute1",
	   resource	=> 'key.format={x%s($minute)}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x$minute,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_dollar_user1",
	   resource	=> 'key.format={x%s($user)}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x$ENV{USER},
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_dollar_hostname1",
	   resource	=> 'key.format={x%s($hostname)}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  x$ENV{HOSTNAME},
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_or1",
	   resource	=> 'key.format={x%#s(abc) # fallback}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  fallback,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_cond1",
	   resource	=> 'key.format={(abc){then}{else}}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  else,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_cond2",
	   resource	=> 'key.format={(title){then}{else}}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  then,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_cond3",
	   resource	=> 'key.format={($key){then}{else}}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  then,
  title		= "The Whole Title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => "key_format_group1",
	   resource	=> 'key.format={{%N(author) # --no-author-- } {%T(title) # --no-title-- } x}',
	   bib 	        => SAMPLE_TITLE,
	   expected_out => <<__EOF__);

\@Misc{		  --no-author--Wholex,
  title		= "The Whole Title"
}
__EOF__

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
