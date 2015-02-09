#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2015 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

print_entry_types.t - Test suite for BibTool print.entry.types.

=head1 SYNOPSIS

print_entry_types.t

=head1 DESCRIPTION

This module contains some test cases. Running this module as program
will run all test cases and print a summary for each. Optionally files
*.out and *.err are left if the expected result does not match the
actual result.

=head1 OPTIONS

none

=head1 AUTHOR

Gerd Neugebauer

=head1 BUGS

=over 4

=item *

...

=back

=cut

use strict;
use BUnit;

use constant BIB_3 =><<__EOF__;
start
\@article{art, author="A.U. Thor"}
\@string{s	     ="s"}
\@string{t	     ="t"}
\@preamble{preamble}
\@book{bk, author =s}
\@alias{kb=bk}
the comment
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_entry_types_0',
	   args		=> 'bib/xampl.bib',
	   resource	=> <<__EOF__ ,
	   print.entry.types = {}
__EOF__
	   expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_entry_types_p1',
	   bib		=> BIB_3,
	   resource	=> <<__EOF__ ,
	   print.entry.types {p}
__EOF__
	   expected_out => <<__EOF__ );
\@PREAMBLE{ preamble }
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_entry_types_p2',
	   args		=> 'bib/xampl.bib',
	   resource	=> <<__EOF__ ,
	   print.entry.types {p}
__EOF__
	   expected_out => <<__EOF__ );
\@PREAMBLE{ "\\newcommand{\\noopsort}[1]{} "
	 # "\\newcommand{\\printfirst}[2]{#1} "
	 # "\\newcommand{\\singleletter}[1]{#1} "
	 # "\\newcommand{\\switchargs}[2]{#2#1} " }
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_entry_types_s1',
	   bib		=> BIB_3,
	   resource	=> <<__EOF__ ,
	   print.entry.types {s}
__EOF__
	   expected_out => <<__EOF__ );
\@STRING{s	= "s" }
\@STRING{t	= "t" }
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_entry_types_s2',
	   args		=> 'bib/xampl.bib',
	   resource	=> <<__EOF__ ,
	   print.entry.types {S}
__EOF__
	   expected_out => <<__EOF__ );
\@STRING{acm	= "The OX Association for Computing Machinery" }
\@STRING{stoc	= " Symposium on the Theory of Computing" }
\@STRING{stoc-key= "OX{\\singleletter{stoc}}" }
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_entry_types_S1',
	   bib		=> BIB_3,
	   resource	=> <<__EOF__ ,
	   print.entry.types {S}
__EOF__
	   expected_out => <<__EOF__ );
\@STRING{s	= "s" }
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'print_entry_types_dollar1',
	   bib		=> BIB_3,
	   resource	=> <<__EOF__ ,
	   print.entry.types {\$}
__EOF__
	   expected_out => <<__EOF__ );
\@STRING{s	= "s" }
\@STRING{t	= "t" }
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_entry_types_c1',
	   ignore	=> 1,
	   bib		=> BIB_3,
	   resource	=> <<__EOF__ ,
	   print.entry.types {c}
__EOF__
	   expected_out => <<__EOF__ );
the comment
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_entry_types_a1',
	   bib		=> BIB_3,
	   resource	=> <<__EOF__ ,
	   print.entry.types {a}
__EOF__
	   expected_out => <<__EOF__ );
\@ALIAS{kb	= bk }
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_entry_types_n1',
	   bib		=> BIB_3,
	   resource	=> <<__EOF__ ,
	   print.entry.types {n}
__EOF__
	   expected_out => <<__EOF__ );

\@Article{	  art,
  author	= "A.U. Thor"
}

\@Book{		  bk,
  author	= s
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_entry_types_1',
	   bib		=> BIB_3,
	   resource	=> <<__EOF__ ,
__EOF__
	   #expected_err	=> '',
	   expected_out	=> <<__EOF__ );
\@PREAMBLE{ preamble }
\@STRING{s	= "s" }
\@STRING{t	= "t" }

\@Article{	  art,
  author	= "A.U. Thor"
}

\@Book{		  bk,
  author	= s
}
\@ALIAS{kb	= bk }
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
