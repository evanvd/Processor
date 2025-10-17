#include <stdio.h> 
#include <stdlib.h>
#ifndef STACK_H
#define STACK_H

const int CANARY_VALUE = 0xC0FFEE;
const int POISON_VALUE = 0xDEAD;


enum stackError 
{
    NoErr = -1,
    Exit = 0,
    LeftCanaryErr = 1,
    RightCanaryErr = 2,
    Nullstack = 3,
    SyntaxError = 4
};

typedef struct stack_t
{
    int* stack = {};
    size_t size = 0;
    size_t capacity = 0;
    stackError stack_error = NoErr;
} stack_t;

struct processor_t
{
    int* read_data = {};
    FILE* native_file = NULL;
    size_t size = 0;
    int regs [50] = {};
    size_t instruction_pointer = 0;
    stack_t ret_addr = {};
    stack_t stack_data = {};
};


void StackInit(stack_t* stk, size_t capacity);
void StackDump(stack_t* stk);
stackError StackVerify(stack_t* stk);
void StackDestroy(stack_t* stk);

#endif 
