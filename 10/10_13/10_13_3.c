#include <stdio.h>

int getLargestNumFromArr(int i_arr[], int count);

int main(int argc, char const *argv[])
{
    int i_arr[5] = {3, 1, 5, 2, 4};

    int i_largest;

    i_largest = getLargestNumFromArr(i_arr, 5);
    printf("%d", i_largest);

    return 0;
}

int getLargestNumFromArr(int i_arr[], int count)
{
    int i_result, i;
    for (i = 1, i_result = i_arr[0]; i < count; i++)
    {
        if (i_result < i_arr[i])
        {
            i_result = i_arr[i];
        }
        printf("i: %d result: %d\n", i, i_result);
    }
    printf("final result: %d\n", i_result);

    return i_result;
}
