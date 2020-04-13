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

select_crossrefs.t - Test suite for BibTool select.crossrefs.

=head1 SYNOPSIS

select_crossrefs.t 

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
BUnit::run(name  => 'select_crossrefs_0',
    args         => '--select\'{"aa"}\' -- select.crossrefs=off',
    expected_err =>'',
    bib	         => <<__EOF__,
\@article{ a,
  author  = "aa",
  title	  = "the title",
  crossref= "b"
}
\@article{ b,
  author = "bb",
  title	 = "THE TITLE"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  a,
  author	= "aa",
  title		= "the title",
  crossref	= "b"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_crossrefs_1',
    args         => '--select\'{"aa"}\' -- select.crossrefs=on',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ a,
  author  = "aa",
  title	  = "the title",
  crossref= "b"
}
\@article{ b,
  author = "bb",
  title	 = "THE TITLE"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  a,
  author	= "aa",
  title		= "the title",
  crossref	= "b"
}

\@Article{	  b,
  author	= "bb",
  title		= "THE TITLE"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_crossrefs_2',
    args         => '--select\'{"aa"}\' -- select.crossrefs=on',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ a,
  author  = "aa",
  title	  = "the title",
  crossref= "b"
}
\@article{ b,
  author  = "bb",
  title	  = "THE title",
  crossref= "c"
}
\@article{ c,
  author = "cc",
  title	 = "THE TITLE"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  a,
  author	= "aa",
  title		= "the title",
  crossref	= "b"
}

\@Article{	  b,
  author	= "bb",
  title		= "THE title",
  crossref	= "c"
}

\@Article{	  c,
  author	= "cc",
  title		= "THE TITLE"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => '_X_c_1',
    args         => '-X aa -c',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ aa,
  author  = "aa",
  title	  = "the title",
  crossref= "b"
}
\@article{ b,
  author = "bb",
  title	 = "THE TITLE"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  aa,
  author	= "aa",
  title		= "the title",
  crossref	= "b"
}

\@Article{	  b,
  author	= "bb",
  title		= "THE TITLE"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => '_X_c_2',
    args         => '-X aa -c',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ aa,
  author  = "aa",
  title	  = "the title",
  crossref= "b"
}
\@article{ b,
  author  = "bb",
  title	  = "THE title",
  crossref= "c"
}
\@article{ c,
  author = "cc",
  title	 = "THE TITLE"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  aa,
  author	= "aa",
  title		= "the title",
  crossref	= "b"
}

\@Article{	  b,
  author	= "bb",
  title		= "THE title",
  crossref	= "c"
}

\@Article{	  c,
  author	= "cc",
  title		= "THE TITLE"
}
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
