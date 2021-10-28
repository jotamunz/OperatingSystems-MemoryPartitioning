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
    generateHeader();

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
        printf("\nTerminating program...\n\n");
        return;
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
    generateHeader();
    printf("Type the number of cells per line: ");
    scanf("%d", &selection);
    generateMemoryMenuAux(memory, processes, selection);
}

void generateMemoryMenuAux(struct MemoryArray *memory, struct ProcessArray *processes, int selection)
{
    system("clear");
    generateHeader();
    printf("CHECKING ON MEMORY STATE\n\n");
    printMemoryCells(memory, selection);
    printf("Press [ENTER] to refresh or any other key to exit...\n");
    char enter = 0;
    enter = getchar();

    system("clear");
    if (enter == '\r' || enter == '\n')
    {
        generateMemoryMenuAux(memory, processes, selection);
    }
    generateMenu(memory, processes);
}

void generateProcessMenu(struct MemoryArray *memory, struct ProcessArray *processes)
{
    int selection = 0;
    generateHeader();
    printf("CHECKING ON PROCESSES STATE\n\n");
    printProcesses(processes);
    printf("Press [ENTER] to refresh or any other key to exit...\n");
    char enter = 0;
    enter = getchar();

    system("clear");
    if (enter == '\r' || enter == '\n')
    {
        generateProcessMenu(memory, processes);
    }
    generateMenu(memory, processes);
}
