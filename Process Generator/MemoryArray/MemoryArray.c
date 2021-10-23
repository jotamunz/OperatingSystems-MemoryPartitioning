#include "MemoryArray.h"

int createSharedMemory (int size, char* keyFilePath){
    int shmid;
    key_t key; 
    if ((key = ftok(keyFilePath, SHSEGMENTID)) < 0) {
        printf ("\nError: No se ha logrado obtener la llave de la memoria compartida\n");
        return -1;
    }
    if ((shmid = shmget(key, sizeof(struct MemoryArray) + size * sizeof(int), IPC_CREAT | 0666)) < 0) {
        printf ("\nNo ha sido posible alocar la memoria compartida\n");
        return -1;
    }
    return shmid;
}

int newSharedMemoryArray (int size, char* keyFilePath){
    int shmid;
    key_t key; 
    if ((key = ftok(keyFilePath, SHSEGMENTID)) < 0) {
        printf ("\nError: No se ha logrado obtener la llave de la memoria compartida\n");
        return -1;
    }
    if ((shmid = shmget(key, sizeof(struct MemoryArray) + size * sizeof(int), IPC_CREAT | 0666)) < 0) {
        printf ("\nError: No ha sido posible reservar la memoria compartida\n");
        return -1;
    }
    return shmid;
}

int getMemoryArrayId (char* keyFilePath) {
    int shmid;
    key_t key; 
    if ((key = ftok(keyFilePath, SHSEGMENTID)) < 0) {
        printf ("\nError: No se ha logrado obtener la llave de la memoria compartida\n");
        return -1;
    }
    if ((shmid = shmget(key, 0, 0666)) < 0) {
        printf ("\nNo ha sido posible obtener el Id de la memoria compartida\n");
        return -1;
    }
    return shmid;
}

struct MemoryArray* attachMemoryArray (char* keyFilePath) {
    struct MemoryArray* MemoryArrayp;
    int shmid;
    if((shmid = getMemoryArrayId(keyFilePath) < 0)) {
        return NULL;
    }
    if ((MemoryArrayp = shmat(shmid, NULL, 0)) == (char *) -1) {
        printf ("\nNo ha sido posible adjuntar la memoria compartida\n");
        return NULL;
    }
    return MemoryArrayp;
}

int dettachMemoryArray (struct MemoryArray* MemoryArrayp) {
    if (shmdt(MemoryArrayp) < 0){
        printf ("\nNo ha sido posible desadjuntar la memoria compartida\n");
        return -1;
    }
    return 1;
}

int removeMemoryArray (int MemoryArrayId) {
   if (shmctl(MemoryArrayId, IPC_RMID, 0) < 0) {
       printf ("\nNo ha sido posible remover la memoria compartida\n");
       return -1;
   }
   return 1;
}

