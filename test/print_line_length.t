#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2015-2018 Gerd Neugebauer
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

print_line_length.t - Test suite for BibTool applying line breaking during printing.

=head1 SYNOPSIS

print_line_length.t 

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


#------------------------------------------------------------------------------
BUnit::run(name  => 'print_line_length-5',
    args         => '--print.line.length=5',
    expected_err => '',
    bib		 => <<__EOF__,
\@Article{key,
  title = {x aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{key,
  title={x
     aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'print_line_length-10-1',
    args         => '--print.line.length=10',
    expected_err => '',
    bib		 => <<__EOF__,
\@Article{key,
  title = {x aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{ key,
  title	  ={x
	  aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'print_line_length-10-2',
    args         => '--print.line.length=10',
    expected_err => '',
    bib		 => <<__EOF__,
\@Article{key,
  title = {x aaaaaaaaa}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{ key,
  title	  ={x
	  aaaaaaaaa}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'print_line_length-10-3',
    args         => '--print.line.length=10',
    expected_err => '',
    bib		 => <<__EOF__,
\@Article{key,
  title = {x aaaaaaaaa aaaaaaaaa}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{ key,
  title	  ={x
	  aaaaaaaaa
	  aaaaaaaaa}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'print_line_length-10-4',
    args         => '--print.line.length=10',
    expected_err => '',
    bib		 => <<__EOF__,
\@Article{key,
  title = {x aaaaaaaaa aaaaaaaaa},
  titlx = {x aaaaaaaaa aaaaaaaaa}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{ key,
  title	  ={x
	  aaaaaaaaa
	  aaaaaaaaa},
  titlx	  ={x
	  aaaaaaaaa
	  aaaaaaaaa}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'print_line_length-20',
    args         => '--print.line.length=20',
    expected_err => '',
    bib		 => <<__EOF__,
\@Article{key,
  title = {x aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  key,
  title		= {x
		  aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'print_line_length-30',
    args         => '--print.line.length=30',
    expected_err => '',
    bib		 => <<__EOF__,
\@Article{key,
  title = {x aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  key,
  title		= {x
		  aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'print_line_length-30b',
    args         => '--print.line.length=30',
    expected_err => '',
    bib		 => <<__EOF__,
\@Article{key,
  title = {x aaaaaaaa}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  key,
  title		= {x
		  aaaaaaaa}
}
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
