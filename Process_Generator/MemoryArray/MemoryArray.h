#ifndef MEMORYARRAY_h
#define MEMORYARRAY_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define MEMARRAYSHAREDID 0
#define SEMMEMORY "Gallote"

// Check if there are memory leaks: ipcs -m

struct MemoryArray {
    int size;
    pid_t programsId [3];
    // semaphore
    int array[]; // This member of the struct must be the last one defined
};

int newSharedMemoryArray (int size, char* keyFilePath);
int getSharedMemoryArrayId (char* keyFilePath);
struct MemoryArray* attachSharedMemoryArray (int shmid);
int detachSharedMemoryArray (struct MemoryArray* MemoryArrayp);
int removeSharedMemoryArray (int MemoryArrayId);

struct MemoryArray *newLocalMemoryArray(int size);

bool firstFit(struct MemoryArray *memoryArray, int size, int pID);
bool bestFit(struct MemoryArray *memoryArray, int size, int pID);
bool worstFit(struct MemoryArray *memoryArray, int size, int pID);

void freeCells(struct MemoryArray *memoryArray, int pID);
void insertProcessIntoMemory(struct MemoryArray *memoryArray, int pID, int size, int startIndex);

void printMemoryArray(struct MemoryArray *memoryArray);
#endif