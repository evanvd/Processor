#include <stdio.h>
#include <stdlib.h>
#include "io.h"


void InitSPU(processor_t* spu, char* filename)
{
    spu->native_file = fopen(filename,"r");
    fscanf(spu->native_file, "%lu", &spu->size);
    spu->read_data = (int*)calloc(spu->size, sizeof(int));
    GetFromFile(spu);
}

void GetFromFile(processor_t* spu)
{
    for (size_t index = 0; index < spu->size; index++)
    {
        fscanf(spu->native_file, "%d", &spu->read_data[index]);
    }
}