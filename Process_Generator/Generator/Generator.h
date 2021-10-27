#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include "../ProcessArray/ProcessArray.h"
#include "../MemoryArray/MemoryArray.h"
#include "../../Spy/Logger/logger.h"

void createProcesses(int algorithm);
void *runProcess();