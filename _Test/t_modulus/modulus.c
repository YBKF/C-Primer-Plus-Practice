/*取模（取余）*/
#include <stdio.h>
#include <math.h>

double mod(double df_a, double df_b)
{
    double df_output;
    df_output = df_a - df_b * floor(df_a / df_b);
    // printf("df_a=%lf, df_b=%lf, df_output=%lf\n", df_a, df_b, df_output);

    return df_output;
}

int main(int argc, char const *argv[])
{
    int i_num = mod(65, 3);
    printf("%d", i_num);
    return 0;
}
