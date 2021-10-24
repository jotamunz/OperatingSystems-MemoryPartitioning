#ifndef PROCESSARRAY_H
#define PROCESSARRAY_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../Process/Process.h"

struct ProcessArray {
    int size;
    struct Process array[];
    // semaphore
};


struct ProcessArray* newLocalProcessArray(int size);
int newSharedProcessArray (int size, char* keyFilePath);

#endif