%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
void yyerror(char *s);
int hasID = 0;
%}
%union
{
    double val;
}
%token <val> DIGIT
%token ID NL
%type <val> exp
%left '+' '-'
%left '*' '/'
%left '='
%left '(' ')'
%%
stmt : ID '=' exp NL
     {
        printf("Valid Expression\n");
        exit(0);
     }
     | exp NL
     {
        printf("Valid Expression\n");
        if(hasID == 0)
        {
            printf("Result = %.2lf\n",$1);
        }
        exit(0);
     }
     ;
exp : exp '+' exp
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
        if($3 == 0)
        {
            printf("Division by zero error\n");
            exit(0);
        }
        $$ = $1 / $3;
    }
    | '(' exp ')'
    {
        $$ = $2;
    }
    | DIGIT
    {
        $$ = $1;
    }
    | ID
    {
        hasID = 1;
        $$ = 0;
    }
    ;
%%
void yyerror(char *s){
    printf("Invalid Expression\n");
}
int main(){
    printf("Enter an arithmetic expression: ");
    yyparse();
    return 0;
}
