#include "Terminator.h"

void terminatorMenu(){
    char trashCollector[100];
    int option;
    system("clear");
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃                      FINALIZER PROGRAM                         ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\n\nPlease confirm you wish to end the simulation (Y/N): ");
    char r;
    char trash;
    scanf("%c", &r);
    while(r != 'n' && r != 'N' && r != 'y' && r != 'Y')
    {
        printf("\nInvalid input, enter the choice(y/Y/n/N) again: ");
        fgets(trashCollector, sizeof(trashCollector), stdin);
        scanf(" %c", &r);
    }
    if (r == 'y' || r == 'Y'){
        terminatePrograms();
        removedSharedMemory();
    }
    printf("\nTerminating program...\n\n");
    return;
}

void removedSharedMemory() {
    int processArrayKey;
    int memoryArrayKey;
    if ((processArrayKey = getSharedProcessArrayId(KEYFILEPATH)) < 0){
        return;
    }
    if ((memoryArrayKey = getSharedMemoryArrayId(KEYFILEPATH)) < 0){
        return;
    }
    if (removeSharedMemoryArray(memoryArrayKey) > -1){
        printf("The allocated shared memory array has been marked for removal\n");
    }
    if (removeSharedProcessArray(memoryArrayKey) > -1){
        printf("The allocated shared process queue has been marked for removal\n");
    }
    return;
}

void terminatePrograms() {
    int key;
    struct ProcessArray* processArrayp;
    if((key= getSharedProcessArrayId(KEYFILEPATH)) < 0 || (processArrayp = attachSharedProcessArray(key)) == NULL)
        return;
    if(processArrayp->programIds[0] < 1 || kill(processArrayp->programIds[0], SIGTERM) !=0){
        printf("\n• No initializer program to terminate found\n");
    } else {
        printf("\n• Initializer program terminated\n\n");
    }
    if(processArrayp->programIds[1] < 1 || kill(processArrayp->programIds[1], SIGTERM) !=0){
        printf("\n• No process generator program to terminate found\n");
    } else {
        printf("\n• Process generator program terminated\n\n");
    }
    if(processArrayp->programIds[1] < 1 || kill(processArrayp->programIds[1], SIGTERM) !=0){
        printf("\n• No spy program to terminate found\n");
    } else {
        printf("\n• Spy program terminated\n\n");
    }
    return;
}