// Write a C program to implement the deadlock detection algorithm.

#include <stdio.h>
#include <stdlib.h>

int main() {
    int m = 3;
    int n = 5;
    int available[3] = {3, 3, 2};
    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int allocation[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int need[5][3];
    int work[3];
    int finish[5];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
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
                    if (need[i][j] > work[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    safe = 1;
                    count++;
                }
            }
        }
        if (safe == 0) {
            break;
        }
    }

    if (count == n) {
        printf("The system is in a safe state\n");
    } else {
        printf("The system is in an unsafe state\n");
    }

    return 0;
}