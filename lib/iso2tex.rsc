%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% 
%% This file is part of BibTool.
%% It is distributed under the GNU General Public License.
%% See the file COPYING for details.
%% 
%% (c) 1995-2016 Gerd Neugebauer
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
% Translation of ISO 8859/1 characters to BibTeX equivalents
%
rewrite.rule {	"¡" # "!`"		}
%rewrite.rule {	"¢" # "{\\cent}"	}
%rewrite.rule {	"£" # "{\\pounds}"	}
%rewrite.rule {	"¤" # "{\\currency}"	}
%rewrite.rule {	"¥" # "{\\yen}"		}
%rewrite.rule {	"¦" # "{\\MiD}"		}
rewrite.rule {	"§" # "{\\S}"		}
%rewrite.rule {	"¨" # "{\\\"{}}"	}
%rewrite.rule {	"©" # "{\\copyright}"	}
%rewrite.rule {	"ª" # "{\\OIfem}"	}
%rewrite.rule {	"«" # "\\ll "		}
%rewrite.rule {	"¬" # "\\neg "		}
%rewrite.rule {	"­" # "\\-"		}
%rewrite.rule {	"®" # "{\\Registered}"	}
%rewrite.rule {	"¯" # "{\\macron}"	}
%rewrite.rule {	"°" # "{\\degree}"	}
%rewrite.rule {	"±" # "\\pm "		}
%rewrite.rule {	"²" # "\\SuperTwo "	}
%rewrite.rule {	"³" # "\\SuperThree "	}
%rewrite.rule {	"´" # "{\\'{}}"		}
%rewrite.rule {	"µ" # "\\mu "		}
rewrite.rule {	"¶" # "{\\P}"		}
%rewrite.rule {	"·" # "\\cdot "		}
%rewrite.rule {	"¸" # "{\\c{}}"		}
%rewrite.rule {	"¹" # "\\SuperOne "	}
%rewrite.rule {	"º" # "{\\OImasc}"	}
%rewrite.rule {	"»" # "\\gg "		}
%rewrite.rule {	"¼" # "\\OneQuater "	}
%rewrite.rule {	"½" # "\\OneHalf "	}
%rewrite.rule {	"¾" # "\\ThreeQuaters "	}
rewrite.rule {	"¿" # "?`"		}
rewrite.rule {	"À" # "{\\`A}"		}
rewrite.rule {	"Á" # "{\\'A}"		}
rewrite.rule {	"Â" # "{\\^A}"		}
rewrite.rule {	"Ã" # "{\\~A}"		}
rewrite.rule {	"Ä" # "{\\\"A}"		}
rewrite.rule {	"Å" # "{\\AA}"		}
rewrite.rule {	"Æ" # "{\\AE}"		}
rewrite.rule {	"Ç" # "{\\c{C}}"	}
rewrite.rule {	"È" # "{\\`E}"		}
rewrite.rule {	"É" # "{\\'E}"		}
rewrite.rule {	"Ê" # "{\\^E}"		}
rewrite.rule {	"Ë" # "{\\\"E}"		}
rewrite.rule {	"Ì" # "{\\`I}"		}
rewrite.rule {	"Í" # "{\\'I}"		}
rewrite.rule {	"Î" # "{\\^I}"		}
rewrite.rule {	"Ï" # "{\\\"I}"		}
%rewrite.rule {	"Ð" # "{\\Dstroke}"	}
rewrite.rule {	"Ñ" # "{\\~N}"		}
rewrite.rule {	"Ò" # "{\\`O}"		}
rewrite.rule {	"Ó" # "{\\'O}"		}
rewrite.rule {	"Ô" # "{\\^O}"		}
rewrite.rule {	"Õ" # "{\\~O}"		}
rewrite.rule {	"Ö" # "{\\\"O}"		}
%rewrite.rule {	"×" # "\\times "	}
rewrite.rule {	"Ø" # "{\\O}"		}
rewrite.rule {	"Ù" # "{\\`U}"		}
rewrite.rule {	"Ú" # "{\\'U}"		}
rewrite.rule {	"Û" # "{\\^U}"		}
rewrite.rule {	"Ü" # "{\\\"U}"		}
rewrite.rule {	"Ý" # "{\\'Y}"		}
%rewrite.rule {	"Þ" # "{\\Thorn}"	}
rewrite.rule {	"ß" # "{\\ss}"		}
rewrite.rule {	"à" # "{\\`a}"		}
rewrite.rule {	"á" # "{\\'a}"		}
rewrite.rule {	"â" # "{\\^a}"		}
rewrite.rule {	"ã" # "{\\~a}"		}
rewrite.rule {	"ä" # "{\\\"a}"		}
rewrite.rule {	"å" # "{\\aa}"		}
rewrite.rule {	"æ" # "{\\ae}"		}
rewrite.rule {	"ç" # "{\\c{c}}"	}
rewrite.rule {	"è" # "{\\`e}"		}
rewrite.rule {	"é" # "{\\'e}"		}
rewrite.rule {	"ê" # "{\\^e}"		}
rewrite.rule {	"ë" # "{\\\"e}"		}
rewrite.rule {	"ì" # "{\\`\\i}"	}
rewrite.rule {	"í" # "{\\'\\i}"	}
rewrite.rule {	"î" # "{\\^\\i}"	}
rewrite.rule {	"ï" # "{\\\"\\i}"	}
%rewrite.rule {	"ð" # "{\\dstroke}"	}
rewrite.rule {	"ñ" # "{\\~n}"		}
rewrite.rule {	"ò" # "{\\`o}"		}
rewrite.rule {	"ó" # "{\\'o}"		}
rewrite.rule {	"ô" # "{\\^o}"		}
rewrite.rule {	"õ" # "{\\~o}"		}
rewrite.rule {	"ö" # "{\\\"o}"		}
%rewrite.rule {	"÷" # "{\\div}"		}
rewrite.rule {	"ø" # "{\\o}"		}
rewrite.rule {	"ù" # "{\\`u}"		}
rewrite.rule {	"ú" # "{\\'u}"		}
rewrite.rule {	"û" # "{\\^u}"		}
rewrite.rule {	"ü" # "{\\\"u}"		}
rewrite.rule {	"ý" # "{\\'y}"		}
%rewrite.rule {	"þ" # "{\\thorn}"	}
rewrite.rule {	"ÿ" # "{\\\"y}"		}
