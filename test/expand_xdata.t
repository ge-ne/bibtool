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

expand_xdata.t - Test suite for BibTool expand.xdata.

=head1 SYNOPSIS

expand_xdata.t 

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
BUnit::run(name => 'expand_xdata_1',
    resource => <<__EOF__,
new.entry.type{XData}
expand.xdata =true
__EOF__
    bib		=> <<__EOF__,
\@Manual{	  bibtool,
  booktitle	= {The Title},
  xdata		= {x}
}
\@XData{ x,
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}
__EOF__
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  booktitle	= {The Title},
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}

__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'expand_xdata_2',
    resource => <<__EOF__,
new.entry.type{XData}
expand.xdata =true
__EOF__
    bib		=> <<__EOF__,
\@Manual{	  bibtool,
  title		= {The Title},
  xdata		= {x}
}
\@XData{ x,
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}
__EOF__
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {The Title},
  author	= {Gerd Neugebauer}
}

__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'expand_xdata_3',
    resource => <<__EOF__,
new.entry.type{XData}
expand.xdata =true
__EOF__
    bib		=> <<__EOF__,
\@Manual{	  bibtool,
  xdata		= {x,y}
}
\@XData{ x,
  title		= {BibTool}
}
\@XData{ y,
  author	= {Gerd Neugebauer}
}
__EOF__
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
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
