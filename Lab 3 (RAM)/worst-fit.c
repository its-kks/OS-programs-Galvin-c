#include <stdlib.h>
#include <stdio.h>
//using fiexed partitioning
struct startEnd{
    int start;
    int end;
    int used;
    int spaceCovered;
};
typedef struct startEnd startEnd;
int main(){
    int sizeRAM,noPartition,noProcess;
    printf("Enter size of RAM:");
    scanf("%d",&sizeRAM);
    startEnd RAM[sizeRAM];
    printf("Enter no of partition:");
    scanf("%d",&noPartition);
    //taking size of partition
    int totalSize=0,traversingRam=0,prevIndex=-1;
    for(int i=0;i<noPartition-1;i++){
        int size;
        printf("Size partition%d:",i+1);
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
    printf("Enter no of processes:");
    scanf("%d",&noProcess);
    int process[noProcess];
    for(int i=0;i<noProcess;i++){
        printf("Size process%d:",i+1);
        scanf("%d",&process[i]);
    }
    //adding process to RAM 
    for(int i=0;i<noProcess;i++){
        int leftSpace=-1;
        int nthPartition;
        for(int j=0;j<noPartition;j++){
            int spaceInPortion=RAM[j].end-RAM[j].start+1;
            if(RAM[j].used==0 && spaceInPortion>=process[i]){
                if(leftSpace<spaceInPortion-process[i]){
                    leftSpace=spaceInPortion-process[i];
                    nthPartition=j;
                }
            }
        }
        if(leftSpace!=-1){
            RAM[nthPartition].used=1;
            printf("Process %d allocated %d partition\n",i+1,nthPartition+1);
        }
        else{
            printf("Process %d can't be allocated\n",i+1);
        }
    }
}