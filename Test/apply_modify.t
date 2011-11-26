#!/bin/perl -W
#******************************************************************************
# $Id: apply_modify.t,v 1.1 2011-11-26 06:21:15 gene Exp $
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

apply_modify.t - Test suite for BibTool apply.modify.

=head1 SYNOPSIS

apply_modify.t 

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
BUnit::run(name  => 'apply_modify_0',
    bib		 => <<__EOF__,
\@article{xyzzy, a=987}
\@modify{xyzzy, a=123}
__EOF__
    resource	 => 'apply.modify=off',
    expected_out => <<__EOF__,

\@Article{	  xyzzy,
  a		= 987
}
\@MODIFY{	  xyzzy,
  a		= 123
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name  => 'apply_modify_1',
    bib		 => <<__EOF__,
\@article{xyzzy, a=987}
\@modify{xyzzy, a=123}
__EOF__
    resource	 => 'apply.modify=on',
    expected_out => <<__EOF__,

\@Article{	  xyzzy,
  a		= 123
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name  => 'apply_modify_2',
    bib		 => <<__EOF__,
\@article{xyzzy, a=987}
\@modify{xyzzy, b=123}
__EOF__
    resource	 => 'apply.modify=on',
    expected_out => <<__EOF__,

\@Article{	  xyzzy,
  a		= 987,
  b		= 123
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name  => 'apply_modify_3',
    bib		 => <<__EOF__,
\@article{xyzzy, a=987}
\@alias{qqq=xyzzy}
\@modify{xyzzy, a=123}

__EOF__
    resource	 => 'apply.modify=on apply.alias=on',
    expected_out => <<__EOF__,

\@Article{	  xyzzy,
  a		= 123
}

\@Article{	  qqq,
  a		= 987
}
__EOF__
    expected_err => '' );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
