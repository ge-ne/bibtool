#!/usr/bin/perl -w
##*****************************************************************************
## $Id: print_indent.pl,v 1.1 2011-11-19 06:50:26 gene Exp $
##*****************************************************************************
## Author: Gerd Neugebauer
##=============================================================================

=head1 NAME

print_indent.pl - Test suite for BibTool print.indent.

=head1 SYNOPSIS

print_indent.pl

=head1 DESCRIPTION

=head1 OPTIONS

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


#------------------------------------------------------------------------------
BUnit::run(name         => 'print_indent_1',
	   resource	=> <<__EOF__ ,
print.indent = 0
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  xxx,
author		= "A. U. Thor"
}
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'print_indent_2',
	   resource	=> <<__EOF__ ,
print.indent = 8
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  xxx,
	author	= "A. U. Thor"
}
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'print_indent_3',
	   resource	=> <<__EOF__ ,
print.indent = 16
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


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
