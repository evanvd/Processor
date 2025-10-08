#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_to_native_code.h"

void ConvertToNative(asm_t* assembler)
{
    for (size_t native_index = 0, asm_index = 0; native_index < assembler->size; asm_index++, native_index++)
    {    
        if(NativeTranslator(assembler, assembler->asm_code[asm_index], &native_index) == ReadError)
        {
            printf("SYNTAX ERROR"); //TODO ABORT PROGRAM WHILE ERROR
        }
    }
}

assembler_err NativeTranslator(asm_t* assembler, char* assembler_text, size_t* native_index)
{
    if (strcmp(assembler_text, "POP") == 0)
    {
        assembler->native_code[*native_index] = OP_POP;
        return NoErr;
    }
    else if (strcmp(assembler_text, "DUMP") == 0)
    {
        assembler->native_code[*native_index] = OP_DUMP;
        return NoErr;
    }
    else if (strcmp(assembler_text, "MUL") == 0)
    {
        assembler->native_code[*native_index] = OP_MUL;
        return NoErr;
    }
    else if (strcmp(assembler_text, "SUB") == 0)
    {
        assembler->native_code[*native_index] = OP_SUB;
        return NoErr;
    }
    else if (strcmp(assembler_text, "OUT") == 0)
    {
        assembler->native_code[*native_index] = OP_OUT;
        return NoErr;
    }
    else if (strcmp(assembler_text, "DIV") == 0)
    {
        assembler->native_code[*native_index] = OP_DIV;
        return NoErr;
    }
    else if (strcmp(assembler_text, "HLT") == 0)
    {
        assembler->native_code[*native_index] = OP_HLT;
        return NoErr;
    }
    else if (ComparePush(assembler_text, assembler, native_index))
    {
        return NoErr; 
    }
    return ReadError;
}

bool ComparePush(char* assembler_text, asm_t* assembler, size_t* native_index)
{
    if(assembler_text[0] == 'P' && assembler_text[1] == 'U' && assembler_text[2] == 'S' && assembler_text[3] == 'H')
    {
        char* push_value = (char*)calloc(strlen(assembler_text) - 3, sizeof(char));
        for (size_t index = 4; index < strlen(assembler_text); index++)
        {
            push_value[index - 4] = assembler_text[index]; 
        }
        int value = atoi(push_value);
        free(push_value);
        //assembler->native_code = (int*)realloc(assembler->native_code, (assembler->size + 1) * sizeof(int));
        assembler->native_code[*native_index] = 3; 
        assembler->native_code[++*native_index] = value;
        // assembler->size += 1; //TODO remove fault
        return true;
    }
    return false;
}