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
                    for (int x = 0; x < size; x++)
                    {
                        memoryArray->array[i + x] = pID;
                    }
                    return true;
                }
            }
            i += (freeSpace - 1);
        }
    }
    return false;
}

bool bestFit(struct MemoryArray *memoryArray, int size, int pID)
{
    return false;
}

bool worstFit(struct MemoryArray *memoryArray, int size, int pID)
{
    return false;
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