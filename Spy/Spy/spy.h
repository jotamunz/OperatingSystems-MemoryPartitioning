#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h> 
#include <sys/types.h>
#include "../../Process_Generator/MemoryArray/MemoryArray.h"
#include "../../Process_Generator/ProcessArray/ProcessArray.h"

void printMemoryCells(struct MemoryArray *, int);
int printCellLine(struct MemoryArray *, int, int);
void formatNumber(int number);
void printProcesses(struct ProcessArray *);
void printStateN(struct ProcessArray *, int);
void formatPID(int number);
