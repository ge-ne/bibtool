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

eq.t - Test suite for BibTool equality.

=head1 SYNOPSIS

eq.t

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

use constant {TRUE  => "true\n",
	      FALSE => "false\n"};

$BUnit::name_prefix = 'eval/';

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-1',
	   args	        => '--eval',
	   resource     => "(nil==nil)",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-2',
	   args	        => '--eval',
	   resource     => "false==false",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-3',
	   args	        => '--eval',
	   resource     => "true==true",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-100',
	   args	        => '--eval',
	   resource     => "0==0",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-101',
	   args	        => '--eval',
	   resource     => "1==1",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-102',
	   args	        => '--eval',
	   resource     => "1==0",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-200',
	   args	        => '--eval',
	   resource     => "\"a\"==\"a\"",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-201',
	   args	        => '--eval',
	   resource     => "\"a\"==\"b\"",
	   expected_err => '',
	   expected_out => FALSE);

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
