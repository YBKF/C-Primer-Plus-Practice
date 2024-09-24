#ifndef _INC_STACK_H
#define _INC_STACK_H

#define STACK_MAX_SIZE (10)
#define STACK_ERROR_CODE (-1)

// Edit item type here
typedef int Item;

typedef struct _stack
{
    const Item *itemList;
    Item *top;
    const Item *limit;
} STACK;

STACK *initStack(Item arr[], int iSize, STACK *pStack);
Item pushStack(Item itemData, STACK *pStack);
Item popStack(STACK *pStack);
int isEmptyStack(STACK *pStack);
int getStackSize(STACK *pStack);
Item getStackTop(STACK *pStack);

#endif