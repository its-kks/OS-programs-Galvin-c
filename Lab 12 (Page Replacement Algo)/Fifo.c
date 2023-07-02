#include <stdio.h>
struct frame{
    int pageId;
    int useCounter;
};
typedef struct frame frame;
int search(frame ram[],int noFrames,int value){
    int i;
    for(i=0;i<noFrames;i++){
        if(ram[i].pageId==value){
            return i;
        }
    }
    return -1;
}
void enterPages(frame ram[],int noFrames,int referenceString[],int noPages){
    int indexF=0,counter=0,indexP=0;
    while(indexP!=noPages){
        int value=search(ram,noFrames,referenceString[indexP]);
        if(value==-1){
            //page not found
            ram[indexF%noFrames].pageId=referenceString[indexP];
            ram[indexF%noFrames].useCounter=counter;
            indexF++;
        }
        else{
            ram[value].useCounter=counter;
            printf("Hit!\n");
        }
        counter++;
        indexP++;
    }
}
int main(){
    int noFrames,noPages;
    printf("Enter no of frames in memory:");
    scanf("%d",&noFrames);
    printf("Enter len of referenceString:");
    scanf("%d",&noPages);
    printf("Enter page nos:");
    int referenceString[noPages];
    for(int i=0;i<noPages;i++){
        scanf("%d",&referenceString[i]);
    }
    frame ram[noFrames];
    for(int i=0;i<noFrames;i++){
        ram[i].pageId=-1;
    }
    enterPages(ram,noFrames,referenceString,noPages);
}
