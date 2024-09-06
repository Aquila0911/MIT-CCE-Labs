/*
Write a C program to accept a set of strings as command line arguments. Sort the
strings and display them in a child process. Parent process should display the unsorted strings only after the child displays the sorted list
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> // Include the wait header
#include <string.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    }
    if (pid == 0) {
        printf("Child process\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        int n = argc - 1;
        char *arr[n];
        for (int i = 0; i < n; i++) {
            arr[i] = argv[i + 1];
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (strcmp(arr[i], arr[j]) > 0) {
                    char *temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        printf("Sorted strings:\n");
        for (int i = 0; i < n; i++) {
            printf("%s\n", arr[i]);
        }
    } else {
        wait(NULL);
        printf("Parent process\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        printf("Unsorted strings:\n");
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    }
    return 0;
}

// Usage
// gcc lab_5/2.c -o lab_5/2
// ./lab_5/2 pineapple orange apple banana
