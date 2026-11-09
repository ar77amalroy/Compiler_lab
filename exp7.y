%{
#include <stdio.h>
int yylex();
void yyerror(const char *s);
%}
%token KEYWORD IDENTIFIER INVALID
%%
input:
      KEYWORD
        {
            printf("Invalid identifier since it is Keyword\n");
        }
    | IDENTIFIER
        {
            printf("Valid Identifier\n");
        }
    | INVALID
        {
            printf("Invalid Identifier\n");
        }
    ;
%%
int main(){
    printf("Enter input: ");
    yyparse();
    return 0;
}
void yyerror(const char *s)
{
    printf("Invalid Identifier\n");
}
//or 
%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}
%token IDENTIFIER NL
%%
input : IDENTIFIER NL
          { printf("Valid Identifier\n"); exit(0); }
      ;
%%
int main() {
    printf("Enter input: ");
    yyparse();
    return 0;
}
void yyerror(const char *s) {
    printf("Invalid Identifier\n");
}
