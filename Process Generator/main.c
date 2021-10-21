#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ProcessList/ProcessList.h"
#include "Memory/Memory.h"

int main()
{
    srand((unsigned int)time(NULL));

    struct Memory *m = newMemory(100);

    occupyNode(&m->first, m->first, 10, 0);
    occupyNode(&m->first, m->first->next, 20, 1);
    freeNode(&m->first, 0);
    occupyNode(&m->first, m->first, 5, 2);
    printMemory(m->first);
}
