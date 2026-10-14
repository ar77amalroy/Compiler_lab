#include <stdio.h>
#include <string.h>

char p[20][30], st[100], in[100];
int n, top = -1, pos = 0;

void show(char action[])
{
    int i;

    printf("$");
    for(i = 0; i <= top; i++)
    {
        if(st[i] == 'i')
            printf("id");
        else
            printf("%c", st[i]);
    }

    printf("\t\t");

    for(i = pos; in[i]; i++)
    {
        if(in[i] == 'i')
            printf("id");
        else
            printf("%c", in[i]);
    }

    printf("$\t\t%s\n", action);
}

void convert(char s[], char t[])
{
    int i = 0, j = 0;

    while(s[i])
    {
        if(s[i] == 'i' && s[i + 1] == 'd')
        {
            t[j++] = 'i';
            i += 2;
        }
        else
            t[j++] = s[i++];

    }

    t[j] = '\0';
}

int reduce()
{
    int i, j, len;
    char rhs[30], action[60];

    for(i = 0; i < n; i++)
    {
        convert(p[i] + 3, rhs);
        len = strlen(rhs);

        if(len > top + 1)
            continue;

        for(j = 0; j < len; j++)
        {
            if(st[top - len + 1 + j] != rhs[j])
                break;
        }

        if(j != len)
            continue;

        if(p[i][0] == 'E' &&
           strcmp(rhs, "E+E") == 0 &&
           in[pos] == '*')
            return 0;

        top -= len;
        st[++top] = p[i][0];

        sprintf(action, "REDUCE TO %c (%s)",
                p[i][0], p[i]);

        show(action);
        return 1;
    }

    return 0;
}

int main()
{
    int i;
    char temp[100];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions:\n");

    for(i = 0; i < n; i++)
        scanf("%s", p[i]);

    printf("\nEnter input string: ");
    scanf("%s", temp);

    convert(temp, in);

    printf("\nStack\t\tInput\t\tAction\n");
    printf("$\t\t%s$\t\t--\n", temp);

    while(in[pos])
    {
        st[++top] = in[pos++];

        if(st[top] == 'i')
            show("SHIFT -> id");
        else
            show("SHIFT");

        while(reduce())
            ;
    }

    while(reduce())
        ;

    if(top == 0 && st[0] == p[0][0])
        printf("$%c\t\t$\t\tACCEPT\n", st[0]);
    else
        printf("$%c\t\t$\t\tREJECT\n", st[0]);

    return 0;
}
