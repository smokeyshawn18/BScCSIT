#include <stdio.h>

// Define a structure to hold all necessary info about a process
struct Process {
    int id;               // Process ID
    int arrivalTime;      // Arrival Time (AT)
    int burstTime;        // Burst Time (BT)
    int startTime;        // Start Time (ST)
    int completionTime;   // Completion Time (CT)
    int waitingTime;      // Waiting Time (WT)
    int turnaroundTime;   // Turnaround Time (TAT)
};

// Function to sort processes by arrival time (for FCFS)
void sortByArrivalTime(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].arrivalTime > p[j].arrivalTime) {
                // Swap processes if the earlier one has a later arrival time
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n); // Input number of processes

    struct Process p[n]; // Declare an array of processes

    // Input Arrival Time and Burst Time for each process
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1; // Assign process ID
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].id);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
    }

    // Sort processes based on arrival time (FCFS rule)
    sortByArrivalTime(p, n);

    int currentTime = 0; // Tracks CPU time

    // Calculate ST, CT, TAT, WT for each process
    for (int i = 0; i < n; i++) {
        // If CPU is idle, jump to the process arrival time
        if (currentTime < p[i].arrivalTime)
            currentTime = p[i].arrivalTime;

        // Start time is the current time
        p[i].startTime = currentTime;

        // Completion time = start time + burst time
        p[i].completionTime = p[i].startTime + p[i].burstTime;

        // Turnaround time = completion time - arrival time
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;

        // Waiting time = turnaround time - burst time
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;

        // Move CPU time forward
        currentTime = p[i].completionTime;
    }

    // Print the result table
    printf("\nID\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].arrivalTime, p[i].burstTime,
               p[i].startTime, p[i].completionTime,
               p[i].turnaroundTime, p[i].waitingTime);
    }

    return 0;
}
