#!/usr/bin/env perl
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2020 Gerd Neugebauer
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

print_align.t - Test suite for BibTool print.align.

=head1 SYNOPSIS

print_align.t

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
use BUnit;use warnings;



#------------------------------------------------------------------------------
BUnit::run(name         => 'print_align_1',
	   resource	=> <<__EOF__ ,
print.align = 0
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  xxx,
  author="A. U. Thor"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_align_2',
	   resource	=> <<__EOF__ ,
print.align = 12
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  xxx,
  author  = "A. U. Thor"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_align_err_1',
	   resource	=> <<__EOF__ ,
print.align = illegal
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor"
}
__EOF__
           expected_err	=> "*** BibTool: Illegal print.align ignored.\n",
	   expected_out => <<__EOF__ );

\@Misc{		  xxx,
  author	= "A. U. Thor"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_align_auto_1',
	   resource	=> <<__EOF__ ,
print.align = auto
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  xxx,
  author="A. U. Thor"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_align_auto_2',
	   resource	=> <<__EOF__ ,
print.align = auto
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor",
  title	= "The title"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  xxx,
  author="A. U. Thor",
  title	="The title"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_align_auto_3',
	   resource	=> <<__EOF__ ,
print.align = auto
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor",
  title	= "The title",
  a-very-long-field-name	= "The value"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  xxx,
  author		="A. U. Thor",
  title			="The title",
  a-very-long-field-name="The value"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_align_auto_11',
	   resource	=> <<__EOF__ ,
print.align = auto
print.wide.equal = true
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  xxx,
  author = "A. U. Thor"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'print_align_auto_12',
	   resource	=> <<__EOF__ ,
print.align = auto
print.wide.equal = true
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor",
  title	= "The title"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  xxx,
  author = "A. U. Thor",
  title	 = "The title"
}
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
