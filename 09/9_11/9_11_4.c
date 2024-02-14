#include <stdio.h>

double takeReciprocal(double df_num);

double hamonic_mean(double df_num_1, double df_num_2);

int main(int argc, char const *argv[])
{
    printf("Hamonic Mean: %lf", hamonic_mean(3.1415, 1.5708));
    return 0;
}

double takeReciprocal(double df_num)
{
    return 1.0 / df_num;
}

double hamonic_mean(double df_num_1, double df_num_2)
{
    double df_result;

    df_num_1 = takeReciprocal(df_num_1);
    df_num_2 = takeReciprocal(df_num_2);

    df_result = (df_num_1 + df_num_2) / 2.0;

    return takeReciprocal(df_result);
}
