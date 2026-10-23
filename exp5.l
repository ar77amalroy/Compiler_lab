%{
#include <stdio.h>
int vowels = 0, consonants = 0;
%}
%%
[aeiouAEIOU]        { vowels++; }
[a-zA-Z]            { consonants++; }
.|\n                { }
%%
int yywrap(){
    return 1;
}
int main(){
    printf("Enter the input string:\n");
    yylex();
    printf("Total number of vowels = %d\n", vowels);
    printf("Total number of consonants = %d\n", consonants);
    return 0;
}
