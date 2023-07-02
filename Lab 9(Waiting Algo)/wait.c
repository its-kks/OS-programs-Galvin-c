#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct resource {
  int id;
  int noInstance;
};
typedef struct resource resource;

struct matrix {
  int **mat;
};
typedef struct matrix matrix;

void addRequest(int noRes, int noPro, matrix *m) {
  for (int i = 0; i < noPro; i++) {
    for (int j = 0; j < noRes; j++) {
      printf("Res %d instance of Proc %d:", j + 1, i + 1);
      scanf("%d", &m->mat[i][j]);
    }
  }
}

void allocate(int noRes, int noPro, matrix *m, resource resList[]) {
  for (int i = 0; i < noPro; i++) {
    for (int j = 0; j < noRes; j++) {
      printf("Res %d instance of Proc %d:", j + 1, i + 1);
      int temp;
      scanf("%d", &temp);
      if (resList[j].noInstance - temp >= 0) {
        m->mat[i][j] = temp;
        resList[j].noInstance -= temp;
      } else {
        printf("Only %d instance(s) left of Res %d\n", resList[j].noInstance,
               j + 1);
        printf("Please re-enter\n");
        j -= 1;
      }
    }
  }
}

// void printResList(int noRes,resource resList[]){
//     printf("%s","List");
//     for(int i=0;i<noRes;i++){
//         printf("%d ",resList->noInstance);
//     }
//     printf("\n");
// }

void printGraph(int **m, int noPro) {
  printf("   ");
  for (int j = 0; j < noPro; j++) {
    printf("P%d   ", j+1);
  }
  printf("\n");
  for (int i = 0; i < noPro; i++) {
    printf("P%d ", i+1);
    for (int j = 0; j < noPro; j++) {
      printf("%4d ", m[i][j]);
    }
    printf("\n");
  }
}

void printMatrix(matrix m, int noPro, int noRes) {
  for (int j = 0; j < noRes; j++) {
    printf("Res%d ", j+1);
  }
  printf("\n");
  for (int i = 0; i < noPro; i++) {
    printf("P%d ", i+1);
    for (int j = 0; j < noRes; j++) {
      printf("%4d ", m.mat[i][j]);
    }
    printf("\n");
  }
}

int **makeWaitForGraph(int noRes, int noPro, matrix requested, matrix allocated,
                       resource resList[]) {
  int **waitForGraph=(int **)malloc(noPro * sizeof(int *));
  for (int i = 0; i < noPro; i++) {
    waitForGraph[i] = (int *)malloc(noPro * sizeof(int));
  }
  for(int i=0;i<noPro;i++){
    for(int j=0;j<noPro;j++){
        if(i==j){
            continue;
        }
        else{
            int flag=0;
            for(int k=0;k<noRes;k++){
                if(allocated.mat[j][k]!=0 && requested.mat[i][k]!=0){
                    flag=1;
                }
            }
            if(flag==1){
                waitForGraph[i][j]=1;
            }
        }
    }
  }
  return waitForGraph;
}

void printCyclesUtil(int **waitForGraph, int currNode, int startNode, int *visited, int *stack, int top, int noPro) {
  visited[currNode] = 1;
  stack[top] = currNode;

  // For each neighbor of currNode
  for (int i = 0; i < noPro; i++) {
    if (waitForGraph[currNode][i]) {
      // If the neighbor is the startNode, we have found a cycle
      if (i == startNode) {
        printf("Cycle found: ");
        for (int j = top; j >= 0; j--) {
          printf("%d ", stack[j] + 1);
          if (stack[j] == i) break;
        }
        printf("\n");
      }
      // If the neighbor has not been visited, recursively search it
      else if (!visited[i]) {
        printCyclesUtil(waitForGraph, i, startNode, visited, stack, top+1, noPro);
      }
    }
  }

  // Remove currNode from the stack
  visited[currNode] = 0;
  stack[top] = -1;
}

void printLoops(int **waitForGraph, int noPro) {
  int visited[noPro], stack[noPro];
  memset(visited, 0, sizeof(visited));
  memset(stack, -1, sizeof(stack));

  for (int i = 0; i < noPro; i++) {
    printCyclesUtil(waitForGraph, i, i, visited, stack, 0, noPro);
  }
}


int main() {
  int noPro, noRes;
  printf("Enter number of processes: ");
  scanf("%d", &noPro);
  printf("Enter number of resources (unique): ");
  scanf("%d", &noRes);
  matrix allocated, requested;
  allocated.mat = (int **)malloc(noPro * sizeof(int *));
  for (int i = 0; i < noPro; i++) {
    allocated.mat[i] = (int *)malloc(noRes * sizeof(int));
  }
  requested.mat = (int **)malloc(noPro * sizeof(int *));
  for (int i = 0; i < noPro; i++) {
    requested.mat[i] = (int *)malloc(noRes * sizeof(int));
  }

  resource resList[noRes];
  // taking values of resources
  for (int i = 0; i < noRes; i++) {
    resList[i].id = i + 1;
    printf("Enter number of instances of Res%d: ", i + 1);
    scanf("%d", &resList[i].noInstance);
  }
  // allocated resources
  printf("Enter resources allocated:\n");
  allocate(noRes, noPro, &allocated, resList);
  // required resources
  printf("Enter resources requested:\n");
  addRequest(noRes, noPro, &requested);
  printf("Requested:\n");
  printMatrix(requested, noPro, noRes);
  printf("Allocated:\n");
  printMatrix(allocated, noPro, noRes);
  // Making wait for graph
  printf("Wait for graph:\n");
  int **waitForGraph=makeWaitForGraph(noRes, noPro, requested, allocated, resList);
  printGraph(waitForGraph, noPro);
  printf("Loops in the Graph:\n");
  printLoops(waitForGraph,noPro);
  return 0;
}