#!/usr/local/bin/perl
##*****************************************************************************
## $Id: bibtool.pl,v 1.2 2007-02-08 05:27:32 gene Exp $
##=============================================================================
## 
## This file is part of BibTool.
## It is distributed under the GNU General Public License.
## See the file COPYING for details.
## 
## (c) 1996-2001 Gerd Neugebauer
## 
## Net: gene@gerd-neugebauer.de
## 
##*****************************************************************************
#
#  This sample file shows how bibtool can be interfaced with Perl.
#  BibTool is assumed to be on the search path for executables.
#  BibTool is called with the appropriate parameters. In this examples
#  it is used only for normalization of the BibTeX database.
#  Afterwards it is rather simple for Perl to parse the result.
#

$file=$ARGV[0];	# take the first argument as file name


open(FD,"bibtool -q -- expand.macros=on -- pass.comments=off -- print.line.length=999999 -- print.indent=0 -- print.align=0 $file |");
$bibtool_is_in_record = 0;
while(<FD>) {
    if (/^\@STRING/o) {
    }
    elsif (/^\@PREAMBLE/o) {
    }
    elsif (/^\@COMMENT/o) {
    }
    elsif ($bibtool_is_in_record == 0 && /^@([a-zA-Z]*){[ \t]*(.*),/o) {
	$type = $1;
	$key  = $2;
	printf("type:  %s\nkey:   %s\n",$type,$key);
	$bibtool_is_in_record = 1;
    }
    elsif ($bibtool_is_in_record == 1 && /([a-zA-Z]*)=(.*)$/o) {
	$item  = $1;
	$value = $2;
	printf("entry: %s\nvalue: %s\n",$item,$value);
    }
    elsif ($bibtool_is_in_record == 1 && /^}/o) {
	printf("END_OF_RECORD\n");
	$bibtool_is_in_record = 0;
    }
}
close(FD);

