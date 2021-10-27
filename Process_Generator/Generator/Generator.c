#include "Generator.h"

// Creates and starts process threads periodically
void createProcesses(int algorithm)
{
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

    // Add id for finalizer
    pArray->programIds[1] = getpid();

    while (true)
    {
        // TEMP
        if (pID >= 3)
            continue;

        // Create a new local process and bundle params
        struct Process *process = newLocalProcess(pID, algorithm);
        struct ThreadArgs *threadArgs = newLocalThreadArgs(process, pArray, mArray);
        pthread_t threadProcess;

        // Create and run the thread
        if (pthread_create(&threadProcess, NULL, runProcess, threadArgs) != 0)
            perror("Failed to create thread\n");

        pID++;

        // TEMP
        //n = (rand() % (60 - 30 + 1)) + 30;
        n = 15;
        sleep(n);
    }
}

// Function that each thread executes
void *runProcess(void *threadArgs)
{
    // Unpack thread arguments
    struct Process *process = ((struct ThreadArgs *)threadArgs)->process;
    struct ProcessArray *pArray = ((struct ThreadArgs *)threadArgs)->processArray;
    struct MemoryArray *mArray = ((struct ThreadArgs *)threadArgs)->memoryArray;

    // Obtain both semaphores
    sem_t *processSem = sem_open(SEMPROCESS, 0, 0644, 0);
    sem_t *memorySem = sem_open(SEMMEMORY, 0, 0644, 0);

    // Lock process list and insert the process into it
    sem_wait(processSem);
    insertProcess(pArray, process);
    appendLog(0, process->pID, process->size, process->duration);
    sem_post(processSem);

    // Lock memory and insert into it
    sem_wait(memorySem);

    // Lock process list and update status
    sem_wait(processSem);
    process->status = 1;
    updateProcessStatus(pArray, process->pID, 1);
    appendLog(1, process->pID, process->size, process->duration);
    sem_post(processSem);

    // Run search and fit algorithm
    bool success = false;
    if (process->algorithm == 0)
        success = firstFit(mArray, process->size, process->pID);
    else if (process->algorithm == 1)
        success = bestFit(mArray, process->size, process->pID);
    else if (process->algorithm == 2)
        success = worstFit(mArray, process->size, process->pID);

    // Lock process list
    sem_wait(processSem);
    if (success)
    {
        // Update status
        process->status = 2;
        updateProcessStatus(pArray, process->pID, 2);
        appendLog(2, process->pID, process->size, process->duration);
    }
    else
    {
        // Exit the process list
        deleteProcess(pArray, process->pID);
        appendLog(6, process->pID, process->size, process->duration);
        // Kill thread
        sem_post(processSem);
        sem_post(memorySem);
        return NULL;
    }
    sem_post(processSem);
    sem_post(memorySem);

    // Run the process
    sleep(process->duration);

    // Lock process list and update status
    sem_wait(processSem);
    process->status = 3;
    updateProcessStatus(pArray, process->pID, 3);
    appendLog(3, process->pID, process->size, process->duration);
    sem_post(processSem);

    // Lock memory and exit it
    sem_wait(memorySem);

    // Lock process list and update status
    sem_wait(processSem);
    process->status = 4;
    updateProcessStatus(pArray, process->pID, 4);
    appendLog(4, process->pID, process->size, process->duration);
    sem_post(processSem);

    // Free memory cells
    freeCells(mArray, process->pID);

    // Lock process list and exit it
    sem_wait(processSem);
    deleteProcess(pArray, process->pID);
    appendLog(5, process->pID, process->size, process->duration);
    sem_post(processSem);
    sem_post(memorySem);
    return NULL;
}