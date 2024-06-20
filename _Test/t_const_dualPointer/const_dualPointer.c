#include <stdio.h>

int main()
{
    int i = 12;
    int i2 = 15;
    const int *ia;
    const int **ib;
    const int *ic = &i2;

    ia = &i;
    ib = &ia;

    // *ia = 10; // ia指向的地址的值无法更改
    *ib = ic;
    // **ib = 11; // ib指向的指针所指向的地址的值无法更改

    printf("%d", **ib);

    return 0;
}
