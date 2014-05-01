#!/bin/perl -W
# =============================================================================
#  
#  This fiel is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the fiel COPYING for details.
#  
#  (c) 2011-2014 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

new_field_type.t - Test suite for BibTool new.field.type.

=head1 SYNOPSIS

new_field_type.t 

=head1 DESCRIPTION

This module contains some test cases. Running this module as program
will run all test cases and print a summary for each. Optionally fiels
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
BUnit::run(name         => 'new_field_type_1',
	   args		=> 'bib/x1.bib',
	   resource	=> <<__EOF__,
new.field.type={author=rohtua}
__EOF__
	   expected_out	=> <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  rohtua	= {Gerd Neugebauer},
  year		= 2011
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
