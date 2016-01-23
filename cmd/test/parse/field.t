#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2015-2016 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

field.t - Test suite for BibTool fields.

=head1 SYNOPSIS

field.t

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

$BUnit::name_prefix = 'parse/';

#------------------------------------------------------------------------------
BUnit::run(name         => 'field-1',
	   resource	=> <<__EOF__ ,
abc;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
abc
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'field-2',
	   resource	=> <<__EOF__ ,
`abc`;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
abc
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'field-3',
	   resource	=> <<__EOF__ ,
`ver bose`;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
`ver bose`
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
