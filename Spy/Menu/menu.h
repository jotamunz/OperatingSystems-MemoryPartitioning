#include <stdio.h>
#include <stdlib.h>
#include "../Spy/spy.h"

void generateMenu(struct MemoryArray *, struct ProcessArray *);
void generateHeader();
void generateMemoryMenu(struct MemoryArray *, struct ProcessArray *);
void generateProcessMenu(struct MemoryArray *, struct ProcessArray *);
void generateMemoryMenuAux(struct MemoryArray *, struct ProcessArray *, int);