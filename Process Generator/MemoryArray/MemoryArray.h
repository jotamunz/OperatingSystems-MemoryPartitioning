#ifndef MEMORYARRAY_h
#define MEMORYARRAY_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


struct MemoryArray {
    int size;
    int array[];
    // semaphore
};

struct MemoryArray* newLocalMemoryArray(int size);
int newSharedMemoryArray (int size, char* keyFilePath);
#endif