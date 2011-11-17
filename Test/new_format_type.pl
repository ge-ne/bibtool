#!/usr/bin/perl -w
##*****************************************************************************
## $Id: new_format_type.pl,v 1.2 2011-11-17 17:45:22 gene Exp $
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
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  AU.SO.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'new_format_type_f2',
	   resource	=> <<__EOF__ ,
new.format.type = {9="\%+f"}
key.format={\%.9p(author)}
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  x,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  AU.SO.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'new_format_type_f3',
	   resource	=> <<__EOF__ ,
new.format.type = {9="\%f[:][-][;]"}
key.format={\%.9p(author)}
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  x,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  :A-U;.:S-O;.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'new_format_type_f4',
	   resource	=> <<__EOF__ ,
new.format.type = {9="\%2f"}
key.format={\%.9p(author)}
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  x,
  author	= "Allan Uwe Thor and Stan Oliver Meone and others"
}
__EOF__
           expected_err	=> '',
	   expected_out => <<__EOF__ );

\@Misc{		  AlUw.StOl.ea,
  author	= "Allan Uwe Thor and Stan Oliver Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'new_format_type_l1',
	   resource	=> <<__EOF__ ,
new.format.type = {9="\%l"}
key.format={\%.9p(author)}
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  x,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__
           expected_err	=> '',
	   expected_out	=> <<__EOF__ );

\@Misc{		  Thor.Meone.ea,
  author	= "A. U. Thor and S. O. Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'new_format_type_v1',
	   resource	=> <<__EOF__ ,
new.format.type = {9="\%v"}
key.format={\%.9p(author)}
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  x,
  author	= "A. U. de Thor and S. O. de la Meone and others"
}
__EOF__
           expected_err	=> '',
	   expected_out	=> <<__EOF__ );

\@Misc{		  de.dela.ea,
  author	= "A. U. de Thor and S. O. de la Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'new_format_type_v3',
	   resource	=> <<__EOF__ ,
new.format.type = {9="\%v[:][-][;]"}
key.format={\%.9p(author)}
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  x,
  author	= "A. U. de Thor and S. O. de la Meone and others"
}
__EOF__
           expected_err	=> '',
	   expected_out	=> <<__EOF__ );

\@Misc{		  :de;.:de-la;.ea,
  author	= "A. U. de Thor and S. O. de la Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'new_format_type_v4',
	   resource	=> <<__EOF__ ,
new.format.type = {9="\%1v"}
key.format={\%.9p(author)}
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  x,
  author	= "A. U. de Thor and S. O. de la Meone and others"
}
__EOF__
           expected_err	=> '',
	   expected_out	=> <<__EOF__ );

\@Misc{		  d.dl.ea,
  author	= "A. U. de Thor and S. O. de la Meone and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'new_format_type_j1',
	   resource	=> <<__EOF__ ,
new.format.type = {9="\%v"}
key.format={\%.9p(author)}
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  x,
  author	= "A. U., Thor, jr. and S. O., Meone, sen. and others"
}
__EOF__
           expected_err	=> '',
	   expected_out	=> <<__EOF__ );

\@Misc{		  jr.sen.ea,
  author	= "A. U., Thor, jr. and S. O., Meone, sen. and others"
}
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'new_format_type_j3',
	   resource	=> <<__EOF__ ,
new.format.type = {9="\%v[:][-][;]"}
key.format={\%.9p(author)}
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  x,
  author	= "A. U., Thor, jr. and S. O., Meone, sen. and others"
}
__EOF__
           expected_err	=> '',
	   expected_out	=> <<__EOF__ );

\@Misc{		  :jr;.:sen;.ea,
  author	= "A. U., Thor, jr. and S. O., Meone, sen. and others"
}
__EOF__


#------------------------------------------------------------------------------
BUnit::run(name         => 'new_format_type_j4',
	   resource	=> <<__EOF__ ,
new.format.type = {9="\%1v"}
key.format={\%.9p(author)}
__EOF__
	   bib 	        => <<__EOF__ ,
\@Misc{		  x,
  author	= "A. U., Thor, jr. and S. O., Meone, sen. and others"
}
__EOF__
           expected_err	=> '',
	   expected_out	=> <<__EOF__ );

\@Misc{		  j.s.ea,
  author	= "A. U., Thor, jr. and S. O., Meone, sen. and others"
}
__EOF__


1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
