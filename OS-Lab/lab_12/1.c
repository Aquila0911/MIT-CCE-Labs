// Write a C program to simulate Rate-Monotonic and Earliest-Deadline-First scheduling for real time system
//     1. Rate-Monotonic
//     2. Earliest-Deadline-First
//     3. Exit

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[10];
    int period;
    int exec_time;
    int deadline;
    int remaining_time;
} Task;

Task *input(int n) {
    Task *tasks = (Task *)malloc(n * sizeof(Task));
    for (int i = 0; i < n; i++) {
        sprintf(tasks[i].name, "T%d", i + 1);
        printf("Enter period: ");
        scanf("%d", &tasks[i].period);
        printf("Enter execution time: ");
        scanf("%d", &tasks[i].exec_time);
        printf("Enter deadline: ");
        scanf("%d", &tasks[i].deadline);
    }
    return tasks;
}

void sort(Task *tasks, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].period > tasks[j].period) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

int __gcd(int a, int b) {
    if (b == 0) return a;
    return __gcd(b, a % b);
}

void rate_monotonic(Task *tasks, int n) {
    int lcm = 1;
    for (int i = 0; i < n; i++) {
        lcm = (lcm * tasks[i].period) / __gcd(lcm, tasks[i].period);
    }
    
    sort(tasks, n);
    int time = 0;
    while (time < lcm) {
        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].exec_time;
            }
        }

        int min = __INT_MAX__;
        int index = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0 && tasks[i].remaining_time < min) {
                min = tasks[i].remaining_time;
                index = i;
            }
        }

        if (index != -1) {
            tasks[index].remaining_time--;
            printf("%s ", tasks[index].name);
        } else {
            printf("Idle ");
        }
        time++;
    }
}

void earliest_deadline_first(Task *tasks, int n) {
    int lcm = 1;
    for (int i = 0; i < n; i++) {
        lcm = (lcm * tasks[i].period) / __gcd(lcm, tasks[i].period);
    }

    sort(tasks, n);

    int current_time = 0;

    int deadlines[n];
    for (int i = 0; i < n; i++) {
        deadlines[i] = tasks[i].deadline;
    }

    while (current_time < lcm) {
        for (int i = 0; i < n; i++) {
            if (current_time % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].exec_time;
                tasks[i].deadline = deadlines[i];
            }
        }

        int min = __INT_MAX__;
        int index = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0 && tasks[i].deadline < min) {
                min = tasks[i].deadline;
                index = i;
            }
        }

        if (index != -1) {
            tasks[index].remaining_time--;
            printf("%s ", tasks[index].name);
        } else {
            printf("Idle ");
        }

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                tasks[i].deadline--;
            }
        }

        current_time++;
    }
}

int main() {
    Task tasks[3] = {
        {"T1", 4, 1, 4},
        {"T2", 6, 2, 6},
        {"T3", 8, 3, 8}
    };

    earliest_deadline_first(tasks, 3);

    return 0;
}