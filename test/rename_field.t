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

rename_field.t - Test suite for BibTool rename.field.

=head1 SYNOPSIS

rename_field.t 

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
BUnit::run(name => 'rename_field_0',
    args	 => 'bib/x1.bib',
    resource 	 => 'rename.field={xyzzy = booktitle}',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2015
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rename_field_1',
    args	 => 'bib/x1.bib',
    resource 	 => 'rename.field={title = booktitle}',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  booktitle	= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2015
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rename_field_2',
    args	 => 'bib/x1.bib',
    resource 	 => 'rename.field={Title = booktitle}',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  booktitle	= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2015
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rename_field_10',
    args	 => 'bib/x1.bib',
    resource 	 => 'rename.field={Title = booktitle # $type "manual"}',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  booktitle	= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2015
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rename_field_11',
    args	 => 'bib/x1.bib',
    resource 	 => 'rename.field={Title = booktitle # $type "book"}',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2015
}
__EOF__
    expected_err => '' );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
