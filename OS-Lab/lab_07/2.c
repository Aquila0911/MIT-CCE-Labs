// Write a C program to solve the readers and writers Problem. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int rc = 0;
int data = 0;

sem_t mutex;
sem_t wrt;

void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex);
        rc++;
        if (rc == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);
        printf("Data read by the reader is %d\n", data);
        sleep(1);
        sem_wait(&mutex);
        rc--;
        if (rc == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);
    }
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&wrt);
        data++;
        printf("Data written by the writer is %d\n", data);
        sleep(1);
        sem_post(&wrt);
    }
}

int main() {
    pthread_t read, write;
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    pthread_create(&write, NULL, writer, NULL);
    pthread_create(&read, NULL, reader, NULL);
    pthread_join(read, NULL);
    pthread_join(write, NULL);
    return 0;
}
