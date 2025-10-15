#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "complete_op_from_file.h"
#include "operation.h"


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
    operation simple_op[] = 
    {
        {.operation_code = OP_DUMP, .operation = StackDump},
        {.operation_code = OP_MUL, .operation = StackMul},
        {.operation_code = OP_DIV, .operation = StackDiv},
        {.operation_code = OP_ADD, .operation = StackAdd},
        {.operation_code = OP_SUB, .operation = StackSub},
        
    };
    
    for (size_t index = 0; index < 5; index++)
    {
        if(spu->read_data[spu->instruction_pointer] == simple_op[index].operation_code)
        {
            printf("SUCCESS op_index %d\n", simple_op[index].operation_code);
            simple_op[index].operation(&spu->stack_data);
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
    else if (spu->read_data[spu->instruction_pointer] == OP_POPR)
    {
        StackPOPR(spu, spu->read_data[++spu->instruction_pointer]);
    }
    else if (spu->read_data[spu->instruction_pointer] == OP_PUSHR)
    {
        StackPUSHR(spu, spu->read_data[++spu->instruction_pointer]);
    }
    else if (spu->read_data[spu->instruction_pointer] == OP_JMP)
    {
        StackJump(spu, spu->read_data[++spu->instruction_pointer]);
    }
    else
    {
        printf("SYNTAX ERROR ip\n"); // TODO Return sth
    }
}