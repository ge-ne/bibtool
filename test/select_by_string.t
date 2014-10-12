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

select_by_string.t - Test suite for BibTool select.by.string.

=head1 SYNOPSIS

select_by_string.t 

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
BUnit::run(name  => 'select_by_string_1',
    args	 => '--select.by.string=\'{"none"}\' bib/xampl.bib',
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
    args	 => '--select.by.string=\'{"anual-mi"}\' bib/xampl.bib',
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
    args	 => '--select.by.string=\'{"manmaker"}\' bib/xampl.bib',
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
  month		= apr # "-" # may,
  year		= 1986,
  note		= "This is a full MANUAL entry"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_by_string_4',
    args	 => '--select.by.string=\'{"MISC"}\' bib/xampl.bib',
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
    args	 => '--select.by.string=\'{"MISC"}\' bib/xampl.bib',
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
    args	 => '--select.by.string=\'{note "Kn"}\' bib/xampl.bib',
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
    args	 => '--select.by.string=\'{$type "misc"}\' bib/xampl.bib',
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


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
