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
int main(){
    struct Transition transitions[MAX_TRANSITIONS];
    char states[MAX_STATES][MAX_LEN];
    char closure[MAX_STATES][MAX_LEN];
    char queue[MAX_STATES][MAX_LEN];
    int n, t;
    int i, j, front, rear, count;
    int found;
    FILE *INPUT;
    INPUT = fopen("exp9.dat", "r");
    if (INPUT == NULL){
        printf("Error: Cannot open input.dat\n");
        return 1;
    }
    printf("Enter the no of states: ");
    scanf("%d", &n);
    printf("Enter the states: ");
    for (i = 0; i < n; i++){
        scanf("%s", states[i]);
    }
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
    for (i = 0; i < n; i++){
        front = 0;
        rear = 0;
        count = 0;
        strcpy(closure[count++], states[i]);
        strcpy(queue[rear++], states[i]);
        while (front < rear){
            char current[MAX_LEN];
            strcpy(current, queue[front++]);
            for (j = 0; j < t; j++){
                if (strcmp(transitions[j].from, current) == 0 &&
                    strcmp(transitions[j].symbol, "e") == 0){
                    found = 0;
                    int k;
                    for (k = 0; k < count; k++){
                        if (strcmp(closure[k],
                                   transitions[j].to) == 0){
                            found = 1;
                            break;
                        }
                    }
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
        printf("\nEpsilon closure of %s = { ", states[i]);
        for (j = 0; j < count; j++){
            printf("%s", closure[j]);
            if (j < count - 1)
                printf(", ");
        }
        printf(" }\n");
    }
    return 0;
}
//or


#include <stdio.h>
#include <string.h>
#define MAX 20
struct T {
    char from[20], sym[20], to[20];
};
int main() {
    struct T tr[50];
    char s[MAX][20], c[MAX][20], q[MAX][20];
    int n, t = 0, i, j, k, f, r, count, found;
    FILE *fp = fopen("exp9.dat", "r");
    if (!fp) {
        printf("Cannot open file\n");
        return 1;
    }
    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter states: ");
    for (i = 0; i < n; i++)
        scanf("%s", s[i]);
    while (t < 50 && fscanf(fp, "%s %s %s",
           tr[t].from, tr[t].sym, tr[t].to) == 3)
        t++;
    fclose(fp);
    for (i = 0; i < n; i++) {
        f = r = 0;
        count = 1;
        strcpy(c[0], s[i]);
        strcpy(q[r++], s[i]);
        while (f < r) {
            for (j = 0; j < t; j++)
                if (!strcmp(tr[j].from, q[f]) &&
                    !strcmp(tr[j].sym, "e")) {
                    found = 0;
                    for (k = 0; k < count; k++)
                        if (!strcmp(c[k], tr[j].to))
                            found = 1;
                    if (!found && count < MAX) {
                        strcpy(c[count++], tr[j].to);
                        strcpy(q[r++], tr[j].to);
                    }
                }
            f++;
        }
        printf("Epsilon closure of %s = { ", s[i]);
        for (j = 0; j < count; j++)
            printf("%s%s", c[j], j < count - 1 ? ", " : "");
        printf(" }\n");
    }
    return 0;
}
