#!/bin/perl -W
#******************************************************************************
# $Id: input.t,v 1.1 2011-11-20 15:22:45 gene Exp $
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

input.t - Test suite for BibTool input.

=head1 SYNOPSIS

input.t 

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
BUnit::run(name         => 'input_1',
	   args         => '--input{bib/x1.bib}',
	   expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name         => '_i_1',
	   args         => '-i bib/x1.bib',
	   expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
