%{
#include <stdio.h>
#include <stdlib.h> 
%}

%%

"if"|"else"|"int"|"switch"|"char" {
    printf("Keyword: %s\n", yytext);
}

[a-z_][a-z0-9_]* {
    printf("Identifier: %s\n", yytext);
}

[0-9]+ {
    printf("Number: %s\n", yytext);
}

"="|"+"|"*"|"/"|"<"|">" {
    printf("Operator: %s\n", yytext);
}

"("|")"|"{"|"}" {
	printf("Separator: %s\n",yytext);
}

"\n" {
    exit(0);
}

[ \t] {
}

. {
}

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter input text:\n");
    yylex();
    return 0;
}

