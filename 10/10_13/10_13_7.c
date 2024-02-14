#include <stdio.h>

void copy_arr(double target[], double source[], int count);
void printf_arr(double arr[], int count);

int main(int argc, char const *argv[])
{
    double df_arr[3][2] = {{1.1, 1.2}, {2.1, 2.2}, {3.1, 3.2}};
    double df_arr1[3][2];

    for (int i_outter = 0; i_outter < 3; i_outter++)
    {
        for (int i_inner = 0; i_inner < 2; i_inner++)
        {
            copy_arr(df_arr1[i_outter], df_arr[i_outter], 2);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        printf_arr(df_arr1[i], 2);
    }

    return 0;
}

void copy_arr(double target[], double source[], int count)
{
    for (int i = 0; i < count; i++)
    {
        target[i] = source[i];
    }
}

void printf_arr(double arr[], int count)
{
    for (int i = 0; i < count; i++, arr++)
    {
        printf("arr%d:%lf ", i, *arr);
    }
    putchar('\n');
}