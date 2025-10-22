#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_to_native_code.h"

void FirstPass(asm_t* assembler)
{
    assembler->instruction_pointer = 0;
    for (size_t instruction_index = 0; instruction_index < assembler->size_file; instruction_index++)
    {
        for (size_t index = 0; index < op_args_count; index++)
        {
            if((strlen(assembler->asm_code[instruction_index]) > strlen(op_arg[index].op_name)) &
            (strncmp(assembler->asm_code[instruction_index], op_arg[index].op_name, strlen(op_arg[index].op_name)) == 0))  
            {
                printf("%s\n", assembler->asm_code[instruction_index]);
                assembler->native_code = (int*)realloc(assembler->native_code, (assembler->size + 1) * sizeof(int));
                ++assembler->size;
                ++assembler->instruction_pointer;
                break;
            }
        }

        if(assembler->asm_code[instruction_index][0] == ':')
        {
            int label_index = atoi(assembler->asm_code[instruction_index] + 1);
            printf("label %d\n", label_index);
            labels[label_index] = assembler->instruction_pointer;
            printf("ip %lu\n", assembler->instruction_pointer);
            continue;
        }
        ++assembler->instruction_pointer;
    }
}

assembler_err ConvertToNative(asm_t* assembler)
{
    FirstPass(assembler);
    assembler->instruction_pointer = 0;
    for (size_t asm_index = 0; assembler->instruction_pointer < assembler->size; asm_index++, assembler->instruction_pointer++)
    {    
        if (assembler->asm_code[asm_index] [0] == '\0' || assembler->asm_code[asm_index][0] == ':')
        {
            continue;
        }
        
        if(NativeTranslator(assembler, assembler->asm_code[asm_index]) == SyntaxError)
        {
            printf("SYNTAX ERROR assembler.asm:%lu \n %s\n", asm_index, assembler->asm_code[asm_index]);
            return SyntaxError;
        }
    }
    return NoErr;
}

assembler_err NativeTranslator(asm_t* assembler, char* assembler_text)
{    
    for (size_t operation_index = 0; operation_index < simple_op_count; operation_index++)
    {
        if (strcmp(assembler_text, operation[operation_index].op_name) == 0)
        {
            assembler->native_code[assembler->instruction_pointer] = operation[operation_index].operation_code;
            return NoErr;
        }
    }
    for (size_t function_index = 0; function_index < op_args_count; function_index++) 
    {
        if (op_arg[function_index].fn(assembler_text, assembler))
        {
            return NoErr; 
        }   
    }
    return SyntaxError;
}

bool ComparePush(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "PUSH ", 5) == 0)
    {  
        char* number = assembler_text + 4;
        assembler->native_code[assembler->instruction_pointer] = OP_PUSH; 
        assembler->native_code[++assembler->instruction_pointer] = atoi(number);
        return true;
    }
    return false;
}

bool ComparePushR(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "PUSHR", 5) == 0)
    {  
        int reg = (int)assembler_text[6] - (int)'A'; // specific of processor
        assembler->native_code[assembler->instruction_pointer] = OP_PUSHR; 
        assembler->native_code[++assembler->instruction_pointer] = reg;
        return true;
    }
    return false;
}

bool ComparePopR(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "POPR", 4) == 0)
    {  
        int reg = (int)assembler_text[5] - (int)'A'; // specific of processor
        assembler->native_code[assembler->instruction_pointer] = OP_POPR; 
        assembler->native_code[++assembler->instruction_pointer] = reg;
        return true;
    }
    return false;
}

bool CompareJump(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "JMP", 3) == 0)
    {  
        char* number = assembler_text + 4;
        assembler->native_code[assembler->instruction_pointer] = OP_JMP;
        if (number[0] == ':')
        {
            assembler->native_code[++assembler->instruction_pointer] = (int)labels[atoi(number + 1)];

        }
        else 
        {
            assembler->native_code[++assembler->instruction_pointer] = atoi(number);
        }
        return true;
    }
    return false;
}
bool CompareJB(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "JB", 2) == 0)
    {  
        char* number = assembler_text + 3;
        assembler->native_code[assembler->instruction_pointer] = OP_JB;
        if (number[0] == ':')
        {
           assembler->native_code[++assembler->instruction_pointer] = (int)labels[atoi(number + 1)];
        }
        else 
        {
            assembler->native_code[++assembler->instruction_pointer] = atoi(number);
        }
        return true;
    }
    return false;
}
bool CompareCall(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "CALL", 4) == 0)
    {  
        char* number = assembler_text + 5;
        assembler->native_code[assembler->instruction_pointer] = OP_CALL;
        if (number[0] == ':')
        {
           assembler->native_code[++assembler->instruction_pointer] = (int)labels[atoi(number + 1)];
        }
        else 
        {
            assembler->native_code[++assembler->instruction_pointer] = atoi(number);
        }
        return true;
    }
    return false; 
}

bool PopM(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "POPM", 4) == 0)
    {  
        char* argument = assembler_text + 5;
        char* reg = NULL;
        assembler->native_code[assembler->instruction_pointer] = OP_POPM;
        sscanf("[%s]", reg);
        return true;
    }
    return false; 
}

bool PushM(char* assembler_text, asm_t* assembler)
{
    if(strncmp(assembler_text, "PushM", 5) == 0)
    {  
        char* argument = assembler_text + 6;
        char* reg = NULL;
        assembler->native_code[assembler->instruction_pointer] = OP_POPM;
        sscanf("[%s]", reg);
        return true;
    }
    return false; 
}