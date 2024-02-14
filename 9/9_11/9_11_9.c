#include <stdio.h>

double power(double n, int p);

int main(int argc, char const *argv[])
{
    double i_a, i_p;
    double df_result;

    scanf("%lf %lf", &i_a, &i_p);

    df_result = power(i_a, i_p);

    printf("%f^%f = %f", i_a, i_p, df_result);

    return 0;
}

double power(double n, int p)
{
    double pow = 1.0;
    int i;

    if (0 == n && 0 != p)
    {
        return 0;
    }

    if (p < 0)
    {
        n = 1 / n;
        p = -p;
    }
    else if (0 == p)
    {
        return 1;
    }

    if (p > 0)
    {
        // printf("p: %d pow: %f\n", p, pow);
        n *= power(n, p - 1);
        pow = n;
    }

    return pow;
}