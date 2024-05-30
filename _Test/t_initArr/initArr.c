#include <stdio.h>

int main(int argc, char const *argv[])
{
    char ch_nin[16];
    char ch_arr[16] = {};
    char ch_mem[16];

    memset(ch_mem, '\0', sizeof(ch_mem));

    fputs("ch_nin: ", stdout);
    for (int j = 0; j < 16; j++)
        printf("%d ", ch_nin[j]);
    putchar('\n');

    fputs("ch_arr: ", stdout);
    for (int k = 0; k < 16; k++)
        printf("%d ", ch_arr[k]);
    putchar('\n');

    fputs("ch_mem: ", stdout);
    for (int q = 0; q < 16; q++)
        printf("%d ", ch_mem[q]);
    return 0;
}