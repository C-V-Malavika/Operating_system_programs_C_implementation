#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define ITERATIONS 10  // Number of times each philosopher will think and eat
sem_t forks[NUM_PHILOSOPHERS];  // One semaphore per fork
sem_t mutex;    // Semaphore to control the number of philosophers trying to eat

void think(int philosopher_number) {
    printf("Philosopher %d is thinking.\n", philosopher_number);
    usleep(rand() % 1000);  // Random thinking time
}

void eat(int philosopher_number) {
    printf("Philosopher %d is eating.\n", philosopher_number);
    usleep(rand() % 1000);  // Random eating time
}

void* philosopher(void* num) {
    
    int philosopher_number = *(int*)num;

    for (int i = 0; i < ITERATIONS; i++) {
        think(philosopher_number);

        // only N-1 philosophers can pick up forks at the same time to avoid deadlock
        sem_wait(&mutex);

        // Pick up the forks
        int left_fork = philosopher_number;
        int right_fork = (philosopher_number + 1) % NUM_PHILOSOPHERS;

        sem_wait(&forks[left_fork]);  // Pick up left fork
        printf("Philosopher %d picked up left fork.\n", philosopher_number);
        sem_wait(&forks[right_fork]); // Pick up right fork
        printf("Philosopher %d picked up right fork.\n", philosopher_number);

        eat(philosopher_number);

        // Put down the forks
        sem_post(&forks[left_fork]);  // Put down left fork
        sem_post(&forks[right_fork]); // Put down right fork

        printf("Philosopher %d put down forks.\n", philosopher_number);

        // Allow another philosopher to try to eat
        sem_post(&mutex);
    }

    printf("Philosopher %d is done.\n", philosopher_number);
    return NULL;
}

int main() {

    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_numbers[NUM_PHILOSOPHERS];

    // Initialize semaphores for forks and mutex
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);  // Each fork is initially available (1)
    }

    sem_init(&mutex, 0, NUM_PHILOSOPHERS - 1);  // Allow up to N-1 philosophers to pick up forks

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_numbers[i] = i;
        pthread_create(&philosophers[i],NULL,philosopher,&philosopher_numbers[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    sem_destroy(&forks[i]);
    }
    sem_destroy(&mutex);
    return 0;
}