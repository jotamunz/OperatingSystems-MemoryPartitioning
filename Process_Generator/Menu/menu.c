#include "menu.h"

void generateHeader()
{
    system("clear");
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃                      PROCESS GENERATOR                         ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\n\n");
}

void generateMenu(struct MemoryArray *memory, struct ProcessArray *processes)
{
    if (memory == NULL || processes == NULL)
    {
        // Obtain a pointer to both structres in shared memory
        int key = getSharedProcessArrayId(KEYFILEPATH);
        processes = attachSharedProcessArray(key);
        key = getSharedMemoryArrayId(KEYFILEPATH);
        memory = attachSharedMemoryArray(key);

        // Validate shared memory access
        if (memory == NULL || processes == NULL)
            return;

        // Add id for finalizer
        processes->programIds[2] = getpid();
    }

    int selection = 0;
    char trashCollector[10];
    generateHeader();
    printf("[1] First Fit \n\n");
    printf("[2] Best Fit \n\n");
    printf("[3] Worst Fit \n\n");
    printf("[4] Exit \n\n");
    printf("Select an option: ");
    scanf("%d", &selection);

    switch (selection)
    {
    case 1:
        printf("First Fit");
        break;

    case 2:
        printf("Best Fit");
        break;

    case 3:
        printf("Worst Fit");

        break;

    case 4:
        printf("Terminating program...\n");
        break;

    default:
        printf("\nThe value typed doesn´t correspond to an available option \n\n");
        printf("Press enter to continue\n");
        char enter = 0;
        fgets(trashCollector, sizeof(trashCollector), stdin);
        while (enter != '\r' && enter != '\n')
        {
            enter = getchar();
        }
        system("clear");
        generateMenu(memory, processes);
    }
}