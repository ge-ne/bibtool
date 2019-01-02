#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2011-2019 Gerd Neugebauer
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
use BUnit;use warnings;


#------------------------------------------------------------------------------
BUnit::run(name     => 'check_rule_1',
	   resource => <<__EOF__,
check.rule { year "^[\\"{]1[89][0-9][0-9][\\"}]\$" }
check.rule { year "^[\\"{][0-9][0-9][\\"}]\$" }
check.rule { year "" "\\@ \\\$: Year has to be a suitable number"}
__EOF__
	   bib	   => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "2011"
}
__EOF__
    expected_err => "*** BibTool (line 1 in _test.bib): Manual bibtool: Year has to be a suitable number\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'check_rule_2',
	   resource => <<__EOF__,
check.rule { year "^[\\"{]1[89][0-9][0-9][\\"}]\$" }
check.rule { year "^[\\"{][0-9][0-9][\\"}]\$" }
check.rule { year "" "\\@ \\\$: Year has to be a suitable number"}
__EOF__
	   bib	   => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "1987"
}
__EOF__
    expected_err => ''
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'check_rule_3',
	   resource => <<__EOF__,
check.rule { year "^[\\"{]1[89][0-9][0-9][\\"}]\$" }
check.rule { year "^[\\"{][0-9][0-9][\\"}]\$" }
check.rule { year "" "\\@ \\\$: Year has to be a suitable number"}
__EOF__
	   bib	   => <<__EOF__,
\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "xxx"
}
__EOF__
    expected_err => "*** BibTool (line 1 in _test.bib): Manual bibtool: Year has to be a suitable number\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'check_rule_4',
	   resource => <<__EOF__,
check.rule { year "^[\\"{]20[0-9][0-9][\\"}]\$" }
check.rule { year "^[\\"{][0-9][0-9][\\"}]\$" }
check.rule { year "" "\\@ \\\$: Year has to be a suitable number"}
__EOF__
	   bib	   => <<__EOF__,


\@Manual{BibTool,
  title = 	 {BibTool},
  author =	 {Gerd Neugebauer},
  year =	 "xxx"
}
__EOF__
    expected_err => "*** BibTool (line 3 in _test.bib): Manual bibtool: Year has to be a suitable number\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'check_rule_5',
	   stdin    => 1,
	   resource => <<__EOF__,
check.rule { year "^[\\"{]20[0-9][0-9][\\"}]\$" }
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
    expected_err => "*** BibTool (line 3 in <STDIN>): Manual bibtool: Year has to be a suitable number\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name     => 'check_rule_6',
	   stdin    => 1,
	   resource => <<__EOF__,
sort = true
check.rule { year "^[\\"{]20[0-9][0-9][\\"}]\$" }
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
    expected_err => "*** BibTool (line 3 in <STDIN>): Manual bibtool: Year has to be a suitable number\n"
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
