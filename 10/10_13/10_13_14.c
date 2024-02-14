#include <stdio.h>
#define ROWS 3
#define COLS 5

void getchar_arr(double df_arr[], int count);
void getInputintoArr2d(int i_rows, int i_cols, double df_arr[i_rows][i_cols]);

void printf_arr(double df_arr[], int i_count);
void printf_arr2d(int i_rows, int i_cols, double df_arr[i_rows][i_cols]);

double getAverage_arr(double df_arr[], int i_count);
void printfAverage(int i_rows, int i_cols, double df_arr[i_rows][i_cols]);

double getMax_arr2d(int i_rows, int i_cols, double df_arr[i_rows][i_cols]);

int main(int argc, char const *argv[])
{
    double df_arr[ROWS][COLS];

    getInputintoArr2d(ROWS, COLS, df_arr);

    putchar('\n');
    printf_arr2d(ROWS, COLS, df_arr);

    printfAverage(ROWS, COLS, df_arr);

    printf("Max: %lf", getMax_arr2d(ROWS, COLS, df_arr));

    return 0;
}

void getchar_arr(double df_arr[], int count)
{
    for (int i = 0; i < count; i++)
    {
        scanf("%lf", df_arr + i);
    }

    // 去除多余的输入
    while (getchar() != '\n')
        continue;
}

void getInputintoArr2d(int i_rows, int i_cols, double df_arr[i_rows][i_cols])
{
    for (int i = 0; i < i_rows; i++)
    {
        printf("Please input %d numbers, store into row %d:\n", i_cols, i + 1);
        getchar_arr(df_arr[i], i_cols);
    }
}

void printf_arr(double df_arr[], int i_count)
{
    for (int i = 0; i < i_count; i++)
    {
        printf("%lf ", df_arr[i]);
    }
}

void printf_arr2d(int i_rows, int i_cols, double df_arr[i_rows][i_cols])
{
    for (int i_outter = 0; i_outter < i_rows; i_outter++)
    {
        for (int i_inner = 0; i_inner < i_cols; i_inner++)
        {
            printf("%lf ", df_arr[i_outter][i_inner]);
        }
        putchar('\n');
    }
}

double getAverage_arr(double df_arr[], int i_count)
{
    double df_tot = 0.0;

    for (int i = 0; i < i_count; i++)
    {
        df_tot += df_arr[i];
    }

    return df_tot / i_count;
}

void printfAverage(int i_rows, int i_cols, double df_arr[i_rows][i_cols])
{
    for (int i = 0; i < i_rows; i++)
    {
        printf("Average %d: %lf\n", i, getAverage_arr(df_arr[i], i_cols));
    }
}

double getMax_arr2d(int i_rows, int i_cols, double df_arr[i_rows][i_cols])
{
    double df_max;
    int i_outter, i_inner;

    df_max = 0.0;

    for (i_outter = 0; i_outter < i_rows; i_outter++)
    {
        for (i_inner = 0; i_inner < i_cols; i_inner++)
        {
            if (df_arr[i_outter][i_inner] > df_max)
            {
                df_max = df_arr[i_outter][i_inner];
            }
        }
    }

    return df_max;
}
