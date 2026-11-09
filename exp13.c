#include <stdio.h>
#include <string.h>
char expr[100];
char rhs[100];
int tempCount = 0;
void generateCode(){
    int i, j;
    char op, a, b, result;
    for (i = 0; expr[i] != '\0'; i++){
        if (expr[i] == '=' || expr[i] == ':'){
            strcpy(rhs, expr + i + 1);
            break;
        }
    }
    for (i = 0; rhs[i] != '\0'; i++){
        if (rhs[i] == '*' || rhs[i] == '/'){
            op = rhs[i];
            a = rhs[i - 1];
            b = rhs[i + 1];
            result = 'Z' - tempCount;
            printf("%c=%c%c%c\n", result, a, op, b);
            rhs[i - 1] = result;
            rhs[i] = ' ';
            rhs[i + 1] = ' ';
            tempCount++;
            i = -1;
        }
    }
    for (i = 0; rhs[i] != '\0'; i++){
        if (rhs[i] == '+' || rhs[i] == '-') {
            op = rhs[i];
            j = i - 1;
            while (j >= 0 && rhs[j] == ' ')
                j--;
            a = rhs[j];
            j = i + 1;
            while (rhs[j] == ' ')
                j++;
            b = rhs[j];
            result = 'Z' - tempCount;
            printf("%c=%c%c%c\n", result, a, op, b);
            rhs[j] = result;
            rhs[i] = ' ';
            rhs[j - 1] = ' ';
            tempCount++;
            i = -1;
        }
    }
}
int main(){
    printf("Enter expression: ");
    scanf("%s", expr);
    printf("\nIntermediate Code:\n");
    generateCode();
    return 0;
}
//or



#include <stdio.h>
#include <string.h>
char rhs[100];
int t = 0;
void reduce(const char *ops) {
    for (int i = 0; rhs[i]; i++)
        if (strchr(ops, rhs[i])) {
            int l = i - 1, r = i + 1;
            while (rhs[l] == ' ') l--;
            while (rhs[r] == ' ') r++;
            char res = 'Z' - t++;
            printf("%c=%c%c%c\n", res, rhs[l], rhs[i], rhs[r]);
            rhs[l] = res;
            rhs[i] = rhs[r] = ' ';
            i = -1;
        }
}
int main() {
    char expr[100], *p, *q;
    printf("Enter expression: ");
    scanf("%s", expr);
    p = strpbrk(expr, "=:");
    strcpy(rhs, p ? p + 1 : expr);
    printf("\nIntermediate Code:\n");
    reduce("*/");
    reduce("+-");
    if (p) {
        q = rhs;
        while (*q == ' ') q++;
        printf("%c=%c\n", expr[0], *q);
    }
    return 0;
}
