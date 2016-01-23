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
  BindBool("apply.alias"		, g_apply_alias, rsc_apply_alias);/* RscBoolean*/
  BindBool("apply.modify"		, g_apply_modify, rsc_apply_modify);/* RscBoolean*/
  BindBool("apply.include"		, g_apply_include, rsc_apply_include);/* RscBoolean*/
  Bind("and"			, sym_and);  	   /* RscTerm	             */
  BIND("bibtex.env.name"	);   		   /* RscString	             */
  BIND("bibtex.search.path"	);   		   /* RscString	             */
  BindBool("check.double"		, g_check_double, rsc_double_check);/* RscBoolean*/
  BindBool("check.double.delete"	, g_check_double_delete, rsc_del_dbl);/* RscBoolean*/
  BIND("check.rule"		);   		   /* RscByFct	             */
  BindBool("check.case.sensitive"	, g_check_case_sensitive, rsc_case_check);/* RscBoolean*/
  BIND("clear.ignored.words"	);   		   /* RscByFct	             */
  BindBool("count.all"		, g_count_all, rsc_cnt_all);/* RscBoolean	*/
  BindBool("count.used"		, g_count_used, rsc_cnt_used);/* RscBoolean*/
  BIND("crossref.limit"		);   		   /* RscNumeric	     */
  BIND("default.key"		);   		   /* RscByFct	             */
  BIND("delete.field"		);   		   /* RscByFct	             */
  BIND("dir.file.separator"	);   		   /* RscString	             */
  BindBool("dump.symbols"		, g_dump_symbols, rsc_dump_symbols);/* RscBoolean*/
  BIND("env.separator"		);   		   /* RscString	             */
  BIND("extract.file"		);   		   /* RscByFct	             */
  BIND("extract.regex"		);   		   /* RscByFct	             */
  BindBool("expand.macros"		, g_expand_macros, rsc_expand_macros);/* RscBoolean*/
  BindBool("expand.crossref"	, g_expand_crossref, rsc_expand_crossref);/* RscBoolean*/
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
  BindBool("key.generation"	, g_make_key, rsc_make_key);/* RscBoolean    */
  BIND("key.base"		);   		   /* RscByFct	             */
  BIND("key.format"		);   		   /* RscByFct	             */
  BindBool("key.make.alias"	, g_key_make_alias, rsc_make_alias);/* RscBoolean*/
  BIND("key.number.separator"	);   		   /* RscByFct	             */
  BindBool("key.expand.macros"	, g_key_expand_macros, rsc_key_expand_macros);/* RscBoolean*/
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
  BindBool("pass.comments"	, g_pass_comments, rsc_pass_comment);/* RscBoolean*/
  BindBool("preserve.key.case"	, g_preserve_key_case, rsc_key_case);/* RscBoolean*/
  BindBool("preserve.keys"	, g_preserve_keys, rsc_key_preserve);/* RscBoolean*/
  BindGet("print"		, g_print);	   /* RscByFct	             */
  BIND("print.align.string"	);   		   /* RscNumeric	     */
  BIND("print.align.comment"	);   		   /* RscNumeric	     */
  BIND("print.align.preamble"	);   		   /* RscNumeric	     */
  BIND("print.align.key"	);   		   /* RscNumeric	     */
  BIND("print.align"		);   		   /* RscNumeric	     */
  BindBool("print.all.strings"	, g_print_all_strings, rsc_all_macs);/* RscBoolean*/
  BIND("print.entry.types"	);   		   /* RscString	             */
  BindBool("print.equal.right"	, g_eq_right, rsc_eq_right);/* RscBoolean    */
  BindBool("print.braces"	, g_braces, rsc_braces);/* RscBoolean        */
  BindBool("print.comma.at.end"	, g_print_ce, rsc_print_ce);/* RscBoolean    */
  BIND("print.deleted.prefix"	);   		   /* RscString	             */
  BindBool("print.deleted.entries", g_del_q_entries, rsc_del_q);/* RscBoolean*/
  BIND("print.indent"		);   		   /* RscNumeric	     */
  BIND("print.line.length"	);   		   /* RscNumeric	     */
  BIND("print.newline"		);   		   /* RscNumeric	     */
  BindBool("print.parentheses"	, g_parentheses, rsc_parentheses);/* RscBoolean*/
  BindBool("print.terminal.comma", g_print_tc, rsc_print_tc);/* RscBoolean   */
  BindBool("print.use.tab"	, g_use_tabs, rsc_use_tabs);/* RscBoolean    */
  BindBool("print.wide.equal"	, g_print_we, rsc_print_we);/* RscBoolean    */
  Bind("quote"			, sym_quote);	   /*	                     */
  BindBool("quiet"		, g_quiet, rsc_quiet);/* RscBoolean	     */
  BIND("regexp.syntax"		);   		   /* RscByFct	             */
  BIND("rename.field"		);   		   /* RscByFct	             */
  BIND("resource"		);   		   /* RscByFct	             */
  BIND("resource.search.path"	);   		   /* RscByFct	             */
  BIND("rewrite.rule"		);   		   /* RscByFct	             */
  BindBool("rewrite.case.sensitive", g_case_rewrite, rsc_case_rewrite);/* RscBoolean*/
  BIND("rewrite.limit"		);   		   /* RscNumeric	     */
  BIND("select"			);   		   /* RscByFct	             */
  BIND("select.by.string"	);   		   /* RscByFct	             */
  BIND("select.by.non.string"	);   		   /* RscByFct	             */
  BIND("select.by.string.ignored");   		   /* RscString	             */
  BindBool("select.case.sensitive", g_case_select, rsc_case_select);/* RscBoolean*/
  BIND("select.fields"		);   		   /* RscString	             */
  BIND("select.non"		);   		   /* RscByFct	             */
  BindBool("select.crossrefs"	, g_xref_select, rsc_xref_select);/* RscBoolean*/
  BindBool("sort"		, g_sort, rsc_sort);/* RscBoolean	     */
  BindBool("sort.cased"		, g_sort_cased, rsc_sort_cased);/* RscBoolean*/
  BindBool("sort.macros"	, g_srt_macs, rsc_srt_macs);/* RscBoolean    */
  BindBool("sort.reverse"	, g_sort_reverse, rsc_sort_reverse);/* RscBoolean*/
  BIND("sort.order"		);   		   /* RscByFct	             */
  BIND("sort.format"		);   		   /* RscByFct	             */
  BindBool("suppress.initial.newline", g_no_nl, rsc_no_nl);/* RscBoolean     */
  BIND("symbol.type"		);   		   /* RscByFct	             */
  BIND("tex.define"		);   		   /* RscByFct	             */
  Bind("true"			, sym_true);  	   /* RscTerm	             */
  BindBool("verbose"		, g_verbose, rsc_verbose);/* RscBoolean      */
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
