#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "stack.h"
#include "operation.h"

enum op_code
{
    OP_POP  = 1,
    OP_DUMP = 2,
    OP_PUSH = 3,
    OP_ADD  = 4,
    OP_SUB  = 5,
    OP_MUL  = 6,
    OP_DIV  = 7,
    OP_OUT  = 8,
    OP_HLT  = 9,
    OP_PUSHR = 42,
    OP_POPR = 33,
    OP_JMP = 50,
    OP_JB = 52,
    OP_CALL = 69,
    OP_RET = 72
};

typedef void (*operation_fn_t) (stack_t*);
typedef void (*opr_args_fn_t) (processor_t*, int);

const int EPS = 10e-6;

struct operation
{
    op_code operation_code;
    operation_fn_t operation = NULL;
};

struct arg_operation
{
    op_code operation_code;
    opr_args_fn_t operation = NULL;
};
void RunCode(processor_t* spu);
stackError CallOperation(processor_t* spu);