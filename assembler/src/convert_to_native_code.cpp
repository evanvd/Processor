#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_to_native_code.h"

void ConvertToNative(asm_t* assembler)
{
    assembler->instruction_pointer = 0;
    for (size_t asm_index = 0; assembler->instruction_pointer < assembler->size; asm_index++, assembler->instruction_pointer++)
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
    else if (ComparePopR(assembler_text, assembler))
    {
        return NoErr; 
    }
    else if (ComparePushR(assembler_text, assembler))
    {
        return NoErr; 
    }
    return ReadError;
}


bool ComparePush(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "PUSH ", 5) == 0)
    {  
        char* number = assembler_text + 4;
        assembler->native_code = (int*)realloc(assembler->native_code, (assembler->size + 1) * sizeof(int));
        assembler->native_code[assembler->instruction_pointer] = OP_PUSH; 
        assembler->native_code[++assembler->instruction_pointer] = atoi(number);
        assembler->size += 1;
        return true;
    }
    return false;
}

bool ComparePushR(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "POSHR", 5) == 0)
    {  
        int reg = (int)assembler_text[6] - (int)'A' + 1; // specific of processor
        assembler->native_code = (int*)realloc(assembler->native_code, (assembler->size + 1) * sizeof(int));
        assembler->native_code[assembler->instruction_pointer] = OP_PUSHR; 
        assembler->native_code[++assembler->instruction_pointer] = reg;
        assembler->size += 1;
        return true;
    }
    return false;
}

bool ComparePopR(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "POPR", 4) == 0)
    {  
        int reg = (int)assembler_text[5] - (int)'A' + 1; // specific of processor
        assembler->native_code = (int*)realloc(assembler->native_code, (assembler->size + 1) * sizeof(int));
        assembler->native_code[assembler->instruction_pointer] = OP_POPR; 
        assembler->native_code[++assembler->instruction_pointer] = reg;
        assembler->size += 1;
        return true;
    }
    return false;
}

bool CompareJump(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "JMP", 3) == 0)
    {  
        char* number = assembler_text + 4;
        assembler->native_code = (int*)realloc(assembler->native_code, (assembler->size + 1) * sizeof(int));
        assembler->native_code[assembler->instruction_pointer] = OP_JMP; 
        assembler->native_code[++assembler->instruction_pointer] = atoi(number);
        assembler->size += 1;
        return true;
    }
    return false;
}