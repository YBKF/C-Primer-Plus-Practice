#include <stdio.h>

void larger_of(double *x, double *y);

int main(int argc, char const *argv[])
{
    double df_x, df_y;

    df_x = 3.14;
    df_y = 1.57;

    printf("before: x=%f, y=%f\n", df_x, df_y);

    larger_of(&df_x, &df_y);

    printf("now: x=%f, y=%f\n", df_x, df_y);

    return 0;
}

void larger_of(double *x, double *y)
{
    if (*x > *y)
    {
        *y = *x;
    }
    else
    {
        *x = *y;
    }
}
