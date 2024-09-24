#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void test_printStackData(STACK *pIntStack, int count)
{
    Item stackTop = 0;

    if ((stackTop = getStackTop(pIntStack)) == STACK_ERROR_CODE)
        fprintf(stdout, "error:  ");
    else
        fprintf(stdout, "%2d:  ", getStackTop(pIntStack));

    for (int i = 0; i < count; i++)
        fprintf(stdout, "%02d ", pIntStack->itemList[i]);
    putchar('\n');
}

int main(int argc, char const *argv[])
{
    Item iArr[STACK_MAX_SIZE];
    memset((Item *)iArr, 0, STACK_MAX_SIZE * sizeof(Item));

    STACK stack;
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
