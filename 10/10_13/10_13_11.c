#include <stdio.h>
#define ROWS 3
#define COLS 5

void printf_arr(int i_arr[][COLS], int i_rows);
void double_arr(int i_arr[][COLS], int i_rows);

int main(int argc, char const *argv[])
{
    int i_arr[ROWS][COLS] = {{11, 12, 13, 14, 15},
                             {21, 22, 23, 24, 25},
                             {31, 32, 33, 34, 35}};

    printf("Array before:\n");
    printf_arr(i_arr, ROWS);
    putchar('\n');
    double_arr(i_arr, ROWS);
    printf("Array after:\n");
    printf_arr(i_arr, ROWS);

    return 0;
}

void printf_arr(int i_arr[][COLS], int i_rows)
{
    for (int i_outter = 0; i_outter < i_rows; i_outter++)
    {
        for (int i_inner = 0; i_inner < COLS; i_inner++)
        {
            printf("%d ", i_arr[i_outter][i_inner]);
        }
        putchar('\n');
    }
}

void double_arr(int i_arr[][COLS], int i_rows)
{
    for (int i_outter = 0; i_outter < i_rows; i_outter++)
    {
        for (int i_inner = 0; i_inner < COLS; i_inner++)
        {
            i_arr[i_outter][i_inner] *= 2;
        }
    }
}
