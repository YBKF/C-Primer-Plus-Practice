#include <stdio.h>

/**
 * 计算输入值的立方值。
 */
double cubize(double df_input)
{
    double df_calcu = df_input;

    for (char c = 1; c < 3; c++)
    {
        df_calcu *= df_input;
    }

    return df_calcu;
}

int main(int argc, char const *argv[])
{
    double df_input;
    printf("Please input a double-float:");
    scanf("%lf", &df_input);
    printf("%lf ^3 = %lf\n", df_input, cubize(df_input));

    return 0;
}
