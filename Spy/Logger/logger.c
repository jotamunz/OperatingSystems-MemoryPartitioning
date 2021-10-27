#include "logger.h"

int createLog(int memSize)
{
    FILE *fptr;
    if ((fptr = fopen(LOGPATH, "w")) == NULL)
    {
        printf("The simulation log couldn't be created\n");
        return -1;
    }
    char destination[120] = "Log entries: \n\nThe log file was created at: ";
    ;
    char source[21];
    char memory[20];
    sprintf(memory, "%d", memSize);
    size_t i;
    struct tm tim;
    time_t now;
    now = time(NULL);
    tim = *(localtime(&now));
    i = strftime(source, 30, "%b %d, %Y; %H:%M:%S\n", &tim);
    fputs("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n┃                 DYNAMIC MEMORY ALLOCATION LOG                  ┃\n┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n", fptr);
    strcat(destination, source);
    fputs(destination, fptr);
    strncpy(destination, "\nShared memory initialized with ", sizeof(destination));
    strcat(destination, memory);
    strcat(destination, " memory cells at: ");
    strcat(destination, source);
    strcat(destination, "\n");
    fputs(destination, fptr);
    fclose(fptr);

    return 0;
}

void appendLog(int state, int pID, int pSize)
{

    FILE *fptr;
    fptr = fopen(LOGPATH, "a");
    char log[250] = "";
    char id[10];
    char size[10];
    char finalTime[21];
    sprintf(id, "%d", pID);
    sprintf(size, "%d", pSize);

    size_t i;
    struct tm tim;
    time_t now;
    now = time(NULL);
    tim = *(localtime(&now));
    i = strftime(finalTime, 30, "%b %d, %Y; %H:%M:%S\n", &tim);

    switch (state)
    {
    case 0:
        strncpy(log, "\nThe process ", sizeof(log));
        strcat(log, id);
        strcat(log, " is waiting for the semaphore in order to be located in memory ");
        strcat(log, finalTime);
        break;

    case 1:
        strncpy(log, "\nThe process ", sizeof(log));
        strcat(log, id);
        strcat(log, " is being located in memory ( ");
        strcat(log, size);
        strcat(log, " cells occupied ) ");
        strcat(log, finalTime);
        break;

    case 2:
        strncpy(log, "\nThe process ", sizeof(log));
        strcat(log, id);
        strcat(log, " is executing in memory ");
        strcat(log, finalTime);
        break;

    case 3:
        strncpy(log, "\nThe process ", sizeof(log));
        strcat(log, id);
        strcat(log, " is waiting for the semaphore in order to free memory ");
        strcat(log, finalTime);
        break;

    case 4:
        strncpy(log, "\nThe process ", sizeof(log));
        strcat(log, id);
        strcat(log, " is freeing memory ( ");
        strcat(log, size);
        strcat(log, " cells freed ) ");
        strcat(log, finalTime);
        break;

    case 5:
        strncpy(log, "\nThe process ", sizeof(log));
        strcat(log, id);
        strcat(log, " has freed memory ( ");
        strcat(log, size);
        strcat(log, " cells freed ) ");
        strcat(log, finalTime);
        break;

    case 6:
        strncpy(log, "\nThe process ", sizeof(log));
        strcat(log, id);
        strcat(log, " didn´t find available space in memory ");
        strcat(log, finalTime);
        break;
    }
    strcat(log, "\n");
    fputs(log, fptr);
    fclose(fptr);
}