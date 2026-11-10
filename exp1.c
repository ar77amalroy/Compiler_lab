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
//or







#include <stdio.h>
#include <ctype.h>
#include <string.h>
int isKeyword(char *w){
    char *k[] = {"int", "float", "if", "else", "while", "return"};
    for(int i = 0; i < 6; i++)
        if(!strcmp(w, k[i])) return 1;
    return 0;
}
void lexical(FILE *fp){
    int ch, next, prev, i;
    char w[30];
    while((ch = fgetc(fp)) != EOF){
        if(isspace(ch)) continue;
        if(ch == '/'){
            next = fgetc(fp);
            if(next == '/'){
                while((ch = fgetc(fp)) != '\n' && ch != EOF);
                continue;
            }
            if(next == '*'){
                for(prev = 0; (ch = fgetc(fp)) != EOF && !(prev == '*' && ch == '/'); prev = ch);
                continue;
            }
            ungetc(next, fp);
            printf("/-->Operator\n");
        }
        else if(isalpha(ch) || ch == '_'){
            for(i = 0; isalnum(ch) || ch == '_'; ch = fgetc(fp)) w[i++] = ch;
            w[i] = '\0';
            ungetc(ch, fp);
            printf("%s-->%s\n", w, isKeyword(w) ? "Keyword" : "Identifier");
        }
        else if(isdigit(ch)){
            for(i = 0; isdigit(ch); ch = fgetc(fp)) w[i++] = ch;
            w[i] = '\0';
            ungetc(ch, fp);
            printf("%s-->Number\n", w);
        }
        else if(strchr("+-*=<>%", ch))
            printf("%c-->Operator\n", ch);
        else if(strchr(";,(){}[]", ch))
            printf("%c-->Delimiter\n", ch);
        else
            printf("%c-->Invalid token\n", ch);
    }
}
int main(){
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "r");
    if(!fp){
        printf("Error! Cannot open file.\n");
        return 0;
    }
    lexical(fp);
    fclose(fp);
    return 0;
}
