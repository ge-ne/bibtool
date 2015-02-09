#!/usr/bin/perl
#------------------------------------------------------------------------------
#
# This file is part of BibTool.
# It is distributed under the GNU General Public License.
# See the file COPYING for details.
#
# (c) 1997-2015 Gerd Neugebauer
#
# Net: gene@gerd-neugebauer.de
#
#*****************************************************************************

foreach $_ (@ARGV)
{ print stderr "$_\n";
  &analyze_file($_);
}

sub analyze_file
{ local ($file) = @_;
  local (%purpose,$name,%function,%macro,%variable,$state);
  
  open(FD,$file) || return;

  $file =~ s/_/\\_/go;
  $file =~ s/^\.\.\///o;
  $file =~ s/^include\///o;
  $_ = $file;
  s/[^.a-zA-Z0-9]//go;

  if    ( /\.c$/ ) { print "\n\\Module{$file}{$_}\n\n"; }
  elsif ( /\.h$/ ) { print "\n\\Header{$file}{$_}\n\n"; }
  else             { print "\n\\File{$file}{$_}\n\n"; }

  $state = 0;
  while (<FD>)
  {
    if (/^\*\*/o)
    {
      if (/^\*\* Function:[ 	]*([a-zA-Z0-9_]+)/o)
      { $name = $1;
	$name =~ s/_/\\_/go;
	$source{$name}   = $file;
	$type{$name}     = 0;
	$function{$name} = 1
      }
      elsif (/^\*\* Macro:[ 	]*([a-zA-Z0-9_]+)/o)
      { $name = $1;
	$name =~ s/_/\\_/go;
	$source{$name} = $file;
	$type{$name}   = 10;
	$macro{$name}  = 1;
      }
      elsif (/^\*\* Constant:[ 	]*([a-zA-Z0-9_]+)/o)
      { $name = $1;
	$name =~ s/_/\\_/go;
	$source{$name} = $file;
	$type{$name}   = 11;
	$macro{$name}  = 1;
      }
      elsif (/^\*\* Typedef:[ 	]*([a-zA-Z0-9_]+)/o)
      { $name = $1;
	$name =~ s/_/\\_/go;
	$source{$name} = $file;
	$type{$name}   = 22;
      }
      elsif (/^\*\* Type:[ 	]*([%* a-zA-Z0-9_]+)/o)
      { $head{$name} = "$1 \\Mac{$name}";
      }
      elsif (/^\*\* Variable:[ 	]*([a-zA-Z0-9_]+)/o)
      { $name = $1;
	$name =~ s/_/\\_/go;
	$source{$name}    = $file;
	$type{$name}      = 1;
	$variable{$name}  = 1;
      }
      elsif (/^\*\*[ 	]*Description:[ 	]*([a-zA-Z0-9_]*)/o)
      { print $1."\n" if $1 ne '';
	$state = 9;
      }
      elsif ($name eq '' && $state == 0 )
      {
      }
      elsif (/^\*\* Arguments:/o)
      { $state = 2;
	@a = ();
      }
      elsif (/^\*\* Returns:[ 	]*(.*)/o)
      { $returns{$name} = '    '.$1;
	$state   = 3;
      }
      elsif (/^\*\* Purpose:[ 	]*(.*)/o)
      { $_ = $1;
	s/_/\\_/go;
	$purpose{$name} = '  '.$_;
	$state   = 1;
      }
      elsif (/^\*\* Example:[ 	]*(.*)/o)
      { $_ = $1;
	s/_/\\_/go;
	$example{$name} = '  '.$_;
	$state   = 5;
      }
      elsif ( /^\*\*[-*_]/o )
      { $state = 0;
	if ( $type{$name} == 10 )
	{ $_ = $name;
	  s/\\_//go;
	  if ( $head{$name} eq '' ) { $n = "\\Mac{$name}"; }
	  else { $n = $head{$name}; }
	  print "\\begin{Macro}{$n}{$_}\n  \\begin{Arguments}";
	  foreach $a (@a)
	  { print "\n    & \\Var{$a} & $arg{$a}\\\\";
	  }
	  print "\n  \\end{Arguments}%\n";
	  print "$purpose{$name}\n";
	  print "  \\begin{Result}\n$returns{$name}\n  \\end{Result}\n"
	      if ($returns{$name} ne '');
	  print "\\end{Macro}\n";
	  $name = '';
	}
	elsif ( $type{$name} == 11 )
	{ $_ = $name;
	  s/\\_//go;
	  if ( $head{$name} eq '' ) { $n = "\\Mac{$name}"; }
	  else { $n = $head{$name}; }
	  print "\\begin{Constant}{$n}{$_}\n";
	  print "\n  \\begin{Arguments}$arg{$name}\n  \\end{Arguments}%\n"
	      if ($arg{$name} ne '');
	  print "$purpose{$name}\n";
	  print "\\end{Constant}\n";
	  $name = '';
	}
	elsif ( $type{$name} == 1 )
	{ $_ = $name;
	  s/\\_//go;
	  if ( $head{$name} eq '' ) { $n = "\\Mac{$name}"; }
	  else { $n = $head{$name}; }
	  print "\\begin{Variable}{$n}{$_}\n";
	  print "$purpose{$name}\n";
	  print "\\end{Variable}\n";
	  $name = '';
	}
	elsif ( $type{$name} == 22 )
	{ $_ = $name;
	  s/\\_//go;
	  if ( $head{$name} eq '' ) { $n = "\\Type{$name}"; }
	  else { $n = $head{$name}; }
	  print "\\begin{Typedef}{$n}{$_}\n";
	  print "$purpose{$name}\n";
	  $name  = '';
	  $state = 22;
	}
      }
      elsif ( $state == 9 && /^\*\*[ 	]*(.*)/o )
      { print $1."\n";
      }
      elsif ( $state == 1 && /^\*\*[ 	]*(.*)/o )
      { $purpose{$name} = $purpose{$name}."\n  ".$1;
      }
      elsif ( $state == 2 && /^\*\*		(.*)/o )
      { $arg{$lastarg} = $arg{$lastarg}."\n".$1;
      }
      elsif ( $state == 2 && /^\*\*[ 	]+([a-zA-Z0-9_]+)[ 	]*(.*)/o )
      { $arg{$1} = $2;
	$lastarg = $1;
	push (@a,($1));
      }
      elsif ( $state == 3 && /^\*\*[ 	]*(.*)/o )
      { $returns{$name} = $returns{$name}."\n    ".$1;
      }
    }
    elsif ( /^([a-zA-Z_][^(]*[^a-zA-Z0-9_(])([a-zA-Z0-9_]*)/o && $state == 0 )
    { $_ = "$1\\Fct{$2}";
      if ( /^static/ )
      { undef $purpose{$name};
      }
      else
      {
	s/_/\\_/go;
	$head{$name}  = $_;
	$proto{$name} = '';
	$state = 11;
      }
    }
    elsif ( $state == 11 && /^[ 	]+([^;]*;)/o )
    { $_ = $1;
      s/register //o;
      s/[ 	]+/ /go;
      s/_ARG\((.*)\)/\1/o;
      if ( /^(.*\([^a-zA-Z0-9_]*)([a-zA-Z0-9_]+)(\)\(.*\);)$/o )
      { $_ = "$1\\ \t&\\Var{$2}$3 \t&$arg{$2}";
      }
      else
      { s/([a-zA-Z0-9_]+)(\[[0-9a-zA-Z_]*\])?;/\\ \t&\\Var{\1}\2;\t&$arg{$1}/o;
      }
      s/_/\\_/go;
      if ($proto{$name} eq '')
      {	$proto{$name} = "\n    ".$_; }
      else
      {	$proto{$name} = $proto{$name}."\\\\\n    ".$_; }
    }
    elsif ( $state == 22 )
    { if ( /^[ ]*typedef[ ]*struct[ ]*([a-zA-Z_0-9]+|)/o )
      { print "  \\STRUCT{$1}\n";
	$NL = '';
      } elsif (/^[ ]*}[ ]*(.*[a-zA-Z])[ ]*;/o)
      { $x = '';
	foreach $_ (split(/,[ ]*/,$1))
	{ $x = $x . ', ' if ( $x ne '');
	  $x = $x . "\\Type{$_}";
	}
	print "\n  \\EndSTRUCT{$x}\n\\end{Typedef}\n";
	$state = 0;
      } elsif ( /^[ {]*([a-zA-Z_][^(]*[^a-zA-Z0-9_(])([a-zA-Z0-9_]+);[ 	]*\/\*[ 	]*(.*)\*\//o )
      { $_ = $2;
	$t = $1;
	$c = $3;
	s/_/\\_/go;
	print "$NL    $t\\ \t&\\Member{$_};\t& $c";
	$NL = "\\\\\n";
      } elsif ( /^[ {]*([a-zA-Z_][^(]*[^a-zA-Z0-9_(])([a-zA-Z0-9_]+);/o )
      { $_ = $2;
	$t = $1;
	s/_/\\_/;
	print "$NL    $t\\ \t&\\Member{$_};\t& ";
	$NL = "\\\\\n";
      } elsif ( /^[ 	]*\/\*[ 	]*(.*)\*\//o )
      { print "\n\t\t\t$1";
      } else
      { print $_;
      }
    }
    elsif ( /^{/o && $name ne '' )
    { 
      $name  = '';
      $state = 0;
    }
  }

  foreach $_ (sort(keys %function))
  {
    if ( $_ ne '' && $head{$_} ne '' )
    { print "\\begin{Function}{$head{$_}}{$_}";
      print "\n  \\begin{Arguments}$proto{$_}\n  \\end{Arguments}%\n"
	  if ($proto{$_} ne '');
      print "$purpose{$_}\n";
      print "  \\begin{Result}\n$returns{$_}\n  \\end{Result}\n";
      print "\\end{Function}\n";
    }
  }

  close(FD);
}

#------------------------------------------------------------------------------
# Local Variables:
# mode: perl
# End:
