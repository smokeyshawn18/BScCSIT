#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Philosopher states
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[NUM_PHILOSOPHERS];                // State of each philosopher
int philosopher_ids[NUM_PHILOSOPHERS];      // IDs for threads

sem_t mutex;                                // Global mutex to control state changes
sem_t sem[NUM_PHILOSOPHERS];                // One semaphore per philosopher

// Helper macros for neighbors
#define LEFT(i) ((i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS)
#define RIGHT(i) ((i + 1) % NUM_PHILOSOPHERS)

// Function to check whether a philosopher can eat
void test(int i) {
    if (state[i] == HUNGRY &&
        state[LEFT(i)] != EATING &&
        state[RIGHT(i)] != EATING) {
        
        state[i] = EATING;
        sem_post(&sem[i]); // Allow philosopher to eat
    }
}

void take_forks(int i) {
    sem_wait(&mutex);           // Enter critical section

    state[i] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", i);
    
    test(i);                    // Try to pick up forks

    sem_post(&mutex);           // Exit critical section
    sem_wait(&sem[i]);          // Wait if forks were not available
}

void put_forks(int i) {
    sem_wait(&mutex);           // Enter critical section

    state[i] = THINKING;
    printf("Philosopher %d puts down forks and starts THINKING\n", i);
    
    test(LEFT(i));              // Check if left neighbor can eat
    test(RIGHT(i));             // Check if right neighbor can eat

    sem_post(&mutex);           // Exit critical section
}

void* philosopher(void* arg) {
    int id = *(int*)arg;

    while (1) {
        printf("Philosopher %d is THINKING\n", id);
        sleep(1);                       // Simulate thinking

        take_forks(id);                // Try to eat

        printf("Philosopher %d is EATING\n", id);
        sleep(2);                      // Simulate eating

        put_forks(id);                // Done eating, put down forks
    }
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);           // Binary semaphore for mutual exclusion
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&sem[i], 0, 0);      // Initialize per-philosopher semaphores to 0
        philosopher_ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&threads[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join threads (infinite loop, so we never reach here)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
