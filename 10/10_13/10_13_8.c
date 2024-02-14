#include <stdio.h>

void copy_arr(int target[], int source[], int count);
void printf_arr(int arr[], int count);

int main(int argc, char const *argv[])
{
    int i_arr7[7] = {1, 2, 3, 4, 5, 6, 7};
    int i_arr3[3];

    copy_arr(i_arr3, i_arr7 + 2, 3);

    printf_arr(i_arr3, 3);

    return 0;
}

void copy_arr(int target[], int source[], int count)
{
    for (int i = 0; i < count; i++)
    {
        target[i] = source[i];
    }
}

void printf_arr(int arr[], int count)
{
    for (int i = 0; i < count; i++, arr++)
    {
        printf("arr%d:%d ", i, *arr);
    }
    putchar('\n');
}