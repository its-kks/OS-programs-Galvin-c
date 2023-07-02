//LinkedList
#include <stdio.h>
#include <stdlib.h>
struct block{
    int data;
    struct block *point;
};
typedef struct block block;
int main(){
    //considering each block of size 1kb+extra space(to store pointer)
    int diskSize,diskLeft;
    printf("Enter disk size:");
    scanf("%d",&diskSize);
    diskLeft=diskSize;
    block disk[diskSize];
    for(int i=0;i<diskSize;i++){
        disk[i].data=0;
    }
    int exit=1;
    while(exit){
        int fileSize,storedAt=-1,prev=-1;
        printf("Enter file size:");
        scanf("%d",&fileSize);
        if(fileSize>diskLeft){
            printf("File too large!\n");
        }
        else{
            int i=0;
            diskLeft-=fileSize;
            for(;fileSize!=0;i++){
                if(disk[i].data==0){
                    if(prev==-1){
                        storedAt=i;
                        prev=i;
                        disk[i].data=1;
                    }
                    else{
                        disk[prev].point=&disk[i];
                        prev=i;
                        disk[i].data=1;
                    }
                    fileSize--;
                }
            }
            disk[prev].point=NULL;
            printf("File's 1st block is:%d\n",storedAt);
        }
        printf("Enter more file(0/1):");
        scanf("%d",&exit);
    }
}