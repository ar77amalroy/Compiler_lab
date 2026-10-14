#include <stdio.h>
#include <string.h>

int main()
{
    char filename[100];
    char op[10], arg1[50], arg2[50], result[50];
    FILE *in, *out;

    printf("Enter input file name: ");
    scanf("%s", filename);

    in = fopen(filename, "r");
    if (in == NULL)
    {
        printf("Unable to open input file.\n");
        return 1;
    }

    out = fopen("output.txt", "w");
    if (out == NULL)
    {
        printf("Unable to create output file.\n");
        fclose(in);
        return 1;
    }

    while (fscanf(in, "%s %s %s %s", op, arg1, arg2, result) == 4)
    {
        if (strcmp(op, "+") == 0)
        {
            fprintf(out, "MOV R0,%s\n", arg1);
            fprintf(out, "ADD R0,%s\n", arg2);
            fprintf(out, "MOV %s,R0\n", result);
        }
        else if (strcmp(op, "-") == 0)
        {
            fprintf(out, "MOV R0,%s\n", arg1);
            fprintf(out, "SUB R0,%s\n", arg2);
            fprintf(out, "MOV %s,R0\n", result);
        }
        else if (strcmp(op, "*") == 0)
        {
            fprintf(out, "MOV R0,%s\n", arg1);
            fprintf(out, "MUL R0,%s\n", arg2);
            fprintf(out, "MOV %s,R0\n", result);
        }
        else if (strcmp(op, "/") == 0)
        {
            fprintf(out, "MOV R0,%s\n", arg1);
            fprintf(out, "DIV R0,%s\n", arg2);
            fprintf(out, "MOV %s,R0\n", result);
        }
        else if (strcmp(op, "=") == 0)
        {
            fprintf(out, "MOV R0,%s\n", arg1);
            fprintf(out, "MOV %s,R0\n", result);
        }
    }

    fclose(in);
    fclose(out);

    printf("Target code generated successfully in output.txt\n");

    return 0;
}
