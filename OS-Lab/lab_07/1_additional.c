// Write a C program to solve the Dining-Philosophers problem.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t mutex;
sem_t chopstick[N];

enum { THINKING, HUNGRY, EATING } state[N];

int left(int i) {
    return (i + N - 1) % N;
}

int right(int i) {
    return (i + 1) % N;
}

void test(int i) {
    if (state[i] == HUNGRY && state[left(i)] != EATING && state[right(i)] != EATING) {
        state[i] = EATING;
        sem_post(&chopstick[i]);
    }
}

void take_chopstick(int i) {
    sem_wait(&mutex);
    state[i] = HUNGRY;
    test(i);
    sem_post(&mutex);
    sem_wait(&chopstick[i]);
}

void put_chopstick(int i) {
    sem_wait(&mutex);
    state[i] = THINKING;
    test(left(i));
    test(right(i));
    sem_post(&mutex);
}

void *philosopher(void *arg) {
    int i = *(int *)arg;
    while (1) {
        printf("Philosopher %d is thinking\n", i);
        sleep(1);
        take_chopstick(i);
        printf("Philosopher %d is eating\n", i);
        sleep(1);
        put_chopstick(i);
    }
}

int main() {
    pthread_t phil[N];
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 0);
    }
    for (int i = 0; i < N; i++) {
        state[i] = THINKING;
    }
    int id[N];
    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &id[i]);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(phil[i], NULL);
    }
    sem_destroy(&mutex);
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopstick[i]);
    }
    return 0;
}
