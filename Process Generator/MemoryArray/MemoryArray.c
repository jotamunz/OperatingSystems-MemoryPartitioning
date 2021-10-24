#include "MemoryArray.h"

int newSharedMemoryArray(int size, char *keyFilePath)
{
    int shmid;
    key_t key;

    key = ftok("SharedKey.txt", 0);
    if ((shmid = shmget(key, sizeof(struct MemoryArray) + size * sizeof(int), IPC_CREAT | 0666)) < 0)
    {
        printf("No ha sido posible alocar la memoria compartida");
        return -1;
    }
    return shmid;
}

// Creates an array based on size full of -1
struct MemoryArray *newLocalMemoryArray(int size)
{
    struct MemoryArray *mArray = malloc(sizeof(struct MemoryArray) + sizeof(int) * size);
    mArray->size = size;
    for (int i = 0; i < size; i++)
    {
        mArray->array[i] = -1;
    }
    return mArray;
}

// Inserts the pID into the memoryArray starting at startIndex
void insertProcessIntoMemory(struct MemoryArray *memoryArray, int pID, int size, int startIndex)
{
    for (int i = 0; i < size; i++)
    {
        memoryArray->array[startIndex + i] = pID;
    }
}

// Inserts the given ID into the first block of cells >= size and returns success status
bool firstFit(struct MemoryArray *memoryArray, int size, int pID)
{
    for (int i = 0; i < memoryArray->size; i++)
    {
        if (memoryArray->array[i] == -1)
        {
            int freeSpace = 0;
            for (int j = i; j < memoryArray->size && memoryArray->array[j] == -1; j++)
            {
                freeSpace++;
                if (size <= freeSpace)
                {
                    insertProcessIntoMemory(memoryArray, pID, size, i);
                    return true;
                }
            }
            i += (freeSpace - 1);
        }
    }
    return false;
}

// Inserts the given ID into the smallest posible block of cells
bool bestFit(struct MemoryArray *memoryArray, int size, int pID)
{
    int bestFitIndex = -1;
    int bestMemorySize = 0;

    // Search for smallest posible memory space
    for (int i = 0; i < memoryArray->size; i++)
    {
        if (memoryArray->array[i] == -1)
        {
            int currentBlockSize = 0;
            // Calculate current block size
            for (int j = i; j < memoryArray->size; j++)
            {
                if (memoryArray->array[j] != -1)
                    break;
                currentBlockSize++;
            }
            if (currentBlockSize >= size && (bestFitIndex == -1 || bestMemorySize > currentBlockSize))
            {
                bestFitIndex = i;
                bestMemorySize = currentBlockSize;
            }
            i += currentBlockSize;
        }
    }
    if (bestFitIndex == -1)
        return false;

    insertProcessIntoMemory(memoryArray, pID, size, bestFitIndex);
    return true;
}

bool worstFit(struct MemoryArray *memoryArray, int size, int pID)
{
    int worstFitIndex = -1;
    int worstMemorySize = 0;
    // Search the biggest possible memory space
    for (int i = 0; i < memoryArray->size; i++)
    {
        if (memoryArray->array[i] == -1)
        {
            int currentBlockSize = 0;
            // Calculate current block size
            for (int j = i; j < memoryArray->size; j++)
            {
                if (memoryArray->array[j] != -1)
                    break;
                currentBlockSize++;
            }
            if (currentBlockSize >= size && (worstFitIndex == -1 || worstMemorySize < currentBlockSize))
            {
                worstFitIndex = i;
                worstMemorySize = currentBlockSize;
            }
            i += currentBlockSize;
        }
    }
    if (worstFitIndex == -1)
        return false;

    insertProcessIntoMemory(memoryArray, pID, size, worstFitIndex);
    return true;
}

// Changes the ID = -1 for the cells with the given ID
void freeCells(struct MemoryArray *memoryArray, int pID)
{
    for (int i = 0; i < memoryArray->size; i++)
    {
        if (memoryArray->array[i] == pID)
        {
            memoryArray->array[i] = -1;
        }
    }
    return;
}

// Prints the memory array
void printMemoryArray(struct MemoryArray *memoryArray)
{
    for (int i = 0; i < memoryArray->size; i++)
    {
        printf("%d\n", memoryArray->array[i]);
    }
    printf("\n");
    return;
}