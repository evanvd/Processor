#include <stdio.h>
#include "stack.h"

void StackPush(stack_t* data, int element);
int StackPop(stack_t* data);

void CallFromConsole(stack_t* stk, char* console_input);
void StackMul(stack_t* stk);
void StackSub(stack_t* stk);
void StackAdd(stack_t* stk);
void StackDiv(stack_t* stk);
void StackPUSHR(processor_t* spu, int reg);
void StackPOPR(processor_t* spu, int reg);