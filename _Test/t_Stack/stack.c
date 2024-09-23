#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_MAX_SIZE (10)
#define STACK_ERROR_CODE (-1)

typedef struct _IntSTACK
{
    const int *data;
    int *top;
    const int *limit;
} INTSTACK;

INTSTACK *initStack(int iArr[], int iSize, INTSTACK *pIntStack);
int pushStack(int iData, INTSTACK *pIntStack);
int popStack(INTSTACK *pIntStack);
int isEmptyStack(INTSTACK *pIntStack);
int getStackSize(INTSTACK *pIntStack);
int getStackTop(INTSTACK *pIntStack);

void test_printStackData(INTSTACK *pIntStack, int count)
{
    fprintf(stdout, "%2d:  ", getStackTop(pIntStack));

    for (int i = 0; i < count; i++)
        fprintf(stdout, "%02d ", pIntStack->data[i]);
    putchar('\n');
}

int main(int argc, char const *argv[])
{
    int iArr[STACK_MAX_SIZE];
    memset((int *)iArr, 0, STACK_MAX_SIZE);

    INTSTACK stack;
    initStack(iArr, 10, &stack);
    test_printStackData(&stack, 10);

    for (int i = 1; i <= 10; i++)
    {
        pushStack(i, &stack);
        test_printStackData(&stack, 10);
    }

    while (!isEmptyStack(&stack))
    {
        popStack(&stack);
        test_printStackData(&stack, 10);
    }

    for (int i = 11; i <= 20; i++)
    {
        pushStack(i, &stack);
        test_printStackData(&stack, 10);
    }

    return 0;
}

INTSTACK *initStack(int iArr[], int iSize, INTSTACK *pIntStack)
{
    if (iArr == NULL || pIntStack == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while initialing the stack.\n\
            Null pointer.\n");
        return NULL;
    }

    *pIntStack = (INTSTACK){
        .data = iArr,
        .top = iArr - 1,
        .limit = iArr + (iSize - 1)};

    return pIntStack;
}

int pushStack(int iData, INTSTACK *pStack)
{
    if (pStack == NULL || pStack->data == NULL || pStack->limit == NULL || pStack->top == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while pushing data onto the stack.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    if (pStack->top >= pStack->limit || pStack->top < (pStack->data - 1))
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

    *(++pStack->top) = iData;

    return 0;
}

int popStack(INTSTACK *pIntStack)
{
    if (pIntStack == NULL || pIntStack->data == NULL || pIntStack->top == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while popping data from the stack.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    if (pIntStack->top < pIntStack->data)
    {
        fprintf(stderr, "\
[ERROR]     Empty stack.\n\
            No data popped from the stack.\n");
        return STACK_ERROR_CODE;
    }

    int iRetVal = *(pIntStack->top--);
    return iRetVal;
}

int isEmptyStack(INTSTACK *pIntStack)
{
    if (pIntStack == NULL || pIntStack->data == NULL || pIntStack->limit == NULL || pIntStack->top == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Cannot check if the stack is empty.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    if (pIntStack->top == pIntStack->data - 1)
    {
        return 1;
    }
    else if (pIntStack->top >= pIntStack->data && pIntStack->top <= pIntStack->limit)
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

int getStackSize(INTSTACK *pIntStack)
{
    if (pIntStack == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Unable to get the stack size.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    return pIntStack->top - pIntStack->data + 1;
}

int getStackTop(INTSTACK *pIntStack)
{
    if (pIntStack == NULL || pIntStack->data == NULL || pIntStack->limit == NULL || pIntStack->top == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Unable to get data at the top of the stack.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    if (pIntStack->top >= pIntStack->data && pIntStack->top <= pIntStack->limit)
    {
        return *pIntStack->top;
    }
    else if (pIntStack->top == pIntStack->data - 1)
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
