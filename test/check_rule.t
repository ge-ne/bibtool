#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2014 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

check_rule.t - Test suite for BibTool check.rule.

=head1 SYNOPSIS

check_rule.t 

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
BUnit::run(name         => 'check_rule_1',
	   resource     => <<__EOF__,
check.rule { year "^[\\"{]1[89][0-9][0-9][\\"}]\$" }
check.rule { year "^[\\"{][0-9][0-9][\\"}]\$" }
check.rule { year "" "\\@ \\\$: Year has to be a suitable number"}
__EOF__
	   bib				    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2011"
}
__EOF__
    expected_err => '*** BibTool: Manual bibtool: Year has to be a suitable number'
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'check_rule_2',
	   resource     => <<__EOF__,
check.rule { year "^[\\"{]1[89][0-9][0-9][\\"}]\$" }
check.rule { year "^[\\"{][0-9][0-9][\\"}]\$" }
check.rule { year "" "\\@ \\\$: Year has to be a suitable number"}
__EOF__
	   bib				    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "1987"
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name         => 'check_rule_3',
	   resource     => <<__EOF__,
check.rule { year "^[\\"{]1[89][0-9][0-9][\\"}]\$" }
check.rule { year "^[\\"{][0-9][0-9][\\"}]\$" }
check.rule { year "" "\\@ \\\$: Year has to be a suitable number"}
__EOF__
	   bib				    => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "xxx"
}
__EOF__
    expected_err => '*** BibTool: Manual bibtool: Year has to be a suitable number'
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
