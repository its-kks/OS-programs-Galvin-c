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
    int counter=0,indexP=0;
    //fill ram till ram not empty
    for(int i=0;i<noFrames;i++){
        ram[i].pageId=referenceString[indexP++];
        ram[i].useCounter=counter++;
    }
    while(indexP!=noPages){
        int value=search(ram,noFrames,referenceString[indexP]);
        if(value==-1){
            //page not found
            //find index to replace
            //array storing frame values 
            int tempArray[noFrames];
            for(int i=0;i<noFrames;i++){
                tempArray[i]=ram[i].pageId;
            }
            int indexF=-1;
            for(int i=indexP+1;i<noPages;i++){
                int page=referenceString[i];
                int searchIndex=search(ram,noFrames,page);
                if(searchIndex!=-1){
                    tempArray[searchIndex]=-1;//making -1 so don't count if duplicate present
                    indexF=searchIndex;
                }
            }
            //check if any page not found so it would not be made -1
            //it will be given priority
            for(int i=0;i<noFrames;i++){
                if(tempArray[i]!=-1){
                    indexF=i;
                    break;
                }
            }
            ram[indexF].pageId=referenceString[indexP];
            ram[indexF].useCounter=counter;
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
