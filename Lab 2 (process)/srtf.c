#include <stdio.h>
#include <stdlib.h>
struct processNode{
    int pID;
    int AT;
    int BT;
    int CT;
    int BT2;
    int left;
    struct processNode *next;
};
int inf=2147483647;
typedef struct processNode pNode;
void makeProcList(pNode processList[],int noProcess){
    for(int i=0;i<noProcess;i++){
        processList[i].pID=i;
        printf("Enter Process %d AT:",i);
        scanf("%d",&processList[i].AT);
        printf("Enter Process %d BT:",i);
        scanf("%d",&processList[i].BT);
        processList[i].BT2=processList[i].BT;
        processList[i].left=processList[i].BT;
    }
}
void printOutput(pNode processList[],int noProcess,int clock){
    float totalWT=0,totalTAT=0,totalBT=0;
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<noProcess;i++){
        int tat=processList[i].CT-processList[i].AT;
        int wt=tat-processList[i].BT2;
        int bt=processList[i].BT2;
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
int compare(const void* a,const void* b){
    pNode *p1=(pNode*)a;
    pNode *p2=(pNode*)b;
    if(p1->BT>p2->BT){
        return 1;
    }
    else if(p1->BT==p2->BT){
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
    //add processes that have arrived and then sort them
    //important to add from back
    int j=noProcess-1;
    for(int i=0;i<noProcess;i++){
        if(clock>=processList[i].AT){
            waitingQueue[j].pID=processList[i].pID;
            waitingQueue[j].AT=processList[i].AT;
            waitingQueue[j].BT2=processList[i].BT2;
            waitingQueue[j].BT=processList[i].BT;
            waitingQueue[j].CT=processList[i].CT;
            waitingQueue[j].left=processList[i].left;
            //make at of added process inf so can't be readded
            processList[i].AT=inf;
            j--;
        }
    }
    //perform sorting
    qsort(waitingQueue,noProcess,sizeof(pNode),compare);
}
int main(){
    int noProcess,clock=0,processLeft=0;
    printf("Enter no of Process:");
    scanf("%d",&noProcess);
    processLeft=noProcess;
    pNode processList[noProcess];
    makeProcList(processList,noProcess);
    //sort processList wrt AT
    qsort(processList,noProcess,sizeof(pNode),compare);
    //make a waiting queue
    pNode waitingQueue[noProcess];
    //filling AT=inf and priority=inf
    for(int i=0;i<noProcess;i++){
        waitingQueue[i].AT=inf;
        waitingQueue[i].BT=inf;
    }
    while(processLeft!=0){
        addToQueue(processList,noProcess,waitingQueue,clock);
        if(clock>=waitingQueue[0].AT){
            waitingQueue[0].left-=1;
            clock++;
            if(waitingQueue[0].left==0){
                processLeft--;
                //firse use na ho jae
                waitingQueue[0].CT=clock;
                waitingQueue[0].BT=inf;
            }
        }
        else{
            clock++;
        }
    }
    printOutput(waitingQueue,noProcess,clock);
}