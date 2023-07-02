#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void sortAscending(int arr[],int noElements){
    //insertion sort 
    for(int i=1;i<noElements;i++){
        int value=arr[i];
        int j;
        for(j=i-1;j>=0;j--){
            if(arr[j]>value){
                arr[j+1]=arr[j];
            }
            else{
                break;
            }
        }
        arr[j+1]=value;
    }
}
void sortDescending(int arr[],int noElements){
    //insertion sort 
    for(int i=1;i<noElements;i++){
        int value=arr[i];
        int j;
        for(j=i-1;j>=0;j--){
            if(arr[j]<value){
                arr[j+1]=arr[j];
            }
            else{
                break;
            }
        }
        arr[j+1]=value;
    }
}
void printArray(int arr[],int noElements){
    for(int i=0;i<noElements;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
int main(){
    int count=0;
    printf("Enter no of elements:");
    scanf("%d",&count);
    printf("Enter list elements:");
    int array[count];
    for(int i=0;i<count;i++){
        scanf("%d",&array[i]);
    }
    int f=fork();
    if(f<0){
        printf("Child process can't be created!\n");
    }
    else if(f==0){
        //child process
        printf("Child process:\n");
        sortAscending(array,count);
        printArray(array,count);
    }
    else{
        //parent process
        printf("Parent process:\n");
        sortDescending(array,count);
        printArray(array,count);
    }
}