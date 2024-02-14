#include <stdio.h>
#include <string.h>

void copydoubleArr(double df_arr_target[], double df_arr_source[], int count);

void sortArrbyReverse(double df_arr_source[], int count);

int main(int argc, char const *argv[])
{
    double df_arr[5] = {4.4, 2.2, 2.2, 3.3, 5.5};

    printf("Before: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%lf ", df_arr[i]);
    }
    putchar('\n');

    sortArrbyReverse(df_arr, 5);

    printf("After: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%lf ", df_arr[i]);
    }
    putchar('\n');

    return 0;
}

void copydoubleArr(double df_arr_target[], double df_arr_source[], int count)
{
    size_t size = (size_t)(8 * count);
    memcpy(df_arr_target, df_arr_source, size);
}

void sortArrbyReverse(double df_arr_source[], int count)
{
    int i_op_outter, i_op_inner; // 定义两个用于操作内外两个for循环的操作数
    double df_arr_temp[count];   // 为了便于排序，不能改变源数组，故定义一个临时数组
    int i_seq_temp;              // 后面作为临时数组数组下标，用于给临时数组排序

    for (i_op_outter = 0, i_seq_temp = 0; i_op_outter < count; i_op_outter++)
    {
        for (i_op_inner = 0; i_op_inner < count; i_op_inner++)
        {
            if (df_arr_source[i_op_outter] < df_arr_source[i_op_inner])
            {
                i_seq_temp++;
            }

            /**
             * 从当前元素向后检测，如检测到有与当前元素的值相等的元素值则 临时顺序+1
             */
            if (df_arr_source[i_op_outter] == df_arr_source[i_op_inner] && i_op_inner > i_op_outter)
            {
                i_seq_temp++;
            }
        }
        df_arr_temp[i_seq_temp] = df_arr_source[i_op_outter];
        i_seq_temp = 0;
    }

    copydoubleArr(df_arr_source, df_arr_temp, count);
}
