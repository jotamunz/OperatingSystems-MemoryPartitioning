#include "MemoryArray.h"

/* Creates a new shared memory array of given size, and returns its Id */
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

/* Gets the Id of an already created shared memory array, given its key filepath */
int getSharedMemoryArrayId (char* keyFilePath) {
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

/* Returns a pointer to an already created shared memory array, given its key filepath */
struct MemoryArray* attachSharedMemoryArray (char* keyFilePath) {
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

/* Detach a pointer to an already created shared memory array, given its key filepath */
int detachSharedMemoryArray (struct MemoryArray* MemoryArrayp) {
    if (shmdt(MemoryArrayp) < 0){
        printf ("\nNo ha sido posible desadjuntar la memoria compartida\n");
        return -1;
    }
    return 1;
}

/* Removes an already created shared memory array, given its Id*/
int removeSharedMemoryArray (int MemoryArrayId) {
   if (shmctl(MemoryArrayId, IPC_RMID, 0) < 0) {
       printf ("\nNo ha sido posible remover la memoria compartida\n");
       return -1;
   }
   return 1;
}

