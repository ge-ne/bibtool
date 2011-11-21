#!/bin/perl -W
#******************************************************************************
# $Id: resource.t,v 1.1 2011-11-21 20:31:03 gene Exp $
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
use BUnit;


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
# Local Variables: 
# mode: perl
# End: 
