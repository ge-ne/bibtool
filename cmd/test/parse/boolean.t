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

boolean.t - Test suite for BibTool boolean values.

=head1 SYNOPSIS

boolean.t

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
BUnit::run(name         => 'boolean-0',
	   resource	=> <<__EOF__ ,
false;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
false
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'boolean-1',
	   resource	=> <<__EOF__ ,
true;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
true
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-err-1',
	   resource	=> <<__EOF__ ,
123 ==
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for ==
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-1',
	   resource	=> <<__EOF__ ,
123==456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(== 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-2',
	   resource	=> <<__EOF__ ,
123 == -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(== 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'eq-3',
	   resource	=> <<__EOF__ ,
-123 == -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(== -123 -456)
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'ge-err-1',
	   resource	=> <<__EOF__ ,
123 >=
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for >=
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'ge-1',
	   resource	=> <<__EOF__ ,
123>=456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(>= 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'ge-2',
	   resource	=> <<__EOF__ ,
123 >= -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(>= 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'ge-3',
	   resource	=> <<__EOF__ ,
-123 >= -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(>= -123 -456)
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'gt-err-1',
	   resource	=> <<__EOF__ ,
123 >
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for >
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'gt-1',
	   resource	=> <<__EOF__ ,
123>456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(> 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'gt-2',
	   resource	=> <<__EOF__ ,
123 > -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(> 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'gt-3',
	   resource	=> <<__EOF__ ,
-123 > -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(> -123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'le-err-1',
	   resource	=> <<__EOF__ ,
123 <=
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for <=
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'le-1',
	   resource	=> <<__EOF__ ,
123<=456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(<= 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'le-2',
	   resource	=> <<__EOF__ ,
123 <= -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(<= 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'le-3',
	   resource	=> <<__EOF__ ,
-123 <= -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(<= -123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'lt-err-1',
	   resource	=> <<__EOF__ ,
123 <
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for <
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'lt-1',
	   resource	=> <<__EOF__ ,
123<456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(< 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'lt-2',
	   resource	=> <<__EOF__ ,
123 < -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(< 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'lt-3',
	   resource	=> <<__EOF__ ,
-123 < -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(< -123 -456)
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-err-1',
	   resource	=> <<__EOF__ ,
123 !=
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for !=
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-err-2',
	   resource	=> <<__EOF__ ,
123 !
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 1 in _test.rsc): Missing operator for not
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-1',
	   resource	=> <<__EOF__ ,
123!=456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(!= 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-2',
	   resource	=> <<__EOF__ ,
123 != -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(!= 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'ne-3',
	   resource	=> <<__EOF__ ,
-123 != -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(!= -123 -456)
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'and-err-1',
	   resource	=> <<__EOF__ ,
123 &&
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for and
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'and-err-2',
	   resource	=> <<__EOF__ ,
123 and
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for and
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'and-1',
	   resource	=> <<__EOF__ ,
123&&456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(and 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'and-2',
	   resource	=> <<__EOF__ ,
123 && -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(and 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'and-3',
	   resource	=> <<__EOF__ ,
-123 && -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(and -123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'and-11',
	   resource	=> <<__EOF__ ,
123and 456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(and 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'and-12',
	   resource	=> <<__EOF__ ,
123 and -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(and 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'and-13',
	   resource	=> <<__EOF__ ,
-123 and -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(and -123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-err-1',
	   resource	=> <<__EOF__ ,
123 ||
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for or
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-err-2',
	   resource	=> <<__EOF__ ,
123 or
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for or
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-1',
	   resource	=> <<__EOF__ ,
123||456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-2',
	   resource	=> <<__EOF__ ,
123 || -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-3',
	   resource	=> <<__EOF__ ,
-123 || -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or -123 -456)
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'or-11',
	   resource	=> <<__EOF__ ,
123or 456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or 123 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-12',
	   resource	=> <<__EOF__ ,
123 or -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or 123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'or-13',
	   resource	=> <<__EOF__ ,
-123 or -456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or -123 -456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-err-1',
	   resource	=> <<__EOF__ ,
123 not
__EOF__
	   expected_err => <<__EOF__ );

*** BibTool ERROR:  (line 2 in _test.rsc): Missing operator for not
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-1',
	   resource	=> <<__EOF__ ,
not 456;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(not 456)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-2',
	   resource	=> <<__EOF__ ,
not true;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(not true)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-3',
	   resource	=> <<__EOF__ ,
not not a;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(not (not a))
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-10',
	   resource	=> <<__EOF__ ,
not a and b;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(and (not a) b)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'not-11',
	   resource	=> <<__EOF__ ,
not a or b;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(or (not a) b)
__EOF__

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
