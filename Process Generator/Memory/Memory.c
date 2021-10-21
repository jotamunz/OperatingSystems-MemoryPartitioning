#include "Memory.h"

// Constructor for double linked list
struct Memory *newMemory(int size){
    struct Memory *list = malloc(sizeof(struct Memory));
    struct MNode* newNode = (struct MNode*) malloc(sizeof(struct MNode));

    // Start the list as a single free node
    newNode->size = size;
    newNode->free = true;
    newNode->pID = -1;
    newNode->prev = NULL;
    newNode->next = NULL;
    list->first = newNode;

    return list;
}

// Insert before a given node in a double linked list
void occupyNode(struct MNode** firstRef, struct MNode* nextNode, int newSize, int pID){
    // Next node can not be null
    if (nextNode == NULL) {
        return;
    }

    // If process takes up the whole node
    if (nextNode->size == newSize){
        // Insert process data into next node
        nextNode->free = false;
        nextNode->pID = pID;
    } else {
        struct MNode* newNode = (struct MNode*) malloc(sizeof(struct MNode));

        // Occupy the node
        newNode->free = false;
        newNode->size = newSize;
        newNode->pID = pID;

        // Link new node
        newNode->prev = nextNode->prev;
        nextNode->prev = newNode;
        newNode->next = nextNode;
        if (newNode->prev != NULL)
            newNode->prev->next = newNode;
        else
            (*firstRef) = newNode;

        // Subtract size from next node
        nextNode->size -= newSize;
    }
}

// Delete the first occurrence of the key in a doube linked list
void freeNode(struct MNode **firstRef, int key){
    struct MNode *temp = *firstRef, *neighbor;

    // Search for the key
    while (temp != NULL && temp->pID != key) {
        temp = temp->next;
    }

    // Key was not found
    if (temp == NULL)
        return;

    // Free the node
    temp->free = true;
    temp->pID = -1;

    // Add free memoy from prev node
    neighbor = temp->prev;
    if (neighbor != NULL && neighbor->free){
        temp->size += neighbor->size;
        deleteNode(firstRef, neighbor);
    }

    // Add free memoy from next node
    neighbor = temp->next;
    if (neighbor != NULL && neighbor->free){
        temp->size += neighbor->size;
        deleteNode(firstRef, neighbor);
    }
}

// Delete the given node from a double linked list
void deleteNode(struct MNode **firstRef, struct MNode *del){
    // If del is the head
    if (*firstRef == del)
        *firstRef = del->next;
    // If del is not the last node
    if (del->next != NULL)
        del->next->prev = del->prev;
    // If del is not the first node
    if (del->prev != NULL)
        del->prev->next = del->next;
    free(del);
}

void printMemory(struct MNode *node){
    while (node != NULL){
        printf(" %d", node->pID);
        printf("(%d) ", node->size);
        node = node->next;
    }
    printf("\n");
}
