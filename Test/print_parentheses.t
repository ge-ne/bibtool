#!/bin/perl -W
#******************************************************************************
# $Id: print_parentheses.t,v 1.1 2011-11-20 15:22:45 gene Exp $
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

print_parentheses.t - Test suite for BibTool print.parentheses.

=head1 SYNOPSIS

print_parentheses.t 

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
BUnit::run(name         => 'print_parentheses_1',
	   args         => '-- print.parentheses=on',
	   bib		=> <<__EOF__,
\@String{BT  ="BibTool"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
__EOF__
	   expected_out => <<__EOF__,
\@STRING(bt	= "BibTool" )

\@Manual(	  bibtool,
  title		= bt,
  author	= {Gerd Neugebauer},
  year		= 2011
)
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_parentheses_2',
	   args         => '-- print.parentheses=off',
	   bib		=> <<__EOF__,
\@String{BT  ="BibTool"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
__EOF__
	   expected_out => <<__EOF__,
\@STRING{bt	= "BibTool" }

\@Manual{	  bibtool,
  title		= bt,
  author	= {Gerd Neugebauer},
  year		= 2011
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
