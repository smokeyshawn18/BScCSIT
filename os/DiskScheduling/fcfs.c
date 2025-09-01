#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id, at, bt, ct, tat, wt, rt;
} Process;

void printTable(Process p[], int n){
    int totalTAT=0,totalWT=0;
    printf("\n%-8s%-8s%-8s%-8s%-8s%-8s%-8s\n","Process","AT","BT","CT","TAT","WT","RT");
    for(int i=0;i<n;i++){
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
        printf("P%-7d%-8d%-8d%-8d%-8d%-8d%-8d\n",
               p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
    }
    printf("\nAverage TAT = %.2f\n",(float)totalTAT/n);
    printf("Average WT  = %.2f\n",(float)totalWT/n);
}

int main(){
    int n;
    printf("Enter number of processes: "); scanf("%d",&n);
    Process p[n];
    for(int i=0;i<n;i++){
        p[i].id=i+1;
        printf("Enter AT and BT for P%d: ",i+1);
        scanf("%d %d",&p[i].at,&p[i].bt);
    }

    int time=0;
    for(int i=0;i<n;i++){
        if(time < p[i].at) time=p[i].at;
        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].wt;
        time = p[i].ct;
    }

    printTable(p,n);
    return 0;
}
