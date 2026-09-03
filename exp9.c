#include <stdio.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_TRANSITIONS 50
#define MAX_LEN 20

struct Transition {
    char from[MAX_LEN];
    char symbol[MAX_LEN];
    char to[MAX_LEN];
};

int main()
{
    struct Transition transitions[MAX_TRANSITIONS];

    char states[MAX_STATES][MAX_LEN];
    char closure[MAX_STATES][MAX_LEN];
    char queue[MAX_STATES][MAX_LEN];

    int n, t;
    int i, j, front, rear, count;
    int found;

    FILE *INPUT;

    INPUT = fopen("exp9.dat", "r");

    if (INPUT == NULL)
    {
        printf("Error: Cannot open input.dat\n");
        return 1;
    }

    /* Read number of states */
    printf("Enter the no of states: ");
    scanf("%d", &n);

    /* Read states */
    printf("Enter the states: ");
    for (i = 0; i < n; i++)
    {
        scanf("%s", states[i]);
    }

    /* Read transitions from input.dat */
    t = 0;

    while (t < MAX_TRANSITIONS &&
           fscanf(INPUT, "%s %s %s",
                  transitions[t].from,
                  transitions[t].symbol,
                  transitions[t].to) == 3)
    {
        t++;
    }

    fclose(INPUT);

    /* Find epsilon closure of every state */
    for (i = 0; i < n; i++)
    {
        front = 0;
        rear = 0;
        count = 0;

        /* Add starting state to closure */
        strcpy(closure[count++], states[i]);

        /* Add starting state to queue */
        strcpy(queue[rear++], states[i]);

        /*
         * Process all states in the queue
         */
        while (front < rear)
        {
            char current[MAX_LEN];

            strcpy(current, queue[front++]);

            /*
             * Find all epsilon transitions
             * from the current state
             */
            for (j = 0; j < t; j++)
            {
                if (strcmp(transitions[j].from, current) == 0 &&
                    strcmp(transitions[j].symbol, "e") == 0)
                {
                    found = 0;

                    /*
                     * Check whether destination is
                     * already in the closure
                     */
                    int k;

                    for (k = 0; k < count; k++)
                    {
                        if (strcmp(closure[k],
                                   transitions[j].to) == 0)
                        {
                            found = 1;
                            break;
                        }
                    }

                    /*
                     * If not already visited,
                     * add it to closure and queue
                     */
                    if (!found && count < MAX_STATES)
                    {
                        strcpy(closure[count++],
                               transitions[j].to);

                        strcpy(queue[rear++],
                               transitions[j].to);
                    }
                }
            }
        }

        /* Display epsilon closure */
        printf("\nEpsilon closure of %s = { ", states[i]);

        for (j = 0; j < count; j++)
        {
            printf("%s", closure[j]);

            if (j < count - 1)
                printf(", ");
        }

        printf(" }\n");
    }

    return 0;
}

