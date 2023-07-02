#include <stdio.h>
#include <stdlib.h>
struct process{
    int pID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int countLeft;
    int index;
};
struct readyQueue{
    int queue[1000];
    int inIndex;
    int exIndex;
};
typedef struct process proc;
typedef struct readyQueue rQ;
int compare(const void *p1,const void *p2){
    proc *a=(proc*)p1;
    proc *b=(proc*)p2;
    if(a->index!=-1 && b->index!=-1){
        if(a->pID>b->pID){
            return 1;
        }
        else if(a->pID<b->pID){
            return -1;
        }
        else{
            return 0;
        }
    }
    else if(a->index==-1 && b->index==-1){
        return 0;
    }
    else{
        if(a->index==-1){
            return 1;
        }
        else{
            return -1;
        }
    }
}
void enterReadyQueue(int time,proc processArray[],int noProcess,rQ *readyQueue,int timeQuantum){
    proc temp[noProcess];
    for(int i=0;i<noProcess;i++){
        temp[i].index=-1;
    }
    int index=0;
    for(int i=0;i<noProcess;i++){
        if(time>=processArray[i].arrivalTime && processArray[i].arrivalTime>time-timeQuantum){
            temp[index++]=processArray[i];
        }
    }
    qsort(temp,noProcess,sizeof(proc),compare);
    for(int i=0;i<noProcess;i++){
        if(temp[i].index==-1){
            break;
        }
        readyQueue->queue[readyQueue->inIndex]=temp[i].index;
        readyQueue->inIndex+=1;
    }
}
void printReadyQueue(rQ readyQueue,int time){
    printf("T:%d\n",time);
    for(int i=0;i<15;i++){
        printf("%d ",readyQueue.queue[i]);
    }
    printf("\n");
}
void main(){
    int noProcess,timeQuantum,completedProcess=0,cpuUsageTime=0,
    cpuIdolTime,time=0;
    rQ readyQueue;
    readyQueue.inIndex=readyQueue.exIndex=0;
    //initialise readyQueue with -1
    for(int i=0;i<1000;i++){
        readyQueue.queue[i]=-1;
    }
    printf("Lower processID/priority is given priority!\n");
    printf("Enter time-quantum:");
    scanf("%d",&timeQuantum);
    printf("Enter no of process:");
    scanf("%d",&noProcess);
    proc processArray[noProcess];
    for(int i=0;i<noProcess;i++){
        printf("Enter process ID(int):");
        scanf("%d",&processArray[i].pID);
        printf("Enter arrival time:");
        scanf("%d",&processArray[i].arrivalTime);
        printf("Enter burst-time:");
        scanf("%d",&processArray[i].burstTime);
        printf("\n");
        processArray[i].countLeft=processArray[i].burstTime;
        processArray[i].index=i;
    }
    int prevHaltedprocess;
    prevHaltedprocess=-1;
    while(completedProcess!=noProcess){
        //entering process in ready queue according to arrival time
        enterReadyQueue(time,processArray,noProcess,&readyQueue,timeQuantum);
        //entering previously halted process
        if(prevHaltedprocess!=-1){
            readyQueue.queue[readyQueue.inIndex++]=prevHaltedprocess;
            prevHaltedprocess=-1;
        }
        printReadyQueue(readyQueue,time);
        if(readyQueue.queue[readyQueue.exIndex]==-1){
            cpuIdolTime+=timeQuantum;
        }
        else{
            if(processArray[readyQueue.queue[readyQueue.exIndex]].countLeft<=timeQuantum){
                //adding completion time
                processArray[readyQueue.queue[readyQueue.exIndex]].completionTime=
                time+processArray[readyQueue.queue[readyQueue.exIndex]].countLeft;
                //add cpu usage
                cpuUsageTime+=processArray[readyQueue.queue[readyQueue.exIndex]].countLeft;
                time+=processArray[readyQueue.queue[readyQueue.exIndex]].countLeft;
                //set count_left=0
                processArray[readyQueue.queue[readyQueue.exIndex]].countLeft=0;
                completedProcess++;
                readyQueue.exIndex++;
                continue;//continuing becuase time added to time might be less then timeQuantum

            }
            else{
                //reducing count_left
                processArray[readyQueue.queue[readyQueue.exIndex]].countLeft-=timeQuantum;
                //storing current process
                prevHaltedprocess=readyQueue.queue[readyQueue.exIndex];
                readyQueue.exIndex++;
                cpuUsageTime+=timeQuantum;
            }
        }
        time+=timeQuantum;
    }
    int totalTat=0;
    int totalWt=0;
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<noProcess;i++){
        int TAT=processArray[i].completionTime-processArray[i].arrivalTime;
        int WT=TAT-processArray[i].burstTime;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
        processArray[i].pID,
        processArray[i].arrivalTime,
        processArray[i].burstTime,
        processArray[i].completionTime,
        TAT,
        WT
        );
        totalTat+=TAT;
        totalWt+=WT;
    }
    printf("Average TAT:%f\n",(float)(totalTat)/noProcess);
    printf("Average WT:%f\n",(float)(totalWt)/noProcess);
    printf("Throughput:%f%%",100*((float)cpuUsageTime/time));
}
