#!/usr/local/bin/perl
##*****************************************************************************
## $Id: L2H.pm,v 1.5 2010-05-31 04:02:43 gene Exp $
##*****************************************************************************
## Author: Gerd Neugebauer
##=============================================================================

package L2H;

use vars qw ( @ISA @EXPORT @EXPORT_OK $VERSION );
use strict;

my %opt = (
	   'dirname' => '.',
	   'prefix'  => 'm',
	   'title'   => '',
	   'main'    => 'index.html',
	   'author'  => 'Gerd Neugebauer',
	   'email'   => 'gene@gerd.neugebauer.de',
	   'year'    => '2010',
	   'ext'     => '.html'
	  );
{
  my ($sec,$min,$hour,$day,$mon,$year,$wday,$yday,$isdst) = localtime;
  $opt{year} = $year + 1900;
}

require Exporter;
@ISA       = qw(Exporter);
@EXPORT    = qw(newcommand newenvironment sf set_opt hyphenate);
@EXPORT_OK = qw();

BEGIN{
  my $VERSION = '$Revision: 1.5 $'; #'
  $VERSION =~ s/[^0-9.]//go;
}

use hyph_en;


#------------------------------------------------------------------------------
# Function:	new
# Description:	
# Returns:	
#
sub new
{ my $class = shift;
  my $self  =
  { 'ignore:p'		=> 0,
    'footnotes'		=> '',
    'footnote_number'	=> 0,
    'NAV'		=> '',
    'TOC'		=> '',
    'IDX'		=> '',
    'BIB'		=> '',
    'current_label'	=> '',
    'label_number'	=> 1,
    'index_number'	=> 1,
    'context'		=> 'text',
    'group'		=> '',
    'result'		=> '',
    'page'		=> '',
    'Group'		=> [],		# stack of the group informations
    'Context'		=> [],		# stack of the contexts
    'SectionMinNo'	=> 1,
    'SectionNumber'	=> [0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    'debug'		=> 0,		# bitfield determining the verbosity
    'message:p'		=> 0,		# indicator for the last pass
					# for which messages should be issued.
    'hyphenate'		=> 1,		# indicator to turn on hyphenation
  };
  bless $self,$class;
  return $self;
}

#------------------------------------------------------------------------------
# Function:	restart
# Description:	
# Returns:	
#
sub restart
{ my $self = shift;
  my %args = @_;
  local $_ = new L2H()->LaTeX2HTML($opt{'title'} || $self->{'title'} || '');
  $self->{'title:'.$opt{'main'}} = $_;
  $self->{'Context'}       = [];
  $self->{'context'}       = 'text';
  $self->{'SectionNumber'} = [0,0,0,0,0,0,0,0,0,0,0,0,0,0];
  $self->{'current_label'} = '';
  $self->{'index_number'}  = 1;
  $self->{'label_number'}  = 1;
  $self->{'page'}          = '';
  $self->{'ignore:p'}      = 1;
  $self->{'NAV'}           = "<div class=\"toc0\"><a href=\"doc.html\" target=\"content\">$_</a></div>\n";
  $self->{'TOC'}           = '';
  while ( my($key,$value) = each %args)
  { $self->{$key} = $value; }
  $self->redirect($opt{'main'}, 0);
}

#------------------------------------------------------------------------------
# Function:	push_context
# Description:	
# Returns:	
#
sub push_context
{ my $self    = shift;
  my $context = shift;
  my @a = $self->{'Context'};
  unshift @a,$context;
  $self->{'Context'} = @a;
  $self->{'context'} = $context;
  return '';
}

#------------------------------------------------------------------------------
# Function:	pop_context
# Description:	
# Returns:	
#
sub pop_context
{ my $self    = shift;
  my @a = $self->{'Context'};
  my $context = shift @a;
  $self->{'Context'} = @a;
  $self->{'context'} = $context;
  return '';
}

#------------------------------------------------------------------------------
# Function:	opt
# Description:	
# Returns:	
#
sub opt
{ local $_ = shift;
  $_ = shift;
  return $opt{$_};
}

#------------------------------------------------------------------------------
# Function:	set_opt
# Description:	
# Returns:	
#
sub set_opt
{ shift;
  my ($key,$value) = @_;
  $opt{$key} = $value;
}

#------------------------------------------------------------------------------
# Variable:	%SectionLevel
# Description:	
#
my %SectionLevel =
  ( 'tableofcontents'	=> 1,
    'bibliography'	=> 1,
    'index'		=> 1,
    'part'		=> 1,
    'chapter'		=> 1,
    'section'		=> 2,
    'subsection'	=> 3,
    'subsubsection'	=> 4,
    'paragraph'		=> 5,
    'subparagraph'	=> 6,
    'subsubparagraph'	=> 7,
    'Summary'		=> 3,
  );

#------------------------------------------------------------------------------
# Variable:	%Macro
# Description:	Hash of array containing the defined macros.
#		The first element is the array is the arity of the macro.
#		The second argument is a modifier for the context. The value
#		undef leaves the context unchanged. The value '/' pos a value
#		from the context stack. All aotehr values are pushed to the
#		context stack.
#		The third element is the replacement text. The strings
#		#1, #2,..., #9 are replaced by the actual parameters. If it is
#		undef then the next element is taken into account.
#		The fourth element is a piece of code (anonymous subroutine)
#		to be evaluated when no replacement text is given. The
#		parameters of the macro are passed to this code in the array
#		@_. The return value is used as replacement text.
#
my %Macro;


#------------------------------------------------------------------------------
# Function:	begingroup
# Description:	
# Returns:	
#
sub begingroup
{ my $self = shift;
  unshift @{$self->{Group}},$self->{group};
  $self->{group} = '';
  return '';
}

#------------------------------------------------------------------------------
# Function:	endgroup
# Description:	
# Returns:	
#
sub endgroup
{ my $self = shift;
  local $_ = $self->{group};
  $self->{group} = shift @{$self->{Group}};
  return $_;
}

#------------------------------------------------------------------------------
# Function:	atendgroup
# Description:	
# Returns:	
#
sub atendgroup
{ my $self = shift;
  local $_ = shift;
  $self->{group} = $_.$self->{group};
  return '';
}

#------------------------------------------------------------------------------
# Function:	load
# Description:	
# Returns:	
#
sub load
{ my $self = shift;
  my $file = shift;
  print STDERR "--- Loading $file\n" if $self->{'debug'} & 1;
  do "$file" ;
  die $@ if $@;
}

#------------------------------------------------------------------------------
# Function:	newcommand
# Description:	
# Returns:	
#
sub newcommand
{ my ($macro,%arg) = @_;
  my $arity = ( $arg{arity} || 0 );
  if ( exists $L2H::Macro{$macro} )
  { # print STDERR "*** `$macro' is already defined.\n";
  }
  else
  { $L2H::Macro{$macro} = [$arity,$arg{context},$arg{text},$arg{code}];
  }
  return '';
}

#------------------------------------------------------------------------------
# Function:	renewcommand
# Description:	
# Returns:	
#
sub renewcommand
{ my ($macro,%arg) = @_;
  my $arity = ( $arg{arity} || 0 );
  if ( not defined $arg{noredef} )
  { $L2H::Macro{$macro} = [$arity,$arg{context},$arg{text},$arg{code},$arg{redef}];
  }
  return '';
}

#------------------------------------------------------------------------------
# Function:	newenvironment
# Description:	
# Returns:	
#
sub newenvironment
{ my ($macro,%arg) = @_;
  newcommand("begin{$macro}",
	     context => $macro,
	     arity   => $arg{arity},
	     text    => $arg{text},
	     code    => $arg{code},
	    );
  newcommand("end{$macro}",
	     context => '/',
	     arity   => 0,
	     text    => $arg{endtext},
	     code    => $arg{endcode},
	    );
  return '';
}

#------------------------------------------------------------------------------
# Function:	put
# Description:	
# Returns:	
#
sub put (@)
{ my $self = shift;
  my $s = shift;
  return if not defined($s);
  $self->{result} .= $s;
}

#------------------------------------------------------------------------------
# Function:	redirect
# Description:	
# Returns:	
#
sub redirect (@)
{
}

#------------------------------------------------------------------------------
# Function:	finish
# Description:	
# Returns:	
#
sub finish
{ my $self = shift;
  local $_ = shift;
  $self->put($_);
  $_ = $self->{result};
  $self->{result} = '';
  s/<\/blockquote><br>/<\/blockquote>/go;
  s/<p>\n<blockquote>/<blockquote>/go;
  s/<\/blockquote>\n*<blockquote>/<br>/go;
  s/<p><dt>/<dt>/go;
  if (defined $self->{hyphenate}) {
    $_ = hyphenate($self->{hyphenate}, $_);
  }
  return $_;
}

#------------------------------------------------------------------------------
# Method:	hyphenate
# Arguments:	
# Returns:	
# Description:	
#
sub hyphenate
{ my $h  = shift;
  my $s = shift;
  my ($t, $a);
  local $_ = '';

  while ($s =~ m/^([a-z_.\-]*)([^a-z_.\-]+)/is) {
    $t = $2;
    $s = $';
    $a = $1;
    if (length($a) > 4) {
#      print STDERR "  '$a'\t=> '$a',\n";
      $a = hyph($a);
    }
    $_	.= $a;
    $_	.= $t;
  }
  if (length($s) > 4) {
#    print STDERR "  ==>$s<<<\n" if $s =~ m/poss/;
    $s = hyph($s);
  }
  $_  .= $s;
  return $_;
}

#------------------------------------------------------------------------------
# Function:	LaTeX2HTML
# Description:	
# Returns:	
#
sub LaTeX2HTML
{ my $self = shift;
  local $_ = shift;
  $self->{result} = '';

  while ( m/[\~\{\}\^_\%\&]|(\\([^a-z@]|[a-z@]+\s*))|---?/oi )
  { my $token = $&;
    my $pre = $`;
    $_ =  $';
    $pre =~ s|\n[ ]*\n|\n<p>|go;
    $self->put($pre) if not $self->{'ignore:p'};

    if ( substr($token,0,1) eq '\\' )
    { $token = substr($token,1);
      $token =~ s/\s//go if ( $token =~ m/^[a-z@]/oi );
      if ( ($token eq 'begin' || $token eq 'end') && m/^{[a-z\*]+}/oi )
      { $_ = $';
	$token .= $&;
      }
      my $arity = $L2H::Macro{$token}[0];
      if ( defined($arity) )
      { my @a     = ();
	my $start = 1;
	my $pre   = '\\'.$token;
	if ( $arity =~ m/^\[\](\d)/o )
	{ $start = 2;
	  $arity = $1+1;
	  ($a[1],$_) = get_optarg($_);
	}
	elsif ( $arity =~ m/^1\[\](\d)/o )
	{ $start = 3;
	  $arity = $1+2;
	  ($a[1],$_) = get_arg($token,$_);
	  ($a[2],$_) = get_optarg($_);
	  $pre .= "{$a[1]}";
	}
	elsif ( $arity =~ m/^\*(\d)/o )
	{ $start = 2;
	  $arity = $1+1;
	  s/^\s//go;
	  if ( substr($_,0,1) eq '*' )
	  { $a[1] = '*';
	    $_ = substr($_,1);
	    $pre .= '*';
	  }
	}
	for ( my $i=$start; $i<=$arity; $i++ )
	{ ($a[$i],$_) = get_arg($pre,$_);
	  $pre .= "{$a[$i]}";
	}

	my $text = '';
	if ( not $self->{'ignore:p'} )
	{ my $mac = $L2H::Macro{$token}[2];
      	  if ( defined($mac) )
	  { for (my $i=1;$i<=$arity;$i++) { $mac =~ s/\#$i/$a[$i]/g; }
	    $text = $mac;
	  }
	}
	if ( defined($L2H::Macro{$token}[3]) )
	{ shift @a;
	  $text .= &{$L2H::Macro{$token}[3]}($self,@a);
	}
	$_ = $text.$_;
      }
      else
      { print STDERR "'\\$token' is undefined.\n"
	    if( $self->{'debug'} & 128 );
	$self->put('\\'.$token.' ') if ( not $self->{'ignore:p'});
      }
    }
    elsif ($token eq '---')
    { $self->put('&mdash;');
    }
    elsif ($token eq '--')
    { $self->put('&ndash;');
    }
    elsif ( $token eq '%' ) # comments
    { s/^.*\n[ \t]*//o;
    }
    elsif ( $token eq '&' ) # next column
    { if ( m/^((#[0-9][0-9][0-9])|amp|quot|lt|gt);/o )
      { $_ = $';
	$self->put('&'.$&);
      }
      else
      { $self->put('</td><td>'); }
    }
    elsif ( $token eq '^' ) # superscript
    { my $a;
      ($a,$_) = get_arg('^',$_);
      $self->put("<sup>$a</sup>");
    }
    elsif ( $token eq '_' ) # subscript
    { my $a;
      ($a,$_) = get_arg('_',$_);
      $self->put("<sub>$a</sub>");
    }
    elsif ( $token eq '~' )
    { $self->put('&nbsp;');
    }
    elsif ( $token eq '{' )
    { $self->begingroup();
    }
    elsif ( $token eq '}' )
    { $self->put($self->endgroup());
    }
  }
  return $self->finish($_);
}

#------------------------------------------------------------------------------
# Function:	get_arg
# Description:	
#		
# Returns:	
#
#
sub get_arg
{ my $mac  = shift;
  my $arg  = shift;

  return ($&,$') if ( $arg =~ m/^[^{}\\]/oi );
  return ($&,$') if ( $arg =~ m/^\\([^a-z@]|[a-z@]+)/oi );
  die "wrong start of args: $arg\n" if (substr($arg,0,1)ne '{');
  $arg     = substr($arg,1);
  my $n    = 1;
  local $_ = '';
  while ( $n>0 && $arg =~ m/(\\.|[\{\}])/o )
  { if    ( $& eq '{' ) { $n++; }
    elsif ( $& eq '}' ) { $n--; }
    $_ .= $`;
    $_ .= $&;
    $arg = $';
  } 
  die "missing paren for $mac\n" if ($n>0);
  return (substr($_,0,length($_)-1),$arg);
}

#------------------------------------------------------------------------------
# Function:	get_optarg
# Description:	
#		
# Returns:	
#
#
sub get_optarg
{ my $arg  = shift;
  local $_ = '';
  return (undef,$arg) if ( substr($arg,0,1) ne '[' );
  $arg     = substr($arg,1);
  my $n    = 1;
  while ( $n>0 && $arg =~ m/(\\.|[\[\]\{\}])/o )
  { if    ( $& eq '[' ) { $n++; }
    elsif ( $& eq ']' ) { $n--; }
    elsif ( $& eq '{' ) { $n++; }
    elsif ( $& eq '}' ) { $n--; }
    $_ .= $`;
    $_ .= $&;
    $arg = $';
  } 
  die "missing paren\n" if ($n>0);
  return (substr($_,0,length($_)-1),$arg);
}

#------------------------------------------------------------------------------
# Function:	get_dimen
# Description:	
# Returns:	
#
sub get_dimen
{ local $_ = shift;
  s/^\s*//go;
  while ( s/^%.*//go ) { s/^\s*//go; }
  die "missing data" if ( $_ eq '' );
  return ($1,$') if ( m/^([-]?\s*(\d+|\d+\.\d*|\.\d+)\s*(pt|mm|cm|dd|sp|in))\s*/o );
  die "syntax error";
}

#------------------------------------------------------------------------------
# Function:	section
# Description:	
#		
# Returns:	
#
#
sub section
{ my $self   = shift;
  my $name   = shift;
  my $level  = shift;
  my $title  = shift;
  my $post   = shift;

  $level = $SectionLevel{$level} || 1;
  print STDERR '.' if $self->{debug} & 1;
  if ( not defined($name) )
  { $self->{'SectionNumber'}[$level]++;
    for ( my $i = $level + 1; $i < 10; $i++ )
    { $self->{'SectionNumber'}[$i] = 0}
    $name = $opt{'prefix'};
    for ( my $i = $self->{'SectionMinNo'}; $i <= $level; $i++ )
    { $name .= '_'.$self->{'SectionNumber'}[$i]; }
    $name .= $opt{'ext'};
  }
  $name =~ s/&#095;/_/go;

  { my $tr = new L2H();
    $title = $tr->LaTeX2HTML($title);
    $self->{'title:'. $name} = $title;
    $self->{'current_label'} = $title;
  }

  if ( $self->{'ignore:p'} )
  { $name  = undef;
    $level = 0
  }

  $self->redirect($name, $level);
  $self->put($post) if defined $post;

  $self->{TOC} .= "<div class=\"toc$level\"><a href=\"$self->{page}\">$title</a></div>\n";
  $self->{NAV} .= "<div class=\"toc$level\"><a href=\"$self->{page}\" target=\"content\">$title</a></div>\n";

  return '';
}

#------------------------------------------------------------------------------
# Function:	footnote
# Description:	
# Returns:	
#
sub footnote
{ my ($self,$text) = @_;
  my $l2h = new L2H();
  my $no = $self->{'footnote_number'}++;

  $text = $l2h->LaTeX2HTML($text);
  $self->{footnotes} .= "<small><sup><a name='FN$no'>$no</a></sup> $text</small><br />";
  return "<sup><small><a href='#FN$no'>$no</a></small></sup>";
}

#------------------------------------------------------------------------------
# Function:	label
# Description:	
#		
# Returns:	
#
#
sub label
{ my    $self  = shift;
  my    $label = shift;
  my    $tag   = shift;
  local $_     = $self->{'page'};
  s/\.html?$//o;
  s/_/\&\#095;/go;
  $self->{'label_text:'.$label} = $self->{'current_label'};
  if ( $tag )
  { local $_ = 'tag'.($self->{'label_number'}++);
    $self->{'label_url:'.$label} = $self->{'page'}.'#'.$_;
    $self->{'label_url:'.$label} =~ s/_/\&\#095;/go;
    return "<a name=\"$_\">";
  }
  $self->{'label_url:'.$label} = $self->{'page'};
  $self->{'label_url:'.$label} =~ s/_/\&\#095;/go;
  return '';
}

#------------------------------------------------------------------------------
# Function:	Index
# Description:	
#		
# Returns:	
#
#
sub Index
{ my $self  = shift;
  my $key   = shift;

  return '' if ( $self->{'message:p'} or $key eq '' );

  my $i     = $self->{'index_number'}++;
  my $page  = $self->{'page'};
  my $title = $self->{'title:'.$page} || '';
  local $_  = $key;

  if ( $key =~ m/@/o )
  { $_ = $`;
    $key = $';
  }
  $_ = lc($_);

  $self->{'index_name:'.$_} = $key;
  $self->{'INDEX'}{$_} .= ", " if ( defined ($self->{'INDEX'}{$_}) and
				    $self->{'INDEX'}{$_} ne '' );
  $self->{'INDEX'}{$_} .= "<a href='$page#IDX$i'>$title</a>";
  return "<a name='IDX$i'>";
}

#------------------------------------------------------------------------------
# Function:	sf
# Description:	
#		
# Returns:	
#
#
sub sf
{ return '<font face="sans-serif">'.join('',@_).'</font>';
}

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
