#include "Process.h"

// Constructor for a process with pID = -1
struct Process *newLocalDummyProcess(){
    struct Process *process = malloc(sizeof(struct Process));
    process->pID = -1;
    return process;
}

// Constructor for a process
struct Process *newLocalProcess(int pID, int algorithm){
    struct Process *process = malloc(sizeof(struct Process));
    process->pID = pID;
    process->algorithm = algorithm;
    process->status = 0;
    
    // Random attributes
    process->size = (rand() % (10 - 1 + 1)) + 1;
    process->duration = (rand() % (60 - 20 + 1)) + 20;
    return process;
}

// Bundles all necesary parameters for the run function
struct ThreadArgs *newLocalThreadArgs(struct Process *process, struct ProcessArray *processArray, struct MemoryArray *memoryArray){
    struct ThreadArgs *args = malloc(sizeof(struct ThreadArgs));
    args->process = process;
    args->processArray = processArray;
    args->memoryArray = memoryArray;
    return args;
}

// Creates and starts process threads periodically
void createProcesses(int algorithm){

    // Seed the rand function
    srand(time(NULL));

    // Start the pID counter
    int pID = 0;

    // TO DO: Obtain a pointer to both structres in shared memory

    while(1){
        // Create a new local process
        struct Process *process = newLocalProcess(pID, algorithm);

        // TO DO: Create ThreadArgs struct and run thread

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

void printProcess(struct Process process){
    printf("ID: %d\n", process.pID);
    printf("Size: %d\n", process.size);
    printf("Algorithm: %d\n", process.algorithm);
    printf("Duration: %d\n", process.duration);
    printf("Status: %d\n\n", process.status);
    return;
}