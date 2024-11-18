#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>

int main() {

  int number;
  char buffer[100]; // Buffer for reading from files
  int fileDescriptor = -1; // Initialize to -1 to indicate no file is open
  char *filename = "testfile.txt";

  while (1) { 
    printf("\nMenu:\n");
    printf("1. fork() \n");
    printf("2. exit() \n");
    printf("3. getpid() \n");
    printf("4. getppid() \n");
    printf("5. sleep() \n");
    printf("6. setpriority() \n");
    printf("7. wait() \n");
    printf("8. open() \n");
    printf("9. read() \n");
    printf("10. write() \n");
    printf("11. close() \n");
    printf("12. chmod() \n");
    printf("13. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &number);

    switch(number) {

        case 1: {
            pid_t pid = fork();

            if (pid == -1) {
            perror("fork");
            }
            else if (pid == 0) {
            // Child process
            printf("Child process: PID = %d\n", getpid());
            exit(0); // Ensure child process exits here
            }
            else {
            // Parent process
            printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
            }
        }
        break;

        case 2:
            printf("Exiting program \n");
            exit(0); 
        break;

        case 3:
            printf("Process ID: %d\n", getpid());
        break;

        case 4:
            printf("Parent Process ID: %d\n", getppid());
        break;

        case 5:
            sleep(5);
            printf("Woke up after 5 seconds\n");
        break;

        case 6: {
            int priority;
            printf("Enter priority value (lower value means higher priority): ");
            scanf("%d", &priority);
            if (setpriority(PRIO_PROCESS, 0, priority) == -1) {
                perror("setpriority");
            }
            else {
            printf("Priority set to %d\n", priority);
            }
        }
        break;

        case 7: {
            int status;
            wait(&status);
            if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
            }
        }
        break;

        case 8:
            fileDescriptor = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
            if (fileDescriptor == -1) {
            perror("open");
            }
            else {
            printf("File opened with descriptor %d\n", fileDescriptor);
        }
        break;

        case 9:
            if (fileDescriptor != -1) {
            ssize_t bytesRead = read(fileDescriptor, buffer, sizeof(buffer) - 1);
            if (bytesRead >= 0) {
                buffer[bytesRead] = '\0'; // Null-terminate the buffer
            printf("Read from file: %s\n", buffer);
            }
            else {
            perror("read");
            }
            }
            else {
            printf("File not opened\n");
            }
        break;

        case 10:
            if (fileDescriptor != -1) {
            const char *text = "Hello, file!";
            ssize_t bytesWritten = write(fileDescriptor, text, strlen(text));
            if (bytesWritten == -1) {
                perror("write");
            }
            else {
            printf("Wrote %zd bytes to file\n", bytesWritten);
            }
            }
            else {
            printf("File not opened\n");}
        break;

        case 11:
            if (fileDescriptor != -1) {
            close(fileDescriptor);
            printf("File closed\n");
            }
            else {
            printf("File not opened\n");
            }
        break;

        case 12:
            if (chmod(filename, S_IRUSR | S_IWUSR | S_IXUSR) == -1) {
            perror("chmod");
            }
            else {
            printf("File mode changed\n");
            }
        break;

        case 13:
            printf("Exiting...\n");
            return 0; // Exit the program
        break;
        
        default:
            printf("Invalid choice\n");
        }
    return 0;
  }
}