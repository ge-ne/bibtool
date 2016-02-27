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

string.t - Test suite for BibTool string expressions.

=head1 SYNOPSIS

string.t

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
BUnit::run(name         => 'string-1',
	   resource	=> '"";',
	   expected_err => '',
	   expected_out => "\"\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-2',
	   resource	=> '"a";',
	   expected_err => '',
	   expected_out => "\"a\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-11',
	   resource	=> <<__EOF__ ,
"a\\"b";
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
"a\\"b"
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-12',
	   resource	=> <<__EOF__ ,
"a\\nb";
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
"a\\nb"
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-13',
	   resource	=> <<__EOF__ ,
"a\\!b";
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
"a!b"
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-14',
	   resource	=> <<__EOF__ ,
"a\tb";
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
"a\\tb"
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-15',
	   resource	=> <<__EOF__ ,
"a\fb";
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
"a\\fb"
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'string-err-1',
	   resource	=> <<__EOF__ ,
"abc
__EOF__
	   expected_err => <<__EOF__ );


^
*** BibTool ERROR:  (line 1 in _test.rsc): Missing closing delimiter "
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'string-err-2',
	   resource	=> <<__EOF__ ,
"abc
d
e
f
__EOF__
	   expected_err => <<__EOF__ );


^
*** BibTool ERROR:  (line 1 in _test.rsc): Missing closing delimiter "
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'like-1',
	   resource	=> 'a like "abc";',
	   expected_err => '',
	   expected_out => <<__EOF__ );
a like "abc"
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'ilike-1',
	   resource	=> 'a ilike "abc";',
	   expected_err => '',
	   expected_out => <<__EOF__ );
a ilike "abc"
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
