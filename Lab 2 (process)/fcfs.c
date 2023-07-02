#include <stdio.h>
#include <stdlib.h>
struct processNode{
    int pID;
    int AT;
    int BT;
    int CT;
    struct processNode *next;
};
typedef struct processNode pNode;
void makeProcList(pNode processList[],int noProcess){
    for(int i=0;i<noProcess;i++){
        processList[i].pID=i;
        printf("Enter Process %d AT:",i);
        scanf("%d",&processList[i].AT);
        printf("Enter Process %d BT:",i);
        scanf("%d",&processList[i].BT);
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
    if(p1->AT>p2->AT){
        return 1;
    }
    else if(p1->AT==p2->AT){
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
int main(){
    int noProcess,clock=0,index=0,idle=0;
    printf("Enter no of Process:");
    scanf("%d",&noProcess);
    pNode processList[noProcess];
    makeProcList(processList,noProcess);
    //sort processList wrt AT
    qsort(processList,noProcess,sizeof(pNode),compare);
    while(index<noProcess){
        if(clock>=processList[index].AT){
            clock+=processList[index].BT;
            processList[index].CT=clock;
            index++;
        }
        else{
            //no process yet arrived
            clock+=1;
            idle+=1;
        }
    }
    printOutput(processList,noProcess,clock);
}   
//No need to make ready queue
//simply make a list 
//sort this list wrt to arrival
//keep completing one process at a time
//increment clock if no process present