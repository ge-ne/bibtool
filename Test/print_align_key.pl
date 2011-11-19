#!/usr/bin/perl -w
##*****************************************************************************
## $Id: print_align_key.pl,v 1.1 2011-11-19 06:44:09 gene Exp $
##*****************************************************************************
## Author: Gerd Neugebauer
##=============================================================================

=head1 NAME

print_align_key.pl - Test suite for BibTool print.align.key.

=head1 SYNOPSIS

print_align_key.pl

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
BUnit::run(name         => 'print_align_key_f1',
	   resource	=> <<__EOF__ ,
print.align.key = 0
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{xxx,
  author	= "A. U. Thor"
}
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'print_align_key_f1',
	   resource	=> <<__EOF__ ,
print.align.key = 1
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{xxx,
  author	= "A. U. Thor"
}
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'print_align_key_f1',
	   resource	=> <<__EOF__ ,
print.align.key = 24
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  xxx,
  author	= "A. U. Thor"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{			xxx,
  author	= "A. U. Thor"
}
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
