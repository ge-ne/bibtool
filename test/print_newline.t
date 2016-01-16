#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2016 Gerd Neugebauer
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

print_newline.t - Test suite for BibTool print.newline.

=head1 SYNOPSIS

print_newline.t 

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
BUnit::run(name         => 'print_newline_1',
	   args         => '-- print.newline=0 bib/x1.bib bib/x1.bib',
	   expected_out => "\n".
	   "\@Manual{	  bibtool,\n".
	   "  title		= {BibTool},\n".
	   "  author	= {Gerd Neugebauer},\n".
	   "  year		= 2015\n".
	   "}\n".
	   "\@Manual{	  bibtool,\n".
	   "  title		= {BibTool},\n".
	   "  author	= {Gerd Neugebauer},\n".
	   "  year		= 2015\n".
	   "}",
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_newline_2',
	   args         => '-- print.newline=1 bib/x1.bib bib/x1.bib',
	   expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2015
}

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2015
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_newline_3',
	   args         => '-- print.newline=2 bib/x1.bib bib/x1.bib',
	   expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2015
}


\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2015
}

__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
