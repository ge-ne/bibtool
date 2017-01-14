#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2017 Gerd Neugebauer
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

symbol_type.t - Test suite for BibTool symbol.type.

=head1 SYNOPSIS

symbol_type.t 

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
BUnit::run(name         => 'symbol_type_0',
	   args         => '-- symbol.type=123',
	   bib		=> '',
	   expected_out => <<__EOF__,
__EOF__
    expected_err => <<__EOF__
*** BibTool: Unknown symbol type ignored.
__EOF__
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'symbol_type_1',
	   args         => '-- symbol.type=xyz',
	   bib		=> '',
	   expected_out => <<__EOF__,
__EOF__
    expected_err => <<__EOF__
*** BibTool: Unknown symbol type ignored.
__EOF__
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'symbol_type_2',
	   args         => '-- symbol.type=upper',
	   bib		=> <<__EOF__,
\@String{BT  ="BibTool"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
__EOF__
	   expected_out => <<__EOF__,
\@STRING{BT	= "BibTool" }

\@Manual{	  bibtool,
  TITLE		= BT,
  AUTHOR	= {Gerd Neugebauer},
  YEAR		= 2011
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'symbol_type_3',
	   args         => '-- symbol.type=lower',
	   bib		=> <<__EOF__,
\@String{BT  ="BibTool"}

\@Manual{BibTool,
  Title = 	 BT,
  Author =	 {Gerd Neugebauer},
  Year =	 2011
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

#------------------------------------------------------------------------------
BUnit::run(name         => 'symbol_type_4',
	   args         => '-- symbol.type=cased',
	   bib		=> <<__EOF__,
\@String{BT  ="BibTool"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
__EOF__
	   expected_out => <<__EOF__,
\@STRING{Bt	= "BibTool" }

\@Manual{	  bibtool,
  Title		= Bt,
  Author	= {Gerd Neugebauer},
  Year		= 2011
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
