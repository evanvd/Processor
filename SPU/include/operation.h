#include <stdio.h>
#include "stack.h"

#ifndef OPERATION_H
#define OPERATION_H

void StackPush(stack_t* stk, double element);
double StackPop(stack_t* stk);

void CallFromConsole(stack_t* stk, char* console_input);
void StackMul(stack_t* stk);
void StackSub(stack_t* stk);
void StackAdd(stack_t* stk);
void StackDiv(stack_t* stk);
void StackPUSHR(processor_t* spu, int reg);
void StackPOPR(processor_t* spu, int reg);

void StackJump(processor_t* spu, int adr);
void StackJB (processor_t* spu, int adr);

void StackRet(processor_t* spu);
void StackCall(processor_t* spu, int adr);
#endif