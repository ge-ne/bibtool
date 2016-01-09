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

function.t - Test suite for BibTool functions.

=head1 SYNOPSIS

function.t

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
BUnit::run(name         => 'fct-err-1',
	   args	        => '--eval',
	   resource     => "a()",
	   expected_err => "\n*** BibTool ERROR: Undefined function a\n",
	   expected_out => '');

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-err-2',
	   args	        => '--eval',
	   resource     => "a(1)",
	   expected_err => "\n*** BibTool ERROR: Undefined function a\n",
	   expected_out => '');

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-err-3',
	   args	        => '--eval',
	   resource     => "a(1, \"\")",
	   expected_err => "\n*** BibTool ERROR: Undefined function a\n",
	   expected_out => '');

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
