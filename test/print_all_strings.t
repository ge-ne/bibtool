#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2018 Gerd Neugebauer
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

print_all_strings.t - Test suite for BibTool print.all.strings.

=head1 SYNOPSIS

print_all_strings.t 

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
BUnit::run(name         => 'print_all_strings_1',
	   args         => '-- print.all.strings=on',
	   bib		=> <<__EOF__,
\@String{BT  ="BibTool"}
\@String{TeX ="\\TeX"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
__EOF__
	   expected_out => <<__EOF__,
\@STRING{bt	= "BibTool" }
\@STRING{tex	= "\\TeX" }

\@Manual{	  bibtool,
  title		= bt,
  author	= {Gerd Neugebauer},
  year		= 2011
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_all_strings_2',
	   args         => '-- print.all.strings=off',
	   bib		=> <<__EOF__,
\@String{BT  ="BibTool"}
\@String{TeX ="\\TeX"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
__EOF__
	   expected_out => <<__EOF__,
\@STRING{bt	= "BibTool" }

\@Manual{	  bibtool,
  title		= bt,
  author	= {Gerd Neugebauer},
  year		= 2011
}
__EOF__
    expected_err => ''
    );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
