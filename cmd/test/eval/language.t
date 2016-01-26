#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2016 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

language.t - Test suite for BibTool 3 language features.

=head1 SYNOPSIS

language.t

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

$BUnit::name_prefix = 'eval/';

#------------------------------------------------------------------------------
BUnit::run(name         => 'block-0',
	   args	        => '--eval',
	   resource     => "{};",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'block-1',
	   args	        => '--eval',
	   resource     => "{}",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'block-2',
	   args	        => '--eval',
	   resource     => "{123}",
	   expected_err => '',
	   expected_out => "123\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'block-3',
	   args	        => '--eval',
	   resource     => "{123; 321}",
	   expected_err => '',
	   expected_out => "321\n");

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
