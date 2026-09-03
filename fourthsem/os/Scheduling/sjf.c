#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;  // Flag to check if process is done
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
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].id);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].isCompleted = 0;
    }
    
    while (completed != n) {
        int idx = -1;
        int minBurst = 1e9;
        
        // Find process with shortest burst time among arrived & incomplete
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].isCompleted == 0) {
                if (p[i].burstTime < minBurst) {
                    minBurst = p[i].burstTime;
                    idx = i;
                } else if (p[i].burstTime == minBurst) {
                    // Tie-breaker: smaller arrival time
                    if (p[i].arrivalTime < p[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }
        
        if (idx != -1) {
            // Process found, execute it
            p[idx].completionTime = currentTime + p[idx].burstTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            
            totalWT += p[idx].waitingTime;
            totalTAT += p[idx].turnaroundTime;
            
            currentTime = p[idx].completionTime;
            p[idx].isCompleted = 1;
            completed++;
        } else {
            // No process arrived yet, increment currentTime
            currentTime++;
        }
    }
    
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
