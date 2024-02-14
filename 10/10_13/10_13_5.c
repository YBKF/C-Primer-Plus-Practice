#include <stdio.h>

double getGap(double df_arr[], int count);

int main(int argc, char const *argv[])
{

    double df_arr[5] = {1.1, 2.2, 3.3, 4.4, 7.5};
    double df_gap = getGap(df_arr, 5);

    printf("Gap: %lf\n", df_gap);

    return 0;
}

double getGap(double df_arr[], int count)
{
    double df_min, df_max;
    int i;

    for (i = 1, df_min = df_arr[0], df_max = df_arr[0];
         i < count; i++)
    {
        if (df_min > df_arr[i])
        {
            df_min = df_arr[i];
        }

        if (df_max < df_arr[i])
        {
            df_max = df_arr[i];
        }
    }

    return df_max - df_min;
}
