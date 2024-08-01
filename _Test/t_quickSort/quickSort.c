#include <stdio.h>

static void insertSort(int *piArr[], int iLow, int iHigh);
static int partition(int *piArr[], int iLow, int iHigh);
static void quickSort(int *piArr[], int iLow, int iHigh);
void sort(int *piArr[], int iMaxCount);

static void insertSort(int *piArr[], int iLow, int iHigh)
{
    if (piArr == NULL)
    {
        fputs("ERROR: Found a null pointer at function insertSort.\n", stderr);
        return;
    }

    int *piBuf;

    for (int i = iLow + 1; i <= iHigh; i++)
        for (int j = i; j > iLow && *piArr[j] < *piArr[j - 1]; j--)
        {
            piBuf = piArr[j];
            piArr[j] = piArr[j - 1];
            piArr[j - 1] = piBuf;
        }
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

    // if (iHigh <= iLow)
    //     return;

    if (iHigh <= iLow + 5)
    {
        insertSort(piArr, iLow, iHigh);
        return;
    }

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
