#include <stdio.h>

int main(int argc, char const *argv[])
{
    double df_arrA[8];
    double df_arrB[8];
    int i_seq;

    printf("Enter eight numbers:\n");

    // 用来输入arrA, arrB数组的第一个元素的数据
    scanf("%d", &df_arrA[0]);
    df_arrB[0] = df_arrA[0];

    for (i_seq = 1; i_seq < 8; i_seq++)
    {
        scanf("%d", &df_arrA[i_seq]);

        df_arrB[i_seq] = df_arrB[i_seq - 1] + df_arrA[i_seq]; // arrB数组的第2个元素是arrB数组的第1个元素与arrA数组的第2个元素之和
    }

    for (i_seq = 0; i_seq < 8; i_seq++)
    {
        printf("%4d\t", df_arrA[i_seq]);
    }
    printf("\n");
    for (i_seq = 0; i_seq < 8; i_seq++)
    {
        printf("%4d\t", df_arrB[i_seq]);
    }

    return 0;
}
