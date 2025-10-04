#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "read_from_file.h"

void GetFromFile(asm_t* assembler)
{
    size_t buffer_size = 0;
    for (size_t index = 0; index < assembler->size; index++)
    {
        getline(&assembler->asm_code[index], &buffer_size, assembler->file);
    }
}

assembler_err InitAssembler(asm_t* data, const char* filename)
{
    data->size = NumLines(filename);
    if (data->size == 0) 
    {
        return BadFilenameErr; 
    }
    data->file = fopen(filename,"r");
    if (data->file == NULL)
    {
        data->asm_code = NULL;
        return FileNull;
    }

    data->asm_code = (char**)calloc(data->size, sizeof(char*));
    data->native_code = (char**)calloc(data->size, sizeof(char*));

    return NoErr;
}


size_t NumLines(const char* filename)
{
    FILE* file = fopen(filename, "r");
    assert(file != NULL);
    int ch = 0;
    size_t lines = 0;
    while((ch = fgetc(file)) != EOF)
    {
        if(ch == '\n')
        {
            lines++;
        }
    }
    fclose(file);
    return lines;
}

void AssemblerDestroy(asm_t* assembler)
{
    for (size_t index = 0; index < assembler->size; index++)
    {
        free(assembler->asm_code[index]);
        free(assembler->native_code[index]);
    }
    free(assembler->asm_code);
    free(assembler->native_code);
    fclose(assembler->file);
    assembler->file = NULL;    
}
void WriteToFile(asm_t* assembler)
{
    
}