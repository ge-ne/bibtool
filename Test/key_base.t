#!/bin/perl -W
#******************************************************************************
# $Id: key_base.t,v 1.2 2013-11-24 21:40:14 gene Exp $
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

key_base.t - Test suite for BibTool key.base.

=head1 SYNOPSIS

key_base.t

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
BUnit::run(name         => 'key_base_digit1',
	   resource	=> <<__EOF__ ,
key.base = digit
key.format=short
__EOF__
	   bib 	        => BIB2,
	   expected_out => <<__EOF__ );

\@Misc{		  thor,
  author	= "A. U. Thor"
}

\@Misc{		  thor*1,
  author	= "A. U. Thor"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_base_digit2',
	   resource	=> <<__EOF__ ,
key.base = digit
key.format=short
__EOF__
	   bib 	        =>
	   BIB2.BIB2.BIB2.BIB2.BIB2.BIB2, 
	   expected_out => <<__EOF__ );

\@Misc{		  thor,
  author	= "A. U. Thor"
}

\@Misc{		  thor*1,
  author	= "A. U. Thor"
}

\@Misc{		  thor*2,
  author	= "A. U. Thor"
}

\@Misc{		  thor*3,
  author	= "A. U. Thor"
}

\@Misc{		  thor*4,
  author	= "A. U. Thor"
}

\@Misc{		  thor*5,
  author	= "A. U. Thor"
}

\@Misc{		  thor*6,
  author	= "A. U. Thor"
}

\@Misc{		  thor*7,
  author	= "A. U. Thor"
}

\@Misc{		  thor*8,
  author	= "A. U. Thor"
}

\@Misc{		  thor*9,
  author	= "A. U. Thor"
}

\@Misc{		  thor*10,
  author	= "A. U. Thor"
}

\@Misc{		  thor*11,
  author	= "A. U. Thor"
}
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'key_base_upper1',
	   resource	=> <<__EOF__ ,
key.base = upper
key.format=short
__EOF__
	   bib 	        => BIB2,
	   expected_out => <<__EOF__ );

\@Misc{		  thor,
  author	= "A. U. Thor"
}

\@Misc{		  thor*A,
  author	= "A. U. Thor"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_base_upper2',
	   resource	=> <<__EOF__ ,
key.base = upper
key.format=short
__EOF__
	   bib 	        =>
	   BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.
	   BIB2, 
	   expected_out => <<__EOF__ );

\@Misc{		  thor,
  author	= "A. U. Thor"
}

\@Misc{		  thor*A,
  author	= "A. U. Thor"
}

\@Misc{		  thor*B,
  author	= "A. U. Thor"
}

\@Misc{		  thor*C,
  author	= "A. U. Thor"
}

\@Misc{		  thor*D,
  author	= "A. U. Thor"
}

\@Misc{		  thor*E,
  author	= "A. U. Thor"
}

\@Misc{		  thor*F,
  author	= "A. U. Thor"
}

\@Misc{		  thor*G,
  author	= "A. U. Thor"
}

\@Misc{		  thor*H,
  author	= "A. U. Thor"
}

\@Misc{		  thor*I,
  author	= "A. U. Thor"
}

\@Misc{		  thor*J,
  author	= "A. U. Thor"
}

\@Misc{		  thor*K,
  author	= "A. U. Thor"
}

\@Misc{		  thor*L,
  author	= "A. U. Thor"
}

\@Misc{		  thor*M,
  author	= "A. U. Thor"
}

\@Misc{		  thor*N,
  author	= "A. U. Thor"
}

\@Misc{		  thor*O,
  author	= "A. U. Thor"
}

\@Misc{		  thor*P,
  author	= "A. U. Thor"
}

\@Misc{		  thor*Q,
  author	= "A. U. Thor"
}

\@Misc{		  thor*R,
  author	= "A. U. Thor"
}

\@Misc{		  thor*S,
  author	= "A. U. Thor"
}

\@Misc{		  thor*T,
  author	= "A. U. Thor"
}

\@Misc{		  thor*U,
  author	= "A. U. Thor"
}

\@Misc{		  thor*V,
  author	= "A. U. Thor"
}

\@Misc{		  thor*W,
  author	= "A. U. Thor"
}

\@Misc{		  thor*X,
  author	= "A. U. Thor"
}

\@Misc{		  thor*Y,
  author	= "A. U. Thor"
}

\@Misc{		  thor*Z,
  author	= "A. U. Thor"
}

\@Misc{		  thor*A_,
  author	= "A. U. Thor"
}
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'key_base_lower1',
	   resource	=> <<__EOF__ ,
key.base = lower
key.format=short
__EOF__
	   bib 	        => BIB2,
	   expected_out => <<__EOF__ );

\@Misc{		  thor,
  author	= "A. U. Thor"
}

\@Misc{		  thor*a,
  author	= "A. U. Thor"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'key_base_lower2',
	   resource	=> <<__EOF__ ,
key.base = lower
key.format=short
__EOF__
	   bib 	        =>
	   BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.BIB2.
	   BIB2, 
	   expected_out => <<__EOF__ );

\@Misc{		  thor,
  author	= "A. U. Thor"
}

\@Misc{		  thor*a,
  author	= "A. U. Thor"
}

\@Misc{		  thor*b,
  author	= "A. U. Thor"
}

\@Misc{		  thor*c,
  author	= "A. U. Thor"
}

\@Misc{		  thor*d,
  author	= "A. U. Thor"
}

\@Misc{		  thor*e,
  author	= "A. U. Thor"
}

\@Misc{		  thor*f,
  author	= "A. U. Thor"
}

\@Misc{		  thor*g,
  author	= "A. U. Thor"
}

\@Misc{		  thor*h,
  author	= "A. U. Thor"
}

\@Misc{		  thor*i,
  author	= "A. U. Thor"
}

\@Misc{		  thor*j,
  author	= "A. U. Thor"
}

\@Misc{		  thor*k,
  author	= "A. U. Thor"
}

\@Misc{		  thor*l,
  author	= "A. U. Thor"
}

\@Misc{		  thor*m,
  author	= "A. U. Thor"
}

\@Misc{		  thor*n,
  author	= "A. U. Thor"
}

\@Misc{		  thor*o,
  author	= "A. U. Thor"
}

\@Misc{		  thor*p,
  author	= "A. U. Thor"
}

\@Misc{		  thor*q,
  author	= "A. U. Thor"
}

\@Misc{		  thor*r,
  author	= "A. U. Thor"
}

\@Misc{		  thor*s,
  author	= "A. U. Thor"
}

\@Misc{		  thor*t,
  author	= "A. U. Thor"
}

\@Misc{		  thor*u,
  author	= "A. U. Thor"
}

\@Misc{		  thor*v,
  author	= "A. U. Thor"
}

\@Misc{		  thor*w,
  author	= "A. U. Thor"
}

\@Misc{		  thor*x,
  author	= "A. U. Thor"
}

\@Misc{		  thor*y,
  author	= "A. U. Thor"
}

\@Misc{		  thor*z,
  author	= "A. U. Thor"
}

\@Misc{		  thor*a_,
  author	= "A. U. Thor"
}
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
