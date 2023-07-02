#include <stdio.h>
#include <stdlib.h>
struct processNode{
    int pID;
    int priority;
    int AT;
    int BT;
    int CT;
    int left;
    struct processNode *next;
};
typedef struct processNode pNode;
void makeProcList(pNode processList[],int noProcess){
    for(int i=0;i<noProcess;i++){
        processList[i].pID=i;
        printf("Enter Process %d priority:",i);
        scanf("%d",&processList[i].priority);
        printf("Enter Process %d AT:",i);
        scanf("%d",&processList[i].AT);
        printf("Enter Process %d BT:",i);
        scanf("%d",&processList[i].BT);
        processList[i].left=processList[i].BT;
    }
}
void printOutput(pNode processList[],int noProcess,int clock){
    float totalWT=0,totalTAT=0,totalBT=0;
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<noProcess;i++){
        int tat=processList[i].CT-processList[i].AT;
        int wt=tat-processList[i].BT;
        int bt=processList[i].BT;
        totalTAT+=tat;
        totalWT+=wt;
        totalBT+=bt;
        printf(" %02d\t%d\t%d\t%d\t%d\t%d\n",processList[i].pID,processList[i].AT,bt,
        processList[i].CT,tat,wt);
    }
    printf("Avg TAT %0.2f\n",totalTAT/noProcess);
    printf("Avg WT %0.2f\n",totalWT/noProcess);
    printf("Throughput %0.2f percent\n",(1-(clock-totalBT)/clock)*100);
}
int compare(const void *a,const void *b){
    pNode* p1=(pNode*)a;
    pNode* p2=(pNode*)b;
    if(p1->priority>p2->priority){
        return 1;
    }
    else if(p1->priority==p2->priority){
        //check pID
        if(p1->pID>p2->pID){
            return 1;
        }
        else if(p1->pID<p2->pID){
            return -1;
        }
        else{
            return 0;
        }
    }
    else{
        return -1;
    }
}
void addToQueue(pNode processList[],int noProcess,pNode waitingQueue[],int clock){
    int j=noProcess-1;
    for(int i=0;i<noProcess;i++){
        //it is vital to add from back to prevent previously added values
        if(clock>=processList[i].AT){
            waitingQueue[j].pID=processList[i].pID;
            waitingQueue[j].AT=processList[i].AT;
            waitingQueue[j].priority=processList[i].priority;
            waitingQueue[j].BT=processList[i].BT;
            waitingQueue[j].CT=processList[i].CT;
            waitingQueue[j].left=processList[i].left;
            //once added to wt make its AT to infinity so it cant be added again
            processList[i].AT=2147483647;
            j--;
        }
    }
    //sort wrt priority
    qsort(waitingQueue,noProcess,sizeof(pNode),compare);
}
int main(){
    int noProcess,clock=0,processCount,idle=0;
    printf("Enter no of Process:");
    scanf("%d",&noProcess);
    processCount=noProcess;
    pNode processList[noProcess];
    makeProcList(processList,noProcess);
    //make waiting queue
    pNode waitingQueue[noProcess];
    //fill waitingQueue with dummy process having priority=infinity
    //and arrival time=infinity
    for(int i=0;i<noProcess;i++){
        waitingQueue[i].priority=2147483647;
        waitingQueue[i].AT=2147483647;
    }
    while(processCount!=0){
        //enter values to waiting queue
        addToQueue(processList,noProcess,waitingQueue,clock);
        if(clock>=waitingQueue[0].AT){
            waitingQueue[0].left-=1;
            clock+=1;
            if(waitingQueue[0].left==0){
                processCount--;
                //make priority infinite taki repeat na ho
                waitingQueue[0].priority=2147483647;
                waitingQueue[0].CT=clock;
            }
        }
        else{
            printf("Idle\n");
            clock+=1;
            idle+=1;
        }
    }
    printOutput(waitingQueue,noProcess,clock);
}
