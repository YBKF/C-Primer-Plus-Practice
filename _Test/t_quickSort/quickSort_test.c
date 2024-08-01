#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quickSort.h"

#define ARRAY_COUNT 100

void printArr(int *piArr[], int iCount);

int main()
{
    // int iArr[10] = {54, 73, 72, 26, 35, 13, 17, 56, 88, 10};
    // int iArr2[10] = {54, 73, 54, 26, 35, 13, 17, 54, 88, 54};

    int iArr[ARRAY_COUNT];
    int iArr2[ARRAY_COUNT];

    int *piArr[ARRAY_COUNT];
    int *piArr2[ARRAY_COUNT];

    srand((unsigned int)time(NULL));

    for (int i = 0; i < ARRAY_COUNT; i++)
    {
        iArr[i] = rand() % 100 + 1;
        iArr2[i] = rand() % 100 + 1;
    }

    for (int i = 0; i < ARRAY_COUNT; i++)
    {
        piArr[i] = &iArr[i];
        piArr2[i] = &iArr2[i];
    }

    puts("piArr:");

    printArr(piArr, ARRAY_COUNT);

    sort(piArr, ARRAY_COUNT);

    printArr(piArr, ARRAY_COUNT);

    // iArr2
    puts("piArr2:");

    printArr(piArr2, ARRAY_COUNT);

    sort(piArr2, ARRAY_COUNT);

    printArr(piArr2, ARRAY_COUNT);

    return 0;
}

void printArr(int *piArr[], int iCount)
{
    for (int i = 0; i < iCount; i++)
        printf("%d ", *piArr[i]);
    putchar('\n');
}
