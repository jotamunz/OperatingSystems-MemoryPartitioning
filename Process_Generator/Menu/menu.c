#include "menu.h"

void generateHeader()
{
    system("clear");
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃                      PROCESS GENERATOR                         ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("\n\n");
}

void generateMenu()
{
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
        printf("\n");
        createProcesses(0);
        break;

    case 2:
        printf("\n");
        createProcesses(1);
        break;

    case 3:
        printf("\n");
        createProcesses(2);
        break;

    case 4:
        printf("\nTerminating program...\n\n");
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
        generateMenu();
    }
}