#include <stdio.h>
#include <stdbool.h>

#define MAX_RESOURCES 10
#define MAX_PROCESSES 10

// Number of processes and resources
int n, m;

// Available resources
int available[MAX_RESOURCES];

// Maximum demand of each process
int max[MAX_PROCESSES][MAX_RESOURCES];

// Amount currently allocated to each process
int allocation[MAX_PROCESSES][MAX_RESOURCES];

// Remaining need of each process
int need[MAX_PROCESSES][MAX_RESOURCES];

// Function to calculate the need matrix
void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Safety algorithm to check if system is in safe state
bool isSafe() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safeSeq[MAX_PROCESSES];
    int count = 0;

    // Initialize work as available resources
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    // Simulate allocation
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            // Could not find a safe sequence
            return false;
        }
    }

    // Print safe sequence
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        if (i != n - 1)
            printf(" -> ");
    }
    printf("\n");
    return true;
}

// Function to request resources for a process
bool requestResource(int processNumber, int request[]) {
    // Check if request is less than need
    for (int i = 0; i < m; i++) {
        if (request[i] > need[processNumber][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Check if request is less than available
    for (int i = 0; i < m; i++) {
        if (request[i] > available[i]) {
            printf("Resources are not available now. Process must wait.\n");
            return false;
        }
    }

    // Pretend to allocate requested resources
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[processNumber][i] += request[i];
        need[processNumber][i] -= request[i];
    }

    // Check if new state is safe
    if (isSafe()) {
        printf("Resources allocated to process P%d.\n", processNumber);
        return true;
    } else {
        // Rollback, as the state is unsafe
        printf("State is unsafe after allocation. Rolling back.\n");
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[processNumber][i] -= request[i];
            need[processNumber][i] += request[i];
        }
        return false;
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter total available resources of each type:\n");
    for (int i = 0; i < m; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &available[i]);
    }

    printf("Enter maximum demand matrix (max) for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Maximum demand for process P%d (space separated for each resource): ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter allocation matrix for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Allocation for process P%d (space separated for each resource): ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate the need matrix
    calculateNeed();

    // Check the system safety initially
    if (!isSafe()) {
        printf("System is not in a safe state initially.\n");
        return 1;
    }

    // Example resource request input
    int processNumber;
    printf("Enter process number making the resource request: ");
    scanf("%d", &processNumber);

    int request[MAX_RESOURCES];
    printf("Enter request for each resource (space separated): ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &request[i]);
    }

    requestResource(processNumber, request);

    return 0;
}
