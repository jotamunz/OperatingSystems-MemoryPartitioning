#include "../Spy/Menu/menu.h"

int main(void)
{

    struct MemoryArray *mArray = newLocalMemoryArray(21);
    struct ProcessArray *pArray = newLocalProcessArray(5);

    firstFit(mArray, 2, 0);
    firstFit(mArray, 4, 1);
    firstFit(mArray, 1, 2);
    firstFit(mArray, 1, 3);
    firstFit(mArray, 5, 4);
    firstFit(mArray, 15, 5);
    //printMemoryArray(mArray);

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
    
    */
    //worstFit(mArray, 5, 1);
    //worstFit(mArray, 4, 2);
    //worstFit(mArray, 2, 4);
    // freeCells(mArray, 4);
    // freeCells(mArray, 3);
    // freeCells(mArray, 1);

    //printMemoryCells(mArray, 5);
    generateMenu(mArray, pArray);
}
