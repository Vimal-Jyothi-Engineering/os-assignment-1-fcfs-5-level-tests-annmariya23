#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char pid[64];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int index;
} Process;

int main() {

    int n;
    if (scanf("%d", &n) != 1) return 0;

    Process *p = malloc(n * sizeof(Process));
    if (!p) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
        p[i].index = i;
    }

    // Stable sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j+1].arrival ||
               (p[j].arrival == p[j+1].arrival && p[j].index > p[j+1].index)) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int current_time = 0;
    double total_waiting = 0;
    double total_turnaround = 0;

    for (int i = 0; i < n; i++) {

        int start_time;

        if (current_time < p[i].arrival)
            start_time = p[i].arrival;
        else
            start_time = current_time;

        p[i].waiting = start_time - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;

        current_time = start_time + p[i].burst;

        total_waiting += p[i].waiting;
        total_turnaround += p[i].turnaround;
    }

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].waiting);

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].turnaround);

    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f", total_turnaround / n);

    free(p);
    return 0;
}