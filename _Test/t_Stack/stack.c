#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX_SIZE (10)

typedef struct _IntSTACK
{
    int *data;
    int *top;
    const int *limit;
} INTSTACK;

INTSTACK *initStack(int iArr[], int iSize, INTSTACK *pIntStack);
void pushStack(int iData, INTSTACK *pIntStack);
int popStack(INTSTACK *pIntStack);
int isEmptyStack(INTSTACK *pIntStack);
int getStackSize(INTSTACK *pIntStack);
int getStackTop(INTSTACK *pIntStack);

int main(int argc, char const *argv[])
{
    int arr[STACK_MAX_SIZE];

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

void pushStack(int iData, INTSTACK *pIntStack)
{
    if (pIntStack == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while pushing data onto the stack.\n\
            Null pointer.\n");
        return;
    }

    if (pIntStack->top >= pIntStack->limit || pIntStack->top < (pIntStack->data - 1))
    {
        if (pIntStack->top == pIntStack->limit)
        {
            fprintf(stderr, "\
[ERROR]     The stack is full.\n");
        }
        else
        {
            fprintf(stderr, "\
[ERROR]     The stack has overflowed.\n");
        }
        return;
    }

    *(++pIntStack->top) = iData;
}

int popStack(INTSTACK *pIntStack)
{
    if (pIntStack == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while popping data from the stack.\n\
            Null pointer.\n");
        return -1;
    }

    if (pIntStack->top < pIntStack->data)
    {
        fprintf(stderr, "\
[ERROR]     Empty stack.\n\
            No data popped from the stack.\n");
        return -1;
    }

    int iRetVal = *(pIntStack->top--);
    return iRetVal;
}

int isEmptyStack(INTSTACK *pIntStack)
{
    if (pIntStack == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Cannot check if the stack is empty.\n\
            Because of the parameter is a null pointer.\n");
        return -1;
    }

    if (pIntStack->top == (pIntStack->data - 1))
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
        return -1;
    }
}

int getStackSize(INTSTACK *pIntStack)
{
    if (pIntStack == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Cannot got size of the stack.\n\
            Because of the parameter is a null pointer.\n");
        return -1;
    }

    return pIntStack->top - pIntStack->data
}

int getStackTop(INTSTACK *pIntStack)
{
}
