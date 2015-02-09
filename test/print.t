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

print.t - Test suite for BibTool print.

=head1 SYNOPSIS

print.t 

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
BUnit::run(name  => 'print_0',
    args	 => '',
    resource 	 => 'print',
    expected_out => '',
    expected_err => <<__EOF__,

*** BibTool ERROR:  (line 2 in ./_test.rsc): Unterminated value
__EOF__
    );

#------------------------------------------------------------------------------
BUnit::run(name  => 'print_1',
    args	 => '',
    resource 	 => 'print{Hello World!}',
    expected_out => '',
    expected_err => <<__EOF__,
Hello World!
__EOF__
    );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
