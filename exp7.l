%{
#include "y.tab.h"
%}
%%
"int"       { return KEYWORD; }
"float"     { return KEYWORD; }
"double"    { return KEYWORD; }
[a-zA-Z_][a-zA-Z0-9_]*   { return IDENTIFIER; }
[ \t\n]+    ;
.           { return INVALID; }
%%
//or 
%{
#include "y.tab.h"
%}
%option noyywrap
%%
[a-zA-Z][a-zA-Z0-9]*   { return IDENTIFIER; }
\n                     { return NL; }
[ \t]+                 ;
.                      { return yytext[0]; }
%%
