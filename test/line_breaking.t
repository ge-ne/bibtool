#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2015 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

line_breaking.t - Test suite for BibTool applying line breaking during printing.

=head1 SYNOPSIS

line_breaking.t 

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
BUnit::run(name  => 'line_breaking-1',
    args         => '',
    expected_err => '',
    bib	         => <<__EOF__,
\@Article{key,
  title = {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa x}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  key,
  title		= {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa x}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'line_breaking-2',
    args         => '',
    expected_err => '',
    bib	         => <<__EOF__,
\@Article{key,
  title = {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa x}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  key,
  title		= {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa x}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'line_breaking-3',
    args         => '',
    expected_err => '',
    bib	         => <<__EOF__,
\@Article{key,
  title = {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa x}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  key,
  title		= {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa x}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'line_breaking-4',
    args         => '',
    expected_err => '',
    bib	         => <<__EOF__,
\@Article{key,
  title = {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa x}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  key,
  title		= {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa x}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'line_breaking-5',
    args         => '',
    expected_err => '',
    bib	         => <<__EOF__,
\@Article{key,
  title = {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa x}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  key,
  title		= {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa x}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'line_breaking-6',
    args         => '',
    expected_err => '',
    bib	         => <<__EOF__,
\@Article{key,
  title = {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa x}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  key,
  title		= {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
		  x}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'line_breaking-7',
    args         => '',
    expected_err => '',
    bib	         => <<__EOF__,
\@Article{key,
  title = {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa x}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  key,
  title		= {aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
		  x}
}
__EOF__



#------------------------------------------------------------------------------
BUnit::run(name  => 'line_breaking-11',
    args         => '',
    expected_err => '',
    bib	         => <<__EOF__,
\@Article{key,
  title = {x aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}
}
__EOF__
    expected_out => <<__EOF__);

\@Article{	  key,
  title		= {x aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa}
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name  => 'line_breaking-12',
    args         => '',
    expected_err => '',
    bib	         => <<__EOF__,
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


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
