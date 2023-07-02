//variable length partitioning using First Fit
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct process{
    int pID;
    int pSize;
};
typedef struct process prcs;
void printRAM(int RAM[],int sizeOfRAM){
    //print the RAM
    printf("RAM:\n");
    for(int i=0;i<sizeOfRAM;i++){
        printf("%d ",RAM[i]);
    }
    printf("\n");
}
int compactation(int pID, prcs *processList[], int RAM[], int *noProcess,int *RAMIndex) {
    int flag = 0;
    //finding process
    for (int i = 0; i < *noProcess; i++) {
        if (processList[i] != NULL && processList[i]->pID == pID) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        //process not found
        return 0;
    } else {
        //deleting the process
        int start=0,end=0;
        while(RAM[start]!=pID){
            start++;
        }
        end=start;
        while(RAM[end]==pID){
            RAM[end++]=0;
        }
        //performing compactation
        int movement=0;
        while(end<*RAMIndex){
            RAM[start++]=RAM[end];
            RAM[end++]=0;
            movement++;
        }
        *noProcess=*noProcess-1;
        *RAMIndex=*RAMIndex-(end-start);
        return movement;
    }
}
void addToRAM(int RAM[],int *RAMIndex,int size,int id){
    int i=0;
    for(i=*RAMIndex;i<*RAMIndex+size;i++){
        RAM[i]=id;
    }
    *RAMIndex=i;
}
void main(){
    int sizeOfRAM,ramCovered=0,processCounter=0,indexProcessList=0,RAMindex=0;
    printf("Enter size of memory(in KB):");
    scanf("%d",&sizeOfRAM);
    prcs *processList[sizeOfRAM];
    int RAM[sizeOfRAM];
    //emptying the RAM
    for(int i=0;i<sizeOfRAM;i++){
        RAM[i]=0;
    }
    int flag=1;
    //taking input about the process
    while(flag){
        printf("Enter size of process %d:",processCounter+1);
        //Making new processes dyanamically
        prcs* newProcess = (prcs*)malloc(sizeof(prcs));
        if (newProcess == NULL) {
            printf("Memory allocation failed. Exiting...\n");
            exit(1);
        }
        scanf("%d",&newProcess->pSize);
        if(newProcess->pSize+ramCovered>sizeOfRAM){
            printf("Process size too large mermory left %d KB\n",sizeOfRAM-ramCovered);
        }
        else if(newProcess->pSize<=0){
            printf("Process size should be positive integer\n");
        }
        else{
            newProcess->pID=++processCounter;
            processList[indexProcessList++]=newProcess;
            ramCovered+=newProcess->pSize;
            //add process to RAM
            addToRAM(RAM,&RAMindex,newProcess->pSize,newProcess->pID);
        }
        printf("Do you want to enter more process(0/1):");
        scanf("%d",&flag);
    }
    printf("Available processes:\n");
    for(int i=0;i<indexProcessList;i++){
        printf("P%d:%dKB\n",processList[i]->pID,processList[i]->pSize);
    }
    printRAM(RAM,sizeOfRAM);
    //completing the process
    flag=1;
    while(flag){
        printf("Enter process ID that has completed:");
        int pID;
        scanf("%d",&pID);
        //calling compactation function
        int movement=compactation(pID,processList,RAM,&indexProcessList,&RAMindex);
        if(movement){
            printf("%d KBs of data moved\n",movement);
            printRAM(RAM,sizeOfRAM);
        }
        else{
            printf("Invalid process ID!\n");
        }
        printf("Do you want to finish another process(0/1):");
        scanf("%d",&flag);
    }
}