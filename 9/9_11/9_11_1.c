#include <stdio.h>

double min(double x, double y)
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

int main(int argc, char const *argv[])
{
    double df_x, df_y;
    df_x = 3.1415926;
    df_y = 1.5707963;

    printf("Between %lf and %lf, %lf is smaller.", df_x, df_y, min(df_x, df_y));
    return 0;
}
