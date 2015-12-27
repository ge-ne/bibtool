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

arith.t - Test suite for BibTool arithmetic expresions.

=head1 SYNOPSIS

arith.t

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
PUnit::run(name         => 'arith-1',
	   resource	=> <<__EOF__ ,
123;
__EOF__
	   expected_out => <<__EOF__ );
123
__EOF__

#------------------------------------------------------------------------------
PUnit::run(name         => 'arith-2',
	   resource	=> <<__EOF__ ,
-123;
__EOF__
	   expected_out => <<__EOF__ );
-123
__EOF__

#------------------------------------------------------------------------------
PUnit::run(name         => 'arith-3',
	   resource	=> <<__EOF__ ,
-   123;
__EOF__
	   expected_out => <<__EOF__ );
-123
__EOF__

#------------------------------------------------------------------------------
PUnit::run(name         => 'arith-10',
	   resource	=> <<__EOF__ ,
2 * 3 + 4;
__EOF__
	   expected_out => <<__EOF__ );
(+  (*  2  3)  4)
__EOF__

#------------------------------------------------------------------------------
PUnit::run(name         => 'arith-11',
	   resource	=> <<__EOF__ ,
2 + 3 * 4;
__EOF__
	   expected_out => <<__EOF__ );
(+  2  (*  3  4))
__EOF__

#------------------------------------------------------------------------------
PUnit::run(name         => 'arith-12',
	   resource	=> <<__EOF__ ,
1 * (3 + 4);
__EOF__
	   expected_out => <<__EOF__ );
(*  1  (+  3  4))
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
