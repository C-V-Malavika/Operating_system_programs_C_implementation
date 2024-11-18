#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <wait.h>

#define NUM_MESSAGES 10
#define TOPIC_A "Technology"
#define TOPIC_B "Health"

const char *topic_a_contents[] = {
    "AI is transforming industries.",
    "Quantum computing is the future.",
    "Blockchain technology is revolutionizing finance."
};

const char *topic_b_contents[] = {
    "Eating healthy boosts immunity.",
    "Regular exercise improves mental health.",
    "Sleep is crucial for well-being."
};

typedef struct {
    char topic[20];
    char content[100];
};Message

void audience(const char *topic, int read_fd) {
    Message msg;
    while (read(read_fd, &msg, sizeof(msg)) > 0) {
        if (strcmp(msg.topic, topic) == 0) {
            printf("%s Audience received: %s\n", topic, msg.content);
        }
    }
    close(read_fd);
    exit(0);
}

int main() {
    int pipe_main[2], pipe_a[2], pipe_b[2];

    // Create pipes
    pipe(pipe_main);
    pipe(pipe_a);
    pipe(pipe_b);

    // Fork separator process
    if (fork() == 0) { // Separator
        close(pipe_main[1]);
        close(pipe_a[0]);
        close(pipe_b[0]);

        Message msg;
        while (read(pipe_main[0], &msg, sizeof(msg)) > 0) {
            if (strcmp(msg.topic, TOPIC_A) == 0) {
                write(pipe_a[1], &msg, sizeof(msg));
            } else {
                write(pipe_b[1], &msg, sizeof(msg));
            }
        }
        close(pipe_a[1]);
        close(pipe_b[1]);
        exit(0);
    }

    // Fork audience for Topic A
    if (fork() == 0) {
        close(pipe_main[0]);
        close(pipe_a[1]);
        audience(TOPIC_A, pipe_a[0]);
    }

    // Fork audience for Topic B
    if (fork() == 0) {
        close(pipe_main[0]);
        close(pipe_b[1]);
        audience(TOPIC_B, pipe_b[0]);
    }

    // Parent process
    close(pipe_main[0]);
    srand(time(NULL));
    for (int i = 0; i < NUM_MESSAGES; i++) {
        Message msg;
        if (rand() % 2 == 0) {
            strcpy(msg.topic, TOPIC_A);
            strcpy(msg.content, topic_a_contents[rand() % 3]);
        } else {
            strcpy(msg.topic, TOPIC_B);
            strcpy(msg.content, topic_b_contents[rand() % 3]);
        }
        write(pipe_main[1], &msg, sizeof(msg));
    printf("Parent sent: [%s] %s\n", msg.topic, msg.content);
    sleep(1);
    }
    close(pipe_main[1]);
    wait(NULL); // Wait for separator
    wait(NULL); // Wait for audience A
    wait(NULL); // Wait for audience B
    return 0;
}