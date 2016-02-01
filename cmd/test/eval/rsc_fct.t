#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2016 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

rsc_fct.t - Test suite for the BibTool built-in function-backed parameters.

=head1 SYNOPSIS

rsc_fct.t

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

$BUnit::name_prefix = 'eval/';

#------------------------------------------------------------------------------
BUnit::run(name       => "input-1",
	   args		=> '--eval',
	   resource	=> "input \"a.bib\";input;\n",
	   expected_err	=> '',
	   expected_out	=> "[\"a.bib\"]\n" );

#------------------------------------------------------------------------------
BUnit::run(name       => "input-2",
	   args		=> '--eval',
	   resource	=> "input {a.bib};input;\n",
	   expected_err	=> '',
	   expected_out	=> "[\"a.bib\"]\n" );

#------------------------------------------------------------------------------
BUnit::run(name       => "macro.file-1",
	   args		=> '--eval',
	   resource	=> "macro.file \"a.bib\";\n",
	   expected_err	=> '',
	   expected_out	=> "\"a.bib\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name       => "macro.file-2",
	   args		=> '--eval',
	   resource	=> "macro.file \"a.bib\";macro.file;\n",
	   expected_err	=> '',
	   expected_out	=> "\"a.bib\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name       => "macro.file-3",
	   args		=> '--eval',
	   resource	=> "macro.file {a.bib};macro.file;\n",
	   expected_err	=> '',
	   expected_out	=> "\"a.bib\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name       => "output.file-1",
	   args		=> '--eval',
	   resource	=> "output.file \"a.bib\";\n",
	   expected_err	=> '',
	   expected_out	=> "\"a.bib\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name       => "output.file-2",
	   args		=> '--eval',
	   resource	=> "output.file \"a.bib\";output.file;\n",
	   expected_err	=> '',
	   expected_out	=> "\"a.bib\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name       => "output.file-3",
	   args		=> '--eval',
	   resource	=> "output.file {a.bib};output.file;\n",
	   expected_err	=> '',
	   expected_out	=> "\"a.bib\"\n" );

sub test_string
{ my ($key, $val) = @_;
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$key-1",
	   args		=> '--eval',
	   resource	=> "$key;\n",
	   expected_err	=> '',
	   expected_out	=> "\"$val\"\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$key-2",
	   args		=> '--eval',
	   resource	=> "$key\"xx\";\n",
	   expected_err	=> '',
	   expected_out	=> "\"xx\"\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$key-3",
	   args		=> '--eval',
	   resource	=> "$key\"xx\";$key\n",
	   expected_err	=> '',
	   expected_out	=> "\"xx\"\n" );
  #------------------------------------------------------------------------------
  BUnit::run(name       => "$key-4",
	   args		=> '--eval',
	   resource	=> "$key\"x#x\";$key\n",
	   expected_err	=> '',
	   expected_out	=> "\"xx\"\n" );
}

test_string('default.key', '**key*');
test_string('fmt.inter.name', '-');
test_string('fmt.name.pre', '.');
test_string('fmt.name.name', '.');
test_string('fmt.name.title', ':');
test_string('fmt.title.title', '-');
test_string('fmt.et.al', '.ea');
test_string('key.number.separator', '*');

#------------------------------------------------------------------------------
BUnit::run(name         => "key.base-1",
	   args		=> '--eval',
	   resource	=> "key.base;\n",
	   expected_err	=> '',
	   expected_out	=> "\"digit\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "key.base-11",
	   args		=> '--eval',
	   resource	=> "key.base\"upper\";\n",
	   expected_err	=> '',
	   expected_out	=> "\"upper\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "key.base-12",
	   args		=> '--eval',
	   resource	=> "key.base\"A\";key.base;\n",
	   expected_err	=> '',
	   expected_out	=> "\"upper\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "key.base-13",
	   args		=> '--eval',
	   resource	=> "key.base\"Z\";key.base;\n",
	   expected_err	=> '',
	   expected_out	=> "\"upper\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => "key.base-21",
	   args		=> '--eval',
	   resource	=> "key.base\"lower\";\n",
	   expected_err	=> '',
	   expected_out	=> "\"lower\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "key.base-22",
	   args		=> '--eval',
	   resource	=> "key.base\"a\";key.base;\n",
	   expected_err	=> '',
	   expected_out	=> "\"lower\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "key.base-23",
	   args		=> '--eval',
	   resource	=> "key.base\"z\";key.base;\n",
	   expected_err	=> '',
	   expected_out	=> "\"lower\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => "key.base-31",
	   args		=> '--eval',
	   resource	=> "key.base\"digit\";\n",
	   expected_err	=> '',
	   expected_out	=> "\"digit\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "key.base-32",
	   args		=> '--eval',
	   resource	=> "key.base\"1\";key.base;\n",
	   expected_err	=> '',
	   expected_out	=> "\"digit\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "key.base-33",
	   args		=> '--eval',
	   resource	=> "key.base\"9\";key.base;\n",
	   expected_err	=> '',
	   expected_out	=> "\"digit\"\n" );

#------------------------------------------------------------------------------
BUnit::run(name         => "symbol.type-1",
	   args		=> '--eval',
	   resource	=> "symbol.type;\n",
	   expected_err	=> '',
	   expected_out	=> "\"lower\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "symbol.type-11",
	   args		=> '--eval',
	   resource	=> "symbol.type\"upper\";\n",
	   expected_err	=> '',
	   expected_out	=> "\"upper\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "symbol.type-12",
	   args		=> '--eval',
	   resource	=> "symbol.type\"UPPER\";symbol.type;\n",
	   expected_err	=> '',
	   expected_out	=> "\"upper\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "symbol.type-21",
	   args		=> '--eval',
	   resource	=> "symbol.type\"lower\";symbol.type;\n",
	   expected_err	=> '',
	   expected_out	=> "\"lower\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "symbol.type-22",
	   args		=> '--eval',
	   resource	=> "symbol.type\"LOWER\";symbol.type;\n",
	   expected_err	=> '',
	   expected_out	=> "\"lower\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "symbol.type-31",
	   args		=> '--eval',
	   resource	=> "symbol.type\"cased\";symbol.type;\n",
	   expected_err	=> '',
	   expected_out	=> "\"cased\"\n" );
#------------------------------------------------------------------------------
BUnit::run(name         => "symbol.type-32",
	   args		=> '--eval',
	   resource	=> "symbol.type\"CASED\";symbol.type;\n",
	   expected_err	=> '',
	   expected_out	=> "\"cased\"\n" );

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 
