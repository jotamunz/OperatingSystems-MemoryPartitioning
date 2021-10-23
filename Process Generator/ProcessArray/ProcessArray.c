#include "ProcessArray.h"

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

// Changes the ID = -1 for the process with ID == key
void deleteProcess(struct ProcessArray *processArray, int key){
    for (int i = 0; i < processArray->size; i++){
        if (processArray->array[i].pID == key){
            processArray->array[i].pID = -1;
            return;
        }
    }
    return;
}

// Prints the process array
void printProcessArray(struct ProcessArray *processArray){
    for (int i = 0; i < processArray->size; i++){
        printProcess(processArray->array[i]);
    }
    return;
}