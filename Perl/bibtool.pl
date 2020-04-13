#!/usr/local/bin/perl
##*****************************************************************************
## 
##  This file is part of BibTool.
##  It is distributed under the GNU General Public License.
##  See the file COPYING for details.
## 
##  (c) 1996-2020 Gerd Neugebauer
## 
##  Net: gene@gerd-neugebauer.de
## 
##  This program is free software; you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation; either version 2, or (at your option)
##  any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##
##  You should have received a copy of the GNU General Public License
##  along with this program; if not, write to the Free Software
##  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
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

