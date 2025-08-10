#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int n, timeQuantum, currentTime = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].id);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    int queue[n * 10]; // Enough size for re-enqueuing
    int front = 0, rear = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    // Find the earliest arrival time
    int earliestArrival = p[0].arrivalTime;
    for (int i = 1; i < n; i++) {
        if (p[i].arrivalTime < earliestArrival) {
            earliestArrival = p[i].arrivalTime;
        }
    }

    // Set current time and enqueue processes with earliest arrival
    currentTime = earliestArrival;
    for (int i = 0; i < n; i++) {
        if (p[i].arrivalTime == currentTime) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            // No process in queue, jump to next available process
            currentTime++;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && p[i].arrivalTime <= currentTime) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++]; // Dequeue
        int execTime = (p[idx].remainingTime < timeQuantum) ? p[idx].remainingTime : timeQuantum;

        currentTime += execTime;
        p[idx].remainingTime -= execTime;

        // Enqueue newly arrived processes during this time slice
        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].arrivalTime <= currentTime) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[idx].remainingTime == 0) {
            // Process completed
            p[idx].completionTime = currentTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            totalWT += p[idx].waitingTime;
            totalTAT += p[idx].turnaroundTime;
            completed++;
        } else {
            // Re-queue the process for the next round
            queue[rear++] = idx;
        }
    }

    // Output result
    printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
