#include "Generator.h"

// Creates and starts process threads periodically
void createProcesses(int algorithm){

    // Seed the rand function
    srand(time(NULL));

    // Start the pID counter
    int pID = 0;
    int n;

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
        pthread_t threadProcess;

        // Create and join the thread
        if (pthread_create(&threadProcess, NULL, runProcess, threadArgs) != 0)
            perror("FAILED CREATE\n");
        if (pthread_join(threadProcess, NULL) != 0)
            perror("FAILED JOIN\n");

        pID++;
        n = (rand() % (60 - 30 + 1)) + 30;
        sleep(n);
    }
}

// Function that each thread executes
void *runProcess(void *threadArgs){
    
    // Unpack thread arguments
    struct Process *process = ((struct ThreadArgs *)threadArgs)->process;
    struct ProcessArray *pArray = ((struct ThreadArgs *)threadArgs)->processArray;
    struct MemoryArray *mArray = ((struct ThreadArgs *)threadArgs)->memoryArray;

    // Obtain both semaphores
    sem_t *processSem = sem_open(SEMPROCESS, 0, 0644, 0);
    sem_t *memorySem = sem_open(SEMMEMORY, 0, 0644, 0);

    sem_wait(processSem);
    insertProcess(pArray, process);
    // TO DO: update logs
    sem_post(processSem);

    /* TO DO:

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