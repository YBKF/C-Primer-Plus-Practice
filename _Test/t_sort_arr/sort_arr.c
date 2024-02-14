#include <stdio.h>
#include <string.h>

void copyintArr(int iArr_target[], int iArr_source[], int count);

void sortArrByReverse(int iArr_source[], int count);

int main(int argc, char const *argv[])
{
    int i_arr[7] = {4, 2, 2, 2, 2, 1, 3};
    int i_arrb[7];

    // printf("i_arr size: %zd\n", sizeof i_arr);

    // copyintArr(i_arrb, i_arr, 7);
    // memcpy(i_arrb, i_arr, sizeof i_arr);

    sortArrByReverse(i_arr, 7);

    printf("arr:");
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", i_arr[i]);
    }
    putchar('\n');

    return 0;
}

void copyintArr(int iArr_target[], int iArr_source[], int count)
{
    size_t size = (size_t)(4 * count);
    memcpy(iArr_target, iArr_source, size);
}

void sortArrByReverse(int iArr_source[], int count)
{
    int iOP_outter, iOP_inner; // 定义两个用于操作内外两个for循环的操作数
    int iArr_temp[count];      // 为了便于排序，不能改变源数组，故定义一个临时数组
    int iSeq_temp;             // 后面作为临时数组数组下标，用于给临时数组排序

    for (iOP_outter = 0, iSeq_temp = 0; iOP_outter < count; iOP_outter++)
    {
        for (iOP_inner = 0; iOP_inner < count; iOP_inner++)
        {
            if (iArr_source[iOP_outter] < iArr_source[iOP_inner])
                iSeq_temp++;

            /**
             * 从当前元素向后检测，如检测到有与当前元素的值相等的元素值则 临时顺序+1
             */
            if (iArr_source[iOP_outter] == iArr_source[iOP_inner] && iOP_inner > iOP_outter)
                iSeq_temp++;

            printf("No.%d inspect %d and %d, seq: %d\n", iOP_outter, iArr_source[iOP_outter], iArr_source[iOP_inner], iSeq_temp);
        }
        printf("Done!\n");
        iArr_temp[iSeq_temp] = iArr_source[iOP_outter];
        iSeq_temp = 0;
    }

    copyintArr(iArr_source, iArr_temp, count);

    printf("arr_temp:");
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", iArr_temp[i]);
    }
    putchar('\n');
}