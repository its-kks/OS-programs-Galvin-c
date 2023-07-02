//continuous
#include <stdlib.h>
#include <stdio.h>
int main(){
    int diskSize,spaceLeft;
    printf("Enter size of disk:");
    scanf("%d",&diskSize);
    int disk[diskSize];
    for(int i=0;i<diskSize;i++){
        disk[i]=0;
    }
    spaceLeft=diskSize;
    int exit=1;
    while(exit){
        int fileSize=0;
        printf("Enter file size:");
        scanf("%d",&fileSize);
        if(spaceLeft<fileSize){
            printf("File too large");
        }
        else{
            int start=-1,end=-1,i,j;
            for(i=0;i<diskSize;i++){
                if(disk[i]==0){
                    int flag=1;
                    for(j=i;j!=i+fileSize-1 && j<diskSize;j++){
                        if(disk[j]==1){
                            flag=0;
                            break;
                        }
                    }
                    if(flag==0){
                        i+=j;
                    }
                    else{
                        //space found
                        start=i;
                        end=i+fileSize-1;
                        for(int k=start;k<end+1;k++){
                            disk[k]=1;
                        }
                        break;
                    }
                }
            }
            if(end!=-1){
                printf("File stored from %d to %d\n",start,end);
            }
            else{
                printf("Contiguous space unavailable!\n");
            }
        }
        printf("Enter more file(0/1):");
        scanf("%d",&exit);
    }
}