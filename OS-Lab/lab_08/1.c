// Develop a program to simulate banker’s algorithm. (Consider safety and resource request algorithms)

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int *available = (int *)malloc(m * sizeof(int));
    int *max = (int *)malloc(n * m * sizeof(int));
    int *allocation = (int *)malloc(n * m * sizeof(int));
    int *need = (int *)malloc(n * m * sizeof(int));
    int *work = (int *)malloc(m * sizeof(int));
    int *finish = (int *)malloc(n * sizeof(int));

    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum resources: ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i * m + j]);
        }
    }

    printf("Enter the allocated resources: ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i * m + j]);
            need[i * m + j] = max[i * m + j] - allocation[i * m + j];
        }
    }

    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int count = 0;
    int safe = 0;
    while (count < n) {
        safe = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i * m + j] > work[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i * m + j];
                    }
                    finish[i] = 1;
                    count++;
                    safe = 1;
                    printf("Process %d is executed\n", i);
                    break;
                }
            }
        }
        if (safe == 0) {
            break;
        }
    }

    if (count == n) {
        printf("The system is in safe state\n");
    } else {
        printf("The system is in unsafe state\n");
    }

    free(available);
    free(max);
    free(allocation);
    free(need);
    free(work);
    free(finish);

    return 0;
}
