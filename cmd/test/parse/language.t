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
	   resource	=> <<__EOF__ ,
\'[123];
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(quote (123))
__EOF__

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
	   ignore	=> 'TODO',
	   resource	=> '?',
	   expected_out	=> '',
	   expected_err	=> <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Semicolon expected instead of ?
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-4',
	   ignore	=> 'TODO',
	   resource	=> '\\' ,
	   expected_out => '',
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Semicolon expected instead of \\
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'error-5',
	   ignore	=> 'TODO',
	   resource	=> '\\ \n' ,
	   expected_out => '',
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Semicolon expected instead of \\
__EOF__

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
