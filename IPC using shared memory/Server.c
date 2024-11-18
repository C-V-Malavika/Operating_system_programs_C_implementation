#include <stdio.h> 
#include <stdlib.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h> 
 
#define SHM_SIZE 128 // Define shared memory size 
 
int main() { 
    int shmid; 
    key_t key = 1234; // Unique key for the shared memory 
    char *data; 
 
    // Create shared memory segment 
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); 
    if (shmid == -1) { 
        perror("shmget failed"); 
        exit(1); 
    } 
 
    // Attach to shared memory 
    data = (char *)shmat(shmid, NULL, 0); 
    if (data == (char *)(-1)) { 
        perror("shmat failed"); 
        exit(1); 
    } 
 
    // Print message once and wait until input is provided 
    printf("Waiting for temperature input (Celsius) from client...\n"); 
 
    while (1) { 
        // Check if client has written to shared memory 
        if (data[0] != '\0') { 
            float celsius = atof(data); 
            float fahrenheit = (celsius * 9 / 5) + 32; 
            sprintf(data, "Fahrenheit: %.2f", fahrenheit); 
            printf("Converted %.2f Celsius to %.2f Fahrenheit\n", celsius, fahrenheit); 
            data[0] = '\0'; // Reset shared memory for next input 
 
            // Print waiting message again after processing the input 
            printf("Waiting for temperature input (Celsius) from client...\n"); 
        } 
        usleep(100000); // Short wait to reduce CPU usage 
    } 
 
    // Detach from shared memory 
    shmdt(data); 
    return 0; 
}