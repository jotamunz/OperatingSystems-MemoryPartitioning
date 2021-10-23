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
    int array[];
    // semaphore
};

struct MemoryArray* newLocalMemoryArray(int size);
int newMemoryArray (int size, char* keyFilePath);
int getMemoryArrayId (char* keyFilePath);
struct MemoryArray* attachMemoryArray (char* keyFilePath);
int dettachMemoryArray (struct MemoryArray* MemoryArrayp);
int removeMemoryArray (int MemoryArrayId);
#endif