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

database.t - Test suite for BibTool 3 database features.

=head1 SYNOPSIS

database.t

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
BUnit::run(name         => 'db-1',
	   args	        => '--eval',
	   resource     => "read();",
	   expected_err => '',
	   expected_out => "<DB>\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'db-2',
	   args	        => '--eval',
	   resource     => "read([]);",
	   expected_err => '',
	   expected_out => "<DB>\n");

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
