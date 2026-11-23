#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void *philosopher(void *num) {
    int id = *(int *)num;
    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        usleep(500000);
        /* 奇数先左后右，偶数先右后左，破坏循环等待，避免死锁 */
        if (id % 2 == 0) {
            sem_wait(&forks[id]);
            sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        } else {
            sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);
            sem_wait(&forks[id]);
        }
        printf("Philosopher %d is eating.\n", id);
        usleep(800000);
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
    }
    return NULL;
}

int main() {
    int ids[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_init(&forks[i], 0, 1);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_destroy(&forks[i]);
    return 0;
}
