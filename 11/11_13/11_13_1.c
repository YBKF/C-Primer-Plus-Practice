#include <stdio.h>
#define LENGTH_MAX 100
#define LENGTH 10

char *getnchar(unsigned int lenth_n, char ch_arr[]);

int main(int argc, char const *argv[])
{
    char ch_arr[LENGTH_MAX];

    getnchar(LENGTH, ch_arr);

    for (unsigned u = 0; u < LENGTH; u++)
    {
        printf("%c", ch_arr[u]);
    }

    return 0;
}

char *getnchar(unsigned int lenth_n, char ch_arr[])
{
    unsigned int ui = 0;
    char ch;

    while (ui < lenth_n)
    {
        ch_arr[ui] = getchar();
        printf("%u *%c* ", ui, ch_arr[ui]);
        ui++;
    }

    // ch_arr[ui] = '\0';

    while ((ch = getchar()) != '\n')
    {
        printf("\nch=*%c*\n", ch);
        continue;
    }

    return ch_arr;
}
