#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ProcessArray/ProcessArray.h"
#include "MemoryArray/MemoryArray.h"

int main()
{

    struct ProcessArray *pArray = newLocalProcessArray(10);
    struct Process *p0 = newLocalProcess(0, 0);
    struct Process *p1 = newLocalProcess(1, 0);
    struct Process *p2 = newLocalProcess(2, 0);
    struct Process *p3 = newLocalProcess(3, 0);
    struct Process *p4 = newLocalProcess(4, 0);
    insertProcess(pArray, p0);
    insertProcess(pArray, p2);
    insertProcess(pArray, p1);
    deleteProcess(pArray, 0);
    insertProcess(pArray, p3);
    insertProcess(pArray, p4);
    printProcessArray(pArray);
}
