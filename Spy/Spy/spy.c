#include "spy.h"

void printMemoryCells(struct MemoryArray *memory, int cellsXline)
{
    // Obtain memory sempahore
    sem_t *memorySem = sem_open(SEMMEMORY, 0, 0644, 0);
    // Lock
    sem_wait(memorySem);

    int lineSize = cellsXline;
    int remaining = memory->size;
    int remXline = 0;
    int cont = 0;
    int index = 0;

    while (remaining != 0)
    {
        if (remaining > lineSize)
        {
            remXline = lineSize;
        }

        else
        {
            remXline = remaining;
        }
        index = printCellLine(memory, remXline, index);
        remaining = remaining - remXline;
    }

    // Unlock
    sem_post(memorySem);
}

int printCellLine(struct MemoryArray *memory, int elements, int index)
{
    for (int i = 0; i <= elements * 3; i++)
    {

        if (i < elements)
        {
            printf("┏    ┓  ");
        }

        if (i <= elements * 2 && i > elements)
        {
            int value = memory->array[index];
            index++;
            formatNumber(value);
        }

        if (i <= elements * 3 && i > elements * 2)
        {
            printf("┗    ┛  ");
        }

        if (i == elements || i == elements * 2)
        {
            printf("\n");
        }
    }

    printf("\n");
    return index;
}

void formatNumber(int number)
{
    if (number < 0)
    {
        printf("┃    ┃  ");
    }
    else if (number < 10)
    {
        printf("┃ 0%d ┃  ", number);
    }
    else
    {
        printf("┃ %d ┃  ", number);
    }
}

void printProcesses(struct ProcessArray *processes)
{
    // Obtain process list semaphore
    sem_t *processSem = sem_open(SEMPROCESS, 0, 0644, 0);
    // Lock
    sem_wait(processSem);

    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃      PROCESSES ACCESSING MEMORY        ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃   Critical Section Running Algorithm   ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printStateN(processes, 1);
    printf("┃                                        ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃     Critical Section Freeing Memory    ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printStateN(processes, 4);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

    printf("\n\n");

    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃         PROCESSES IN EXECUTION         ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printStateN(processes, 2);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

    printf("\n\n");

    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃           BLOCKED PROCESSESS           ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃    Blocked Waiting to Enter Memory     ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printStateN(processes, 0);
    printf("┃                                        ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃     Blocked Waiting to Exit Memory     ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printStateN(processes, 3);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

    printf("\n\n");

    // Unlock
    sem_post(processSem);
}

void printStateN(struct ProcessArray *processes, int state)
{
    int id = -1;
    for (int i = 0; i < processes->size; i++)
    {
        if (state == processes->array[i].status)
        {
            printf("┃  Process ID:");
            formatPID(processes->array[i].pID);
            printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
        }
    }
}

void formatPID(int number)
{
    if (number < 10 && number >= 0)
    {
        printf(" 0%d                        ┃\n", number);
    }
    else
    {
        printf(" %d                        ┃\n", number);
    }
}
