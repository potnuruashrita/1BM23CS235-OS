#include <stdio.h>
#include <stdlib.h>

// Structure to represent a task
typedef struct {
    int task_id;
    int execution_time;  // The time required to execute the task
    int period;          // The period of the task
    int remaining_time;  // Remaining execution time of the task
} Task;

// Function to sort tasks by their period (ascending order)
int compare(const void *a, const void *b) {
    return ((Task*)a)->period - ((Task*)b)->period;
}

// Function to simulate the Rate-Monotonic Scheduling
void rate_monotonic_scheduling(Task tasks[], int num_tasks) {
    int time = 0;
    int all_tasks_completed = 0;

    printf("\nRate-Monotonic Scheduling\n");
    printf("Time\tTask Executing\n");

    while (all_tasks_completed < num_tasks) {
        int task_executed = 0;
        
        // Iterate through tasks and execute the task with the highest priority (smallest period)
        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].remaining_time > 0 && time % tasks[i].period == 0) {
                tasks[i].remaining_time--;  // Decrease the remaining time of the task
                task_executed = 1;
                printf("%d\tTask %d\n", time, tasks[i].task_id);
            }
        }

        // Check if all tasks are completed
        all_tasks_completed = 0;
        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].remaining_time == 0) {
                all_tasks_completed++;
            }
        }

        // Increment time at each step
        time++;

        // If no task was executed in this cycle, move to the next time unit
        if (!task_executed) {
            printf("%d\tIdle\n", time);
        }
    }
}

// Main function to take input and run the scheduler
int main() {
    int num_tasks;

    // Input the number of tasks
    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    Task tasks[num_tasks];

    // Input each task's execution time and period
    for (int i = 0; i < num_tasks; i++) {
        tasks[i].task_id = i + 1;
        printf("Enter execution time and period for Task %d: ", i + 1);
        scanf("%d %d", &tasks[i].execution_time, &tasks[i].period);
        tasks[i].remaining_time = tasks[i].execution_time;  // Initialize remaining time
    }

    // Sort tasks by period to implement Rate-Monotonic Scheduling
    qsort(tasks, num_tasks, sizeof(Task), compare);

    // Simulate the Rate-Monotonic Scheduling
    rate_monotonic_scheduling(tasks, num_tasks);

    return 0;
}
