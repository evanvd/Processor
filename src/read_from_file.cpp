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
        ssize_t read = getline(&assembler->asm_code[index], &buffer_size, assembler->asm_file);
        if (read != -1) 
        {
            if (read > 0 && assembler->asm_code[index][read - 1] == '\n') 
            {
                assembler->asm_code[index][read - 1] = '\0';
            }
        }
    }
}

assembler_err InitAssembler(asm_t* data, const char* asm_filename, const char* native_filename)
{
    data->size = NumLines(asm_filename);
    if (data->size == 0) 
    {
        return BadFilenameErr; 
    }
    data->asm_file = fopen(asm_filename,"r");
    data->native_file = fopen(native_filename,"w");
    if (data->asm_file == NULL)
    {
        data->asm_code = NULL;
        return FileNull;
    }

    data->asm_code = (char**)calloc(data->size, sizeof(char*));
    data->native_code = (int*)calloc(data->size, sizeof(int));

    return NoErr;
}


size_t NumLines(const char* asm_filename)
{
    FILE* file = fopen(asm_filename, "r");
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
    return lines + 1;
}

void AssemblerDestroy(asm_t* assembler)
{
    for (size_t index = 0; index < assembler->size; index++)
    {
        free(assembler->asm_code[index]);
        //free(assembler->native_code[index]);
    }
    free(assembler->asm_code);
    free(assembler->native_code);

    fclose(assembler->asm_file);
    fclose(assembler->native_file);

    assembler->asm_file = NULL;
    assembler->native_file = NULL;    
}
