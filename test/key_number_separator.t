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

key_number_separator.t - Test suite for BibTool key.number.separator.

=head1 SYNOPSIS

key_number_separator.t

=head1 DESCRIPTION

This module contains some test cases. Running this module as program
will run all test cases and print a summary for each. Optionally files
*.out and *.err are left if the expected result does not match the
actual result.

=head1 OPTIONS

none

=head1 AUTHOR

Gerd Neugebauer

=head1 BUGS

=over 4

=item *

...

=back

=cut

use strict;
use BUnit;

use constant BIB2 => <<__EOF__;
\@Misc{		  xxx,
  author	= "A. U. Thor"
}
\@Misc{		  xxx,
  author	= "A. U. Thor"
}
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'key_number_separator_digit1',
	   resource	=> <<__EOF__ ,
key.number.separator = {--}
key.base = digit
key.format=short
__EOF__
	   bib 	        => BIB2,
	   expected_out => <<__EOF__ );

\@Misc{		  thor,
  author	= "A. U. Thor"
}

\@Misc{		  thor--1,
  author	= "A. U. Thor"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_number_separator_upper1',
	   resource	=> <<__EOF__ ,
key.number.separator = {--}
key.base = upper
key.format=short
__EOF__
	   bib 	        => BIB2,
	   expected_out => <<__EOF__ );

\@Misc{		  thor,
  author	= "A. U. Thor"
}

\@Misc{		  thor--A,
  author	= "A. U. Thor"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_number_separator_lower2',
	   resource	=> <<__EOF__ ,
key.number.separator = {--}
key.base = lower
key.format=short
__EOF__
	   bib 	        => BIB2,
	   expected_out => <<__EOF__ );

\@Misc{		  thor,
  author	= "A. U. Thor"
}

\@Misc{		  thor--a,
  author	= "A. U. Thor"
}
__EOF__

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
