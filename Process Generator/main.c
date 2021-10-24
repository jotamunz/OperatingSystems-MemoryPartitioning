#include <stdio.h>
#include <stdlib.h>
#include "ProcessArray/ProcessArray.h"
#include "MemoryArray/MemoryArray.h"

int main()
{
    // The main will call createProcesses(int algorithm) with the algorithm selected by the user

    /* TESTS */

    struct MemoryArray *mArray = newLocalMemoryArray(20);
    // firstFit(mArray, 2, 0);
    // firstFit(mArray, 4, 1);
    // freeCells(mArray, 0);
    // firstFit(mArray, 1, 2);
    // firstFit(mArray, 1, 3);
    // firstFit(mArray, 5, 4);
    // firstFit(mArray, 15, 5);
    // printMemoryArray(mArray);

    /* BEST FIT ALGORITHM TESTS
    bestFit(mArray, 5, 1);
    bestFit(mArray, 5, 2);
    bestFit(mArray, 6, 3);
    bestFit(mArray, 4, 4);
    // freeCells(mArray, 3);
    // freeCells(mArray, 1);
    freeCells(mArray, 4);
    freeCells(mArray, 3);
    freeCells(mArray, 1);
    bestFit(mArray, 3, 8);
    printMemoryArray(mArray);
    */
    bestFit(mArray, 5, 1);
    bestFit(mArray, 5, 2);
    bestFit(mArray, 6, 3);
    bestFit(mArray, 4, 4);
    freeCells(mArray, 3);
    freeCells(mArray, 1);
    // freeCells(mArray, 4);
    // freeCells(mArray, 3);
    // freeCells(mArray, 1);
    bestFit(mArray, 6, 8);
    printMemoryArray(mArray);
}
