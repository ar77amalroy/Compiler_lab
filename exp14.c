#include <stdio.h>
#include <string.h>
int main(){
    char filename[100];
    char op[10], arg1[50], arg2[50], result[50];
    FILE *in, *out;
    printf("Enter input file name: ");
    scanf("%s", filename);
    in = fopen(filename, "r");
    if (in == NULL){
        printf("Unable to open input file.\n");
        return 1;
    }
    out = fopen("output.txt", "w");
    if (out == NULL){
        printf("Unable to create output file.\n");
        fclose(in);
        return 1;
    }
    while (fscanf(in, "%s %s %s %s", op, arg1, arg2, result) == 4){
        if (strcmp(op, "+") == 0){
            fprintf(out, "MOV R0,%s\n", arg1);
            fprintf(out, "ADD R0,%s\n", arg2);
            fprintf(out, "MOV %s,R0\n", result);
        }
        else if (strcmp(op, "-") == 0){
            fprintf(out, "MOV R0,%s\n", arg1);
            fprintf(out, "SUB R0,%s\n", arg2);
            fprintf(out, "MOV %s,R0\n", result);
        }
        else if (strcmp(op, "*") == 0){
            fprintf(out, "MOV R0,%s\n", arg1);
            fprintf(out, "MUL R0,%s\n", arg2);
            fprintf(out, "MOV %s,R0\n", result);
        }
        else if (strcmp(op, "/") == 0){
            fprintf(out, "MOV R0,%s\n", arg1);
            fprintf(out, "DIV R0,%s\n", arg2);
            fprintf(out, "MOV %s,R0\n", result);
        }
        else if (strcmp(op, "=") == 0){
            fprintf(out, "MOV R0,%s\n", arg1);
            fprintf(out, "MOV %s,R0\n", result);
        }
    }
    fclose(in);
    fclose(out);
    printf("Target code generated successfully in output.txt\n");
    return 0;}
//or
#include <stdio.h>
int main() {
    char op, a[100], b[100], c[100];
    const char *instruction;
    FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
    if (!in || !out) { printf("File error!\n"); return 1; }
    while (fscanf(in, " %c %s %s %s", &op, a, b, c) == 4) {
        switch (op) {
            case '+': instruction = "ADD"; break;
            case '-': instruction = "SUB"; break;
            case '*': instruction = "MUL"; break;
            case '/': instruction = "DIV"; break;
            case '=':
                fprintf(out, "MOV R0,%s\nMOV %s,R0\n", a, c);
                continue;
            default: continue;
        }
        fprintf(out, "MOV R0,%s\n", a);
        fprintf(out, "%s R0,%s\n", instruction, b);
        fprintf(out, "MOV %s,R0\n", c);
    }
    printf("Target code generated in output.txt\n");
    fclose(in); fclose(out); return 0;
}
