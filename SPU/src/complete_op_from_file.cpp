#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "complete_op_from_file.h"

void RunCode(processor_t* spu)
{
    for (; spu->operation_index < spu->size; spu->operation_index++)
    {
        CallOperation(spu);
    }
    
}

void CallOperation(processor_t* spu)
{
    if(spu->read_data[spu->operation_index] == OP_PUSH)
    {
        StackPush(&spu->stack_data, spu->read_data[spu->operation_index++]);
    }
    
    else if(spu->read_data[spu->operation_index] == OP_POP)
    {
        printf("%d\n", StackPop(&spu->stack_data));
    }
    
    else if(spu->read_data[spu->operation_index] == OP_DUMP)
    {
        StackDump(&spu->stack_data);
    }
    else if (spu->read_data[spu->operation_index] == OP_MUL)
    {
        StackMul(&spu->stack_data);
    }
    else if (spu->read_data[spu->operation_index] == OP_SUB)
    {
        StackSub(&spu->stack_data);
    }
    else
    {
        printf("unknown command\n");
    }
}