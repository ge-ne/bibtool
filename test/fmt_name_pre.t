#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2017-2020 Gerd Neugebauer
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

fmt_name_pre.t - Test suite for BibTool fmt.name.pre.

=head1 SYNOPSIS

fmt_name_pre.t 

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
use BUnit;use warnings;


use constant BIBTEX => <<__EOF__;

\@Book{		  b,
  author	= "Brinch Hansen, Per and Knuth, Donald E."
}
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name => 'fmt_name_pre_1',
	resource => <<__EOF__,
fmt.name.pre	= {}
key.format	= "%N(author)"
__EOF__
	bib => BIBTEX,
	expected_out => <<__EOF__,

\@Book{		  Brinch-HansenP.KnuthDE,
  author	= "Brinch Hansen, Per and Knuth, Donald E."
}
__EOF__
	expected_err => '');

#------------------------------------------------------------------------------
BUnit::run(name => 'fmt_name_pre_2',
	resource => <<__EOF__,
fmt.name.pre	= ""
key.format	= "%N(author)"
__EOF__
	bib => BIBTEX,
	expected_out => <<__EOF__,

\@Book{		  Brinch-HansenP.KnuthDE,
  author	= "Brinch Hansen, Per and Knuth, Donald E."
}
__EOF__
	expected_err => '');

#------------------------------------------------------------------------------
BUnit::run(name => 'fmt_name_pre_3',
	resource => <<__EOF__,
fmt.name.pre	= "  "
key.format	= "%N(author)"
__EOF__
	bib => BIBTEX,
	expected_out => <<__EOF__,

\@Book{		  Brinch-HansenP.KnuthDE,
  author	= "Brinch Hansen, Per and Knuth, Donald E."
}
__EOF__
	expected_err => '');

#------------------------------------------------------------------------------
BUnit::run(name => 'fmt_name_pre_4',
	resource => <<__EOF__,
fmt.name.pre	= " -- "
key.format	= "%N(author)"
__EOF__
	bib => BIBTEX,
	expected_out => <<__EOF__,

\@Book{		  Brinch-Hansen--P.Knuth--DE,
  author	= "Brinch Hansen, Per and Knuth, Donald E."
}
__EOF__
	expected_err => '');

#------------------------------------------------------------------------------
BUnit::run(name => 'fmt_name_pre_5',
	resource => <<__EOF__,
fmt.name.pre	= " -- xx "
key.format	= "%N(author)"
__EOF__
	bib => BIBTEX,
	expected_out => <<__EOF__,

\@Book{		  Brinch-Hansen--P.Knuth--DE,
  author	= "Brinch Hansen, Per and Knuth, Donald E."
}
__EOF__
	expected_err => '');

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
