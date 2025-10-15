#include <stdio.h>
#include "stack.h"
#include "operation.h"

void StackPush(stack_t* stk, int element)
{
    if (stk->capacity == stk->size)
    {
        stk->stack = (int*)realloc(stk->stack,stk->size);
        stk->capacity++;
        stk->stack[stk->capacity + 1] = CANARY_VALUE;
    }
    printf("\tel %d\n",element);
    stk->size++;
    stk->stack[stk->size] = element;
    StackVerify(stk);    
}


int StackPop(stack_t* stk)
{
    StackVerify(stk);
    if (stk->size < 1)
    {
        printf("Stack empty\n");
        return 0;
    }
    
    int temp = stk->stack[stk->size];
    stk->size--;
    StackVerify(stk);
    return temp;
}
void StackMul(stack_t* stk)
{
    if (stk->size < 2)
    {
        printf("Stack empty\n");
        return ;
    }
    
    int num1 = StackPop(stk); 
    int num2 = StackPop(stk);
    StackPush(stk, num1 * num2);
}

void StackSub(stack_t* stk)
{
    if (stk->size < 2)
    {
        printf("Stack empty\n");
        return ;
    }
    int num1 = StackPop(stk);
    int num2 = StackPop(stk);
    StackPush(stk, num1 - num2);
}

void StackAdd(stack_t* stk)
{
    if (stk->size < 2)
    {
        printf("Stack empty\n");
        return ;
    }
    int num1 = StackPop(stk);
    int num2 = StackPop(stk);
    StackPush(stk, num1 + num2);
}
void StackDiv(stack_t* stk)
{
    if (stk->size < 2)
    {
        printf("Stack empty\n");
        return ;
    }
    int num1 = StackPop(stk);
    int num2 = StackPop(stk);
    StackPush(stk, num1 / num2);
}
void StackPUSHR(processor_t* spu, int reg)
{
    printf("pushr %d\n",reg);
    if (spu->stack_data.capacity == spu->stack_data.size)
    {
        spu->stack_data.stack = (int*)realloc(spu->stack_data.stack,spu->stack_data.size);
        spu->stack_data.capacity++;
        spu->stack_data.stack[spu->stack_data.capacity + 1] = CANARY_VALUE;
    } // TODO error when reg uninit
    spu->stack_data.size++;
    spu->stack_data.stack[spu->stack_data.size] = spu->regs[reg];
    StackVerify(&spu->stack_data);   
}

void StackPOPR(processor_t* spu, int reg)
{
    StackVerify(&spu->stack_data);
    printf("popr %d\n",reg);
    spu->regs[reg] = StackPop(&spu->stack_data); // TODO abort if empty stack
    
    StackVerify(&spu->stack_data);
}

void StackJump(processor_t* spu, int adr)
{
    spu->instruction_pointer = (size_t)adr;
}
void StackJB (processor_t* spu, int adr)
{
    int n1 = StackPop(&spu->stack_data);
    int n2 = StackPop(&spu->stack_data);
    if (n1 < n2)
    {
        spu->instruction_pointer = (size_t)adr;
    }
    
}