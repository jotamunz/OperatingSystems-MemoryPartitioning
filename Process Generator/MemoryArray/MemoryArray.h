#ifndef MEMORYARRAY_h
#define MEMORYARRAY_h
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>

struct MemoryArray {
    int size;
    // semaphore
    int array[];
};

struct MemoryArray* newLocalMemoryArray(int size);
int newSharedMemoryArray(int size, char* keyFilePath);
bool firstFit(struct MemoryArray *memoryArray, int size, int pID);
void freeCells(struct MemoryArray *memoryArray, int pID);
void printMemoryArray(struct MemoryArray *memoryArray);
#endif