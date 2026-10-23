%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
int divzero = 0;
%}
%token DIGIT NL INVALID
%left '+' '-'
%left '*' '/'
%right UMINUS
%%
stmt:
      exp NL
      {
          if (!divzero)
              printf("Result = %d\n", $1);
          divzero = 0;
      }
    | INVALID NL
      {
          printf("Not a number\n");
      }
    ;
exp:
      exp '+' exp
      {
          $$ = $1 + $3;
      }
    | exp '-' exp
      {
          $$ = $1 - $3;
      }
    | exp '*' exp
      {
          $$ = $1 * $3;
      }
    | exp '/' exp
      {
          if ($3 == 0)
          {
              printf("Division by 0 not possible\n");
              divzero = 1;
              $$ = 0;
          }
          else
          {
              $$ = $1 / $3;
          }
      }
    | '(' exp ')'
      {
          $$ = $2;
      }
    | '-' exp %prec UMINUS
      {
          $$ = -$2;
      }
    | DIGIT
      {
          $$ = $1;
      }
    ;
%%
void yyerror(const char *s){
    printf("Not a number\n");
}
int main(){
    printf("Enter expression: ");
    yyparse();
    return 0;
}
