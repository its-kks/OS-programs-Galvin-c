#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct resource
{
    int id;
    int noInstance;
};
typedef struct resource resource;
struct matrix
{
    int **mat;
};
typedef struct matrix matrix;
void addRequest(int noPro, int noRes, matrix *m)
{
    for (int j = 0; j < noPro; j++)
    {
        for (int i = 0; i < noRes; i++)
        {
            printf("Proc %d instance of Res %d:", j + 1, i + 1);
            scanf("%d", &m->mat[i][j]);
        }
    }
}
void allocate(int noPro, int noRes, matrix *m,resource resList[])
{
    int count[noRes];
    for(int i=0;i<noPro;i++){
        count[i]=resList[i].noInstance;
    }
    for (int j = 0; j < noPro; j++)
    {
        for (int i = 0; i < noRes; i++)
        {
            printf("Proc %d instance of Res %d:", j + 1, i + 1);
            int temp;
            scanf("%d", &temp);
            if(count[i]-temp>=0){
                m->mat[i][j]=temp;
                count[i]-=temp;
            }
            else{
                printf("Only %d instance left of R%d\n",count[i],i+1);
                printf("Please re-enter\n");
                i-=1;
            }
        }
    }
}
void printMatrix(matrix m,int noPro,int noRes){
    for(int i=0;i<noPro;i++){
        printf("   P%d",i+1);
    }
    printf("\n");
    for(int i=0;i<noRes;i++){
        printf("R%d ",i+1);
        for(int j=0;j<noPro;j++){
            printf("%d    ",m.mat[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    int noRes, noPro;
    printf("Enter no of process:");
    scanf("%d", &noPro);
    printf("Enter no of Resources(Unique):");
    scanf("%d", &noRes);
    matrix allocated, requested;
    allocated.mat = (int **)malloc(noRes * sizeof(int *));
    for (int i = 0; i < noRes; i++)
    {
        allocated.mat[i] = (int *)malloc(noPro * sizeof(int));
    }
    requested.mat = (int **)malloc(noRes * sizeof(int *));
    for (int i = 0; i < noRes; i++)
    {
        requested.mat[i] = (int *)malloc(noPro * sizeof(int));
    }
    resource resList[noRes];
    // taking values of resources
    for (int i = 0; i < noRes; i++)
    {
        resList[i].id = i + 1;
        printf("Enter no of instances of Res%d:", i + 1);
        scanf("%d", &resList[i].noInstance);
    }
    // allocated resources
    printf("Enter Resources Allocated:\n");
    allocate(noPro, noRes, &allocated,resList);
    // required resources
    printf("Enter Resources Requested:\n");
    addRequest(noPro, noRes, &requested);
    // printing values
    printf("Required instances:\n");
    printMatrix(requested, noPro, noRes);
    printf("Allocated instances:\n");
    printMatrix(allocated, noPro, noRes);
}
