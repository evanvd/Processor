#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_to_native_code.h"

void ConvertToNative(asm_t* assembler)
{
    // TODO separate asm_index for asm_code
    for (size_t native_index = 0, asm_index = 0; native_index < assembler->size; asm_index++, native_index++)
    {    
        printf("%zu ",native_index);
        if(NativeTranslator(assembler, assembler->asm_code[asm_index], &native_index) == ReadError)
        {
            printf("SYNTAX ERROR"); //TODO ABORT PROGRAM WHILE ERROR
        }
        printf("%d",assembler->native_code[native_index]);
    }
}

assembler_err NativeTranslator(asm_t* assembler, char* assembler_text, size_t* asm_index)
{
    if (strcmp(assembler_text, "POP") == 0)
    {
        assembler->native_code[*asm_index] = 1;
        return NoErr;
    }
    else if (strcmp(assembler_text, "DUMP") == 0)
    {
        assembler->native_code[*asm_index] = 2;
        return NoErr;
    }
    else if (strcmp(assembler_text, "PUSH") == 0)
    {
        assembler->native_code = (int*)realloc(assembler->native_code, (assembler->size + 1) * sizeof(int)); //TODO FIX heap overflow
        assembler->native_code[*asm_index] = 3; 
        assembler->native_code[*asm_index++] = 10; //TODO PUSH number fix 
        return NoErr; 
    }
    return ReadError;
}

bool ComparePush(char* assembler_text, asm_t* assembler, size_t* asm_index)
{
    if(assembler_text[0] == 'P' && assembler_text[1] == 'U' && assembler_text[2] == 'S' && assembler_text[3] == 'H')
    {
        char* push_value = {};
        for (size_t index = 4; index < strlen(assembler_text); index++)
        {
            push_value[index - 4] = assembler_text[index]; 
        }
        assembler->native_code = (int*)realloc(assembler->native_code, (assembler->size + 1) * sizeof(int));
        assembler->native_code[*asm_index] = 3; 
    }
    return false;
}