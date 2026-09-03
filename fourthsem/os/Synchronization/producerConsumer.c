#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Size of the buffer

int buffer[BUFFER_SIZE];     // Shared buffer
int in = 0;                  // Index for producer
int out = 0;                 // Index for consumer

// Semaphores
sem_t empty;  // Counts empty slots
sem_t full;   // Counts filled slots
pthread_mutex_t mutex; // Mutex for mutual exclusion

// Producer function
void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100; // Produce a random item

        sem_wait(&empty);             // Wait if buffer is full (empty == 0)
        pthread_mutex_lock(&mutex);   // Lock critical section

        buffer[in] = item;            // Put item in buffer
        printf("Produced: %d at %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;  // Move to next index circularly

        pthread_mutex_unlock(&mutex); // Unlock critical section
        sem_post(&full);              // Signal that buffer has more items

        sleep(1); // Simulate time to produce
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);              // Wait if buffer is empty (full == 0)
        pthread_mutex_lock(&mutex);   // Lock critical section

        item = buffer[out];           // Remove item from buffer
        printf("Consumed: %d at %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE; // Move to next index circularly

        pthread_mutex_unlock(&mutex); // Unlock critical section
        sem_post(&empty);             // Signal that buffer has more empty slots

        sleep(1); // Simulate time to consume
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // All slots initially empty
    sem_init(&full, 0, 0);            // No filled slots initially
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    // Create threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
