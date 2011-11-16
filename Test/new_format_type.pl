#!/usr/bin/perl -w
##*****************************************************************************
## $Id: new_format_type.pl,v 1.1 2011-11-16 18:51:06 gene Exp $
##*****************************************************************************
## Author: Gerd Neugebauer
##=============================================================================

=head1 NAME

new_format_type.pl - Test suite for BibTool new.format.type.

=head1 SYNOPSIS

new_format_type.pl

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
BUnit::run(name         => 'new_format_type_f1',
	   resource	=> <<__EOF__ ,
new.format.type = {9="\%f"}
key.format={\%.9p(author)}
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  x,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__
	   expected_out => <<__EOF__ );

\@Misc{		  AU.SO.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
