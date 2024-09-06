#include <stdio.h>
#include <stdlib.h>

#define DISK_SIZE 199

typedef struct {
    int *queue;
    int qsize;
    int head;
} DiskData;

void sort(int data[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                int temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

DiskData *input() {
    DiskData *data = (DiskData *)malloc(sizeof(DiskData));
    printf("Enter the size of the queue: ");
    scanf("%d", &data->qsize);

    data->queue = (int *)malloc(sizeof(int) * (data->qsize));
    for (int i = 0; i < data->qsize; i++) {
        printf("Enter queue[%d]: ", i);
        scanf("%d", &data->queue[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &data->head);

    return data;
}

void SSTF() {
    DiskData *data = input();

    int visited[data->qsize];
    for (int i = 0; i < data->qsize; i++) {
        visited[i] = 0;
    }

    double avg = 0;
    int done = 0, seek = 0, idx = -1;

    while (data->qsize > done) {
        int min = __INT_MAX__;
        for (int i = 0; i < data->qsize; i++) {
            int check = abs(data->head - data->queue[i]);
            if (min > check && !visited[i]) {
                min = check;
                idx = i;
            }
        }
        seek += min;
        printf("%d, ", data->head);
        data->head = data->queue[idx];
        visited[idx] = 1;
        done++;
    }
    printf("%d\n", data->head);

    printf("Total seek time is %d\n", seek);
    avg = seek / (float)data->qsize;
    printf("Average seek time is %lf\n", avg);
}

void SCAN() {
    DiskData *data = input();

    data->queue = realloc(data->queue, sizeof(int) * (data->qsize + 3));

    data->queue[data->qsize++] = data->head;
    data->queue[data->qsize++] = 0;
    data->queue[data->qsize++] = DISK_SIZE;

    int dloc;
    double avg = 0;
    int done = 0, seek = 0, idx = -1;

    sort(data->queue, data->qsize);

    for (int i = 0; i < data->qsize; i++) {
        if (data->head == data->queue[i]) {
            dloc = i;
            break;
        }
    }

    char dir;
    printf("Enter the direction (l/r): ");
    scanf(" %c", &dir);

    int max = abs(dloc - data->qsize), min = abs(0 - dloc);

    if (max < min) { // dir == 'l'
        for (int j = dloc; j >= 0; j--) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
        for (int j = dloc + 1; j < data->qsize - 1; j++) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
    } else {
        for (int j = dloc; j < data->qsize; j++) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
        for (int j = dloc - 1; j >= 1; j--) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
    }

    printf("\nTotal seek time is %d\n", seek);
    avg = seek / (float)data->qsize;
    printf("Average seek time is %lf\n", avg);
}

void CSCAN() {
    DiskData *data = input();

    data->queue = realloc(data->queue, sizeof(int) * (data->qsize + 3));

    data->queue[data->qsize++] = data->head;
    data->queue[data->qsize++] = 0;
    data->queue[data->qsize++] = DISK_SIZE;

    int dloc;
    double avg = 0;
    int done = 0, seek = 0, idx = -1;

    sort(data->queue, data->qsize);

    for (int i = 0; i < data->qsize; i++) {
        if (data->head == data->queue[i]) {
            dloc = i;
            break;
        }
    }

    char dir;
    printf("Enter the direction (l/r): ");
    scanf(" %c", &dir);

    int max = abs(dloc - data->qsize), min = abs(0 - dloc);

    if (dir == 'l') { // max < min
        for (int j = dloc; j >= 0; j--) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
        for (int j = data->qsize - 1; j > dloc; j--) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
    } else {
        for (int j = dloc; j < data->qsize; j++) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
        for (int j = 0; j < dloc; j++) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
    }

    printf("\nTotal seek time is %d\n", seek);
    avg = seek / (float)data->qsize;
    printf("Average seek time is %lf\n", avg);
}

void LOOK() {
    DiskData *data = input();

    data->queue = realloc(data->queue, sizeof(int) * (data->qsize + 1));

    data->queue[data->qsize++] = data->head;

    int dloc;
    double avg = 0;
    int done = 0, seek = 0, idx = -1;

    sort(data->queue, data->qsize);

    for (int i = 0; i < data->qsize; i++) {
        if (data->head == data->queue[i]) {
            dloc = i;
            break;
        }
    }

    char dir;
    printf("Enter the direction (l/r): ");
    scanf(" %c", &dir);

    int max = abs(dloc - data->qsize), min = abs(0 - dloc);

    if (dir == 'l') { // max < min
        for (int j = dloc; j >= 0; j--) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
        for (int j = dloc + 1; j < data->qsize; j++) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
    } else {
        for (int j = dloc; j < data->qsize; j++) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
        for (int j = dloc - 1; j >= 0; j--) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
    }

    printf("\nTotal seek time is %d\n", seek);
    avg = seek / (float)data->qsize;
    printf("Average seek time is %lf\n", avg);
}

void CLOOK() {
    DiskData *data = input();

    data->queue = realloc(data->queue, sizeof(int) * (data->qsize + 1));

    data->queue[data->qsize++] = data->head;

    int dloc;
    double avg = 0;
    int done = 0, seek = 0, idx = -1;

    sort(data->queue, data->qsize);

    for (int i = 0; i < data->qsize; i++) {
        if (data->head == data->queue[i]) {
            dloc = i;
            break;
        }
    }

    char dir;
    printf("Enter the direction (l/r): ");
    scanf(" %c", &dir);

    int max = abs(dloc - data->qsize), min = abs(0 - dloc);

    if (dir == 'l') { // max < min
        for (int j = dloc; j >= 0; j--) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
        for (int j = data->qsize - 1; j > dloc; j--) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
    } else {
        for (int j = dloc; j < data->qsize; j++) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
        for (int j = 0; j < dloc; j++) {
            seek += abs(data->head - data->queue[j]);
            data->head = data->queue[j];
            printf("%d --> ", data->queue[j]);
        }
    }

    printf("\nTotal seek time is %d\n", seek);
    avg = seek / (float)data->qsize;
    printf("Average seek time is %lf\n", avg);
}

void FCFS() {
    DiskData *data = input();

    double avg = 0;
    int seek = 0;

    printf("%d --> ", data->head);

    for (int i = 0; i < data->qsize; i++) {
        seek += abs(data->head - data->queue[i]);
        data->head = data->queue[i];
        printf("%d --> ", data->queue[i]);
    }

    printf("\nTotal seek time is %d\n", seek);
    avg = seek / (float)data->qsize;
    printf("Average seek time is %lf\n", avg);
}

int main() {
    char choice;
    do {
        printf("Enter the choice of disk scheduling algorithm\n");
        printf("1. FCFS\n");
        printf("2. SSTF\n");
        printf("3. SCAN\n");
        printf("4. CSCAN\n");
        printf("5. LOOK\n");
        printf("6. CLOOK\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        int algorithm;
        scanf("%d", &algorithm);

        switch (algorithm) {
            case 1:
                FCFS();
                break;
            case 2:
                SSTF();
                break;
            case 3:
                SCAN();
                break;
            case 4:
                CSCAN();
                break;
            case 5:
                LOOK();
                break;
            case 6:
                CLOOK();
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice\n");
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');
    return 0;
}