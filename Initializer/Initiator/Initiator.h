#ifndef INITATOR_H
#define INTIATOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>
#include "../../Process_Generator/ProcessArray/ProcessArray.h"
#include "../../Process_Generator/MemoryArray/MemoryArray.h"
#include "../../Spy/Logger/logger.h"
#define PROCESSARRAYSIZE 50

void initializerMenu();
int openSemaphore(const char *name, int count);
#endif