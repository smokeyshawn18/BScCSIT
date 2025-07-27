#include <stdio.h>
#include <limits.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;
};

int main() {
    int n, completed = 0, currentTime = 0, prev = -1;
    float totalWT = 0, totalTAT = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process p[n];
    
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].id);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
        p[i].isCompleted = 0;
    }
    
    while (completed != n) {
        int idx = -1;
        int minRemaining = INT_MAX;
        
        // Find process with shortest remaining time at currentTime
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].isCompleted == 0 && p[i].remainingTime < minRemaining && p[i].remainingTime > 0) {
                minRemaining = p[i].remainingTime;
                idx = i;
            }
        }
        
        if (idx != -1) {
            // Process found, execute for 1 unit time
            p[idx].remainingTime--;
            currentTime++;
            
            if (p[idx].remainingTime == 0) {
                p[idx].completionTime = currentTime;
                p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                p[idx].isCompleted = 1;
                completed++;
                
                totalWT += p[idx].waitingTime;
                totalTAT += p[idx].turnaroundTime;
            }
        } else {
            // No process available, increment time
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
