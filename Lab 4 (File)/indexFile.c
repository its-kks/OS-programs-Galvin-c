#include <stdio.h>
#include <stdlib.h>
struct block {
  struct block *pointer[1000];
  int occupied;
};
typedef struct block block;
int main() {
  int sizeOfDisk, spaceLeft;
  printf("Enter size of Disk(in KBs):");
  // Disk size
  scanf("%d", &sizeOfDisk);
  spaceLeft = sizeOfDisk;
  block disk[sizeOfDisk];
  // making Disk empty
  for (int i = 0; i < sizeOfDisk; i++) {
    disk[i].occupied = 0;
  }
  // storing data
  int flag = 1;
  while (flag) {
    printf("Enter size of Data(in KBs):");
    int sizeData, i;
    scanf("%d", &sizeData);
    if (sizeData <= spaceLeft) {
      // search block to store indexFile
      spaceLeft -= sizeData;
      for (i = 0; i < sizeOfDisk; i++) {
        if (disk[i].occupied == 0) {
          break;
        }
      }
      int fileIndex = i, indexPointerArray = 0;
      // storing data
      for (i = 0; i < sizeOfDisk; i++) {
        if (disk[i].occupied == 0) {
          disk[i].occupied = 1;
          disk[fileIndex].pointer[indexPointerArray++] = &disk[i];
          sizeData--;
        }
        if (sizeData == 0) {
          break;
        }
      }
      printf("File index stored at block %d\n",fileIndex);
    } else {
      printf("Only %d KBs left\n", spaceLeft);
    }
    if(spaceLeft==0){
        printf("Disk full");
        flag=0;
    }
    printf("Enter more data(0/1):");
    scanf("%d",&flag);
  }
}