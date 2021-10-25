#include "Initiator.h"

void initializerMenu(int *memArrayId, int *processArrayId){
    char s[100];
    char trashCollector[5];
    fgets(trashCollector, sizeof(trashCollector), stdin);
    int requestedCells;
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃                        INITIALIZER PROGRAM                     ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\n\n");
    printf("Please input the amount of cells to request for the simulation: ");
    fgets(s, sizeof(s), stdin);
    requestedCells = atoi(s);
    while (requestedCells < 1){
        printf("Please input a natural number of cells to request: ");
        fgets(s, sizeof(s), stdin);
        requestedCells = atoi(s);
    }
    if (((*memArrayId) = newSharedMemoryArray(requestedCells, KEYFILEPATH)) > -1) {
        printf("\n%d memory simulation cells have been allocated in shared memory with the Id %d\n", requestedCells, (*memArrayId));
    } else {return;}
    if (((*processArrayId) = newSharedProcessArray(PROCESSARRAYSIZE, KEYFILEPATH)) > -1) {
        printf("The shared process array has also been allocated in shared memory with the Id %d\n", (*processArrayId));
    } else {return;}
    return;
}