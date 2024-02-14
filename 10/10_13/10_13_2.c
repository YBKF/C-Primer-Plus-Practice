#include <stdio.h>
#define ELEMT_COUNT 5

void copy_arr(double target[], double source[], int count);
void copy_ptr(double target[], double source[], int count);
void copy_ptrs(double target[], double source[], const double last_path[]);

void printf_arr(double arr[], int count);

int main(int argc, char const *argv[])
{
    double df_arr_source[ELEMT_COUNT] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double df_arr_target1[ELEMT_COUNT];
    double df_arr_target2[ELEMT_COUNT];
    double df_arr_target3[ELEMT_COUNT];

    copy_arr(df_arr_target1, df_arr_source, ELEMT_COUNT);
    copy_ptr(df_arr_target2, df_arr_source, ELEMT_COUNT);
    copy_ptrs(df_arr_target3, df_arr_source, df_arr_source + ELEMT_COUNT);

    printf_arr(df_arr_target1, 5);
    printf_arr(df_arr_target2, 5);
    printf_arr(df_arr_target3, 5);

    return 0;
}

void copy_arr(double target[], double source[], int count)
{
    for (int i = 0; i < count; i++)
    {
        target[i] = source[i];
    }
}

void copy_ptr(double target[], double source[], int count)
{
    for (int i = 0; i < count; i++, source++, target++)
    {
        *target = *source;
    }
}

void copy_ptrs(double target[], double source[], const double last_path[])
{
    for (; source < last_path; source++, target++)
    {
        *target = *source;
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
