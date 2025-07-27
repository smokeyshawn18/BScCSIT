#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;
};

int main() {
    int n, completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time, Burst Time and Priority for Process %d: ", p[i].id);
        scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
        p[i].isCompleted = 0;
    }

    while (completed < n) {
        int idx = -1;
        int highestPriority = 9999;

        // Select highest priority process that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && !p[i].isCompleted) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == highestPriority && p[i].arrivalTime < p[idx].arrivalTime) {
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            currentTime += p[idx].burstTime;
            p[idx].completionTime = currentTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            p[idx].isCompleted = 1;
            totalWT += p[idx].waitingTime;
            totalTAT += p[idx].turnaroundTime;
            completed++;
        } else {
            currentTime++;
        }
    }

    printf("\nID\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].arrivalTime, p[i].burstTime, p[i].priority,
               p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
