#include <stdio.h>
#define ROWS 3
#define COLS 5

void copyarr(int rows, int cols, double df_target[rows][cols], double df_source[rows][cols]);

int main(int argc, char const *argv[])
{
    double df_arr[ROWS][COLS] = {{1.1, 1.2, 1.3, 1.4, 1.5},
                                 {2.1, 2.2, 2.3, 2.4, 2.5},
                                 {3.1, 3.2, 3.3, 3.4, 3.5}};
    double df_arr_target[ROWS][COLS];

    copyarr(ROWS, COLS, df_arr_target, df_arr);

    for (int i_outter = 0; i_outter < ROWS; i_outter++)
    {
        for (int i_inner = 0; i_inner < COLS; i_inner++)
        {
            printf("%lf ", df_arr_target[i_outter][i_inner]);
        }
        putchar('\n');
    }

    return 0;
}

void copyarr(int rows, int cols, double df_target[rows][cols], double df_source[rows][cols])
{
    for (int i_outter = 0; i_outter < rows; i_outter++)
    {
        for (int i_inner = 0; i_inner < cols; i_inner++)
        {
            df_target[i_outter][i_inner] = df_source[i_outter][i_inner];
        }
    }
}
