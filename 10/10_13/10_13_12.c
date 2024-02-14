#include <stdio.h>
#define ROWS 3
#define COLS 2

void copy_arr_elem(double target[], double source[], int count);
void printf_arr_elem(double arr[], int count);
void copy_arr2d(double target[][COLS], double source[][COLS], int i_rows);
void printf_arr2d(double df_arr[][COLS], int i_rows);

int main(int argc, char const *argv[])
{
    double df_arr[ROWS][COLS] = {{1.1, 1.2}, {2.1, 2.2}, {3.1, 3.2}};
    double df_arr1[ROWS][COLS];

    // for (int i_outter = 0; i_outter < 3; i_outter++)
    // {
    //     for (int i_inner = 0; i_inner < 2; i_inner++)
    //     {
    //         copy_arr_elem(df_arr1[i_outter], df_arr[i_outter], 2);
    //     }
    // }

    // for (int i = 0; i < 3; i++)
    // {
    //     printf_arr_elem(df_arr1[i], 2);
    // }

    copy_arr2d(df_arr1, df_arr, ROWS);
    printf_arr2d(df_arr1, ROWS);

    return 0;
}

void copy_arr_elem(double target[], double source[], int count)
{
    for (int i = 0; i < count; i++)
    {
        target[i] = source[i];
    }
}

void printf_arr_elem(double arr[], int count)
{
    for (int i = 0; i < count; i++, arr++)
    {
        printf("arr%d:%lf ", i, *arr);
    }
    putchar('\n');
}

void copy_arr2d(double target[][COLS], double source[][COLS], int i_rows)
{
    for (int i_outter = 0; i_outter < i_rows; i_outter++)
    {
        for (int i_inner = 0; i_inner < COLS; i_inner++)
        {
            target[i_outter][i_inner] = source[i_outter][i_inner];
        }
    }
}

void printf_arr2d(double df_arr[][COLS], int i_rows)
{
    for (int i_outter = 0; i_outter < i_rows; i_outter++)
    {
        for (int i_inner = 0; i_inner < COLS; i_inner++)
        {
            printf("%lf ", df_arr[i_outter][i_inner]);
        }
        putchar('\n');
    }
}
