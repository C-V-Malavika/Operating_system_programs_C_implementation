#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
  
sem_t wrt; 
pthread_mutex_t mutex; 
int read_count = 0; 
int current_writer = 0;  // To track the writer currently accessing the resource 
int current_reader = 0;  // To track the first reader accessing the resource 
int writer_active = 0;   // Flag to track if a writer is actually writing 
  
void* writer(void* arg) { 

    int writer_id = *((int*)arg); 
     
    while (1) { 
        printf("Writer %d is trying to write.\n", writer_id); 
  
        // Now actually block until the writer can proceed 
        sem_wait(&wrt); 
  
        // Mark the current writer and set writer active flag 
        current_writer = writer_id; 
        writer_active = 1;  // Writer is actively writing 
  
        // Critical section (writing) 
        printf("Writer %d is writing.\n", writer_id); 
        sleep(1); 
  
        // Writer finished 
        printf("Writer %d finished writing. Unlocking the resource.\n", writer_id); 
        writer_active = 0;  // Writer finished writing 
        current_writer = 0;  // Reset current writer 
        sem_post(&wrt);  // Unlock resource 
  
        // sleep(2); 
    } 
} 

  
void* reader(void* arg) { 

    int reader_id = *((int*)arg); 
     
    while (1) { 
        printf("Reader %d is trying to read.\n", reader_id); 
  
        // Lock the mutex to update the reader count 
        pthread_mutex_lock(&mutex); 
        read_count++; 
        if (read_count == 1) { 
            // First reader blocks the writer and marks the current reader 
            if (writer_active == 1) { 
                printf("Reader %d waiting because resource is being written by Writer %d.\n", reader_id, current_writer); 
            } 
            sem_wait(&wrt);  // Lock the resource for readers 
        } 
        current_reader = reader_id; 
        pthread_mutex_unlock(&mutex); 
  
        // Critical section (reading) 
        printf("Reader %d is reading.\n", reader_id); 
        // sleep(1); 
  
        // Lock the mutex to update the reader count 
        pthread_mutex_lock(&mutex); 
        read_count--; 
        if (read_count == 0) { 
            // Last reader releases the writer 
            current_reader = 0;  // Reset current reader 
            printf("Reader %d finished reading. Unlocking the resource.\n", reader_id); 
            sem_post(&wrt);  // Unlock resource 
        } else { 
            printf("Reader %d finished reading.\n", reader_id); 
        } 
        pthread_mutex_unlock(&mutex); 
  
        // sleep(2); 
    } 
} 
  
int main() { 

    pthread_t readers[3], writers[2]; 
    int reader_ids[3] = {1, 2, 3}; 
    int writer_ids[2] = {1, 2}; 
    sem_init(&wrt, 0, 1); 
    pthread_mutex_init(&mutex, NULL); 
  
    // Create writer threads 
    for (int i = 0; i < 2; i++) { 
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]); 
    } 
  
    // Create reader threads 
    for (int i = 0; i < 3; i++) { 
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]); 
    } 
  
    // Join threads (the program runs indefinitely, so this is just for demonstration) 
    for (int i = 0; i < 2; i++) { 
        pthread_join(writers[i], NULL); 
    } 
    for (int i = 0; i < 3; i++) { 
        pthread_join(readers[i], NULL); 
    } 

    sem_destroy(&wrt); 
    pthread_mutex_destroy(&mutex); 
    return 0; 
}