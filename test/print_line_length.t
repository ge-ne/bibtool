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
use BUnit;

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
BUnit::run(name  => 'print_line_length-10',
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
BUnit::run(name  => 'print_line_length-10b',
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
