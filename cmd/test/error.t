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

=cut

use strict;
use BUnit;

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-1',
	   resource	=> <<__EOF__ ,
+
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Unexpected operator +
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-2',
	   resource	=> <<__EOF__ ,
-+
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Unexpected end-of-file
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'error-3',
	   resource	=> <<__EOF__ ,
-
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Unexpected end-of-file
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-10',
	   resource	=> <<__EOF__ ,
123
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Unexpected end-of-file
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-20',
	   resource	=> <<__EOF__ ,
?
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Semicolon expected instead of ?
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-21',
	   resource	=> <<__EOF__ ,
\\
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Semicolon expected instead of \\
__EOF__

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
