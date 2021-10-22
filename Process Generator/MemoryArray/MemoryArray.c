#include "MemoryArray.h"

int createSharedMemory (int size, char* keyFilePath){
    int shmid;
    key_t key;

    key = ftok("SharedKey.txt", 0);
    if ((shmid = shmget(key, sizeof(struct MemoryArray) + size * sizeof(int), IPC_CREAT | 0666)) < 0) {
        printf ("No ha sido posible alocar la memoria compartida");
        return -1;
    }
    return shmid;
}