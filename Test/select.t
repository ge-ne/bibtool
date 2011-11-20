#!/bin/perl -W
#******************************************************************************
# $Id: select.t,v 1.1 2011-11-20 15:22:45 gene Exp $
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

select.t - Test suite for BibTool select.

=head1 SYNOPSIS

select.t 

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
BUnit::run(name  => '_X_0',
    args         => '-X',
    expected_err => <<__EOF__);

*** BibTool WARNING: Missing pattern.
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => '_X_1',
    args         => '-X aa',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ aaa,
  author = "aa",
  title	 = "the title"
}
\@article{ aba,
  author = "bb",
  title	 = "Just another text"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  aaa,
  author	= "aa",
  title		= "the title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => '_X_2',
    args         => '-X a+a+',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ aaa,
  author = "aa",
  title	 = "the title"
}
\@article{ aba,
  author = "bb",
  title	 = "Just another text"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  aaa,
  author	= "aa",
  title		= "the title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_1',
    args         => '--select\'{"aa"}\'',
    expected_err => '',
    bib	         => <<__EOF__,
\@article{ a,
  author = "aa",
  title	 = "the title"
}
\@article{ b,
  author = "bb",
  title	 = "THE TITLE"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  a,
  author	= "aa",
  title		= "the title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_2',
    args         => '--select\'{"title"}\'',
    expected_err =>'',
    bib	         => <<__EOF__,
\@article{ a,
  author = "aa",
  title	 = "the title"
}
\@article{ b,
  author = "bb",
  title	 = "Just another text"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  a,
  author	= "aa",
  title		= "the title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'select_3',
    args         => '--select\'{"t.*le"}\'',
    expected_err =>'',
    bib	         => <<__EOF__,
\@article{ a,
  author = "aa",
  title	 = "the title"
}
\@article{ b,
  author = "bb",
  title	 = "Just another text"
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  a,
  author	= "aa",
  title		= "the title"
}
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
