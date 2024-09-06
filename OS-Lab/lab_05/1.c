/*
Write a C program to create a child process. Display different messages in parent
process and child process. Display PID and PPID of both parent and child process.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
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
    } else {
        wait(NULL);
        printf("Parent process\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
    }
    return 0;
}

// Output
// Parent process
// PID: 1234
// PPID: 1233
// Child process
// PID: 1235
// PPID: 1234
