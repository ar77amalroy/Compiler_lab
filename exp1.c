#include<stdio.h>
#include<ctype.h>
#include<string.h>
char *keywords[]={"int", "float", "if", "else", "while", "return"};
int isKeyword(char word[]){
    int i;
    for(i=0;i<6;i++){
        if(strcmp(word,keywords[i])==0)
            return 1;
    }
    return 0;
}
void lexical(FILE *fp){
    char ch;
    while((ch=fgetc(fp))!=EOF){
        if(isspace(ch))
            continue;
        if(ch == '/')
        {
            char next = fgetc(fp);
            if(next == '/')
            {
                while((ch = fgetc(fp)) != '\n' && ch != EOF);
                continue;
            }
            else if(next == '*')
            {
                char prev = 0;
                while((ch = fgetc(fp)) != EOF)
                {
                    if(prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
                continue;
            }
            else
            {
                ungetc(next, fp);
                printf("%c-->Operator\n", ch);
            }
        }
        else if(isalpha(ch) || ch=='_'){
            char word[30];
            int i=0;
            do{
                word[i++]=ch;
                ch=fgetc(fp);
            }while(isalnum(ch) || ch=='_');
            word[i]='\0';
            ungetc(ch,fp);
            if(isKeyword(word))
                printf("%s-->Keyword\n",word);
            else
                printf("%s-->Identifier\n",word);
        }
        else if(isdigit(ch)){
            char num[20];
            int i=0;
            do{
                num[i++]=ch;
                ch=fgetc(fp);
            }while(isdigit(ch));
            num[i]='\0';
            ungetc(ch,fp);
            printf("%s-->Number\n",num);
        }
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='='||ch=='<'||ch=='>'||ch=='%'){
            printf("%c-->Operator\n",ch);
        }
        else if(ch==';'||ch==','||ch=='('||ch==')'||ch=='{'||ch=='}'||ch=='['||ch==']'){
            printf("%c-->Delimiter\n",ch);
        }
        else{
            printf("%c-->Invalid token\n",ch);
        }
    }
}
int main(){
    FILE *fp;
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error! Cannot open file.\n");
        return 0;
    }
    lexical(fp);
    fclose(fp);
    return 0;
}
