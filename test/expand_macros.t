#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2020 Gerd Neugebauer
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

expand_macros.t - Test suite for BibTool expand.macros.

=head1 SYNOPSIS

expand_macros.t 

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
BUnit::run(name         => 'expand_macros_1',
	   args         => '-- expand.macros=on',
	   bib				    => <<__EOF__,
\@String{BT				    ="BibTool"}
\@String{TeX				    ="\\TeX"}

\@Manual{BibTool,
  title = 	 BT,
  author =	 {Gerd Neugebauer},
  year =	 2011
}
__EOF__
	   expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= {2011}
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'expand_macros_2',
	   args         => '-- expand.macros=on',
	   bib				    => <<__EOF__,
\@String{BT				    ="BibTool"}
\@String{TeX				    ="\\TeX"}

\@Manual{BibTool,
  title = 	 {The } # BT # " Manual",
  author =	 {Gerd Neugebauer},
  year =	 2011
}
__EOF__
	   expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {The BibTool Manual},
  author	= {Gerd Neugebauer},
  year		= {2011}
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
