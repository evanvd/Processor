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
    {.operation_code = OP_OUT, .operation = StackDump}

};

static arg_operation args_operation [] =
{
    {.operation_code = OP_JMP, .operation = StackJump},
    {.operation_code = OP_PUSHR, .operation = StackPUSHR},
    {.operation_code = OP_POPR, .operation = StackPOPR},
    {.operation_code = OP_JB, .operation = StackJB},
    {.operation_code = OP_CALL, .operation = StackCall}
};

const size_t simple_op_count = 6;
const size_t args_op_count = 5;

void RunCode(processor_t* spu)
{
    for (; spu->instruction_pointer < spu->size; spu->instruction_pointer++)
    {
        printf("ip %lu op %d\n", spu->instruction_pointer, spu->read_data[spu->instruction_pointer]);
        if(CallOperation(spu) == Exit)
        {
            printf("success");
            break;
        }
    }
}

stackError CallOperation(processor_t* spu)
{
    for (size_t index = 0; index < simple_op_count; index++)
    {
        if(spu->read_data[spu->instruction_pointer] == simple_op[index].operation_code)
        {
            printf("SUCCESS op_index %d\n", simple_op[index].operation_code);
            simple_op[index].operation(&spu->stack_data);
            return NoErr;
        }
    }
    
    for (size_t index = 0; index < args_op_count; index++)
    {
        if(spu->read_data[spu->instruction_pointer] == args_operation[index].operation_code)
        {
            args_operation[index].operation(spu, spu->read_data[++spu->instruction_pointer]);
            return NoErr;
        }
    }
    
    if(spu->read_data[spu->instruction_pointer] == OP_PUSH)
    {
        StackPush(&spu->stack_data, spu->read_data[++spu->instruction_pointer]);
        return NoErr;
    }  
    else if(spu->read_data[spu->instruction_pointer] == OP_RET)
    {
        StackRet(spu);
        return NoErr;
    }
    else if (spu->read_data[spu->instruction_pointer] == OP_HLT)
    {
        return Exit;
    }
    
    printf("SYNTAX ERROR ip\n");
    return SyntaxError;
}