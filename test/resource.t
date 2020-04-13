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

resource.t - Test suite for BibTool resource.

=head1 SYNOPSIS

resource.t 

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
BUnit::run(name         => 'resource_1',
	   resource	=> <<__EOF__,
resource{_rsc.rsc}
__EOF__
	   prepare 	=> sub {
	     BUnit::store_file('_rsc.rsc','print{Been there}');
	   },
	   check 	=> sub {
	     unlink('_rsc.rsc');
	     return 0;
	   },
	   expected_err	=> "Been there\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name         => '_r_1',
	   args		=> "-r _rsc.rsc",
	   prepare 	=> sub {
	     BUnit::store_file('_rsc.rsc','print{Been there}');
	   },
	   check 	=> sub {
	     unlink('_rsc.rsc');
	     return 0;
	   },
	   expected_err	=> "Been there\n"
    );

#------------------------------------------------------------------------------
BUnit::run(name         => '_r_2',
	   args		=> "-r _rsc",
	   prepare 	=> sub {
	     BUnit::store_file('_rsc.rsc','print{Been there}');
	   },
	   check 	=> sub {
	     unlink('_rsc.rsc');
	     return 0;
	   },
	   expected_err	=> "Been there\n"
    );

#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
