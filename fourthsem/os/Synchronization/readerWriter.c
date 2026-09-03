#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // for sleep()

// Shared resource to be read/written
int shared_resource = 0;

// Count of readers currently reading
int readCount = 0;

// Semaphores for synchronization
sem_t mutex;      // Controls access to readCount variable
sem_t writeLock;  // Controls access to shared_resource for writers

// Reader thread function
void* reader(void* arg) {
    int id = *((int*)arg);

    while (1) {
        // Entry section - acquire lock to safely update readCount
        sem_wait(&mutex);
        readCount++;
        if (readCount == 1) {
            // If first reader, block writers from accessing shared_resource
            sem_wait(&writeLock);
        }
        sem_post(&mutex);

        // Critical Section - reading shared resource
        printf("Reader %d is reading value %d\n", id, shared_resource);
        sleep(1); // Simulate reading time

        // Exit section - safely decrement readCount
        sem_wait(&mutex);
        readCount--;
        if (readCount == 0) {
            // If last reader, allow writers to proceed
            sem_post(&writeLock);
        }
        sem_post(&mutex);

        sleep(1); // Give some time before next read attempt
    }
    return NULL;
}

// Writer thread function
void* writer(void* arg) {
    int id = *((int*)arg);

    while (1) {
        // Acquire exclusive access to writeLock semaphore before writing
        sem_wait(&writeLock);

        // Critical Section - writing to shared resource
        shared_resource++;
        printf("Writer %d is writing value %d\n", id, shared_resource);
        sleep(2); // Simulate writing time

        // Release writeLock so others (readers or writers) can proceed
        sem_post(&writeLock);

        sleep(2); // Give some time before next write attempt
    }
    return NULL;
}

int main() {
    pthread_t rtid[5], wtid[2];
    int rids[5], wids[2];

    // Initialize semaphores:
    // mutex starts at 1 to allow one reader to access readCount at a time
    sem_init(&mutex, 0, 1);
    // writeLock starts at 1 to allow either one writer or multiple readers
    sem_init(&writeLock, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        rids[i] = i + 1;
        pthread_create(&rtid[i], NULL, reader, &rids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        wids[i] = i + 1;
        pthread_create(&wtid[i], NULL, writer, &wids[i]);
    }

    // Join threads (in this infinite loop case, this won't return, so mostly for completeness)
    for (int i = 0; i < 5; i++) {
        pthread_join(rtid[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(wtid[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&writeLock);

    return 0;
}
