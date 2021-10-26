#include "Terminator.h"

void terminatorMenu(){
    char s[100];
    char trashCollector[5];
    int option;
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃                        INITIALIZER PROGRAM                     ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    while(1){
        printf("\n\n");
        printf("[1] Terminate initializer, generator and spy program \n\n");
        printf("[2] Remove all shared memory previously allocated\n\n");
        printf("[3] Exit \n\n");
        printf("Select an option: ");
        fgets(s, sizeof(s), stdin);
        option = atoi(s);
        while (!(option == 1 || option == 2 || option == 3)){
            printf("[1] Terminate initializer, generator and spy program \n\n");
            printf("[2] Remove shared memory \n\n");
            printf("[3] Exit \n\n");
            printf("Please pick an option from those described above: ");
            fgets(s, sizeof(s), stdin);
            option = atoi(s);
        }
        switch (option)
        {
        case 1:
            printf("Close all processess \n\n");
            break;
        case 2:
            printf("Remove memory \n\n");
            break;
        case 3:
            printf("Terminating program\n\n");
            exit(0);
            break;
        default:
            break;
        }
    }
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

}