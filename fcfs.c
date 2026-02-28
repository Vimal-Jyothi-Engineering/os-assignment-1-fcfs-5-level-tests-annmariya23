#include <stdio.h>
#include <string.h>

typedef struct {
    char pid[10];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int index;
} Process;

int main() {
    int n;
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
        p[i].index = i;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            if (p[j].arrival > p[j + 1].arrival ||
                (p[j].arrival == p[j + 1].arrival &&
                p[j].index > p[j + 1].index)) {

                    Process temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
            }
        }
    }

    int current_time = p[0].arrival;
    p[0].waiting = 0;
    p[0].turnaround = p[0].burst;

    int total_wt = p[0].waiting;
    int total_tat = p[0].turnaround;

    current_time += p[0].burst;

    for (int i = 1; i < n; i++) {

        if (current_time < p[i].arrival) {
            current_time = p[i].arrival;
        }

        p[i].waiting = current_time - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;

        current_time += p[i].burst;

        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].waiting);
    }

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].turnaround);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    return 0;
}