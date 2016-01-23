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

Bind(	 "=",			     L_SET,		g_setq		    );
Bind(	 "==",			     L_EQ,		g_eq		    );
Bind(	 "!=",			     L_NE,		g_ne		    );
Bind(	 "<=",			     L_LE,		NULL		    );
Bind(	 "<",			     L_LT,		NULL		    );
Bind(	 ">=",			     L_GE,		NULL		    );
Bind(	 ">",			     L_GT,		NULL		    );
Bind(	 "+",			     L_PLUS,		g_plus		    );
Bind(	 "-",			     L_MINUS,		g_minus		    );
Bind(	 "*",			     L_TIMES,		g_times		    );
Bind(	 "/",			     L_DIV,		g_div		    );
Bind(	 "%",			     L_MOD,		g_mod		    );
Bind(	 "'",			     L_QUOTE,		NULL		    );
Bind(	 "&&",			     L_AND,		g_and		    );
Bind(	 "||",			     L_OR,		g_or		    );
Bind(	 "!",			     L_NOT,		g_not		    );
Bind(	 "`",			     L_FIELD,		NULL		    );
Bind(	 "add.field",		     L_FIELD,		NULL		    );
BindBool("apply.alias",		     g_apply_alias,	rsc_apply_alias	    );
BindBool("apply.modify",	     g_apply_modify,	rsc_apply_modify    );
BindBool("apply.include",	     g_apply_include,	rsc_apply_include   );
Bind(	 "and",			     L_AND,		g_and		    );
BindStr( "bibtex.env.name",	     g_e_bibtex,	rsc_e_bibtex	    );
BindStr( "bibtex.search.path",	     g_v_bibtex,	rsc_v_bibtex	    );
BindBool("check.double",	     g_double_check,	rsc_double_check    );
BindBool("check.double.delete",	     g_del_dbl,		rsc_del_dbl	    );
Bind(	 "check.rule",		     L_FIELD,		NULL		    );
BindBool("check.case.sensitive",     g_case_check,	rsc_case_check	    );
Bind(	 "clear.ignored.words",	     L_FIELD,		NULL		    );
BindBool("count.all",		     g_count_all,	rsc_cnt_all	    );
BindBool("count.used",		     g_count_used,	rsc_cnt_used	    );
BindNum( "crossref.limit",	     g_xref_limit,	rsc_xref_limit	    );
Bind(	 "default.key",		     L_FIELD,		NULL		    );
Bind(	 "delete.field",	     L_FIELD,		NULL		    );
BindStr( "dir.file.separator",	     g_dir_file_sep,	rsc_dir_file_sep    );
BindBool("dump.symbols",	     g_dump_symbols,	rsc_dump_symbols    );
BindStr( "env.separator",	     g_env_sep,		rsc_env_sep	    );
Bind(	 "extract.file",	     L_FIELD,		NULL		    );
Bind(	 "extract.regex",	     L_FIELD,		NULL		    );
BindBool("expand.macros",	     g_expand_macros,	rsc_expand_macros   );
BindBool("expand.crossref",	     g_expand_crossref, rsc_expand_crossref );
BindSym( "false",		     sym_false				    );
Bind(	 "fmt.inter.name",	     L_FIELD,		NULL		    );
Bind(	 "fmt.name.pre",	     L_FIELD,		NULL		    );
Bind(	 "fmt.name.name",	     L_FIELD,		NULL		    );
Bind(	 "fmt.name.title",	     L_FIELD,		NULL		    );
Bind(	 "fmt.title.title",	     L_FIELD,		NULL		    );
Bind(	 "fmt.et.al",		     L_FIELD,		NULL		    );
Bind(	 "fmt.word.separator",	     L_FIELD,		NULL		    );
Bind(	 "field.type",		     L_FIELD,		NULL		    );
Bind(	 "function",		     L_FUNCTION,	NULL		    );
Bind(	 "input",		     L_FIELD,		NULL		    );
Bind(	 "if",			     L_IF,		NULL		    );
Bind(	 "ignored.word",	     L_FIELD,		NULL		    );
Bind(	 "ilike",		     L_ILIKE,		NULL		    );
BindBool("key.generation",	     g_make_key,	rsc_make_key	    );
Bind(	 "key.base",		     L_FIELD,		NULL		    );
Bind(	 "key.format",		     L_FIELD,		NULL		    );
BindBool("key.make.alias",	     g_make_alias,	rsc_make_alias	    );
Bind(	 "key.number.separator",     L_FIELD,		NULL		    );
BindBool("key.expand.macros",	     g_key_expand_macs, rsc_key_expand_macros);
Bind(	 "like",		     L_LIKE,		NULL		    );
Bind(	 "macro.file",		     L_FIELD,		NULL		    );
Bind(	 "mod",			     L_MOD,		g_mod		    );
Bind(	 "new.entry.type",	     L_FIELD,		NULL		    );
Bind(	 "new.field.type",	     L_FIELD,		NULL		    );
Bind(	 "new.format.type",	     L_FIELD,		NULL		    );
Bind(	 "not",			     L_NOT,		g_not		    );
Bind(	 "nil",			     L_CONS,		g_self		    );
Bind(	 "output.file",		     L_FIELD,		NULL		    );
Bind(	 "or",			     L_OR,		g_or		    );
BindBool("pass.comments",	     g_pass_comments,	rsc_pass_comment    );
BindBool("preserve.key.case",	     g_key_case,	rsc_key_case	    );
BindBool("preserve.keys",	     g_preserve_keys,	rsc_key_preserve    );
Bind(	 "print",		     L_FIELD,		g_print		    );
BindNum( "print.align.string",	     g_col_s,		rsc_col_s	    );
BindNum( "print.align.comment",	     g_col_c,		rsc_col_c	    );
BindNum( "print.align.preamble",     g_col_p,		rsc_col_p	    );
BindNum( "print.align.key",	     g_col_key,		rsc_col_key	    );
BindNum( "print.align",		     g_col,		rsc_col		    );
BindBool("print.all.strings",	     g_all_macs,	rsc_all_macs	    );
BindStr( "print.entry.types",	     g_print_et,	rsc_print_et	    );
BindBool("print.equal.right",	     g_eq_right,	rsc_eq_right	    );
BindBool("print.braces",	     g_braces,		rsc_braces	    );
BindBool("print.comma.at.end",	     g_print_ce,	rsc_print_ce	    );
BindStr( "print.deleted.prefix" ,    g_del_pre,		rsc_del_pre	    );
BindBool("print.deleted.entries",    g_del_q_entries,	rsc_del_q	    );
BindNum( "print.indent",	     g_indent,		rsc_indent	    );
BindNum( "print.line.length",	     g_linelen,		rsc_linelen	    );
BindNum( "print.newline",	     g_newlines,	rsc_newlines	    );
BindBool("print.parentheses",	     g_parentheses,	rsc_parentheses	    );
BindBool("print.terminal.comma",     g_print_tc,	rsc_print_tc	    );
BindBool("print.use.tab",	     g_use_tabs,	rsc_use_tabs	    );
BindBool("print.wide.equal",	     g_print_we,	rsc_print_we	    );
Bind(	 "quote",		     L_QUOTE,		NULL		    );
BindBool("quiet",		     g_quiet,		rsc_quiet	    );
Bind(	 "regexp.syntax",	     L_FIELD,		NULL		    );
Bind(	 "rename.field",	     L_FIELD,		NULL		    );
Bind(	 "resource",		     L_FIELD,		NULL		    );
Bind(	 "resource.search.path",     L_FIELD,		NULL		    );
Bind(	 "rewrite.rule",	     L_FIELD,		NULL		    );
BindBool("rewrite.case.sensitive",   g_case_rewrite,	rsc_case_rewrite    );
BindNum( "rewrite.limit",	     g_rewrite_limit,	rsc_rewrite_limit   );
Bind(	 "select",		     L_FIELD,		NULL		    );
Bind(	 "select.by.string",	     L_FIELD,		NULL		    );
Bind(	 "select.by.non.string",     L_FIELD,		NULL		    );
BindStr( "select.by.string.ignored", g_sel_ignored,	rsc_sel_ignored	    );
BindBool("select.case.sensitive",    g_case_select,	rsc_case_select	    );
BindStr( "select.fields",	     g_sel_fields,	rsc_sel_fields	    );
Bind(	 "select.non",		     L_FIELD,		NULL		    );
BindBool("select.crossrefs",	     g_xref_select,	rsc_xref_select	    );
BindBool("sort",		     g_sort,		rsc_sort	    );
BindBool("sort.cased",		     g_sort_cased,	rsc_sort_cased	    );
BindBool("sort.macros",		     g_srt_macs,	rsc_srt_macs	    );
BindBool("sort.reverse",	     g_sort_reverse,	rsc_sort_reverse    );
Bind(	 "sort.order",		     L_FIELD,		NULL		    );
Bind(	 "sort.format",		     L_FIELD,		NULL		    );
BindBool("suppress.initial.newline", g_no_nl,		rsc_no_nl	    );
Bind(	 "symbol.type",		     L_FIELD,		NULL		    );
Bind(	 "tex.define",		     L_FIELD,		NULL		    );
BindSym( "true",		     sym_true				    );
BindBool("verbose",		     g_verbose,		rsc_verbose	    );
Bind(	 "version",		     L_FIELD,		g_version	    );
Bind(	 "while",		     L_WHILE,		NULL		    );
Bind(	 "with",		     L_WITH,		NULL		    );

/*---------------------------------------------------------------------------*/
