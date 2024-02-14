#include <stdio.h>
#define LENGTH_MAX 100
#define LENGTH 10

char *getnchar(char ch_arr[], unsigned int lenth_n);

int main(int argc, char const *argv[])
{
    char ch_arr[LENGTH_MAX];

    getnchar(ch_arr, LENGTH);

    for (unsigned u = 0; u < LENGTH; u++)
    {
        printf("%c", ch_arr[u]);
    }

    return 0;
}

char *getnchar(char ch_arr[], unsigned int lenth_n)
{
    unsigned int ui = 0;
    char ch_temp;

    while ((ch_temp = getchar()) && (ui < lenth_n && ch_temp != ' ' && ch_temp != '\t' && ch_temp != '\n'))
    {
        ch_arr[ui] = ch_temp;
        printf("%u *%c* \n", ui, ch_arr[ui]);
        ui++;
    }

    // ch_arr[ui] = '\0';

    while (getchar() != '\n')
    {
        continue;
    }

    return ch_arr;
}
