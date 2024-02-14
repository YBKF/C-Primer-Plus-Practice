#include <stdio.h>

int getLargestSub(double df_arr[], int count);

int main(int argc, char const *argv[])
{
    double df_arr[5] = {2.2, 1.1, 3.3, 3.3, 4.4};
    int i_sub = getLargestSub(df_arr, 5);

    printf("%d", i_sub);
    return 0;
}

int getLargestSub(double df_arr[], int count)
{
    int i, i_sub, i_temp;
    for (i = 1, i_temp = df_arr[0], i_sub = 0; i < count; i++)
    {
        if (i_temp < df_arr[i])
        {
            i_temp = df_arr[i];
            i_sub = i;
        }
    }

    return i_sub;
}
