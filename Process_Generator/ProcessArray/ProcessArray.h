#ifndef PROCESSARRAY_H
#define PROCESSARRAY_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Process/Process.h"

struct ProcessArray {
    int size;
    // semaphore
    struct Process array[]; // This member of the struct must be the last one defined
};

struct ProcessArray* newLocalProcessArray(int size);
int newSharedProcessArray(int size, char* keyFilePath);
void insertProcess(struct ProcessArray *processArray, struct Process *process);
void deleteProcess(struct ProcessArray *processArray, int pID);
void printProcessArray(struct ProcessArray *processArray);
#endif