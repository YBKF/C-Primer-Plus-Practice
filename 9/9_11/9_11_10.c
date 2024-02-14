#include <stdio.h>
#include <math.h>

unsigned int takeDigit(unsigned long ul_num, unsigned long ul_base);

double mod(double df_a, double df_b);

void to_base_n(unsigned long ul_num, unsigned long ul_base);

int main(void)
{
    unsigned long ul_decimal;
    unsigned u_base;

    printf("Enter a decimal-number to convert to abitrary-base numbers.\n");
    printf("Decimal: ");
    scanf("%u", &ul_decimal);
    printf("Base: ");
    scanf("%u", &u_base);

    to_base_n(ul_decimal, u_base);

    return 0;
}

/**
 * 根据要求的进制(第二个参数)计算第一个参数的总位数。
 * 为保证精确度第一个参数中输入的数字须与第二个参数相对应.
 */
unsigned int takeDigit(unsigned long ul_num, unsigned long ul_base)
{
    unsigned u_digit; // 数的位数

    for (u_digit = 1;
         (ul_num / (unsigned long)pow((double)ul_base, (double)u_digit)) >= 1;
         u_digit++)
        continue;

    return u_digit;
}

double mod(double df_a, double df_b)
{
    return df_a - df_b * floor(df_a / df_b);
}

void to_base_n(unsigned long ul_num, unsigned long ul_base)
{
    unsigned u_digit; // 数的位数
    unsigned u_p;
    unsigned u_result;

    u_p = 0;

    if (ul_base >= 2 && ul_base <= 10)
    {
        u_digit = takeDigit(ul_num, ul_base);
        unsigned int u_arr_output[u_digit];//动态声明的局部变量

        for (u_p = 0; u_p < u_digit; u_p++)
        {
            u_arr_output[u_p] = mod(ul_num / pow(ul_base, u_p), ul_base);
        }
        printf("sizeof: %zd\n", sizeof u_arr_output);

        for (int i = u_digit - 1; i >= 0; i--)
        {
            printf("%u", u_arr_output[i]);
        }
    }
    else
    {
        printf("Error. The base must be between 2 and 10.");
        return;
    }
}
