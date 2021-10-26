#ifndef INITATOR_H
#define INTIATOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <semaphore.h> 
#include <fcntl.h> 
#include "../../Process_Generator/ProcessArray/ProcessArray.h"
#include "../../Process_Generator/MemoryArray/MemoryArray.h"
#define PROCESSARRAYSIZE 3

void initializerMenu(int *memArrayId, int *processArrayId);
int openSemaphore(const char *name, int count);
#endif