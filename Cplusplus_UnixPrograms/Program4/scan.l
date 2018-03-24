/*
 * Ryan Hosford
 * rph160030@utdallas.edu
 * CS 3377.501
 * scan.l - lex file for scanner
 */

%option noyywrap
%option nounput
%option noinput

%{
  #include <stdlib.h>
  #include "y.tab.h"
%}

%%


[ \t\r]+	{ /* eat up whitespace */ }
"#"		{ return HASH; }
","		{ return COMMA; }
"-"		{ return DASH; }
"Sr."		{ return SR; }
"Jr."		{ return JR; }
"\n"		{ return EOL;}
[a-zA-Z]\.*	{ yylval.str = strdup(yytext); return INIT; }
[IVX]+		{ yylval.str = strdup(yytext); return ROMAN; }
[0-9]+		{ yylval.value = atoi(yytext); return INTEGER; }
[a-zA-Z]{2,}	{ yylval.value = strdup(yytext); return NAME; }
[0-9a-zA-Z]+		{ yylval.value = strdup(yytext); return IDENTIFIER; }


%%

/* 
 * This section is empty on purpose.
 *    DO NOT PUT YOUR main() routine here.
 *    
 * Put your main routine in a separate file.
 */
