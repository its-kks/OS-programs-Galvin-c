#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
    char str[100];
    //setting complete array to ' '
    for(int i=0;i<100;i++){
        str[i]=' ';
    }
    printf("Enter a sentence:");
    fgets(str,sizeof(str),stdin);
    int noWords=0,noVowels=0;
    int p=fork();
    if(p<0){
        printf("Child process can't be created\n");
    }
    else if(p==0){
        //child process running
        for(int i=0;i<99;i++){
            if(str[i]==' ' && str[i+1]!=' '){
                noWords++;
            }
        }
        printf("Number of words %d\n",++noWords);
    }
    else{
        //parent process
        for(int i=0;i<100;i++){
            if(str[i]=='a' || str[i]=='e' || 
            str[i]=='i' || str[i]=='o' || str[i]=='u'){
                noVowels++;
            }
        }
        printf("Number of vowels %d\n",noVowels);
    }
}