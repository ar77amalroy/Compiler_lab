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
"int"                      { return KEYWORD; }
"float"                    { return KEYWORD; }
"double"                   { return KEYWORD; }
[a-zA-Z_][a-zA-Z0-9_]*     { return IDENTIFIER; }
[0-9][a-zA-Z0-9_]*         { return INVALID; }
\n                         { return NL; }
[ \t]+                     ;
.                          { return INVALID; }
%%
