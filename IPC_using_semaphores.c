#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Size of the buffer
#define PRODUCE_COUNT 10 // Number of items to produce
int buffer[BUFFER_SIZE]; // The buffer
int in = 0; // Index for the next item to produce
int out = 0; // Index for the next item to consume
sem_t empty; // Semaphore to count empty slots
sem_t full; // Semaphore to count full slots
pthread_mutex_t mutex; // Mutex for critical section

void* producer(void* arg) {
    
    for (int i = 0; i < PRODUCE_COUNT; i++) {
        
        int item = rand() % 100; // Produce a random item
        sem_wait(&empty); // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Enter critical section
        
        // Add the item to the buffer
        buffer[in] = item;
        printf("Produced: %d at %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE; // Move to the next position
        
        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full); // Signal that a new item is available
        sleep(1); // Simulate time taken to produce an item
    }
    return NULL;
}

void* consumer(void* arg) {
    
    for (int i = 0; i < PRODUCE_COUNT; i++) {

        sem_wait(&full); // Wait for a full slot
        pthread_mutex_lock(&mutex); // Enter critical section
        
        // Remove an item from the buffer
        int item = buffer[out];
        printf("Consumed: %d from %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE; // Move to the next position
        
        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty); // Signal that an empty slot is available
        sleep(2); // Simulate time taken to consume an item
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Initially all slots are empty
    sem_init(&full, 0, 0); // No slots are full
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for both threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}