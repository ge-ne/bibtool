#!/bin/perl -W
#******************************************************************************
# $Id: ignored_word.t,v 1.1 2011-11-20 15:22:45 gene Exp $
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

ignored_word.t - Test suite for BibTool ignored.word.

=head1 SYNOPSIS

ignored_word.t 

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
BUnit::run(name => 'ignored_word_1',
    resource 	 => <<__EOF__,
ignored.word{BibTool}
key.format=short
__EOF__
    bib		 => <<__EOF__,
\@Manual{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2011
}
__EOF__
    expected_out => <<__EOF__,

\@Manual{	  neugebauer:manual,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= 2011
}
__EOF__
    expected_err => '' );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
