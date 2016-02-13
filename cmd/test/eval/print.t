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

print.t - Test suite for BibTool built-in print.

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

$BUnit::name_prefix = 'eval/';

#------------------------------------------------------------------------------
BUnit::run(name         => 'print-1',
	   args	        => '--eval',
	   resource     => "print 123\n",
	   expected_err => '',
	   expected_out => "123[]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'print-2',
	   args	        => '-e',
	   resource     => "print {123}\n",
	   expected_err => '',
	   expected_out => "123[]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'print-3',
	   args	        => '--eval',
	   resource     => "print `author`\n",
	   expected_err => '',
	   expected_out => "[][]\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'print-4',
	   args	        => '-e',
	   resource     => "print []\n",
	   expected_err => '',
	   expected_out => "[][]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'print-5',
	   args		=> '-e',
	   resource	=> "print [123]\n",
	   expected_err	=> '',
	   expected_out	=> "[123][]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'print-10',
	   args	        => '-e',
	   resource     => "print ()\n",
	   expected_err => '',
	   expected_out => "[]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'print-11',
	   args	        => '-e',
	   resource     => "print (12)\n",
	   expected_err => '',
	   expected_out => "12[]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'print-12',
	   args	        => '-e',
	   resource     => "print (12,34)\n",
	   expected_err => '',
	   expected_out => "1234[]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'print-20',
	   args	        => '-e',
	   resource     => "print \"\"\n",
	   expected_err => '',
	   expected_out => "[]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'print-21',
	   args	        => '-e',
	   resource     => "print \"123\"\n",
	   expected_err => '',
	   expected_out => "123[]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'print-22',
	   args	        => '-e',
	   resource     => "print \"123\\n\"\n",
	   expected_err => '',
	   expected_out => "123\n[]\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'print-23',
	   args	        => '-e',
	   resource     => "print \"12\\t3\"\n",
	   expected_err => '',
	   expected_out => "12\t3[]\n");

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
