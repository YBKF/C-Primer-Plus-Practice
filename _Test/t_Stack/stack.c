#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

STACK *initStack(Item arr[], int iSize, STACK *pStack)
{
    if (arr == NULL || pStack == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while initialing the stack.\n\
            Null pointer.\n");
        return NULL;
    }

    *pStack = (STACK){
        .itemList = arr,
        .top = arr - 1,
        .limit = arr + (iSize - 1)};

    return pStack;
}

Item pushStack(Item itemData, STACK *pStack)
{
    if (pStack == NULL || pStack->itemList == NULL || pStack->limit == NULL || pStack->top == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while pushing data onto the stack.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    if (pStack->top >= pStack->limit || pStack->top < (pStack->itemList - 1))
    {
        if (pStack->top == pStack->limit)
        {
            fprintf(stderr, "\
[ERROR]     The stack is full.\n");
        }
        else
        {
            fprintf(stderr, "\
[ERROR]     The stack has overflowed.\n");
        }
        return STACK_ERROR_CODE;
    }

    *(++pStack->top) = itemData;

    return 0;
}

Item popStack(STACK *pStack)
{
    if (pStack == NULL || pStack->itemList == NULL || pStack->top == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while popping data from the stack.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    if (pStack->top < pStack->itemList)
    {
        fprintf(stderr, "\
[ERROR]     Empty stack.\n\
            No data popped from the stack.\n");
        return STACK_ERROR_CODE;
    }

    Item iRetVal = *(pStack->top--);
    return iRetVal;
}

int isEmptyStack(STACK *pStack)
{
    if (pStack == NULL || pStack->itemList == NULL || pStack->limit == NULL || pStack->top == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Cannot check if the stack is empty.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    if (pStack->top == pStack->itemList - 1)
    {
        return 1;
    }
    else if (pStack->top >= pStack->itemList && pStack->top <= pStack->limit)
    {
        return 0;
    }
    else
    {
        fprintf(stderr, "\
[ERROR]     The stack has overflowed.\n");
        return STACK_ERROR_CODE;
    }
}

int getStackSize(STACK *pStack)
{
    if (pStack == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Unable to get the stack size.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    return pStack->top - pStack->itemList + 1;
}

Item getStackTop(STACK *pStack)
{
    if (pStack == NULL || pStack->itemList == NULL || pStack->limit == NULL || pStack->top == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Unable to get data at the top of the stack.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    if (pStack->top >= pStack->itemList && pStack->top <= pStack->limit)
    {
        return *pStack->top;
    }
    else if (pStack->top == pStack->itemList - 1)
    {
        fprintf(stderr, "\
[ERROR]     Empty stack.\n");
        return STACK_ERROR_CODE;
    }
    else
    {
        fprintf(stderr, "\
[ERROR]     The stack has overflowed.\n");
        return STACK_ERROR_CODE;
    }
}
