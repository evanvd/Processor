#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_to_native_code.h"

void ConvertToNative(asm_t* assembler)
{
     
    assembler->instruction_pointer = 0;
    for (size_t asm_index = 0; assembler->instruction_pointer < assembler->size; asm_index++, assembler->instruction_pointer++)
    {    
        if(NativeTranslator(assembler, assembler->asm_code[asm_index]) == ReadError)
        {
            printf("SYNTAX ERROR %s \n", assembler->asm_code[asm_index]);
        }
        printf("native index %lu, asm_index %lu size %lu code %d\n", assembler->instruction_pointer, asm_index, assembler->size, 
            assembler->native_code[assembler->instruction_pointer]);
    }
}

assembler_err NativeTranslator(asm_t* assembler, char* assembler_text)
{

    args_fn op_arg[] = {ComparePush, ComparePopR, ComparePushR, CompareJump};
    operation operation [] = 
    {
        {.op_name = "POP", .operation_code = OP_POP},
        {.op_name = "DUMP", .operation_code = OP_DUMP},
        {.op_name = "MUL", .operation_code = OP_MUL},
        {.op_name = "SUB", .operation_code = OP_SUB},
        {.op_name = "OUT", .operation_code = OP_OUT},
        {.op_name = "DIV", .operation_code = OP_DIV},
        {.op_name = "HLT", .operation_code = OP_HLT}
    };
    
    for (size_t operation_index = 0; operation_index < 7; operation_index++)
    {
        if (strcmp(assembler_text, operation[operation_index].op_name) == 0)
        {
            assembler->native_code[assembler->instruction_pointer] = operation[operation_index].operation_code;
            return NoErr;
        }
    }
    if (ComparePush(assembler_text, assembler))
    {
        return NoErr; 
    }
    if (ComparePopR(assembler_text, assembler))
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
    if(strncmp(assembler_text, "PUSHR", 5) == 0)
    {  
        int reg = (int)assembler_text[6] - (int)'A'; // specific of processor
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
        int reg = (int)assembler_text[5] - (int)'A'; // specific of processor
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
        if (number[0] = ':')
        {
            
        }
        else 
        {
            assembler->native_code[++assembler->instruction_pointer] = atoi(number);
        }
        assembler->size += 1;
        return true;
    }
    return false;
}
bool CompareJB(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "JB", 3) == 0)
    {  
        char* number = assembler_text + 2;
        assembler->native_code = (int*)realloc(assembler->native_code, (assembler->size + 1) * sizeof(int));
        assembler->native_code[assembler->instruction_pointer] = OP_JB;
        if (number[0] = ':')
        {
            
        }
        else 
        {
            assembler->native_code[++assembler->instruction_pointer] = atoi(number);
        }
        assembler->size += 1;
        return true;
    }
    return false;
}
