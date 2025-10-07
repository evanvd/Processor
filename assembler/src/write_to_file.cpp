#include <stdio.h>
#include <stdlib.h>
#include "write_to_file.h"
#include "read_from_file.h"

void PrintStringMatrix(char** data, const size_t size)
{
    for(size_t index = 0; index < size; index++)
    {
        printf("%s", data[index]);
        printf("\n");
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

void WriteToFile(asm_t* assembler)
{
    fprintf(assembler->native_file, "%lu\n", assembler->size);
    for (size_t index = 0; index < assembler->size; index++)
    {
       fprintf(assembler->native_file, "%d\n", assembler->native_code[index]);    
    }
}