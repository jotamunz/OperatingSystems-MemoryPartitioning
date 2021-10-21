#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ProcessList/ProcessList.h"
#include "Memory/Memory.h"

int main()
{
    srand((unsigned int)time(NULL));

    struct Memory *m = newMemory(100);

    struct Process *p0 = newProcess(0, 0);
    p0->size = 10;
    struct Process *p1 = newProcess(1, 0);
    p1->size = 20;
    struct Process *p2 = newProcess(2, 0);
    p2->size = 5;
    struct Process *p3 = newProcess(3, 0);
    p3->size = 5;
    struct Process *p4 = newProcess(4, 0);
    p4->size = 80;

    struct MNode *node;
    node = firstFit(p0, m->first);
    occupyNode(&m->first, node, p0->size, p0->pID);
    printMemory(m->first);

    node = firstFit(p1, m->first);
    occupyNode(&m->first, node, p1->size, p1->pID);
    printMemory(m->first);

    freeNode(&m->first, 0);

    node = firstFit(p2, m->first);
    occupyNode(&m->first, node, p2->size, p2->pID);
    printMemory(m->first);

    node = firstFit(p3, m->first);
    occupyNode(&m->first, node, p3->size, p3->pID);
    printMemory(m->first);

    node = firstFit(p4, m->first);
    occupyNode(&m->first, node, p4->size, p4->pID);
    printMemory(m->first);
}
