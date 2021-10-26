#include "MemoryArray.h"

/// Creates a new shared memory array of given size, and returns its Id
int newSharedMemoryArray (int size, char* keyFilePath){
    int shmid;
    struct MemoryArray* memoryArrayp; 
    key_t key; 
    if ((key = ftok(keyFilePath, MEMARRAYSHAREDID)) < 0) {
        printf ("\nError: No se ha logrado obtener la llave de la memoria compartida\n");
        return -1;
    }
    if ((shmid = shmget(key, sizeof(struct MemoryArray) + size * sizeof(int), IPC_CREAT | 0666)) < 0) {
        printf ("\nError: No ha sido posible reservar la memoria compartida\n");
        return -1;
    }
    memoryArrayp = attachSharedMemoryArray(shmid);
    for (int i = 0; i < size; i++)
    {
        memoryArrayp->array[i] = -1;
    }
    memoryArrayp->size = size;
    detachSharedMemoryArray(memoryArrayp);
    return shmid;
}

// Gets the Id of an already created shared memory array, given its key filepath
int getSharedMemoryArrayId (char* keyFilePath) {
    int shmid;
    key_t key; 
    if ((key = ftok(keyFilePath, MEMARRAYSHAREDID)) < 0) {
        printf ("\nError: No se ha logrado obtener la llave de la memoria compartida\n");
        return -1;
    }
    if ((shmid = shmget(key, 0, 0666)) < 0) {
        printf ("\nNo ha sido posible obtener el Id de la memoria compartida\n");
        return -1;
    }
    return shmid;
}

// Returns a pointer to an already created shared memory array, given its key filepath
struct MemoryArray* attachSharedMemoryArray (int shmid) {
    struct MemoryArray* MemoryArrayp;
    if ((MemoryArrayp = shmat(shmid, NULL, 0)) == (struct MemoryArray*) -1) {
        printf ("\nNo ha sido posible adjuntar la memoria compartida\n");
        return NULL;
    }
    return MemoryArrayp;
}

// Detach a pointer to an already created shared memory array, given its key filepath
int detachSharedMemoryArray (struct MemoryArray* MemoryArrayp) {
    if (shmdt(MemoryArrayp) != 0){
        printf ("\nNo ha sido posible desadjuntar la memoria compartida\n");
        return -1;
    }
    return 1;
}

// Removes an already created shared memory array, given its Id
int removeSharedMemoryArray (int MemoryArrayId) {
   if (shmctl(MemoryArrayId, IPC_RMID, 0) < 0) {
       printf ("\nNo ha sido posible remover la memoria compartida\n");
       return -1;
   }
   return 1;
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

// Inserts the given ID into the biggest posible block of cells
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
void printMemoryArray(struct MemoryArray *memoryArray){
    printf("MEMORY\n");
    for (int i = 0; i < memoryArray->size; i++){
        printf("ID: %d\n", memoryArray->array[i]);
    }
    printf("\n");
    return;
}

