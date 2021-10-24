#include "Process.h"

// Constructor for a process
struct Process *newProcess(int pID, int algorithm){
    struct Process *process = malloc(sizeof(struct Process));
    process->pID = pID;
    process->algorithm = algorithm;
    process->status = 0;
    
    // Random attributes
    process->size = (rand() % (10 - 1 + 1)) + 1;
    process->duration = (rand() % (60 - 20 + 1)) + 20;
}

void runProcess(){
    // NEEDS ACCESS TO ALL SHARED STRUCTURES
    // THESE CAN BE PASSED AS PARAMS BY THE CREATOR IN A BUNDLED STRUCT

    /*
    lock process list semaphore
    enter process list
    update logs
    unlock process list semaphore

    lock memory semaphore
    lock process list semaphore
    update staus = 1 and logs
    unlock process list semaphore
    run algorithm
    lock process list semaphore
    update status = 2 and logs
    unlock process list semaphore
    unlock memory semaphore

    sleep

    lock process list semaphore
    update status = 3 and logs
    unlock process list semaphore

    lock memory semaphore
    lock process list semaphore
    update staus = 4 and logs
    unlock process list semaphore
    free memory
    lock process list semaphore
    exit process list
    update logs
    unlock process list semaphore
    unlock memory semaphore    
    */

}

void printProcess(struct Process *process){
    printf("ID: %d\n", process->pID);
    printf("Size: %d\n", process->size);
    printf("Duration: %d\n", process->duration);
    printf("Status: %d\n\n", process->status);
}