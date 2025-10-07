#include <stdio.h>
#include <stdlib.h>
#include "io.h"

void InitSPU(processor_t* proc, char* filename)
{
    proc->native_file = fopen(filename,"r");
    fscanf(proc->native_file, "%lu", &proc->size);
    
}