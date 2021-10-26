#ifndef PROCESSARRAY_H
#define PROCESSARRAY_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "../Process/Process.h"
#define KEYFILEPATH "../Shared key/SharedKey"
#define PROCESSARRAYSHAREDID 1
#define SEMPROCESS "Gallito"

struct ProcessArray {
    int size;
    struct Process array[]; // This member of the struct must be the last one defined
};

int newSharedProcessArray (int size, char* keyFilePath);
int getSharedProcessArrayId (char* keyFilePath);
struct ProcessArray* attachSharedProcessArray (int shmid);
int detachSharedProcessArray (struct ProcessArray* MemoryArrayp);
int removeSharedProcessArray (int MemoryArrayId);

struct ProcessArray* newLocalProcessArray(int size);
void insertProcess(struct ProcessArray *processArray, struct Process *process);
void deleteProcess(struct ProcessArray *processArray, int pID);
void printProcessArray(struct ProcessArray *processArray);
#endif