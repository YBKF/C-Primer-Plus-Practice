#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int partition(int *piArr[], int iLow, int iHigh);
static void quickSort(int *piArr[], int iLow, int iHigh);
void sort(int *piArr[], int iMaxCount);
void printArr(int *piArr[], int iCount);

int main()
{
    int iArr[10] = {54, 73, 72, 26, 35, 13, 17, 56, 88, 10};
    int iArr2[10] = {54, 73, 54, 26, 35, 13, 17, 54, 88, 54};

    int *piArr[10];

    for (int i = 0; i < 10; i++)
    {
        piArr[i] = &iArr[i];
    }
    printArr(piArr, 10);

    sort(piArr, 10);

    printArr(piArr, 10);

    return 0;
}

static int partition(int *piArr[], int iLow, int iHigh)
{
    if (piArr == NULL)
    {
        fputs("ERROR: Found a null pointer at function partition.\n", stderr);
        return EOF;
    }

    int iHead = iLow;
    int iTail = iHigh + 1;
    int *piBuf;

    int *piChosen = piArr[iLow];

    while (1)
    {
        while (*piArr[++iHead] < *piChosen && iHead != iHigh)
            continue;

        while (*piArr[--iTail] > *piChosen && iTail != iLow)
            continue;

        if (iHead >= iTail)
            break;

        piBuf = piArr[iHead];
        piArr[iHead] = piArr[iTail];
        piArr[iTail] = piBuf;
    }

    piBuf = piArr[iLow];
    piArr[iLow] = piArr[iTail];
    piArr[iTail] = piBuf;

    return iTail;
}

static void quickSort(int *piArr[], int iLow, int iHigh)
{
    if (piArr == NULL)
    {
        fputs("ERROR: Found a null pointer at function quickSort.\n", stderr);
        return;
    }

    if (iHigh <= iLow)
        return;

    int iPartVal;

    if ((iPartVal = partition(piArr, iLow, iHigh)) == EOF)
    {
        fputs("ERROR: An error occurred while partitioning the array.\n", stderr);
        return;
    }

    quickSort(piArr, iLow, iPartVal - 1);
    quickSort(piArr, iPartVal + 1, iHigh);
}

/**
 * - [in/out] piArr
 * - [in] iMaxCount
 *
 * 对输入的整型指针数组 piArr 前 iMaxCount 个元素进行排序，按照指针指向的地址的符号整型数值大小进行升序排序。
 * 使用的排序算法是，二分法快速排序
 *
 * [in/out] piArr 应当为一个数组，其中存储的元素类型为整型指针。
 *
 * [in] iMaxCount 通常为数组中元素的总数，应大于 0。
 *
 */
void sort(int *piArr[], int iMaxCount)
{
    if (piArr == NULL)
    {
        fputs("ERROR: Found a null pointer at function sort.\n", stderr);
        return;
    }

    quickSort(piArr, 0, iMaxCount - 1);
}

void printArr(int *piArr[], int iCount)
{
    for (int i = 0; i < iCount; i++)
        printf("%d ", *piArr[i]);
    putchar('\n');
}
