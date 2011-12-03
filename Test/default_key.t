#!/bin/perl -W
#******************************************************************************
# $Id: default_key.t,v 1.2 2011-12-03 06:34:15 gene Exp $
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

default_key.t - Test suite for BibTool default.key.

=head1 SYNOPSIS

default_key.t 

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
BUnit::run(name         => 'default_key_0',
	   args         => '-f short',
	   bib	        => <<__EOF__,
\@Manual{	  bibtool,
  itle		= {BibTool},
  uthor	= {Gerd Neugebauer},
  ear		= 2011
}
__EOF__
	   expected_out => <<__EOF__,

\@Manual{	  **key*,
  itle		= {BibTool},
  uthor		= {Gerd Neugebauer},
  ear		= 2011
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'default_key_1',
	   args         => '-- default.key=on -f short',
	   bib	        => <<__EOF__,
\@Manual{	  bibtool,
  itle		= {BibTool},
  uthor	= {Gerd Neugebauer},
  ear		= 2011
}
__EOF__
	   expected_out => <<__EOF__,

\@Manual{	  on,
  itle		= {BibTool},
  uthor		= {Gerd Neugebauer},
  ear		= 2011
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
