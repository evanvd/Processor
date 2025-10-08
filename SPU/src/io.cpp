#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "stack.h"

void InitSPU(processor_t* spu, const char* filename)
{
    spu->native_file = fopen(filename,"r");
    fscanf(spu->native_file, "%lu", &spu->size);
    spu->read_data = (int*)calloc(spu->size, sizeof(int));
    GetFromFile(spu);
    StackInit(&spu->stack_data, spu->size);
}

void GetFromFile(processor_t* spu)
{
    for (size_t index = 0; index < spu->size; index++)
    {
        fscanf(spu->native_file, "%d", &spu->read_data[index]);
    }
}

void PrintMatrix(int* data, const size_t size)
{
    for(size_t index = 0; index < size; index++)
    {
        printf("%d", data[index]);
        printf("\n");
    }
}
//TODO DoOp
void DestroySPU(processor_t* spu)
{
    free(spu->read_data);
    fclose(spu->native_file);
    spu->native_file = NULL;
    StackDestroy(&spu->stack_data);
}