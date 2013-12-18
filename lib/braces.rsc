%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 
%% This file is part of BibTool.
%% It is distributed under the GNU General Public License.
%% See the file COPYING for details.
%% 
%% (c) 1995-2013 Gerd Neugebauer
%% 
%% Net: gene@gerd-neugebauer.de
%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Translate double quotes as delimiters "" by braces {}
%

rewrite.rule { "^\"\([^#]*\)\"$" = "{\1}" }
rewrite.rule { "# \"\([^#]*\)\"$" = "# {\1}" }
rewrite.rule { "^\"\([^#]*\)\" #" = "{\1} #" }
rewrite.rule { "# \"\([^#]*\)\" #" = "# {\1} #" }
