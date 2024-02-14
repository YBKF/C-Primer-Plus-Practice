#include <stdio.h>
#define COUNT 4

void sumTwoArrIntoArr(int i_arr_target[], int i_arr_sourceA[], int i_arr_sourceB[], int count);

int main(int argc, char const *argv[])
{
    int i_arr_A[COUNT] = {2, 4, 5, 8};
    int i_arr_B[COUNT] = {1, 0, 4, 6};
    int i_arr_C[COUNT];

    sumTwoArrIntoArr(i_arr_C, i_arr_A, i_arr_B, COUNT);

    for (int i = 0; i < COUNT; i++)
    {
        printf("%d ", i_arr_C[i]);
    }

    return 0;
}

void sumTwoArrIntoArr(int i_arr_target[], int i_arr_sourceA[], int i_arr_sourceB[], int count)
{
    for (int i = 0; i < count; i++)
    {
        i_arr_target[i] = i_arr_sourceA[i] + i_arr_sourceB[i];
    }
}
