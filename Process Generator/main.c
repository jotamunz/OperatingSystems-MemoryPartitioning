#include <stdio.h>
#include <stdlib.h>
#include "ProcessArray/ProcessArray.h"
#include "MemoryArray/MemoryArray.h"

int main()
{
    // The main will call createProcesses(int algorithm) with the algorithm selected by the user

    /* TESTS */

    struct MemoryArray *mArray = newLocalMemoryArray(20);
    firstFit(mArray, 2, 0);
    firstFit(mArray, 4, 1);
    freeCells(mArray, 0);
    firstFit(mArray, 1, 2);
    firstFit(mArray, 1, 3);
    firstFit(mArray, 5, 4);
    firstFit(mArray, 15, 5);
    printMemoryArray(mArray);
}
