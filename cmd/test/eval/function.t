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
	   resource     => "a();",
	   expected_err => "\n*** BibTool ERROR: Undefined function a\n",
	   expected_out => '');

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-err-2',
	   args	        => '--eval',
	   resource     => "a(1);",
	   expected_err => "\n*** BibTool ERROR: Undefined function a\n",
	   expected_out => '');

#------------------------------------------------------------------------------
BUnit::run(name         => 'fct-err-3',
	   args	        => '--eval',
	   resource     => "a(1, \"\");",
	   expected_err => "\n*** BibTool ERROR: Undefined function a\n",
	   expected_out => '');

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-1',
	   args	        => '--eval',
	   resource     => "defun a(){};",
	   expected_err => '',
	   expected_out => "function () {}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-2',
	   args	        => '--eval',
	   resource     => "defun a(x){};",
	   expected_err => '',
	   expected_out => "function (x) {}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-3',
	   args	        => '--eval',
	   resource     => "defun a(x,y){};",
	   expected_err => '',
	   expected_out => "function (x, y) {}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-4',
	   args	        => '--eval',
	   resource     => "defun a(x:123){};",
	   expected_err => '',
	   expected_out => "function (x: 123) {}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-11',
	   args	        => '--eval',
	   resource     => "defun a(){};a()",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-12',
	   args	        => '--eval',
	   resource     => "defun a(x){};a(123)",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-13',
	   args	        => '--eval',
	   resource     => "defun a(x,y){};a(1,2)",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-14',
	   args	        => '--eval',
	   resource     => "defun a(x:123){};a(98)",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-21',
	   args	        => '--eval',
	   resource     => "defun a(){777};a()",
	   expected_err => '',
	   expected_out => "777\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-22',
	   args	        => '--eval',
	   resource     => "defun a(x){x+7};a(123)",
	   expected_err => '',
	   expected_out => "130\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-23',
	   args	        => '--eval',
	   resource     => "defun a(x,y){x+y};a(1,2)",
	   expected_err => '',
	   expected_out => "3\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-24',
	   args	        => '--eval',
	   resource     => "defun a(x:123){x};a(98)",
	   expected_err => '',
	   expected_out => "98\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'defun-25',
	   args	        => '--eval',
	   resource     => "defun a(x:123){x};a()",
	   expected_err => '',
	   expected_out => "123\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-1',
	   args	        => '--eval',
	   resource     => "a=function (){};",
	   expected_err => '',
	   expected_out => "function () {}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-2',
	   args	        => '--eval',
	   resource     => "a=function (x){};",
	   expected_err => '',
	   expected_out => "function (x) {}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-3',
	   args	        => '--eval',
	   resource     => "a=function (x,y){};",
	   expected_err => '',
	   expected_out => "function (x, y) {}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-4',
	   args	        => '--eval',
	   resource     => "a=function (x:123){};",
	   expected_err => '',
	   expected_out => "function (x: 123) {}\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-11',
	   args	        => '--eval',
	   resource     => "a=function (){};a()",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-12',
	   args	        => '--eval',
	   resource     => "a=function (x){};a(123)",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-13',
	   args	        => '--eval',
	   resource     => "a=function (x,y){};a(1,2)",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-14',
	   args	        => '--eval',
	   resource     => "a=function (x:123){};a(98)",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-21',
	   args	        => '--eval',
	   resource     => "a=function (){777};a()",
	   expected_err => '',
	   expected_out => "777\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-22',
	   args	        => '--eval',
	   resource     => "a=function (x){x+7};a(123)",
	   expected_err => '',
	   expected_out => "130\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-23',
	   args	        => '--eval',
	   resource     => "a=function (x,y){x+y};a(1,2)",
	   expected_err => '',
	   expected_out => "3\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-24',
	   args	        => '--eval',
	   resource     => "a=function (x:123){x};a(98)",
	   expected_err => '',
	   expected_out => "98\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'function-25',
	   args	        => '--eval',
	   resource     => "a=function (x:123){x};a()",
	   expected_err => '',
	   expected_out => "123\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'with-1',
	   args	        => '--eval',
	   resource     => "with (){};",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'with-2',
	   args	        => '--eval',
	   resource     => "with (x){};",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'with-3',
	   args	        => '--eval',
	   resource     => "with (x,y){};",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'with-4',
	   args	        => '--eval',
	   resource     => "with (x:123){};",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'with-21',
	   args	        => '--eval',
	   resource     => "with (){777}",
	   expected_err => '',
	   expected_out => "777\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'with-22',
	   args	        => '--eval',
	   resource     => "with (x){x+7}",
	   expected_err => '',
	   expected_out => "7\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'with-24',
	   args	        => '--eval',
	   resource     => "with (x:123){x}",
	   expected_err => '',
	   expected_out => "123\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'return-1',
	   args	        => '--eval',
	   resource     => "return;",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'return-2',
	   args	        => '--eval',
	   resource     => "return 123",
	   expected_err => '',
	   expected_out => "123\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'return-3',
	   args	        => '--eval',
	   resource     => "return; 123",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'return-4',
	   args	        => '--eval',
	   resource     => "return 111; 222",
	   expected_err => '',
	   expected_out => "111\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'return-10',
	   args	        => '--eval',
	   resource     => "{111; return; 222};",
	   expected_err => '',
	   expected_out => "return nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'return-11',
	   args	        => '--eval',
	   resource     => "{111; return 666; 222};",
	   expected_err => '',
	   expected_out => "return 666\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'return-12',
	   args		     => '--eval',
	   resource     => "a=123; {111; return a; 222};",
	   expected_err	     => '',
	   expected_out	     => "return 123\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'return-20',
	   args	        => '--eval',
	   resource     => "defun f() {111; return; 222} f()",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'return-21',
	   args	        => '--eval',
	   resource     => "defun f() {111; return 999; 222}; f() ",
	   expected_err => '',
	   expected_out => "999\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'return-22',
	   args	        => '--eval',
	   resource     => "defun f(x) {111; return x; 222}; f(999) ",
	   expected_err => '',
	   expected_out => "999\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'return-30',
	   args	        => '--eval',
	   resource     => "f = function() {111; return; 222}; f() ",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'return-31',
	   args	        => '--eval',
	   resource     => "f = function(x) {111; return x; 222}; f(123) ",
	   expected_err => '',
	   expected_out => "123\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'each-0',
	   args	        => '--eval',
	   resource     => "each (x:[]) {} ",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'each-1',
	   args	        => '--eval',
	   resource     => "each (x:[]) {111} ",
	   expected_err => '',
	   expected_out => "nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'each-2',
	   args	        => '--eval',
	   resource     => "each (x:[1]) {111} ",
	   expected_err => '',
	   expected_out => "111\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'each-3',
	   args	        => '--eval',
	   resource     => "each (x:[2,3]) {x+1} ",
	   expected_err => '',
	   expected_out => "4\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'each-4',
	   args	        => '--eval',
	   resource     => "each (x:[2,3]) {print (x) }",
	   expected_err => '',
	   expected_out => "23nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'each-5',
	   args		=> '--eval',
	   resource     => "a=[2,3]; each (x:a) {print (x) }",
	   expected_err	=> '',
	   expected_out	=> "23nil\n");

#------------------------------------------------------------------------------
BUnit::run(name         => 'each-err-1',
	   args		=> '--eval',
	   resource     => "each (x:123) { x }",
	   expected_err	=> "\n*** BibTool ERROR: Illegal argument for each\n",
	   expected_out	=> '');

#------------------------------------------------------------------------------
BUnit::run(name         => 'each-err-2',
	   args		=> '--eval',
	   resource     => "each (x:true) { x }",
	   expected_err	=> "\n*** BibTool ERROR: Illegal argument for each\n",
	   expected_out	=> '');

#------------------------------------------------------------------------------
BUnit::run(name         => 'each-err-3',
	   args		=> '--eval',
	   resource     => "each (x:false) { x }",
	   expected_err	=> "\n*** BibTool ERROR: Illegal argument for each\n",
	   expected_out	=> '');

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
