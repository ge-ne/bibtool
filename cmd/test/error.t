#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2015 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

error.t - Test suite for BibTool errors.

=head1 SYNOPSIS

error.t

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
use PUnit;

#------------------------------------------------------------------------------
PUnit::run(name         => 'error-1',
	   resource	=> <<__EOF__ ,
+
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Unexpected operator +
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
