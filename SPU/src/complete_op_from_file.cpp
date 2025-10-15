#include <stdio.h>
#include <stdlib.h>
#include "complete_op_from_file.h"

static operation simple_op[] = 
{
    {.operation_code = OP_DUMP, .operation = StackDump},
    {.operation_code = OP_MUL, .operation = StackMul},
    {.operation_code = OP_DIV, .operation = StackDiv},
    {.operation_code = OP_ADD, .operation = StackAdd},
    {.operation_code = OP_SUB, .operation = StackSub},
    
};

static arg_operation args_operation [] =
{
    {.operation_code = OP_JMP, .operation = StackJump},
    {.operation_code = OP_PUSHR, .operation = StackPUSHR},
    {.operation_code = OP_POPR, .operation = StackPOPR},
    {.operation_code = OP_JB, .operation = StackJB},
};

const size_t simple_op_count = 5;
const size_t args_op_count = 4;

void RunCode(processor_t* spu)
{
    for (; spu->instruction_pointer < spu->size; spu->instruction_pointer++)
    {
        printf("ip %lu op %d\n", spu->instruction_pointer, spu->read_data[spu->instruction_pointer]);
        CallOperation(spu);
    }
}

void CallOperation(processor_t* spu)
{
    extern operation simple_op[];
    extern arg_operation args_operation [];

    for (size_t index = 0; index < simple_op_count; index++)
    {
        if(spu->read_data[spu->instruction_pointer] == simple_op[index].operation_code)
        {
            printf("SUCCESS op_index %d\n", simple_op[index].operation_code);
            simple_op[index].operation(&spu->stack_data);
        }
    }
    
    for (size_t index = 0; index < args_op_count; index++)
    {
        if(spu->read_data[spu->instruction_pointer] == args_operation[index].operation_code)
        {
            args_operation[index].operation(spu, spu->read_data[++spu->instruction_pointer]);
        }
    }
    
    if(spu->read_data[spu->instruction_pointer] == OP_PUSH)
    {
        StackPush(&spu->stack_data, spu->read_data[++spu->instruction_pointer]);
    }  
    else if(spu->read_data[spu->instruction_pointer] == OP_POP)
    {
        printf("%d\n", StackPop(&spu->stack_data));
    }
    else
    {
        printf("SYNTAX ERROR ip\n"); // TODO Return sth
    }
}