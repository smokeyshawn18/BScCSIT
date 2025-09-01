#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id, at, bt, ct, tat, wt, rt, done;
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
    int n, dir;
    printf("Enter number of processes: "); scanf("%d",&n);
    Process p[n];
    for(int i=0;i<n;i++){
        p[i].id=i+1; p[i].done=0;
        printf("Enter AT and BT for P%d: ",i+1);
        scanf("%d %d",&p[i].at,&p[i].bt);
    }

    printf("Enter initial direction (1=up,0=down): "); scanf("%d",&dir);

    int time=0, completed=0;
    while(completed<n){
        int idx=-1;
        int candidateBT=dir?0:-1;
        for(int i=0;i<n;i++){
            if(!p[i].done && p[i].at <= time){
                if(dir && p[i].bt >= candidateBT){ candidateBT=p[i].bt; idx=i; }
                if(!dir && p[i].bt <= candidateBT){ candidateBT=p[i].bt; idx=i; }
            }
        }
        if(idx==-1){ time++; continue; }
        p[idx].ct = time + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].rt = p[idx].wt;
        time = p[idx].ct;
        p[idx].done=1; completed++;
    }

    printTable(p,n);
    return 0;
}
