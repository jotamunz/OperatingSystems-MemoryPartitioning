#include "Generator.h"

// Creates and starts process threads periodically
void createProcesses(int algorithm){

    // Seed the rand function
    srand(time(NULL));

    // Start the pID counter
    int pID = 0;

    // Obtain a pointer to both structres in shared memory
    int key = getSharedProcessArrayId(KEYFILEPATH);
    struct ProcessArray *pArray = attachSharedProcessArray(key);
    key = getSharedMemoryArrayId(KEYFILEPATH);
    struct MemoryArray *mArray = attachSharedMemoryArray(key);

    // Validate shared memory access
    if (pArray == NULL || mArray == NULL)
        return;

    while(1){
        // Create a new local process and bundle params
        struct Process *process = newLocalProcess(pID, algorithm);
        struct ThreadArgs *threadArgs = newLocalThreadArgs(process, pArray, mArray);

        // TO DO: Create and run thread (pass threadArgs and runProcess())

        pID++;
        int n = (rand() % (60 - 30 + 1)) + 30;
        sleep(n);
    }
}

// Function that each thread executes
void *runProcess(void *threadArgs){
    struct Process *process = ((struct ThreadArgs *)threadArgs)->process;
    struct ProcessArray *pArray = ((struct ThreadArgs *)threadArgs)->processArray;
    struct MemoryArray *mArray = ((struct ThreadArgs *)threadArgs)->memoryArray;

    /* TO DO:
    lock process list semaphore
    enter process list
    update logs
    unlock process list semaphore

    lock memory semaphore
    lock process list semaphore
    update staus = 1 and update logs
    unlock process list semaphore
    run algorithm
    lock process list semaphore
    if success: update status = 2 and update logs
    if fail: exit process list and update logs
    unlock process list semaphore
    unlock memory semaphore

    sleep

    lock process list semaphore
    update status = 3 and update logs
    unlock process list semaphore

    lock memory semaphore
    lock process list semaphore
    update staus = 4 and update logs
    unlock process list semaphore
    free memory
    lock process list semaphore
    exit process list
    update logs
    unlock process list semaphore
    unlock memory semaphore    
    */
}