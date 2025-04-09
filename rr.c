#include <stdio.h>

#define MAX 10

void calculate_times_round_robin(int n, int arrival[], int burst[], int quantum, int waiting[], int turnaround[]) {
    int remaining[MAX], completed = 0, total_wt = 0, total_tat = 0, time = 0, i, j;
    
    for(i = 0; i < n; i++) {
        remaining[i] = burst[i];
    }

    while(1) {
        int all_done = 1;
        for(i = 0; i < n; i++) {
            if(remaining[i] > 0) {
                all_done = 0;
                if(arrival[i] <= time) {
                    if(remaining[i] > quantum) {
                        remaining[i] -= quantum;
                        time += quantum;
                    } else {
                        time += remaining[i];
                        turnaround[i] = time - arrival[i];
                        waiting[i] = turnaround[i] - burst[i];
                        total_wt += waiting[i];
                        total_tat += turnaround[i];
                        remaining[i] = 0;
                    }
                }
            }
        }
        if(all_done) break;
    }

    printf("\nRound Robin Scheduling (Quantum = %d):\n", quantum);
    printf("Process Arrival Time Burst Time Waiting Time Turnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival[i], burst[i], waiting[i], turnaround[i]);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_tat / n);
}

int main() {
    int n, quantum, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int arrival[MAX], burst[MAX], waiting[MAX], turnaround[MAX];

    printf("Enter arrival time and burst time for each process\n");
    for(i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d%d", &arrival[i], &burst[i]);
    }

    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &quantum);

    calculate_times_round_robin(n, arrival, burst, quantum, waiting, turnaround);

    return 0;
}


