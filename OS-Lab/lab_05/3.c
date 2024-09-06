/*
Write a C program to read N strings. Create two child processes, each of this
should perform sorting using two different methods (bubble, selection, quicksort
etc). The parent should wait until one of the child process terminates. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void bubbleSort(char *arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(char *arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[min]) < 0) {
                min = j;
            }
        }
        char *temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

int main() {
    int n;
    printf("Enter the number of strings: ");
    scanf("%d", &n);
    char *arr[n];
    printf("Enter the strings: ");
    for (int i = 0; i < n; i++) {
        arr[i] = (char *)malloc(100 * sizeof(char));
        scanf("%s", arr[i]);
    }

    int pid1 = fork();
    if (pid1 == 0) {
        bubbleSort(arr, n);
        printf("Bubble Sort: ");
        for (int i = 0; i < n; i++) {
            printf("%s ", arr[i]);
        }
        printf("\n");
        exit(0);
    } else {
        int pid2 = fork();
        if (pid2 == 0) {
            selectionSort(arr, n);
            printf("Selection Sort: ");
            for (int i = 0; i < n; i++) {
                printf("%s ", arr[i]);
            }
            printf("\n");
            exit(0);
        } else {
            int status;
            wait(&status);
            if (WIFEXITED(status)) {
                printf("Child process %d terminated\n", WEXITSTATUS(status));
            }
        }
    }
    return 0;
}

// Usage
// gcc lab_5/3.c -o lab_5/3
// ./lab_5/3
// Enter the number of strings: 5
// Enter the strings: hello world this is a string
// Bubble Sort: a hello is string this world
// Child process 0 terminated
// Selection Sort: a hello is string this world
// Child process 0 terminated
