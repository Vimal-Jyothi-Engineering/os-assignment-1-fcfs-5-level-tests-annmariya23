#include <stdio.h>
#include <string.h>

typedef struct {
    char pid[10];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int completion;
} Process;

int main() {
    int n;
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int total_waiting = 0;
    int total_turnaround = 0;

    p[0].completion = p[0].arrival + p[0].burst;
    p[0].turnaround = p[0].completion - p[0].arrival;
    p[0].waiting = p[0].turnaround - p[0].burst;

    total_waiting += p[0].waiting;
    total_turnaround += p[0].turnaround;

    for (int i = 1; i < n; i++) {
        if (p[i].arrival > p[i - 1].completion)
            p[i].completion = p[i].arrival + p[i].burst;
        else
            p[i].completion = p[i - 1].completion + p[i].burst;

        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;

        total_waiting += p[i].waiting;
        total_turnaround += p[i].turnaround;
    }

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].waiting);
    }

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].turnaround);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround / n);

    return 0;
}