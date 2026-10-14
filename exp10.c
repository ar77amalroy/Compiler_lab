#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX];
char first[MAX][MAX];
char follow[MAX][MAX];
int n;

/* Check whether a character is a non-terminal */
int isNonTerminal(char c)
{
    return (c >= 'A' && c <= 'Z');
}

/* Add a character to a set if it is not already present */
void addToSet(char set[], char c)
{
    int i;

    if (c == '\0')
        return;

    for (i = 0; set[i] != '\0'; i++)
    {
        if (set[i] == c)
            return;
    }

    set[i] = c;
    set[i + 1] = '\0';
}

/* Find FIRST of a symbol */
void findFirst(char symbol)
{
    int i, j, k;
    char *rhs;
    int nullable;

    for (i = 0; i < n; i++)
    {
        /* Check productions having this symbol on LHS */
        if (production[i][0] != symbol)
            continue;

        /* For A->XYZ, RHS starts at index 3 */
        rhs = production[i] + 3;

        nullable = 1;

        for (j = 0; rhs[j] != '\0'; j++)
        {
            char current = rhs[j];

            /* If current symbol is terminal */
            if (!isNonTerminal(current))
            {
                addToSet(first[symbol - 'A'], current);

                if (current != '#')
                    nullable = 0;

                break;
            }

            /* If current symbol is non-terminal */
            findFirst(current);

            /* Add FIRST(current) except epsilon */
            for (k = 0; first[current - 'A'][k] != '\0'; k++)
            {
                if (first[current - 'A'][k] != '#')
                {
                    addToSet(first[symbol - 'A'],
                             first[current - 'A'][k]);
                }
            }

            /* If current cannot produce epsilon, stop */
            if (strchr(first[current - 'A'], '#') == NULL)
            {
                nullable = 0;
                break;
            }
        }

        /* If all symbols can produce epsilon */
        if (nullable)
        {
            addToSet(first[symbol - 'A'], '#');
        }
    }
}

/* Find FOLLOW of a symbol */
void findFollow(char symbol)
{
    int i, j, k, x;
    char lhs;
    char *rhs;

    /* Start symbol gets $ */
    if (symbol == production[0][0])
    {
        addToSet(follow[symbol - 'A'], '$');
    }

    for (i = 0; i < n; i++)
    {
        lhs = production[i][0];

        /* For A->XYZ, RHS starts at index 3 */
        rhs = production[i] + 3;

        for (j = 0; rhs[j] != '\0'; j++)
        {
            /* Look for the symbol in RHS */
            if (rhs[j] != symbol)
                continue;

            int epsilonFound = 1;

            /* Check symbols after the current symbol */
            for (k = j + 1; rhs[k] != '\0'; k++)
            {
                char next = rhs[k];

                /* If next is a terminal */
                if (!isNonTerminal(next))
                {
                    if (next != '#')
                    {
                        addToSet(follow[symbol - 'A'], next);
                    }

                    epsilonFound = 0;
                    break;
                }

                /* Add FIRST(next), except epsilon */
                for (x = 0; first[next - 'A'][x] != '\0'; x++)
                {
                    if (first[next - 'A'][x] != '#')
                    {
                        addToSet(follow[symbol - 'A'],
                                 first[next - 'A'][x]);
                    }
                }

                /* If next cannot produce epsilon, stop */
                if (strchr(first[next - 'A'], '#') == NULL)
                {
                    epsilonFound = 0;
                    break;
                }
            }

            /*
             * If symbol is at the end of RHS,
             * or everything after it can produce epsilon,
             * add FOLLOW(LHS).
             */
            if (epsilonFound && lhs != symbol)
            {
                findFollow(lhs);

                for (k = 0; follow[lhs - 'A'][k] != '\0'; k++)
                {
                    addToSet(follow[symbol - 'A'],
                             follow[lhs - 'A'][k]);
                }
            }
        }
    }
}

/* Print a set with commas */
void printSet(char set[])
{
    int i;

    printf("{ ");

    for (i = 0; set[i] != '\0'; i++)
    {
        if (i > 0)
            printf(", ");

        printf("%c", set[i]);
    }

    printf(" }");
}

int main()
{
    int i, j;
    char symbol;
    int alreadyPrinted;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions using -> (example: S->ABC):\n");

    for (i = 0; i < n; i++)
    {
        scanf("%s", production[i]);
    }

    /* Initialize FIRST and FOLLOW arrays */
    for (i = 0; i < MAX; i++)
    {
        first[i][0] = '\0';
        follow[i][0] = '\0';
    }

    /* Find FIRST sets */
    for (i = 0; i < n; i++)
    {
        findFirst(production[i][0]);
    }

    /* Find FOLLOW sets */
    for (i = 0; i < n; i++)
    {
        findFollow(production[i][0]);
    }

    /* Print FIRST sets */
    printf("\nFIRST sets:\n");

    for (i = 0; i < n; i++)
    {
        symbol = production[i][0];
        alreadyPrinted = 0;

        /* Avoid printing the same non-terminal twice */
        for (j = 0; j < i; j++)
        {
            if (production[j][0] == symbol)
            {
                alreadyPrinted = 1;
                break;
            }
        }

        if (!alreadyPrinted)
        {
            printf("FIRST(%c) = ", symbol);

            printSet(first[symbol - 'A']);

            printf("\n");
        }
    }

    /* Print FOLLOW sets */
    printf("\nFOLLOW sets:\n");

    for (i = 0; i < n; i++)
    {
        symbol = production[i][0];
        alreadyPrinted = 0;

        /* Avoid printing the same non-terminal twice */
        for (j = 0; j < i; j++)
        {
            if (production[j][0] == symbol)
            {
                alreadyPrinted = 1;
                break;
            }
        }

        if (!alreadyPrinted)
        {
            printf("FOLLOW(%c) = ", symbol);

            printSet(follow[symbol - 'A']);

            printf("\n");
        }
    }

    return 0;
}
