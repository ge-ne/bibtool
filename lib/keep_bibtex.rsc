%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 
%% This file is part of BibTool.
%% It is distributed under the GNU General Public License.
%% See the file COPYING for details.
%% 
%% (c) 2017 Gerd Neugebauer
%% 
%% Net: gene@gerd-neugebauer.de
%%
%% This program is free software; you can redistribute it and/or modify
%% it under the terms of the GNU General Public License as published by
%% the Free Software Foundation; either version 2, or (at your option)
%% any later version.
%%
%% This program is distributed in the hope that it will be useful,
%% but WITHOUT ANY WARRANTY; without even the implied warranty of
%% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%% GNU General Public License for more details.
%%
%% You should have received a copy of the GNU General Public License
%% along with this program; if not, write to the Free Software
%% Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Keep only fields in the standard BibTeX styles
%
keep.field {{key
	     note}}
keep.field {{author
	     title
	     journal
	     year
	     volume
	     number
	     pages
	     month}
  if $type = article}

keep.field {{author
	     editor
	     title
	     publisher
	     year
	     volume
	     number
	     series
	     address
	     edition
	     month}
  if $type = book}

keep.field {{title
	     author
	     howpublished
	     address
	     month
	     year}
  if $type = booklet}

keep.field {{author
	     title
	     booktitle
	     year
	     editor
	     volume
	     number
	     series
	     pages
	     address
	     month
	     organization
	     publisher}
  if $type = conference }

keep.field {{author
	     editor
	     title
	     chapter
	     pages
	     publisher
	     year
	     volume
	     number
	     series
	     type
	     address
	     edition
	     month}
  if $type = inbook}

keep.field {{author
	     title
	     booktitle
	     publisher
	     year
	     editor
	     volume
	     number
	     series
	     type
	     chapter
	     pages
	     address
	     edition
	     month}
  if $type = incollection}

keep.field {{author
	     title
	     booktitle
	     year
	     editor
	     volume
	     number
	     series
	     pages
	     address
	     month
	     organization
	     publisher}
  if $type = inproceedings}

keep.field {{title
	     author
	     organization
	     address
	     edition
	     month
	     year}
  if $type = manual}

keep.field {{author
	     title
	     school
	     year
	     type
	     address
	     month}
  if $type = mastersthesis}

keep.field {{author
	     title
	     howpublished
	     month
	     year}
  if $type = misc}

keep.field {{author
	     title
	     school
	     year
	     type
	     address
	     month}
  if $type = phdthesis}

keep.field {{title
	     year
	     editor
	     volume
	     number
	     series
	     address
	     month
	     organization
	     publisher}
  if $type = proceedings}

keep.field {{author
	     title
	     institution
	     year
	     type
	     number
	     address
	     month}
  if $type = techreport}

keep.field {{author
	     title
	     month
	     year}
  if $type = unpublished}
