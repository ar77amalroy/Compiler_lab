%{
#include <stdio.h>
int lines=0,words=0,chars=0;
%}
%%
[a-zA-Z0-9]+	{words++; chars +=yyleng;}
[\t]		{chars++;}
\n		{lines++; chars++;}
.		{chars++;}
%%
int yywrap()
{
	return 1;
}
int main(){
	FILE *fp;
	char fname[100];
	printf("Enter input file name: ");
	scanf("%s", fname);
	fp=fopen(fname,"r");
	if(fp==NULL){
		printf("Cannot open file\n");
		return 0;
	}
	yyin=fp;
	yylex();
	printf("Number of lines=%d\n",lines);
	printf("Number of words=%d\n",words);
	printf("Number of characters=%d\n",chars);
	fclose(fp);
	return 0;
}
