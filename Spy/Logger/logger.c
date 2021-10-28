#include "logger.h"

int createLog(int memSize)
{
    FILE *fptr;
    if ((fptr = fopen(LOGPATH, "w")) == NULL)
    {
        printf("The simulation log couldn't be created\n");
        return -1;
    }
    char destination[122] = "Created on: ";
    ;
    char source[21];
    char memory[20];
    sprintf(memory, "%d", memSize);
    size_t i;
    struct tm tim;
    time_t now;
    now = time(NULL);
    tim = *(localtime(&now));
    i = strftime(source, 30, "%b %d, %Y; %H:%M:%S", &tim);
    fputs("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n┃                 DYNAMIC MEMORY ALLOCATION LOG                  ┃\n┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n", fptr);
    strcat(destination, source);
    fputs(destination, fptr);
    strncpy(destination, "\n\n[", sizeof(destination));
    strcat(destination, source);
    strcat(destination, "] Shared memory initialized with ");
    strcat(destination, memory);
    strcat(destination, " memory cells\n");
    fputs(destination, fptr);
    fclose(fptr);

    return 0;
}

void appendLog(int state, int pID, int pSize, int pDuration)
{
    FILE *fptr;
    fptr = fopen(LOGPATH, "a");
    char log[250] = "";
    char id[10];
    char size[10];
    char duration[10];
    char finalTime[21];
    sprintf(id, "%d", pID);
    sprintf(size, "%d", pSize);
    sprintf(duration, "%d", pDuration);

    size_t i;
    struct tm tim;
    time_t now;
    now = time(NULL);
    tim = *(localtime(&now));
    i = strftime(finalTime, 30, "%b %d, %Y; %H:%M:%S", &tim);

    switch (state)
    {
    case 0:
        strncpy(log, "\n[", sizeof(log));
        strcat(log, finalTime);
        strcat(log, "] The process ");
        strcat(log, id);
        strcat(log, " is waiting for the semaphore in order to be located in memory");
        break;

    case 1:
        strncpy(log, "\n[", sizeof(log));
        strcat(log, finalTime);
        strcat(log, "] The process ");
        strcat(log, id);
        strcat(log, " is being located in memory (");
        strcat(log, size);
        strcat(log, " cells required)");
        break;

    case 2:
        strncpy(log, "\n[", sizeof(log));
        strcat(log, finalTime);
        strcat(log, "] The process ");
        strcat(log, id);
        strcat(log, " is executing in memory (duration ");
        strcat(log, duration);
        strcat(log, "s)");
        break;

    case 3:
        strncpy(log, "\n[", sizeof(log));
        strcat(log, finalTime);
        strcat(log, "] The process ");
        strcat(log, id);
        strcat(log, " is waiting for the semaphore in order to free its memory");
        break;

    case 4:
        strncpy(log, "\n[", sizeof(log));
        strcat(log, finalTime);
        strcat(log, "] The process ");
        strcat(log, id);
        strcat(log, " is freeing its memory (");
        strcat(log, size);
        strcat(log, " cells being freed)");
        break;

    case 5:
        strncpy(log, "\n[", sizeof(log));
        strcat(log, finalTime);
        strcat(log, "] The process ");
        strcat(log, id);
        strcat(log, " has freed its memory (");
        strcat(log, size);
        strcat(log, " cells freed)");
        break;

    case 6:
        strncpy(log, "\n[", sizeof(log));
        strcat(log, finalTime);
        strcat(log, "] The process ");
        strcat(log, id);
        strcat(log, " didn´t find available space in memory (");
        strcat(log, size);
        strcat(log, " consecutive cells not available)");
        break;
    }
    strcat(log, "\n");
    fputs(log, fptr);
    fclose(fptr);
}