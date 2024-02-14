#include <stdio.h>
#include <math.h>

void dec2binAndPrint(int i_input);

int main(int argc, char const *argv[])
{
    dec2binAndPrint(234);
    return 0;
}

void dec2binAndPrint(int i_input)
{
    int i_result;

    // printf("beforeif: %d\n", i_input);

    if (i_input > 0)
    {
        // printf("inif: %d\n", i_input);
        i_result = i_input % 2;
        // printf("result:%d\n", i_result);

        dec2binAndPrint(i_input / 2);

        printf("%d", i_result);
    }
}
