#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2015-2017 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

list.t - Test suite for BibTool list expressions.

=head1 SYNOPSIS

list.t

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
BUnit::run(name         => 'list-1',
	   resource	=> "[];\n",
	   expected_err => '',
	   expected_out => "[]\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-2',
	   resource	=> "[ ];\n",
	   expected_err => '',
	   expected_out => "[]\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-3',
	   resource	=> "nil;\n",
	   expected_err => '',
	   expected_out => "[]\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-10',
	   resource	=> "[123];\n",
	   expected_err => '',
	   expected_out => "[123]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-20',
	   resource	=> "[123, \"abc\"];\n",
	   expected_err => '',
	   expected_out => "[123, \"abc\"]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'list-21',
	   resource	=> "[123, abc];\n",
	   expected_err => '',
	   expected_out => "[123, abc]\n");

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
