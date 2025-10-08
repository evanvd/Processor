#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_to_native_code.h"

void ConvertToNative(asm_t* assembler)
{
    assembler->instruction_pointer = 0;
    for (size_t asm_index = 0; assembler->instruction_pointer < assembler->size; asm_index++, ++assembler->instruction_pointer)
    {    
        printf("native index %lu, asm_index %lu size %lu code %d\n", assembler->instruction_pointer, asm_index, assembler->size, 
            assembler->native_code[assembler->instruction_pointer]);
        if(NativeTranslator(assembler, assembler->asm_code[asm_index]) == ReadError)
        {
            printf("SYNTAX ERROR"); //TODO ABORT PROGRAM WHILE ERROR
        }
        printf("native index %lu, asm_index %lu size %lu code %d\n", assembler->instruction_pointer, asm_index, assembler->size, 
            assembler->native_code[assembler->instruction_pointer]);
    }
}

assembler_err NativeTranslator(asm_t* assembler, char* assembler_text)
{
    if (strcmp(assembler_text, "POP") == 0)
    {
        assembler->native_code[assembler->instruction_pointer] = OP_POP;
        return NoErr;
    }
    else if (strcmp(assembler_text, "DUMP") == 0)
    {
        assembler->native_code[assembler->instruction_pointer] = OP_DUMP;
        return NoErr;
    }
    else if (strcmp(assembler_text, "MUL") == 0)
    {
        assembler->native_code[assembler->instruction_pointer] = OP_MUL;
        return NoErr;
    }
    else if (strcmp(assembler_text, "SUB") == 0)
    {
        assembler->native_code[assembler->instruction_pointer] = OP_SUB;
        return NoErr;
    }
    else if (strcmp(assembler_text, "OUT") == 0)
    {
        assembler->native_code[assembler->instruction_pointer] = OP_OUT;
        return NoErr;
    }
    else if (strcmp(assembler_text, "DIV") == 0)
    {
        assembler->native_code[assembler->instruction_pointer] = OP_DIV;
        return NoErr;
    }
    else if (strcmp(assembler_text, "HLT") == 0)
    {
        assembler->native_code[assembler->instruction_pointer] = OP_HLT;
        return NoErr;
    }
    else if (ComparePush(assembler_text, assembler))
    {
        return NoErr; 
    }
    return ReadError;
}

bool ComparePush(char* assembler_text, asm_t* assembler)
{
    //TODO sscanf(assembler_text, "%4s", buffer); strcmp(buffer, "PUSH")

    if(assembler_text[0] == 'P' && assembler_text[1] == 'U' && assembler_text[2] == 'S' && assembler_text[3] == 'H')
    {
        // TODO sscanf(asm_text, "%d", ...)
        char* push_value = (char*)calloc(strlen(assembler_text) - 3, sizeof(char));
        for (size_t index = 5; index < strlen(assembler_text); index++)
        {
            push_value[index - 5] = assembler_text[index];
        }
        int value = atoi(push_value);
        free(push_value);
        assembler->native_code = (int*)realloc(assembler->native_code, (assembler->size + 1) * sizeof(int));
        assembler->native_code[assembler->instruction_pointer] = OP_PUSH; 
        assembler->native_code[++assembler->instruction_pointer] = value;
        assembler->size += 1;
        return true;
    }
    return false;
}