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

bibtool.t - Test suite for BibTool.

=head1 SYNOPSIS

bibtool.t 

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
BUnit::run(name         => 'bibtool_1',
	   bib		=> <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 "Gerd "#"Neugebauer",
  year =	 "x" # "x" # "x"
}
__EOF__
	   expected_out	=> <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= "Gerd " # "Neugebauer",
  year		= "x" # "x" # "x"
}
__EOF__
	   expected_err	=> ""
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'bibtool_2',
	   bib		=> <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 "Gerd Neugebauer",
  year =	 "x" # may # {x} #"x"
}
__EOF__
	   expected_out	=> <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= "Gerd Neugebauer",
  year		= "x" # may # {x} # "x"
}
__EOF__
	   expected_err	=> ""
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'bibtool_special_underscore',
	   bib		=> <<__EOF__,
\@Manual{BibTool,
  _title = 	 {BibTool},
  author =	 "Gerd Neugebauer",
  year =	 "x"
}
__EOF__
	   expected_out	=> <<__EOF__,

\@Manual{	  bibtool,
  _title	= {BibTool},
  author	= "Gerd Neugebauer",
  year		= "x"
}
__EOF__
	   expected_err	=> <<__EOF__

  _title = 	 {BibTool},
___^
*** BibTool WARNING:  (line 2 in ./_test.bib): Symbol does not start with a letter
__EOF__
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'bibtool_special_dollar',
	   bib		=> <<__EOF__,
\@Manual{BibTool,
  \$title = 	 {BibTool},
  author =	 "Gerd Neugebauer",
  year =	 "x"
}
__EOF__
	   expected_out	=> <<__EOF__,

\@Manual{	  bibtool,
  \$title	= {BibTool},
  author	= "Gerd Neugebauer",
  year		= "x"
}
__EOF__
	   expected_err	=> <<__EOF__

  \$title = 	 {BibTool},
___^
*** BibTool WARNING:  (line 2 in ./_test.bib): Symbol does not start with a letter
__EOF__
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'bibtool_special_exclamation',
	   bib		=> <<__EOF__,
\@Manual{BibTool,
  !title = 	 {BibTool},
  author =	 "Gerd Neugebauer",
  year =	 "x"
}
__EOF__
	   expected_out	=> <<__EOF__,

\@Manual{	  bibtool,
  !title	= {BibTool},
  author	= "Gerd Neugebauer",
  year		= "x"
}
__EOF__
	   expected_err	=> <<__EOF__

  !title = 	 {BibTool},
___^
*** BibTool WARNING:  (line 2 in ./_test.bib): Symbol does not start with a letter
__EOF__
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
