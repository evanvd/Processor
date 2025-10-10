#include <stdio.h> 
#include <stdlib.h>
#ifndef STACK_H
#define STACK_H

const int CANARY_VALUE = 0xC0FFEE;
const int POISON_VALUE = 0xDEAD;


enum stackError 
{
    NoErr = -1,
    LeftCanaryErr = 1,
    RightCanaryErr = 2,
    Nullstack = 3
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
    int* read_data ={};
    FILE* native_file = NULL;
    size_t size = 0;
    size_t instruction_pointer = 0;
    int RAX;
    int RBX;
    stack_t stack_data = {};
};



void StackInit(stack_t* stk, size_t capacity);
void StackDump(stack_t* stk);
void StackPush(stack_t* data, int element);
int StackPop(stack_t* data);
void StackDestroy(stack_t* stk);
stackError StackVerify(stack_t* stk);

void CallFromConsole(stack_t* stk, char* console_input);
void StackMul(stack_t* stk);
void StackSub(stack_t* stk);
#endif 
