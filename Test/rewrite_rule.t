#!/bin/perl -W
#******************************************************************************
# $Id: rewrite_rule.t,v 1.1 2011-11-20 15:22:45 gene Exp $
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

rewrite.t - Test suite for BibTool rewrite.

=head1 SYNOPSIS

rewrite.t 

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
BUnit::run(name => 'rewrite_rule_1',
    args	 => 'bib/x1.bib',
    resource 	 => 'rewrite.rule={"01"}',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer}
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_rule_2',
    args	 => 'bib/x1.bib',
    resource 	 => 'rewrite.rule={"G.* N[a-z]*" # "A.U. Thor"}',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {A.U. Thor},
  year		= 2011
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_rule_3',
    args	 => 'bib/x1.bib',
    resource 	 => 'rewrite.rule={author title # "G.* N[a-z]*" # "A.U. Thor"}',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {A.U. Thor},
  year		= 2011
}
__EOF__
    expected_err => '' );

#------------------------------------------------------------------------------
BUnit::run(name => 'rewrite_rule_4',
    args	 => 'bib/x1.bib',
    resource 	 => 'rewrite.rule={title # "G.* N[a-z]*" # "A.U. Thor"}',
    expected_out => <<__EOF__,

\@Manual{	  bibtool,
  title		= {BibTool},
  author	= {Gerd Neugebauer},
  year		= 2011
}
__EOF__
    expected_err => '' );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
