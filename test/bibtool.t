#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2014 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

bibtool.t - Test suite for BibTool.

=head1 SYNOPSIS

bibtool.t 

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
BUnit::run(name         => 'bibtool_1',
	   bib		=> <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 "Gerd "#"Neugebauer",
  year =	 "x" # "x" # "x"
}
__EOF__
	   expected_out	=> <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= "Gerd " # "Neugebauer",
  year		= "x" # "x" # "x"
}
__EOF__
	   expected_err	=> ""
    );


#------------------------------------------------------------------------------
BUnit::run(name         => 'bibtool_2',
	   bib		=> <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 "Gerd Neugebauer",
  year =	 "x" # may # {x} #"x"
}
__EOF__
	   expected_out	=> <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= "Gerd Neugebauer",
  year		= "x" # may # {x} # "x"
}
__EOF__
	   expected_err	=> ""
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
