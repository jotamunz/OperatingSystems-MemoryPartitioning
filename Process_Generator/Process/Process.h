#ifndef PROCESS_H
#define PROCESS_H
#include <stdio.h>
#include <stdlib.h>

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

struct Process *newProcess(int, int);
void runProcess();
void printProcess(struct Process *);
#endif