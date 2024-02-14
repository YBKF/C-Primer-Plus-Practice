#include <stdio.h>
#include <stdbool.h>

bool isOdd(int i_input);
bool isEven(int i_input);

int main(int argc, char const *argv[])
{
    int i_ceiling;    // 上限（用户输入）
    int i_seq;        // 分母
    double df_result; // 计算结果，需要输出
    double df_resultA, df_resultB;

    printf("Enter a ceiling: ");

    // i_seq = 1;
    // df_result = 0;
    // while (i_seq <= i_ceiling)
    // {
    //     df_result += 2 / i_seq;
    //     i_seq += 2;
    // }

    while (scanf("%d", &i_ceiling) && i_ceiling > 0)
    {
        for (df_resultA = 0.0, df_resultB = 0.0, i_seq = 1;
             i_seq <= i_ceiling;
             i_seq++)
        {
            df_resultA += 1.0 / i_seq;

            if (true == isOdd(i_seq))
            {
                df_resultB += 1.0 / i_seq;
            }
            else
            {
                df_resultB -= 1.0 / i_seq;
            }
        }

        for (df_result = 0.0, i_seq = 1;
             i_seq <= i_ceiling;
             i_seq += 2)
        {
            df_result += 2.0 / i_seq;
        }
        printf("ResultA:%lf\nResultB:%lf\nResult(A+B): %lf\n\n", df_resultA, df_resultB, df_result);
        printf("Enter next number (<=0 to exit): ");
    }

    return 0;
}

bool isOdd(int i_input)
{
    return i_input % 2 == 1;
}

bool isEven(int i_input)
{
    return i_input % 2 == 0;
}