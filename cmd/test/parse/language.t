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

language.t - Test suite for the BibTool 3 resource language.

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

$BUnit::name_prefix = 'parse/';

#------------------------------------------------------------------------------
BUnit::run(name         => 'comment-1',
	   resource	=> <<__EOF__ ,
% a b c d
__EOF__
	   expected_err => '',
	   expected_out => '');

#------------------------------------------------------------------------------
BUnit::run(name         => 'quote-1',
	   resource	=> '\'[123];',
	   expected_err => '',
	   expected_out => "\'([123])\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'quote-2',
	   resource	=> 'quote [123];',
	   expected_err => '',
	   expected_out => "\'([123])\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'quote-3',
	   resource	=> '\'[];',
	   expected_err => '',
	   expected_out => "\'(nil)\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-0',
	   resource	=> "a()\n",
	   expected_err => '',
	   expected_out => "a()\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-1',
	   resource	=> "a ( )\n",
	   expected_err => '',
	   expected_out => "a()\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-2',
	   resource	=> "a(1)\n",
	   expected_err => '',
	   expected_out => "a(1)\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-3',
	   resource	=> "a(\"12\")\n",
	   expected_err => '',
	   expected_out => "a(\"12\")\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-4',
	   resource	=> "a(ab)\n",
	   expected_err => '',
	   expected_out => "a(ab)\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-5',
	   resource	=> "a(a(b))\n",
	   expected_err => '',
	   expected_out => "a(a(b))\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-10',
	   resource	=> "a(1,2)\n",
	   expected_err => '',
	   expected_out => "a(1, 2)\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-20',
	   resource	=> "a(1,2) + 123\n",
	   expected_err => '',
	   expected_out => "(a(1, 2) + 123)\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-err-1',
	   resource	=> "a(",
	   expected_err => "\n*** BibTool ERROR:  (line 1 in _test.rsc): Unclosed list\n",
	   expected_out => '');

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-err-2',
	   resource	=> "a(\n\n\n",
	   expected_err => "\n*** BibTool ERROR:  (line 1 in _test.rsc): Unclosed list\n",
	   expected_out => '');

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-1',
	   resource	=> '-+',
	   expected_out => '',
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Missing operator for +
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-2',
	   resource	=> '-',
	   expected_out => '',
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Missing operator for -
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-3',
	   resource	=> '?',
	   expected_out	=> '',
	   expected_err	=> <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Unexpected character '?' found
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-4',
	   resource	=> '\\' ,
	   expected_out => '',
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Unexpected character '\\' found
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-5',
	   resource	=> '\\ \n' ,
	   expected_out => '',
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Unexpected character '\\' found
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-6',
	   resource	=> 'a b c' ,
	   expected_out => '',
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Missing operator after field
__EOF__

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
