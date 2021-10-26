#include "menu.h"

void generateHeader()
{
    system("clear");
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃                        SPY PROGRAM                             ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\n\n");
}

void generateMenu(struct MemoryArray *memory, struct ProcessArray *processes)
{
    if (memory == NULL || processes == NULL) {
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
    printf("[1] Check memory state \n\n");
    printf("[2] Process state \n\n");
    printf("[3] Exit \n\n");
    printf("Select an option: ");
    scanf("%d", &selection);

    switch (selection)
    {
    case 1:
        generateMemoryMenu(memory, processes);
        break;

    case 2:
        generateProcessMenu(memory, processes);
        break;

    case 3:
        printf("Saliendo...");
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

void generateMemoryMenu(struct MemoryArray *memory, struct ProcessArray *processes)
{
    int selection = 0;
    char trashCollector[10];
    generateHeader();
    printf("Type the number of cells per line: ");
    scanf("%d", &selection);
    system("clear");
    generateHeader();
    printf("CHECKING ON MEMORY STATE\n\n");
    printMemoryCells(memory, selection);
    printf("Press enter to return to the main menu...\n");
    char enter = 0;
    fgets(trashCollector, sizeof(trashCollector), stdin);
    while (enter != '\r' && enter != '\n')
    {
        enter = getchar();
    }
    system("clear");
    generateMenu(memory, processes);
}

void generateProcessMenu(struct MemoryArray *memory, struct ProcessArray *processes)
{
    int selection = 0;
    char trashCollector[10];
    generateHeader();
    printf("CHECKING ON PROCESSES STATE\n\n");
    printProcesses(processes);
    printf("Press enter to return to the main menu...\n");
    char enter = 0;
    fgets(trashCollector, sizeof(trashCollector), stdin);
    while (enter != '\r' && enter != '\n')
    {
        enter = getchar();
    }
    system("clear");
    generateMenu(memory, processes);
}
