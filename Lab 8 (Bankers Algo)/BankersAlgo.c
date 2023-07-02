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

void requestResourceAlgorithm(matrix allocated, matrix requested,
                              resource resList[], int noPro, int noRes) {
  for (int i = 0; i < noPro; i++) {
    for (int j = 0; j < noRes; j++) {
      if (requested.mat[i][j] <= resList[j].noInstance) {
        allocated.mat[i][j] += requested.mat[i][j];
        resList[j].noInstance -= requested.mat[i][j];
        requested.mat[i][j] = 0;
      }
    }
  }
}
void printResList(int noRes,resource resList[]){
    printf("%s","List");
    for(int i=0;i<noRes;i++){
        printf("%d ",resList->noInstance);
    }
    printf("\n");
}
int safetyAlgorithm(matrix allocated, matrix requested, resource resList[],
                    int noPro, int noRes) {
  // extracting resources from completed processes
  resource *work = resList;
  int finish[noPro];
  for (int i = 0; i < noPro; i++) {
    finish[i] = 0;
  }
  int continueLoop = 1;
  while (continueLoop) {
    continueLoop = 0;
    for (int i = 0; i < noPro; i++) {
      if (finish[i] != 1) {
        int retakeAllocated = 1;
        for (int j = 0; j < noRes; j++) {
          if (requested.mat[i][j] > work[j].noInstance) {
            retakeAllocated = 0;
          }
        }
        if (retakeAllocated == 1) {
          finish[i] = 1;
          // taking resources back
          for (int j = 0; j < noRes; j++) {
            work[j].noInstance += allocated.mat[i][j];
          }
          continueLoop = 1;
        }
      }
    }
  }
  for (int i = 0; i < noPro; i++) {
    if (finish[i] == 0) {
      return 0;
    }
  }
  return 1;
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

  // Running Bankers Algo
  requestResourceAlgorithm(allocated, requested, resList, noPro, noRes);
  printMatrix(allocated, noPro,noRes);
  printMatrix(requested, noPro,noRes);
  if (safetyAlgorithm(allocated, requested, resList, noPro, noRes)) {
    printf("The Algorithm is safe!");
  } else {
    printf("Deadlock occured:Algorithm is unsafe!");
  }
  return 0;
}