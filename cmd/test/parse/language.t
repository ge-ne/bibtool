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
	   expected_err => "\n*** BibTool ERROR:  (line 1 in _test.rsc): Missing )\n",
	   expected_out => '');

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-err-2',
	   resource	=> "a(\n\n\n",
	   expected_err => "\n*** BibTool ERROR:  (line 1 in _test.rsc): Missing )\n",
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

*** BibTool ERROR:  (line 1 in _test.rsc): Missing operator after c
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'group-0',
	   resource	=> "{}\n",
	   expected_err => '',
	   expected_out => "{\n}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'group-1',
	   resource	=> "{;}\n",
	   expected_err => '',
	   expected_out => "{\n}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'group-2',
	   resource	=> "{;;}\n",
	   expected_err => '',
	   expected_out => "{\n}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'group-10',
	   resource	=> "{123}\n",
	   expected_err => '',
	   expected_out => "{\n  123\n}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'group-20',
	   resource	=> "{123;abc}\n",
	   expected_err => '',
	   expected_out => "{\n  123;\n  abc\n}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'while-0',
	   resource	=> 'while (false) {}',
	   expected_err => '',
	   expected_out => "while (false) {\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'while-1',
	   resource	=> 'while (false) {1234;}',
	   expected_err => '',
	   expected_out => "while (false) {\n  1234\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'while-3',
	   resource	=> 'while (false) {1234;abc}',
	   expected_err => '',
	   expected_out => "while (false) {\n  1234;\n  abc\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'if-0',
	   resource	=> 'if (false) {}',
	   expected_err => '',
	   expected_out => "if (false) {\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'if-1',
	   resource	=> 'if (false) {1234;}',
	   expected_err => '',
	   expected_out => "if (false) {\n  1234\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'if-2',
	   resource	=> 'if (false) {1234;abc}',
	   expected_err => '',
	   expected_out => "if (false) {\n  1234;\n  abc\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'if-else-0',
	   resource	=> 'if (false) {} else {}',
	   expected_err => '',
	   expected_out => "if (false) {\n} else {\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'if-else-1',
	   resource	=> 'if (false) {1234;} else {abc}',
	   expected_err => '',
	   expected_out => "if (false) {\n  1234\n} else {\n  abc\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'if-else-3',
	   resource	=> 'if (false) {1234;abc} else {a;b}',
	   expected_err => '',
	   expected_out => "if (false) {\n  1234;\n  abc\n} else {\n  a;\n  b\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'else-err-1',
	   resource	=> 'else',
	   expected_out => '',
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): isolated else encountered
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'with-1',
	   resource	=> 'with () {}',
	   expected_err => '',
	   expected_out => "with () {\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'with-2',
	   resource	=> 'with (x:123) {}',
	   expected_err => '',
	   expected_out => "with (x: 123) {\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'with-3',
	   resource	=> 'with (x:123,y:456) {}',
	   expected_err => '',
	   expected_out => "with (x: 123,  y: 456) {\n}\n" );


#------------------------------------------------------------------------------
BUnit::run(name         => 'with-11',
	   resource	=> 'with () {abc}',
	   expected_err => '',
	   expected_out => "with () {\n  abc\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'with-12',
	   resource	=> 'with (x:123) {abc}',
	   expected_err => '',
	   expected_out => "with (x: 123) {\n  abc\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'with-13',
	   resource	=> 'with (x:123,y:456) {abc}',
	   expected_err => '',
	   expected_out => "with (x: 123,  y: 456) {\n  abc\n}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-0',
	   resource	=> 'defun def() {}',
	   expected_err => '',
	   expected_out => "defun def() {}\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-1',
	   resource	=> 'defun def(x:123,y:456) {abc}',
	   expected_err => '',
	   expected_out => "defun def(x: 123, y: 456) {\n  abc\n}\n" );


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
