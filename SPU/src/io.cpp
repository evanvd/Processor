#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "stack.h"
#include "operation.h"
#include <stdarg.h>

void InitSPU(processor_t* spu, const char* filename)
{
    spu->native_file = fopen(filename,"r");
    fscanf(spu->native_file, "%lu", &spu->size);
    spu->read_data = (double*)calloc(spu->size, sizeof(int));
    spu->RAM = (double*)calloc(100,sizeof(double));
    GetFromFile(spu);
    StackInit(&spu->stack_data, spu->size);
    StackInit(&spu->ret_addr, 10); // TODO remove magic number
}

void GetFromFile(processor_t* spu)
{
    for (size_t index = 0; index < spu->size; index++)
    {
        fscanf(spu->native_file, "%f", &spu->read_data[index]);
    }
}

void color_printf(const char* color, const char* format, ...)
{

    printf("%s", color);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    printf("%s", RESET);
}

void PrintMatrix(int* data, const size_t size)
{
    for(size_t index = 0; index < size; index++)
    {
        printf("%d", data[index]);
        printf("\n");
    }
}
void DestroySPU(processor_t* spu)
{
    free(spu->read_data);
    free(spu->RAM);
    fclose(spu->native_file);
    spu->native_file = NULL;
    StackDestroy(&spu->stack_data);
    StackDestroy(&spu->ret_addr);
}