#include "Initiator.h"

void initializerMenu(){
    char s[100];
    char trashCollector[5];
    fgets(trashCollector, sizeof(trashCollector), stdin);
    int requestedCells;
    printf("Welcome to the initializer program\n");
    printf("Please input the amount of cells to request for the simulation: ");
    fgets(s, sizeof(s), stdin);
    requestedCells = atoi(s);
    while (requestedCells < 1){
        printf("Please input a natural number of cells to request: ");
        fgets(s, sizeof(s), stdin);
        requestedCells = atoi(s);
    }
    printf("%d amount of cells have been allocated\n", requestedCells); 
}