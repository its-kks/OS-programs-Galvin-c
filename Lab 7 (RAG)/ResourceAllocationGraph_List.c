#include <stdio.h>
#include <stdlib.h>

struct resource {
    int id;
    int noInstance;
    struct resource *next;
};
typedef struct resource resource;

void addReq(int noPro, int noRes, resource* m[]) {
    for (int j = 0; j < noPro; j++) {
        int num = noRes + 1;
        printf("Enter no of resources requested by P%d:", j + 1);
        scanf("%d", &num);
        resource *traverse = m[j];
        for (int i = 0; i < num; i++) {
            int id;
            printf("Enter Res id:");
            scanf("%d", &id);
            int temp;
            printf("No of R%d's instances requested P%d:", id, j + 1);
            scanf("%d", &temp);
            resource *newResource = (resource *)malloc(sizeof(resource));
            if (newResource == NULL) {
                printf("Error: failed to allocate memory\n");
                exit(1);
            }
            newResource->id = id;
            newResource->noInstance = temp;
            newResource->next = NULL;
            if (traverse == NULL) {
                m[j] = newResource;
                traverse = m[j];
            }
            else {
                traverse->next = newResource;
                traverse = traverse->next;
            }
        }
    }
}

void allocate(int noPro, int noRes, resource* m[], int resList[]) {
    int count[noRes];
    for (int i = 0; i < noPro; i++) {
        count[i] = resList[i];
    }
    for (int j = 0; j < noPro; j++) {
        int num = noRes + 1;
        while (num > noRes) {
            printf("Enter no of resource allocated to P%d:", j + 1);
            scanf("%d", &num);
            if (num > noRes) {
                printf("Only %d resources exist!\n", noRes);
            }
        }
        resource *traverse = m[j];
        for (int i = 0; i < num; i++) {
            int id;
            printf("Enter Res id:");
            scanf("%d", &id);
            if (id > noRes) {
                printf("Id does not exist!\nPlease re-enter\n");
                i -= 1;
            }
            else {
                int temp;
                printf("No of R%d's instances allocated to P%d:", id, j + 1);
                scanf("%d", &temp);
                if (count[id - 1] - temp >= 0) {
                    // allocate
                    resource *newResource = (resource *)malloc(sizeof(resource));
                    if (newResource == NULL) {
                        printf("Error: failed to allocate memory\n");
                        exit(1);
                    }
                    newResource->id = id;
                    newResource->noInstance = temp;
                    newResource->next = NULL;
                    //yha se
                    if (traverse == NULL) {
                        m[j] = newResource;
                        traverse = m[j];
                    }
                    else {
                        traverse->next = newResource;
                        traverse = traverse->next;
                    }
                    count[id - 1] -= temp;
                    //yha tk
                }
                else {
                    // error
                    printf("Only %d instances left of R%d\nPlease re-enter\n", count[id - 1], id);
                    i -= 1;
                }
            }
        }
    }
}

void printList(resource *m[],int noPro){
    for(int i=0;i<noPro;i++){
        printf("P%d:",i+1);
        resource *traverse=m[i];
        while(traverse!=NULL){
            printf("(R%d,I%d) ",traverse->id,traverse->noInstance);
            traverse=traverse->next;
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
    int resList[noRes];
    // taking values of resources
    for (int i = 0; i < noRes; i++)
    {
        printf("Enter no of instances of Res%d:", i + 1);
        scanf("%d", &resList[i]);
    }
    resource* requested[noPro];
    resource* allocated[noPro];
    for(int i=0;i<noPro;i++){
        requested[i]=NULL;
    }
    for(int i=0;i<noRes;i++){
        allocated[i]=NULL;
    }
    printf("Enter Resources Allocated:\n");
    allocate(noPro,noRes,allocated,resList);
    printf("Enter Resources Requested:\n");
    addReq(noPro,noRes,requested);
    printf("Allocations:\n");
    printList(allocated,noPro);
    printf("Rquests:\n");
    printList(requested,noPro);
}
