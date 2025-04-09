#include <stdio.h>

#define MAX 10

int find_highest_priority(int n, int arrival[], int burst[], int priority[], int remaining[], int completed) {
    int i, max_priority = -1, highest_priority_index = -1;
    for(i = 0; i < n; i++) {
        if(arrival[i] <= completed && remaining[i] > 0 && priority[i] > max_priority) {
            max_priority = priority[i];
            highest_priority_index = i;
        }
    }
    return highest_priority_index;
}

void calculate_times_non_preemptive(int n, int arrival[], int burst[], int priority[], int waiting[], int turnaround[]) {
    int remaining[MAX], completed = 0, total_wt = 0, total_tat = 0, i;
    for(i = 0; i < n; i++) {
        remaining[i] = burst[i];
    }
    for(i = 0; i < n; i++) {
        int min = i;
        for(int j = i + 1; j < n; j++) {
            if(arrival[j] < arrival[min]) {
                min = j;
            }
        }
        int temp;
        temp = arrival[i]; arrival[i] = arrival[min]; arrival[min] = temp;
        temp = burst[i]; burst[i] = burst[min]; burst[min] = temp;
        temp = priority[i]; priority[i] = priority[min]; priority[min] = temp;
    }

    while(1) {
        int idx = -1;
        for(i = 0; i < n; i++) {
            if(arrival[i] <= completed && remaining[i] > 0) {
                idx = i;
                break;
            }
        }
        if(idx == -1) break;

        remaining[idx]--;
        completed++;
        if(remaining[idx] == 0) {
            turnaround[idx] = completed - arrival[idx];
            waiting[idx] = turnaround[idx] - burst[idx];
            total_wt += waiting[idx];
            total_tat += turnaround[idx];
        }
    }

    printf("\nNon-Preemptive Priority Scheduling:\n");
    printf("Process Arrival Time Burst Time Waiting Time Turnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i+1, arrival[i], burst[i], waiting[i], turnaround[i]);
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_tat / n);
}

void calculate_times_preemptive(int n, int arrival[], int burst[], int priority[], int waiting[], int turnaround[]) {
    int remaining[MAX], completed = 0, total_wt = 0, total_tat = 0, i;
    for(i = 0; i < n; i++) {
        remaining[i] = burst[i];
    }

    int time = 0, prev = -1, idx;
    while(1) {
        idx = find_highest_priority(n, arrival, burst, priority, remaining, time);
        if(idx == -1) break;

        remaining[idx]--;
        time++;
        if(remaining[idx] == 0) {
            turnaround[idx] = time - arrival[idx];
            waiting[idx] = turnaround[idx] - burst[idx];
            total_wt += waiting[idx];
            total_tat += turnaround[idx];
        }
    }

    printf("\nPreemptive Priority Scheduling:\n");
    printf("Process Arrival Time Burst Time Waiting Time Turnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i+1, arrival[i], burst[i], waiting[i], turnaround[i]);
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_tat / n);
}

int main() {
    int n, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int arrival[MAX], burst[MAX], priority[MAX], waiting[MAX], turnaround[MAX];

    printf("Enter arrival time, burst time, and priority for each process\n");
    for(i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d%d%d", &arrival[i], &burst[i], &priority[i]);
    }

    calculate_times_non_preemptive(n, arrival, burst, priority, waiting, turnaround);
    calculate_times_preemptive(n, arrival, burst, priority, waiting, turnaround);

    return 0;
}
