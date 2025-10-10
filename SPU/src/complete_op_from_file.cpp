#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "complete_op_from_file.h"

void RunCode(processor_t* spu)
{
    for (; spu->instruction_pointer < spu->size; spu->instruction_pointer++)
    {
        CallOperation(spu);
    }
    
}

void CallOperation(processor_t* spu)
{
    if(spu->read_data[spu->instruction_pointer] == OP_PUSH)
    {
        StackPush(&spu->stack_data, spu->read_data[spu->instruction_pointer++]);
    }
    
    else if(spu->read_data[spu->instruction_pointer] == OP_POP)
    {
        printf("%d\n", StackPop(&spu->stack_data));
    }
    
    else if(spu->read_data[spu->instruction_pointer] == OP_DUMP)
    {
        StackDump(&spu->stack_data);
    }
    else if (spu->read_data[spu->instruction_pointer] == OP_MUL)
    {
        StackMul(&spu->stack_data);
    }
    else if (spu->read_data[spu->instruction_pointer] == OP_SUB)
    {
        StackSub(&spu->stack_data);
    }
    else
    {
        printf("SYNTAX ERROR\n");
    }
}