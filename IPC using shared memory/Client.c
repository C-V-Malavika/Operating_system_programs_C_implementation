#include <stdio.h> 
#include <stdlib.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h> 
 
#define SHM_SIZE 128 
 
int main() { 
    
    int shmid; 
    key_t key = 1234; // Same key as server 
    char *data; 
 
    // Access shared memory segment 
    shmid = shmget(key, SHM_SIZE, 0666); 
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
 
    while (1) { 
        // Get temperature input from user 
        float celsius; 
        printf("Enter temperature in Celsius (or -999 to exit): "); 
        scanf("%f", &celsius); 
 
        if (celsius == -999) { 
            break; // Exit condition 
        } 
        // Write to shared memory 
        sprintf(data, "%.2f", celsius); 
        // Wait for the server to process 
        sleep(2); 
        // Read the converted temperature 
        printf("%s\n", data); 
        // Reset shared memory for next input 
        data[0] = '\0'; 
    } 
    // Detach from shared memory 
    shmdt(data); 
    return 0; 
}