#include <stdio.h>

int main(int argc, char const *argv[])
{
    for (int i_outer = 0; i_outer < 5; i_outer++)
    {
        for (int i_inner = 0; i_inner <= i_outer; i_inner++)
        {
            printf("$");
        }
        printf("\n");
    }

    return 0;
}
