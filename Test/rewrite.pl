#!/bin/perl -W
#******************************************************************************
# $Id: rewrite.pl,v 1.1 2011-09-25 13:41:53 gene Exp $
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

rewrite.pl - Test suite for BibTool rewrite.

=head1 SYNOPSIS

rewrite.pl 

=head1 DESCRIPTION

=head1 OPTIONS

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;


#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_add_field_1',
    args	      => 'x1.bib',
    resource 	      => 'add.field={xyzzy="abc"}',
    expected_out      => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011,
  xyzzy		= {abc}
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_add_field_2',
    args	      => 'x1.bib',
    resource 	      => 'add.field={xyzzy={abc}}',
    expected_out      => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011,
  xyzzy		= {abc}
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_add_field_3',
    args	      => 'x1.bib',
    resource 	      => 'add.field={xyzzy=abc}',
    expected_out      => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011,
  xyzzy		= {abc}
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_delete_field_1',
    args	 => 'x1.bib',
    resource 	 => 'delete.field={xyzzy}',
    expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_delete_field_2',
    args	 => 'x1.bib',
    resource 	 => 'delete.field={year}',
    expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_rewrite_1',
    args	 => 'x1.bib',
    resource 	 => 'rewrite.rule={"01"}',
    expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_rewrite_2',
    args	 => 'x1.bib',
    resource 	 => 'rewrite.rule={"G.* N[a-z]*" # "A.U. Thor"}',
    expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {A.U. Thor},
  year		= 2011
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_rewrite_3',
    args	 => 'x1.bib',
    resource 	 => 'rewrite.rule={author title # "G.* N[a-z]*" # "A.U. Thor"}',
    expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {A.U. Thor},
  year		= 2011
}
EOF
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_rewrite_4',
    args	 => 'x1.bib',
    resource 	 => 'rewrite.rule={title # "G.* N[a-z]*" # "A.U. Thor"}',
    expected_out => <<EOF,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011
}
EOF
    expected_err => '' );


#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
