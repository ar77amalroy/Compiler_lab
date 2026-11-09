%{
#include "y.tab.h"
#include <stdlib.h>
%}
%%
-?[0-9]+   {
                yylval = atoi(yytext);
                return DIGIT;
            }
[ \t]       ;
\n          return NL;
"+"         return '+';
"-"         return '-';
"*"         return '*';
"/"         return '/';
"("         return '(';
")"         return ')';
[a-zA-Z]+   return INVALID;
.           return INVALID;
%%
int yywrap(){
    return 1;
}
//or
%{
#include "y.tab.h"
#include <stdlib.h>
%}
%option noyywrap
%%
[0-9]+     { yylval = atoi(yytext); return DIGIT; }
[ \t]      ;
\n         return NL;
[-+*/()]   return yytext[0];
.          return INVALID;
%%
