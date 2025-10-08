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

void StackPush(stack_t* stk, int element)
{
    if (stk->capacity == stk->size)//TODO fix compare size
    {
        stk->stack = (int*)realloc(stk->stack,stk->size);
        stk->capacity++;
        stk->stack[stk->capacity + 1] = CANARY_VALUE;
    }
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

void StackMul(stack_t* stk)
{
    if (stk->size < 2)
    {
        printf("Stack empty\n");
        return ;
    }
    
    int num1 = StackPop(stk); // TODO FIX POP/MUL
    printf("%d\n", num1);
    int num2 = StackPop(stk);
    printf("%d\n", num2);
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

void CallFromConsole(stack_t* stk, char* console_input)
{
    if(strcmp(console_input, "PUSH") == 0)
    {
        int push_stack;
        scanf("%d",&push_stack);
        StackPush(stk, push_stack);
    }
    
    else if(strcmp(console_input,"POP") == 0)
    {
        printf("%d\n", StackPop(stk));
    }
    
    else if(strcmp(console_input, "DUMP") == 0)
    {
        StackDump(stk);
    }
    else if (strcmp(console_input, "MUL") == 0)
    {
        StackMul(stk);
    }
    else if (strcmp(console_input, "SUB") == 0)
    {
        StackSub(stk);
    }
    else
    {
        printf("unknown command\n");
    }
}

//TODO verify