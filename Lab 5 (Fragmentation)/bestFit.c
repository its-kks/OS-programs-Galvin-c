//best fit with fragmentation
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int randomSize(int maxValue) {
    struct timespec currentTime;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);
    srand(currentTime.tv_nsec / 1000);
    int randomInteger = 0;
    do {
        randomInteger = rand() % maxValue + 1;
    } while (randomInteger == 0);

    return randomInteger;
}
//using fiexed partitioning
struct startEnd{
    int start;
    int end;
    int used;
};
typedef struct startEnd startEnd;
int main(){
    int sizeRAM,noPartition,noProcess;
    printf("Enter size of RAM (in KBs):");
    scanf("%d",&sizeRAM);
    startEnd RAM[sizeRAM];
    printf("Enter no of partition:");
    scanf("%d",&noPartition);
    //taking size of partition
    int totalSize=0,traversingRam=0,prevIndex=-1;
    for(int i=0;i<noPartition-1;i++){
        int size;
        printf("Size partition%d (in KBs):",i+1);
        scanf("%d",&size);
        totalSize+=size;
        if(totalSize>sizeRAM){
            printf("Partition too large\n");
            break;
            totalSize-=size;
        }
        else{
            RAM[traversingRam].start=prevIndex+1;
            RAM[traversingRam].end=prevIndex+size;
            RAM[traversingRam].used=0;
            prevIndex=RAM[traversingRam++].start;
        }
    }
    //making portion of left over RAM
    if(totalSize<sizeRAM){
        RAM[traversingRam].start=prevIndex+1;
        RAM[traversingRam].end=prevIndex+sizeRAM-totalSize;
        RAM[traversingRam].used=0;
    }
    //Generating process of random size
    printf("Enter no of processes to be generated:");
    scanf("%d",&noProcess);
    int process[noProcess];
    for(int i=0;i<noProcess;i++){
        process[i]=randomSize(sizeRAM/2);
    }
    int externalFragmentation=0;
    //adding process to RAM
    printf("Process_ID\tProcess_Size\t Allocated_Partion\t Internal_Fragmentation(KB)\n");
    for(int i=0;i<noProcess;i++){
        int leftSpace=__INT_MAX__;
        int nthPartition;
        for(int j=0;j<noPartition;j++){
            int spaceInPortion=RAM[j].end-RAM[j].start+1;
            if(RAM[j].used==0 && spaceInPortion>=process[i]){
                if(leftSpace>spaceInPortion-process[i]){
                    leftSpace=spaceInPortion-process[i];
                    nthPartition=j;
                }
            }
        }
        if(leftSpace!=__INT_MAX__){
            RAM[nthPartition].used=process[i];
            printf("%d\t\t%d\t\t\t%d\t\t\t%d\n",i+1,process[i],
            nthPartition+1,RAM[nthPartition].end-RAM[nthPartition].start+1-process[i]);
            externalFragmentation+=RAM[nthPartition].end-RAM[nthPartition].start+1-process[i];
        }
        else{
            printf("%d\t\t%d\t\t\t-\t\t\t-\n",i+1,process[i]);
        }
    }
    printf("Total external fragmentation:%d KB\n",externalFragmentation);
}