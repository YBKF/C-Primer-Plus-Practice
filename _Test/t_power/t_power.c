#include <stdio.h>
#include <math.h>

/* a^b = e^(ln(a)*b) */
double power(double df_a, double df_b)
{
    return exp(log(df_a) * df_b);
}

// double power(double df_a, double df_b)
// {
//     double df_output;
//     df_output = exp(log(df_a) * df_b);
//     return df_output;
// }

int main(void)
{
    printf("power: %lf, %lf\npow: %lf, %lf\n", power(2, 2), power(2, 1.236), pow(2, 2), pow(2, 1.236));
    return 0;
}