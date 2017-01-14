#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2017 Gerd Neugebauer
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
BUnit::run(name         => 'eq-bool-1',
	   args	        => '--eval',
	   resource     => "false==false",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-bool-2',
	   args	        => '--eval',
	   resource     => "true==true",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-bool-10',
	   args	        => '--eval',
	   resource     => "false==0",
	   expected_err => '',
	   expected_out => FALSE);
#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-bool-11',
	   args	        => '--eval',
	   resource     => "false==11",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-bool-20',
	   args	        => '--eval',
	   resource     => "false==\"\"",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-bool-21',
	   args	        => '--eval',
	   resource     => "false==\"x\"",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-num-1',
	   args	        => '--eval',
	   resource     => "0==0",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-num-2',
	   args	        => '--eval',
	   resource     => "1==1",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-num-3',
	   args	        => '--eval',
	   resource     => "1==0",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-num-11',
	   args	        => '--eval',
	   resource     => "0==\"0\"",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-num-12',
	   args	        => '--eval',
	   resource     => "1==\"1\"",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-num-13',
	   args	        => '--eval',
	   resource     => "1==\"0\"",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-num-21',
	   args	        => '--eval',
	   resource     => "0==false",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-num-22',
	   args	        => '--eval',
	   resource     => "1==true",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-num-23',
	   args	        => '--eval',
	   resource     => "1==false",
	   expected_err => '',
	   expected_out => FALSE);


#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-str-1',
	   args	        => '--eval',
	   resource     => "\"a\"==\"a\"",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-str-2',
	   args	        => '--eval',
	   resource     => "\"a\"==\"b\"",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-list-1',
	   args	        => '--eval',
	   resource     => "(nil==nil)",
	   expected_err => '',
	   expected_out => TRUE);
#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-list-2',
	   args	        => '--eval',
	   resource     => "(nil==[1])",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-list-3',
	   args	        => '--eval',
	   resource     => "[]==[1]",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-list-4',
	   args	        => '--eval',
	   resource     => "[]==[]",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-list-10',
	   args	        => '--eval',
	   resource     => "[1]==[1]",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-list-11',
	   args	        => '--eval',
	   resource     => "[1,2]==[1,2]",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-list-21',
	   args	        => '--eval',
	   resource     => "[1,2]==[1,3]",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-1',
	   args	        => '--eval',
	   resource     => "(nil!=nil)",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-2',
	   args	        => '--eval',
	   resource     => "false!=false",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-3',
	   args	        => '--eval',
	   resource     => "true!=true",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-100',
	   args	        => '--eval',
	   resource     => "0!=0",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-101',
	   args	        => '--eval',
	   resource     => "1!=1",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-102',
	   args	        => '--eval',
	   resource     => "1!=0",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-200',
	   args	        => '--eval',
	   resource     => "\"a\"!=\"a\"",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-201',
	   args	        => '--eval',
	   resource     => "\"a\"!=\"b\"",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'lt-1',
	   args	        => '--eval',
	   resource     => "(0 < 0)",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'lt-2',
	   args	        => '--eval',
	   resource     => "(1 < 0)",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'lt-3',
	   args	        => '--eval',
	   resource     => "(0 < 1)",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'lt-10',
	   args	        => '--eval',
	   resource     => "(\"\" < \"\")",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'lt-11',
	   args	        => '--eval',
	   resource     => "(\"\" < \"x\")",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'lt-12',
	   args	        => '--eval',
	   resource     => "(\"abc\" < \"def\")",
	   expected_err => '',
	   expected_out => TRUE);


#------------------------------------------------------------------------------
BUnit::run(name         => 'le-1',
	   args	        => '--eval',
	   resource     => "(0 <= 0)",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'le-2',
	   args	        => '--eval',
	   resource     => "(1 <= 0)",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'le-3',
	   args	        => '--eval',
	   resource     => "(0 <= 1)",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'le-10',
	   args	        => '--eval',
	   resource     => "(\"\" <= \"\")",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'le-11',
	   args	        => '--eval',
	   resource     => "(\"\" <= \"x\")",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'le-12',
	   args	        => '--eval',
	   resource     => "(\"abc\" <= \"def\")",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'gt-1',
	   args	        => '--eval',
	   resource     => "(0 > 0)",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'gt-2',
	   args	        => '--eval',
	   resource     => "(1 > 0)",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'gt-3',
	   args	        => '--eval',
	   resource     => "(0 > 1)",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'gt-10',
	   args	        => '--eval',
	   resource     => "(\"\" > \"\")",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'gt-11',
	   args	        => '--eval',
	   resource     => "(\"\" > \"x\")",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'gt-12',
	   args	        => '--eval',
	   resource     => "(\"abc\" > \"def\")",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'gt-13',
	   args	        => '--eval',
	   resource     => "(\"x\" > \"\")",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'gt-14',
	   args	        => '--eval',
	   resource     => "(\"def\" > \"abc\")",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ge-1',
	   args	        => '--eval',
	   resource     => "(0 >= 0)",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ge-2',
	   args	        => '--eval',
	   resource     => "(1 >= 0)",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ge-3',
	   args	        => '--eval',
	   resource     => "(0 >= 1)",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ge-10',
	   args	        => '--eval',
	   resource     => "(\"\" >= \"\")",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ge-11',
	   args	        => '--eval',
	   resource     => "(\"x\" >= \"\")",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ge-12',
	   args	        => '--eval',
	   resource     => "(\"def\" >= \"abc\")",
	   expected_err => '',
	   expected_out => TRUE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ge-13',
	   args	        => '--eval',
	   resource     => "(\"\" >= \"x\")",
	   expected_err => '',
	   expected_out => FALSE);

#------------------------------------------------------------------------------
BUnit::run(name         => 'ge-14',
	   args	        => '--eval',
	   resource     => "(\"abc\" >= \"def\")",
	   expected_err => '',
	   expected_out => FALSE);

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
