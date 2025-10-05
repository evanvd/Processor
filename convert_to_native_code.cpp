#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_to_native_code.h"


void ConvertToNative(asm_t* assembler)
{
    for (size_t index = 0; index < assembler->size; index++)
    {
        NativeTranslator(assembler->native_code, assembler->asm_code[index], &index);
    }
}

assembler_err NativeTranslator(char** native_code, char* assembler_text, size_t* index)
{
    if (strcmp(assembler_text, "POP"))
    {
        native_code[*index] = "1";
    }
    else if (strcmp(assembler_text, "DUMP"))
    {
        native_code[*index] = "2";
    }
    else if (strcmp(assembler_text, "PUSH"))
    {
        native_code[*index] = "3";
    }
    else 
    {
        native_code[*index] = "хуй";
    }    
    return ReadError;
}