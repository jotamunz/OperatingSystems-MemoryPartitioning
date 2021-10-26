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

void printProcess(struct Process process){
    printf("ID: %d\n", process.pID);
    printf("Size: %d\n", process.size);
    printf("Algorithm: %d\n", process.algorithm);
    printf("Duration: %d\n", process.duration);
    printf("Status: %d\n\n", process.status);
    return;
}