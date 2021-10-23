#ifndef MEMORYARRAY_h
#define MEMORYARRAY_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHSEGMENTID 0


struct MemoryArray {
    int size;
    // semaphore
    int array[]; // This member of the struct must be the last one defined
};

int newSharedMemoryArray (int size, char* keyFilePath);
int getSharedMemoryArrayId (char* keyFilePath);
struct MemoryArray* attachSharedMemoryArray (char* keyFilePath);
int detachSharedMemoryArray (struct MemoryArray* MemoryArrayp);
int removeSharedMemoryArray (int MemoryArrayId);
#endif