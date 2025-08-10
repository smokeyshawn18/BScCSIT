#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

// Thread function: prints messages and simulates work with sleep
void* threadFunction(void* arg) {
    printf("[Thread] Thread started.\n");
    sleep(2);  // Simulate work
    printf("[Thread] Thread finished.\n");
    return NULL;
}

int main() {
    pid_t pid;
    pthread_t thread;

    printf("[Main] Parent process started. PID: %d\n", getpid());

    // Create child process
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process code
        printf("[Child] Child process started. PID: %d\n", getpid());
        sleep(3);  // Simulate child doing work
        printf("[Child] Child process finished.\n");
        exit(0);
    } else {
        // Parent process code

        // Create a thread
        if (pthread_create(&thread, NULL, threadFunction, NULL) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }

        printf("[Parent] Thread created.\n");

        // Wait for thread to finish
        pthread_join(thread, NULL);
        printf("[Parent] Thread joined.\n");

        // Wait for child process to finish
        waitpid(pid, NULL, 0);
        printf("[Parent] Child process finished.\n");

        printf("[Parent] Parent process finished.\n");
    }

    return 0;
}
