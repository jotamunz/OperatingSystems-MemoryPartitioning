#include "ProcessList.h"

// Constructor for single linked list
struct ProcessList *newProcessList(){
    struct ProcessList *list = malloc(sizeof(struct ProcessList));
    list->first = NULL;
    return list;
}

// Insert at the begining of single linked list
void insertProcess(struct PNode **firstRef, struct Process *newProcess){
    struct PNode* newNode = (struct PNode*) malloc(sizeof(struct PNode));
    newNode->process = newProcess;
    newNode->next = (*firstRef);
    (*firstRef) = newNode;
}

// Delete the first occurrence of the key in a single linked list
void deleteProcess(struct PNode **firstRef, int key){
    struct PNode *temp = *firstRef, *prev;
 
    // The head is the key
    if (temp != NULL && temp->process->pID == key) {
        *firstRef = temp->next; 
        free(temp); 
        return;
    }
 
    // Search for the key
    while (temp != NULL && temp->process->pID != key) {
        prev = temp;
        temp = temp->next;
    }
 
    // Key was not found
    if (temp == NULL)
        return;

    // Remove the node
    prev->next = temp->next;
    free(temp); 
}

void printProcessList(struct PNode *node){
    while (node != NULL){
        printf(" %d ", node->process->pID);
        node = node->next;
    }
    printf("\n");
}
