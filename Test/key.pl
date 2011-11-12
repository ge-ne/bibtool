#!/bin/perl -W
#******************************************************************************
# $Id: key.pl,v 1.3 2011-11-12 14:44:44 gene Exp $
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

key.pl - Test suite for BibTool key.

=head1 SYNOPSIS

key.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name => 'key_k_1',
	 args	      => '-k xampl.bib',
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
  month		= "10~"  # jan,
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
  month		= "10~"  # jan,
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
  month		= apr # "-"  # may,
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
  month		= jun # "-"  # aug,
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
  booktitle	= "Proc. Fifteenth Annual ACM"  # stoc,
  year		= 1983
}

\@InProceedings{	  oaho.ullman.ea:on*1,
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
  title		= "Proc. Fifteenth Annual"  # stoc,
  year		= 1983
}

\@Proceedings{	  oz.yannakakis:proc,
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

\@Proceedings{	  :proc*1,
  key		= stoc-key,
  organization	= acm,
  title		= "Proc. Fifteenth Annual"  # stoc,
  address	= "Boston",
  year		= 1983,
  booktitle	= "Proc. Fifteenth Annual ACM"  # stoc,
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
  month		= jun # "-"  # aug,
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
  month		= nov # ", "  # dec,
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

*** BibTool WARNING:  (line 29 in ./xampl.bib): 125 non-space characters ignored.
EOF

#------------------------------------------------------------------------------
BUnit::run(name => 'f_short_1',
	 args	      => '-f short xampl.bib',
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
  month		= "10~"  # jan,
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
  month		= "10~"  # jan,
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
  month		= apr # "-"  # may,
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
  month		= jun # "-"  # aug,
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
  booktitle	= "Proc. Fifteenth Annual ACM"  # stoc,
  year		= 1983
}

\@InProceedings{	  oaho.ullman.ea:on*1,
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
  title		= "Proc. Fifteenth Annual"  # stoc,
  year		= 1983
}

\@Proceedings{	  oz.yannakakis:proc,
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

\@Proceedings{	  :proc*1,
  key		= stoc-key,
  organization	= acm,
  title		= "Proc. Fifteenth Annual"  # stoc,
  address	= "Boston",
  year		= 1983,
  booktitle	= "Proc. Fifteenth Annual ACM"  # stoc,
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
  month		= jun # "-"  # aug,
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
  month		= nov # ", "  # dec,
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

*** BibTool WARNING:  (line 29 in ./xampl.bib): 125 non-space characters ignored.
EOF

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_K_1',
	   args	        => '-K xampl.bib',
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
  month		= "10~"  # jan,
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
  month		= "10~"  # jan,
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
  month		= apr # "-"  # may,
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
  month		= jun # "-"  # aug,
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
  booktitle	= "Proc. Fifteenth Annual ACM"  # stoc,
  year		= 1983
}

\@InProceedings{	  oaho.av.ullman.jd.ea:on*1,
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
  title		= "Proc. Fifteenth Annual"  # stoc,
  year		= 1983
}

\@Proceedings{	  oz.wv.yannakakis.m:proc,
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

\@Proceedings{	  :proc*1,
  key		= stoc-key,
  organization	= acm,
  title		= "Proc. Fifteenth Annual"  # stoc,
  address	= "Boston",
  year		= 1983,
  booktitle	= "Proc. Fifteenth Annual ACM"  # stoc,
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
  month		= jun # "-"  # aug,
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
  month		= nov # ", "  # dec,
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

*** BibTool WARNING:  (line 29 in ./xampl.bib): 125 non-space characters ignored.
EOF

#------------------------------------------------------------------------------
BUnit::run(name         => 'f_long_1',
	   args	        => '-f long xampl.bib',
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
  month		= "10~"  # jan,
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
  month		= "10~"  # jan,
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
  month		= apr # "-"  # may,
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
  month		= jun # "-"  # aug,
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
  booktitle	= "Proc. Fifteenth Annual ACM"  # stoc,
  year		= 1983
}

\@InProceedings{	  oaho.av.ullman.jd.ea:on*1,
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
  title		= "Proc. Fifteenth Annual"  # stoc,
  year		= 1983
}

\@Proceedings{	  oz.wv.yannakakis.m:proc,
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

\@Proceedings{	  :proc*1,
  key		= stoc-key,
  organization	= acm,
  title		= "Proc. Fifteenth Annual"  # stoc,
  address	= "Boston",
  year		= 1983,
  booktitle	= "Proc. Fifteenth Annual ACM"  # stoc,
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
  month		= jun # "-"  # aug,
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
  month		= nov # ", "  # dec,
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

*** BibTool WARNING:  (line 29 in ./xampl.bib): 125 non-space characters ignored.
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

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
