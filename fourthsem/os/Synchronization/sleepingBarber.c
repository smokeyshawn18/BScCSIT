#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 5

sem_t waitingChairs;  // Number of free chairs in waiting room (initially 5)
sem_t barberReady;    // Signals barber status (0 = sleeping, 1 = ready)
sem_t mutex;          // Mutex to protect critical sections
int customersWaiting = 0;  // Number of customers currently waiting

void* barber(void* arg) {
    while (1) {
        // Wait for a customer to become available
        sem_wait(&barberReady);

        // Barber is cutting hair now
        printf("Barber: Cutting hair...\n");
        sleep(2);  // Haircut takes some time

        // Lock mutex to update shared customersWaiting count
        sem_wait(&mutex);
        customersWaiting--;        // One less customer waiting (they get haircut)
        sem_post(&waitingChairs);  // One waiting chair is now free
        sem_post(&mutex);          // Release mutex
    }
    return NULL;
}

void* customer(void* arg) {
    int id = *((int*)arg);
    free(arg);

    // Customer arrives
    sem_wait(&mutex);
    if (customersWaiting < CHAIRS) {
        // Customer sits down in waiting room chair
        customersWaiting++;
        printf("Customer %d: Sitting in waiting room. Waiting customers = %d\n", id, customersWaiting);
        sem_post(&mutex);

        // Notify barber that a customer is ready
        sem_post(&barberReady);

        // Wait for barber to be ready (simulate time for haircut)
        // No explicit wait here; haircut simulated in barber thread
        
    } else {
        // No chairs available, customer leaves
        printf("Customer %d: No chairs available, leaving.\n", id);
        sem_post(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t bThread;
    pthread_t customers[15];
    int i;

    // Initialize semaphores
    sem_init(&waitingChairs, 0, CHAIRS);
    sem_init(&barberReady, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create barber thread
    pthread_create(&bThread, NULL, barber, NULL);

    // Create customer threads arriving at intervals
    for (i = 0; i < 15; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&customers[i], NULL, customer, id);
        sleep(1);  // Customers arrive every second
    }

    // Wait for all customers to finish
    for (i = 0; i < 15; i++) {
        pthread_join(customers[i], NULL);
    }

    // Barber thread runs infinitely; in practice, program may end here or wait indefinitely
    // For clean exit, you might add a stop condition for barber thread

    // Destroy semaphores
    sem_destroy(&waitingChairs);
    sem_destroy(&barberReady);
    sem_destroy(&mutex);

    return 0;
}
