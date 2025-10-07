#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_to_native_code.h"

void ConvertToNative(asm_t* assembler)
{
    for (size_t index = 0; index < assembler->size; index++)
    {
        if(NativeTranslator(assembler->native_code, assembler->asm_code[index], &index) == ReadError)
        {
            printf("SYNTAX ERROR");
        }
    }
}

assembler_err NativeTranslator(int* native_code, char* assembler_text, size_t* index)
{
    if (strcmp(assembler_text, "POP") == 0)
    {
        native_code[*index] = 1;
        return NoErr;
    }
    else if (strcmp(assembler_text, "DUMP") == 0)
    {
        native_code[*index] = 1;
        return NoErr;
    }
    else if (strcmp(assembler_text, "PUSH") == 0)
    {
        //native_code = (char**)realloc(->size);
        native_code[*index] = 3;
        return NoErr; 
    }
    return ReadError;
}