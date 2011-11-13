#!/bin/perl -W
#******************************************************************************
# $Id: select.pl,v 1.2 2011-11-13 08:26:55 gene Exp $
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

select.pl - Test suite for BibTool select.

=head1 SYNOPSIS

select.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_1',
    args	 => '--select.by.string=\'{"none"}\' xampl.bib',
    expected_out => <<__EOF__);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_2',
    args	 => '--select.by.string=\'{"anual-mi"}\' xampl.bib',
    expected_out => <<__EOF__);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

\@Manual{	  manual-minimal,
  key		= "Manmaker",
  title		= "The Definitive Computer Manual"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_3',
    args	 => '--select.by.string=\'{"manmaker"}\' xampl.bib',
    expected_out => <<__EOF__);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

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
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_4',
    args	 => '--select.by.string=\'{"MISC"}\' xampl.bib',
    expected_out => <<__EOF__);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

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
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_10',
    args	 => '--select.by.string=\'{"MISC"}\' xampl.bib',
    expected_out => <<__EOF__);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

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
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_11',
    args	 => '--select.by.string=\'{note "Kn"}\' xampl.bib',
    expected_out => <<__EOF__);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

\@Misc{		  random-note-crossref,
  key		= {Volume-2},
  note		= "Volume~2 is listed under Knuth \\cite{book-full}"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_12',
    args	 => '--select.by.string=\'{$type "misc"}\' xampl.bib',
    expected_out => <<__EOF__);
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} " 
	 # "\\newcommand{\\printfirst}[2]{#1} " 
	 # "\\newcommand{\\singleletter}[1]{#1} " 
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }

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

\@Misc{		  random-note-crossref,
  key		= {Volume-2},
  note		= "Volume~2 is listed under Knuth \\cite{book-full}"
}
__EOF__

#------------------------------------------------------------------------------
#BUnit::run(name  => 'select_by_non_string_1',
#    args         => '--select.by.non.string=\'{"aa"}\'',
#expected_err=>'',
#    bib	         => <<__EOF__,
#\@article{ a,
#  author = "aa",
#  title	 = "the title"
#}
#\@article{ b,
#  author = "ab",
#  title	 = "the title"
#}
#__EOF__
#    expected_out => <<__EOF__);
#__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => '_X_0',
    args         => '-X',
    expected_err => <<__EOF__);

*** BibTool WARNING: Missing pattern.
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => '_X_1',
    args         => '-X aa',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ aaa,
  author = "aa",
  title	 = "the title"
}
\@article{ aba,
  author = "bb",
  title	 = "Just another text"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  aaa,
  author	= "aa",
  title		= "the title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => '_X_2',
    args         => '-X a+a+',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ aaa,
  author = "aa",
  title	 = "the title"
}
\@article{ aba,
  author = "bb",
  title	 = "Just another text"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  aaa,
  author	= "aa",
  title		= "the title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_1',
    args         => '--select\'{"aa"}\'',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ a,
  author = "aa",
  title	 = "the title"
}
\@article{ b,
  author = "bb",
  title	 = "THE TITLE"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  a,
  author	= "aa",
  title		= "the title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_2',
    args         => '--select\'{"title"}\'',
    expected_err =>'',
    bib	         => <<__EOF__,
\@article{ a,
  author = "aa",
  title	 = "the title"
}
\@article{ b,
  author = "bb",
  title	 = "Just another text"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  a,
  author	= "aa",
  title		= "the title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_3',
    args         => '--select\'{"t.*le"}\'',
    expected_err =>'',
    bib	         => <<__EOF__,
\@article{ a,
  author = "aa",
  title	 = "the title"
}
\@article{ b,
  author = "bb",
  title	 = "Just another text"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  a,
  author	= "aa",
  title		= "the title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_crossrefs_0',
    args         => '--select\'{"aa"}\' -- select.crossrefs=off',
    expected_err =>'',
    bib	         => <<__EOF__,
\@article{ a,
  author  = "aa",
  title	  = "the title",
  crossref= "b"
}
\@article{ b,
  author = "bb",
  title	 = "THE TITLE"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  a,
  author	= "aa",
  title		= "the title",
  crossref	= "b"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_crossrefs_1',
    args         => '--select\'{"aa"}\' -- select.crossrefs=on',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ a,
  author  = "aa",
  title	  = "the title",
  crossref= "b"
}
\@article{ b,
  author = "bb",
  title	 = "THE TITLE"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  a,
  author	= "aa",
  title		= "the title",
  crossref	= "b"
}

\@Article{	  b,
  author	= "bb",
  title		= "THE TITLE"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_crossrefs_2',
    args         => '--select\'{"aa"}\' -- select.crossrefs=on',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ a,
  author  = "aa",
  title	  = "the title",
  crossref= "b"
}
\@article{ b,
  author  = "bb",
  title	  = "THE title",
  crossref= "c"
}
\@article{ c,
  author = "cc",
  title	 = "THE TITLE"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  a,
  author	= "aa",
  title		= "the title",
  crossref	= "b"
}

\@Article{	  b,
  author	= "bb",
  title		= "THE title",
  crossref	= "c"
}

\@Article{	  c,
  author	= "cc",
  title		= "THE TITLE"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => '_X_c_1',
    args         => '-X aa -c',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ aa,
  author  = "aa",
  title	  = "the title",
  crossref= "b"
}
\@article{ b,
  author = "bb",
  title	 = "THE TITLE"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  aa,
  author	= "aa",
  title		= "the title",
  crossref	= "b"
}

\@Article{	  b,
  author	= "bb",
  title		= "THE TITLE"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => '_X_c_2',
    args         => '-X aa -c',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ aa,
  author  = "aa",
  title	  = "the title",
  crossref= "b"
}
\@article{ b,
  author  = "bb",
  title	  = "THE title",
  crossref= "c"
}
\@article{ c,
  author = "cc",
  title	 = "THE TITLE"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  aa,
  author	= "aa",
  title		= "the title",
  crossref	= "b"
}

\@Article{	  b,
  author	= "bb",
  title		= "THE title",
  crossref	= "c"
}

\@Article{	  c,
  author	= "cc",
  title		= "THE TITLE"
}
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
