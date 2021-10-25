#ifndef PROCESS_H
#define PROCESS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LOGPATH ""

struct Process {
    int pID;
    int size;
    int duration;
    int algorithm; // 0 = First Fit, 1 = Best Fit, 2 = Worst Fit
    int status;
    /*
    0 = Blocked waiting to enter memory
    1 = Critical section running algorithm
    2 = Running process (sleeping)
    3 = Blocked waiting to exit memory
    4 = Critical section freeing memory
    */
};

struct ThreadArgs {
    struct Process *process;
    struct ProcessArray *processArray;
    struct MemoryArray *memoryArray;
};

struct Process *newLocalProcess(int pID, int algorithm);
struct Process *newLocalDummyProcess();
struct ThreadArgs *newLocalThreadArgs(struct Process *process, struct ProcessArray *processArray, struct MemoryArray *memoryArray);
void printProcess(struct Process process);
#endif