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
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2, or (at your option)
#  any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#*=============================================================================

=head1 NAME

crossref_map.t - Test suite for BibTool crossref.map.

=head1 SYNOPSIS

crossref_map.t 

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

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_1',
    resource 	      => 'crossref.map {}',
    expected_err      => <<__EOF__,


^
*** BibTool ERROR: List of symbols expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_2',
    resource 	      => 'crossref.map {,}',
    expected_err      => <<__EOF__,

,
^
*** BibTool ERROR: List of symbols expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_3',
    resource 	      => 'crossref.map {""}',
    expected_err      => <<__EOF__,

""
^
*** BibTool ERROR: List of symbols expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_4',
    resource 	      => 'crossref.map {123}',
    expected_err      => <<__EOF__,

123
^
*** BibTool ERROR: List of symbols expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_5',
    resource 	      => 'crossref.map {abc}',
    expected_err      => <<__EOF__,

abc
___^
*** BibTool ERROR: Symbol expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_6',
    resource 	      => 'crossref.map {{}}',
    expected_err      => <<__EOF__,

{}
__^
*** BibTool ERROR: Symbol expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_7',
    resource 	      => 'crossref.map {{abc}}',
    expected_err      => <<__EOF__,

{abc}
_____^
*** BibTool ERROR: Symbol expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_8',
    resource 	      => 'crossref.map {{a c}}',
    expected_err      => <<__EOF__,

{a c}
_____^
*** BibTool ERROR: Symbol expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_10',
    resource 	      => 'crossref.map {{}#}',
    expected_err      => <<__EOF__,

{}#
___^
*** BibTool ERROR: Symbol expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_11',
    resource 	      => 'crossref.map {{} 123}',
    expected_err      => <<__EOF__,

{} 123
___^
*** BibTool ERROR: Symbol expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_12',
    resource 	      => 'crossref.map {{} "123"}',
    expected_err      => <<__EOF__,

{} "123"
___^
*** BibTool ERROR: Symbol expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_20',
    resource 	      => 'crossref.map {{abc} def}',
    expected_err      => <<__EOF__,

{abc} def
_________^
*** BibTool ERROR: List of symbols expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_21',
    resource 	      => 'crossref.map {{abc} def#}',
    expected_err      => <<__EOF__,

{abc} def#
__________^
*** BibTool ERROR: List of symbols expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_22',
    resource 	      => 'crossref.map {{abc} def 123}',
    expected_err      => <<__EOF__,

{abc} def 123
__________^
*** BibTool ERROR: List of symbols expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_23',
    resource 	      => 'crossref.map {{abc} def "123"}',
    expected_err      => <<__EOF__,

{abc} def "123"
__________^
*** BibTool ERROR: List of symbols expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_24',
    resource 	      => 'crossref.map {{abc} def xyz}',
    expected_err      => <<__EOF__,

{abc} def xyz
_____________^
*** BibTool ERROR: Symbol expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_25',
    resource 	      => 'crossref.map {{abc} def {xyz}}',
    expected_err      => <<__EOF__,

{abc} def {xyz}
_______________^
*** BibTool ERROR: Symbol expected.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_30',
    resource 	      => 'crossref.map {{abc} def {xyz} ghi}',
    expected_err      => <<__EOF__,

*** BibTool WARNING: Unknown source entry type \`abc\'. Mapping ignored.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_err_31',
    resource 	      => 'crossref.map {{book} def {xyz} ghi}',
    expected_err      => <<__EOF__,

*** BibTool WARNING: Unknown destination entry type \`xyz\'. Mapping ignored.
__EOF__
    expected_out => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_1',
    resource    => <<__EOF__,
crossref.map {{book} # def = {article} ttt}
expand.crossref=true
__EOF__
    bib		=> <<__EOF__,
\@Manual{	  bibtool,
  title		= {BibTool},
  crossref	= {x}
}
\@Book{ x,
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}
__EOF__
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}

\@Book{		  x,
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'crossref_map_2',
    resource    => <<__EOF__,
crossref.map {{book} \# title = {manual} booktitle}
expand.crossref=true
__EOF__
    bib		=> <<__EOF__,
\@Manual{	  bibtool,
  crossref	= {x}
}
\@Book{ x,
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}
__EOF__
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  booktitle	= {BibTool},
  author	= {Gerd Neugebauer}
}

\@Book{		  x,
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}
__EOF__
    expected_err => '' );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
