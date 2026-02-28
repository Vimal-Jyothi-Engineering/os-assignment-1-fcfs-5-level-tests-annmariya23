#include <stdio.h>

typedef struct {
    char pid[10];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
} Process;

int main() {
    int n;
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int completion = 0;
    int total_wt = 0;
    int total_tat = 0;

    for (int i = 0; i < n; i++) {

        if (completion < p[i].arrival)
            completion = p[i].arrival;

        p[i].waiting = completion - p[i].arrival;
        completion += p[i].burst;
        p[i].turnaround = completion - p[i].arrival;

        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].waiting);

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].turnaround);

    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f", (float)total_tat / n);

    return 0;
}