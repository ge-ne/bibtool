/*** builtin.c ****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2015-2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

  BIND("add.field"		);   		   /* RscByFct	             */
  BIND("apply.alias"		);   		   /* RscBoolean	     */
  BIND("apply.modify"		);   		   /* RscBoolean	     */
  BIND("apply.include"		);   		   /* RscBoolean	     */
  Bind("and"			, sym_and);  	   /* RscTerm	             */
  BIND("bibtex.env.name"	);   		   /* RscString	             */
  BIND("bibtex.search.path"	);   		   /* RscString	             */
  BIND("check.double"		);   		   /* RscBoolean	     */
  BIND("check.double.delete"	);   		   /* RscBoolean	     */
  BIND("check.rule"		);   		   /* RscByFct	             */
  BIND("check.case.sensitive"	);   		   /* RscBoolean	     */
  BIND("clear.ignored.words"	);   		   /* RscByFct	             */
  BIND("count.all"		);   		   /* RscBoolean	     */
  BIND("count.used"		);   		   /* RscBoolean	     */
  BIND("crossref.limit"		);   		   /* RscNumeric	     */
  BIND("default.key"		);   		   /* RscByFct	             */
  BIND("delete.field"		);   		   /* RscByFct	             */
  BIND("dir.file.separator"	);   		   /* RscString	             */
  BIND("dump.symbols"		);   		   /* RscBoolean	     */
  BIND("env.separator"		);   		   /* RscString	             */
  BIND("extract.file"		);   		   /* RscByFct	             */
  BIND("extract.regex"		);   		   /* RscByFct	             */
  BIND("expand.macros"		);   		   /* RscBoolean	     */
  BIND("expand.crossref"	);   		   /* RscBoolean	     */
  BIND("fmt.inter.name"		);   		   /* RscByFct	             */
  BIND("fmt.name.pre"		);   		   /* RscByFct	             */
  BIND("fmt.name.name"		);   		   /* RscByFct	             */
  BIND("fmt.name.title"		);   		   /* RscByFct	             */
  BIND("fmt.title.title"	);   		   /* RscByFct	             */
  BIND("fmt.et.al"		);   		   /* RscByFct	             */
  BIND("fmt.word.separator"	);   		   /* RscByFct	             */
  BIND("field.type"		);   		   /* RscByFct	             */
  Bind("false"			, sym_false);	   /* RscTerm	             */
  BIND("input"			);   		   /* RscByFct	             */
  BIND("ignored.word"		);   		   /* RscByFct	             */
  Bind("ilike"			, sym_ilike);	   /* RscTerm	             */
  BIND("key.generation"		);   		   /* RscBoolean	     */
  BIND("key.base"		);   		   /* RscByFct	             */
  BIND("key.format"		);   		   /* RscByFct	             */
  BIND("key.make.alias"		);   		   /* RscBoolean	     */
  BIND("key.number.separator"	);   		   /* RscByFct	             */
  BIND("key.expand.macros"	);   		   /* RscBoolean	     */
  Bind("like"			, sym_like); 	   /* RscTerm	             */
  BIND("macro.file"		);   		   /* RscByFct	             */
  Bind("mod"			, sym_mod);  	   /* RscTerm	             */
  BIND("new.entry.type"		);   		   /* RscByFct	             */
  BIND("new.field.type"		);   		   /* RscByFct	             */
  BIND("new.format.type"	);   		   /* RscByFct	             */
  Bind("not"			,sym_not);   	   /* RscTerm	             */
  BIND("nil"			);   		   /* RscTerm	             */
  BIND("output.file"		);   		   /* RscByFct	             */
  Bind("or"			,sym_or);	   /* RscTerm	             */
  BIND("pass.comments"		);   		   /* RscBoolean	     */
  BIND("preserve.key.case"	);   		   /* RscBoolean	     */
  BIND("preserve.keys"		);   		   /* RscBoolean	     */
  BindGet("print"		, g_print);	   /* RscByFct	             */
  BIND("print.align.string"	);   		   /* RscNumeric	     */
  BIND("print.align.comment"	);   		   /* RscNumeric	     */
  BIND("print.align.preamble"	);   		   /* RscNumeric	     */
  BIND("print.align.key"	);   		   /* RscNumeric	     */
  BIND("print.align"		);   		   /* RscNumeric	     */
  BIND("print.all.strings"	);   		   /* RscBoolean	     */
  BIND("print.entry.types"	);   		   /* RscString	             */
  BIND("print.equal.right"	);   		   /* RscBoolean	     */
  BIND("print.braces"		);   		   /* RscBoolean	     */
  BIND("print.comma.at.end"	);   		   /* RscBoolean	     */
  BIND("print.deleted.prefix"	);   		   /* RscString	             */
  BIND("print.deleted.entries"	);   		   /* RscBoolean	     */
  BIND("print.indent"		);   		   /* RscNumeric	     */
  BIND("print.line.length"	);   		   /* RscNumeric	     */
  BIND("print.newline"		);   		   /* RscNumeric	     */
  BIND("print.parentheses"	);   		   /* RscBoolean	     */
  BIND("print.terminal.comma"	);   		   /* RscBoolean	     */
  BIND("print.use.tab"		);   		   /* RscBoolean	     */
  BIND("print.wide.equal"	);   		   /* RscBoolean	     */
  Bind("quote"			, sym_quote);	   /*	                     */
  BIND("quiet"			);   		   /* RscBoolean	     */
  BIND("regexp.syntax"		);   		   /* RscByFct	             */
  BIND("rename.field"		);   		   /* RscByFct	             */
  BIND("resource"		);   		   /* RscByFct	             */
  BIND("resource.search.path"	);   		   /* RscByFct	             */
  BIND("rewrite.rule"		);   		   /* RscByFct	             */
  BIND("rewrite.case.sensitive"	);   		   /* RscBoolean	     */
  BIND("rewrite.limit"		);   		   /* RscNumeric	     */
  BIND("select"			);   		   /* RscByFct	             */
  BIND("select.by.string"	);   		   /* RscByFct	             */
  BIND("select.by.non.string"	);   		   /* RscByFct	             */
  BIND("select.by.string.ignored");   		   /* RscString	             */
  BIND("select.case.sensitive"	);   		   /* RscBoolean	     */
  BIND("select.fields"		);   		   /* RscString	             */
  BIND("select.non"		);   		   /* RscByFct	             */
  BIND("select.crossrefs"	);   		   /* RscBoolean	     */
  BIND("sort"			);   		   /* RscBoolean	     */
  BIND("sort.cased"		);   		   /* RscBoolean	     */
  BIND("sort.macros"		);   		   /* RscBoolean	     */
  BIND("sort.reverse"		);   		   /* RscBoolean	     */
  BIND("sort.order"		);   		   /* RscByFct	             */
  BIND("sort.format"		);   		   /* RscByFct	             */
  BIND("suppress.initial.newline");   		   /* RscBoolean	     */
  BIND("symbol.type"		);   		   /* RscByFct	             */
  BIND("tex.define"		);   		   /* RscByFct	             */
  Bind("true"			, sym_true);  	   /* RscTerm	             */
  BindGet("verbose"		, g_verbose);	   /* RscBoolean	     */
  BindGet("version"		, g_version);	   /* RscByFct	             */
 						   /*                        */
  Bind("function"	, sym_fct);	   	   /*                        */
  Bind("="		, sym_set);	   	   /*                        */
  Bind("=="		, sym_eq);	   	   /*                        */
  Bind("<="		, sym_le);	   	   /*                        */
  Bind("<"		, sym_lt);	   	   /*                        */
  Bind(">="		, sym_ge);	   	   /*                        */
  Bind(">"		, sym_gt);	   	   /*                        */
  Bind("!="		, sym_ne);	   	   /*                        */
  Bind("+"		, sym_plus);	   	   /*                        */
  Bind("-"		, sym_minus);	   	   /*                        */
  Bind("*"		, sym_times);	   	   /*                        */
  Bind("/"		, sym_div);	   	   /*                        */
  Bind("&&"		, sym_and);	   	   /*                        */
  Bind("||"		, sym_or);	   	   /*                        */
  Bind("!"		, sym_not);	   	   /*                        */
  Bind("%"		, sym_mod);	   	   /*                        */
  Bind("'"		, sym_quote);	   	   /*                        */
  BIND("`"		);			   /*                        */


/*---------------------------------------------------------------------------*/
