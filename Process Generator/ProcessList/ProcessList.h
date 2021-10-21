#ifndef PROCESSLIST_H
#define PROCESSLIST_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Process/Process.h"

struct PNode {
    struct Process *process;
    struct PNode *next;
};

struct ProcessList {
    struct PNode *first;
    // semaphore
};

struct ProcessList *newProcessList();
void insertProcess(struct PNode **, struct Process *);
void deleteProcess(struct PNode **, int);
void printProcessList(struct PNode *);
#endif