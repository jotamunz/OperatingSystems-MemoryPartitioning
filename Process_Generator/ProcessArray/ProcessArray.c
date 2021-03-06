#include "ProcessArray.h"


/* Creates a new shared process array of given size, and returns its Id */
int newSharedProcessArray (int size, char* keyFilePath){
    int i;
    int shmid;
    struct ProcessArray* processArrayp; 
    key_t key; 
    if ((key = ftok(keyFilePath, PROCESSARRAYSHAREDID)) < 0) {
        printf ("\nError: Could not obtain key to shared process list\n");
        return -1;
    }
    if ((shmid = shmget(key, sizeof(struct ProcessArray) + size * sizeof(struct Process), IPC_CREAT | 0666)) < 0) {
        printf ("\nError: Could not reserve the shared process list\n");
        return -1;
    }
    processArrayp = attachSharedProcessArray(shmid);
    for (int i = 0; i < size; i++)
    {
        processArrayp->array[i].pID = -1;
    }
    processArrayp->size = size;
    processArrayp->programIds[0] = getpid();
    for(i = 1; i < 3; i++)
    {
        processArrayp->programIds[i] = 0;
    }
    detachSharedProcessArray(processArrayp);
    return shmid;
}

/* Gets the Id of an already created shared process array, given its key filepath */
int getSharedProcessArrayId (char* keyFilePath) {
    int shmid;
    key_t key; 
    if ((key = ftok(keyFilePath, PROCESSARRAYSHAREDID)) < 0) {
        printf ("\nError: Could not obtain key to shared process list\n");
        return -1;
    }
    if ((shmid = shmget(key, 0, 0666)) < 0) {
        printf ("\nError: Could not obtain ID of shared process list\n");
        return -1;
    }
    return shmid;
}

/* Returns a pointer to an already created shared process array, given its key filepath */
struct ProcessArray* attachSharedProcessArray (int shmid) {
    struct ProcessArray* ProcessArrayp;
    if ((ProcessArrayp = shmat(shmid, NULL, 0)) == (struct ProcessArray*) -1) {
        printf ("\nError: Could not attach shared process list\n");
        return NULL;
    }
    return ProcessArrayp;
}

/* Detach a pointer to an already created shared process array, given its key filepath */
int detachSharedProcessArray (struct ProcessArray* processArrayp) {
    if (shmdt(processArrayp) != 0){
        printf ("\nError: Could not detach shared process list\n");
        return -1;
    }
    return 1;
}

/* Removes an already created shared process array, given its Id*/
int removeSharedProcessArray (int arrayId) {
   if (shmctl(arrayId, IPC_RMID, 0) < 0) {
       printf ("\nError: Could not remove shared process list\n");
       return -1;
   }
   return 1;
}

// Creates an array based on size full of Dummy Processes
struct ProcessArray* newLocalProcessArray(int size){
    struct ProcessArray *pArray = malloc(sizeof(struct ProcessArray) + sizeof(struct Process)*size);
    pArray->size = size;
    for (int i = 0; i < size; i++){
        pArray->array[i] = *(newLocalDummyProcess());
    }
    return pArray;
}

// Loops through the process array and value copies the process into the first index with pID == -1
void insertProcess(struct ProcessArray *processArray, struct Process *process){
    for (int i = 0; i < processArray->size; i++){
        if (processArray->array[i].pID == -1){
            memcpy(&(processArray->array[i]), process, sizeof(struct Process));
            return;
        }
    }
    return;
}

// Changes the ID = -1 for the process with the given ID
void deleteProcess(struct ProcessArray *processArray, int pID){
    for (int i = 0; i < processArray->size; i++){
        if (processArray->array[i].pID == pID){
            processArray->array[i].pID = -1;
            processArray->array[i].status = 0;
            return;
        }
    }
    return;
}

// Updates the status atribute for the process with the given ID
void updateProcessStatus(struct ProcessArray *processArray, int pID, int status){
    for (int i = 0; i < processArray->size; i++){
        if (processArray->array[i].pID == pID){
            processArray->array[i].status = status;
            return;
        }
    }
    return;
}

// Prints the process array
void printProcessArray(struct ProcessArray *processArray){
    printf("PROCESS LIST\n");
    for (int i = 0; i < processArray->size; i++){
        printf("ID: %d", processArray->array[i].pID);
        printf(" Status: %d", processArray->array[i].status);
        printf(" Size: %d\n", processArray->array[i].size);
    }
    printf("\n");
    return;
}