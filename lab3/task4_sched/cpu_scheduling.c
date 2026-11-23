#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void findWaitingTime(struct Process proc[], int n) {
    proc[0].waiting_time = 0;
    for (int i = 1; i < n; i++)
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
}

void findTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++)
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
}

void print_result(struct Process proc[], int n, const char *title) {
    float avg_wt = 0, avg_tat = 0;
    printf("\n%s\n", title);
    printf("Process  Burst  Waiting  Turnaround\n");
    for (int i = 0; i < n; i++) {
        printf("  P%d\t%d\t%d\t%d\n", proc[i].id, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
        avg_wt += proc[i].waiting_time;
        avg_tat += proc[i].turnaround_time;
    }
    printf("Average waiting time = %.2f, average turnaround time = %.2f\n",
           avg_wt / n, avg_tat / n);
}

void rr_schedule(struct Process proc[], int n, int quantum) {
    int rem[10], finish[10], time = 0, done = 0, i = 0;
    for (int k = 0; k < n; k++) rem[k] = proc[k].burst_time;
    while (done < n) {
        if (rem[i] > 0) {
            int run = (rem[i] > quantum) ? quantum : rem[i];
            time += run;
            rem[i] -= run;
            if (rem[i] == 0) {
                finish[i] = time;
                done++;
            }
        }
        i = (i + 1) % n;
    }
    for (int k = 0; k < n; k++) {
        proc[k].turnaround_time = finish[k];
        proc[k].waiting_time = finish[k] - proc[k].burst_time;
    }
}

int main() {
    struct Process p1[] = {{1, 10}, {2, 5}, {3, 8}};
    int n = sizeof(p1) / sizeof(p1[0]);
    findWaitingTime(p1, n);
    findTurnaroundTime(p1, n);
    print_result(p1, n, "FCFS:");

    struct Process p2[] = {{1, 10}, {2, 5}, {3, 8}};
    rr_schedule(p2, n, 4);
    print_result(p2, n, "Round Robin (quantum = 4):");
    return 0;
}
