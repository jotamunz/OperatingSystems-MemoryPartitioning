#include "Initiator.h"

void initializerMenu(int *memArrayId, int *processArrayId)
{
    system("clear");
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
    while (requestedCells < 1)
    {
        printf("Please input a natural number of cells to request: ");
        fgets(s, sizeof(s), stdin);
        requestedCells = atoi(s);
    }
    if (((*memArrayId) = newSharedMemoryArray(requestedCells, KEYFILEPATH)) > -1)
    {
        printf("\n• %d memory simulation cells have been allocated in shared memory with the Id %d\n", requestedCells, (*memArrayId));
    }
    else
    {
        return;
    }
    if (((*processArrayId) = newSharedProcessArray(PROCESSARRAYSIZE, KEYFILEPATH)) > -1)
    {
        printf("• The shared process array has also been allocated in shared memory with the Id %d\n", (*processArrayId));
    }
    else
    {
        return;
    }
    if (openSemaphore(SEMMEMORY, 1) > -1)
    {
        printf("• The memory array sempahore has been created\n");
    }
    else
    {
        return;
    }
    if (openSemaphore(SEMPROCESS, 1) > -1)
    {
        printf("• The process list sempahore has been created\n");
    }
    else
    {
        return;
    }
    if (createLog(requestedCells) > -1)
    {
        printf("• The log file has been created\n\n");
    }
    else
    {
        return;
    }
    printf("Terminating program...\n\n");
    return;
}

int openSemaphore(const char *name, int count)
{
    sem_t *sem;
    if ((sem = sem_open(name, O_CREAT | O_EXCL, 0644, count)) < 0)
    {
        printf("Could not open %s semaphore\n", name);
        return -1;
    }
    sem_close(sem);
    return 0;
}
