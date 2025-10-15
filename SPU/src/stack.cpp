#include "stack.h"
#include <assert.h>
#include <string.h>

void StackInit(stack_t* stk,size_t capacity)
{
    stk->capacity = capacity;
    stk->stack = (int*)calloc(stk->capacity + 2, sizeof(int));

    if(stk->stack == NULL)
    {
        stk->stack_error = Nullstack;
        return;
    }

    stk->stack[0] = CANARY_VALUE;

    for (size_t index = 2; index <= stk->capacity; index++) 
    {
        stk->stack[index] = POISON_VALUE;
    }

    stk->stack[stk->capacity + 1] = CANARY_VALUE;
}

stackError StackVerify(stack_t* stk) // TODO verify in main
{
    if (stk == NULL) return Nullstack;
    if (stk->stack == NULL) return Nullstack;
    
    if (stk->stack[stk->capacity + 1] != CANARY_VALUE)
    {
        printf("Right canary value has been changed\n");
        stk->stack_error = RightCanaryErr;  
        return RightCanaryErr;      
    }

    else if (stk->stack[0] != CANARY_VALUE)
    {
        printf("Left canary value has been changed\n");
        stk->stack_error = LeftCanaryErr;
        return LeftCanaryErr;
    }
    return NoErr;
}

void StackDump(stack_t* stk)
{
    StackVerify(stk);
    printf("\ncapacity - %lu\n", stk->capacity);
    printf("size - %lu\n", stk->size);

    printf("Left canary %d  should be 12648430\n\n", stk->stack[0]);
    for (size_t index = 1; index <= stk->size; index++)
    {
        printf("stack[%lu] = %d\n", index, stk->stack[index]);
    }
    printf("\nRight canary %d  should be 12648430\n", stk->stack[stk->capacity + 1]);
    StackVerify(stk);   
}

void StackDestroy(stack_t* stk)
{
    free(stk->stack);
    stk->size = POISON_VALUE;
    stk->capacity = POISON_VALUE;
}