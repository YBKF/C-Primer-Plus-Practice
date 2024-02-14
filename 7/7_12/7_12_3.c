#include <stdio.h>
#include <stdbool.h>

bool isOddnumber(int i_input_num);
bool isEvennumber(int i_input_num);

int main(int argc, char const *argv[])
{
    int i_num_even, i_num_odd; // 偶数的个数，奇数的个数
    int i_total_even;          // 所有偶数的总值
    int i_total_odd;           // 所有奇数的总值
    float i_aver_even;         // 所有偶数的平均值
    float i_aver_odd;          // 所有奇数的平均值

    int i_entered_buffer;
    int i_entered_data;

    i_num_even = 0;
    i_num_odd = 0;
    i_total_even = 0;
    i_total_odd = 0;

    while (scanf("%d", &i_entered_buffer))
    {
        if (0 == i_entered_buffer)
        {
            break;
        }
        else
        {
            i_entered_data = i_entered_buffer;
        }

        if (0 == i_entered_data % 2)
        {
            i_num_even++;
            i_total_even += i_entered_data;
        }
        else
        {
            i_num_odd++;
            i_total_odd += i_entered_data;
        }

        printf("num_even=%d, num_odd=%d\n", i_num_even, i_num_odd);
    }

    if ((0 == i_num_even) && (0 == i_num_odd))
    {
        printf("Not numbers entered.");
        return 0;
    }

    if (0 != i_num_even)
    {
        i_aver_even = (float)i_total_even / (float)i_num_even;
    }

    if (0 != i_num_odd)
    {
        i_aver_odd = (float)i_total_odd / (float)i_num_odd;
    }

    printf("total_even=%d\naver_even=%f\ntotal_odd=%d\naver_odd=%f", i_total_even, i_aver_even, i_total_odd, i_aver_odd);

    return 0;
}
