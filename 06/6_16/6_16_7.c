#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char ch_arr_str[32];
    int i_strlen;

    scanf("%s", ch_arr_str);
    i_strlen = strlen(ch_arr_str);

    for (int i = i_strlen; i > 0; i--)
    {
        printf("%c", ch_arr_str[i - 1]);
    }

    printf("\n%s", ch_arr_str);
    return 0;
}
