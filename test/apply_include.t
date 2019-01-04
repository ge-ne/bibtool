#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2019 Gerd Neugebauer
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

apply_include.t - Test suite for BibTool apply.include.

=head1 SYNOPSIS

apply_include.t 

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
use warnings;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name  => 'apply_include_0',
    bib		 => <<__EOF__,
\@include{xyzzy}
__EOF__
    resource 	 => 'apply.include=off',
    expected_out => <<__EOF__,
\@INCLUDE{xyzzy}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name  => 'apply_include_1',
    bib		 => <<__EOF__,
\@include{xyzzy}
__EOF__
    resource 	 => 'apply.include=on',
    expected_out => '',
    expected_err => "\n*** BibTool ERROR: File not found: xyzzy\n" );

#------------------------------------------------------------------------------
BUnit::run(name  => 'apply_include_2',
    bib		 => <<__EOF__,
\@include{bib/x1.bib}
__EOF__
    resource 	 => 'apply.include=on',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2018
}
__EOF__
    expected_err => '' );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
