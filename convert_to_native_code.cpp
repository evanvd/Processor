#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_to_native_code.h"
void ConvertToNative(asm_t* assembler)
{
    for (size_t index = 0; index < assembler->size; index++)
    {
        assembler->native_code[index] = NativeTranslator(assembler->asm_code[index]);
    }
    
}

char* NativeTranslator(char* assembler_text)
{
    if (strcmp(assembler_text, "POP"))
    {
        return "1";
    }
    else if (strcmp(assembler_text, "DUMP"))
    {
        return "2";
    }
    else if (strcmp(assembler_text, "PUSH"))
    {
        return "3";
    }
    else if (strcmp(assembler_text, "PUSH"))
    {
        return "3";
    }    
}