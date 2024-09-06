// Write a C program to simulate the unix commands: ls -l, cp and wc commands.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command> <file>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "ls") == 0) {
        system("ls -l");
    } else if (strcmp(argv[1], "cp") == 0) {
        if (argc < 3) {
            printf("Usage: %s cp <source> <destination>\n", argv[0]);
            return 1;
        }
        char command[100];
        sprintf(command, "cp %s %s", argv[2], argv[3]);
        system(command);
    } else if (strcmp(argv[1], "wc") == 0) {
        if (argc < 3) {
            printf("Usage: %s wc <file>\n", argv[0]);
            return 1;
        }
        char command[100];
        sprintf(command, "wc %s", argv[2]);
        system(command);
    } else {
        printf("Invalid command\n");
    }

    return 0;
}

// Usage:
// $ gcc lab_5/1_additional.c -o lab_5/1_additional
// $ ./lab_5/1_additional ls