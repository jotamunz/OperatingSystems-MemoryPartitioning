#ifndef MEMORY_h
#define MEMORY_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct MNode {
    int size;
    bool free;
    int pID;
    struct MNode *next;
    struct MNode *prev;
};

struct Memory {
    struct MNode *first;
    // semaphore
};

struct Memory *newMemory(int);
void occupyNode(struct MNode**, struct MNode*, int, int);
void freeNode(struct MNode**, int);
void deleteNode(struct MNode **, struct MNode *);
void printMemory(struct MNode *);
#endif