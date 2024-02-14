/**
 * 5.编写一个程序，生成100个1～10范围内的随机数，
 * 并以降序排列（可以把第11章的排序算法稍加改动，便可用于整数排序，这里仅对整数排序）。
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_COUNT 100

void setRandNum(int iArr[], int iTotalNum, int iMin, int iMax);
void setIntArr2PointerArr(int *piAddrArr_target[], int iArr_source[], int iTotalNum);
void sortIntAddrInDesOrder(int *piAddrArr[], int num);

int main(int argc, char const *argv[])
{
    srand((unsigned)time(NULL));

    int iArr[ARRAY_COUNT];
    int *iAddrArr[ARRAY_COUNT];

    setRandNum(iArr, ARRAY_COUNT, 1, 10);
    setIntArr2PointerArr(iAddrArr, iArr, ARRAY_COUNT);
    sortIntAddrInDesOrder(iAddrArr, ARRAY_COUNT);

    printf("arr:");
    for (int i = 0; i < ARRAY_COUNT; i++)
    {
        printf("%d ", *iAddrArr[i]);
    }
    putchar('\n');

    return 0;
}

void setRandNum(int iArr[], int iTotalNum, int iMin, int iMax)
{
    if (!iArr)
    {
        puts("Funcation setRandNum(): NULL Pointer!");
        return;
    }

    if (iTotalNum <= 0)
    {
        puts("Total Number must be greater than 0.");
        return;
    }

    while (iTotalNum)
    {
        iTotalNum--;
        iArr[iTotalNum] = (rand() % iMax + iMin);
    }
}

void setIntArr2PointerArr(int *piAddrArr_target[], int iArr_source[], int iTotalNum)
{
    if (!piAddrArr_target || !iArr_source)
    {
        puts("Funcation setRandNum(): NULL Pointer!");
        return;
    }

    if (iTotalNum <= 0)
    {
        puts("Total Number must be greater than 0.");
        return;
    }

    while (iTotalNum)
    {
        iTotalNum--;
        piAddrArr_target[iTotalNum] = &iArr_source[iTotalNum];
    }
}

void sortIntAddrInDesOrder(int *piAddrArr[], int num)
{
    int *temp;
    int top, seek;

    for (top = 0; top < num - 1; top++)
        for (seek = top + 1; seek < num; seek++)
            if (*piAddrArr[top] < *piAddrArr[seek])
            {
                temp = piAddrArr[top];
                piAddrArr[top] = piAddrArr[seek];
                piAddrArr[seek] = temp;
            }
}
