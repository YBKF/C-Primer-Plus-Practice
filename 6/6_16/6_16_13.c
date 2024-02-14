#include <stdio.h>

int power(int i_input, int i_pow);

int main(int argc, char const *argv[])
{
    int i_arr[8];
    int i_pow;
    int seq = 0;

    for (int i = 0; i < 8; i++)
    {
        i_arr[i] = power(2, i + 1);
    }

    do
    {
        printf("%d ", i_arr[seq]);
        seq++;
    } while (seq < 8);

    return 0;
}

int power(int i_base, int i_index)
{
    int i_result = i_base;

    for (int i = 1; i < i_index; i++)
    {
        i_result *= i_base;
    }

    return i_result;
}