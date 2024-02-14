/**
 *  
 */
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char ch_sentence[64] = 0;
    char ch_return;
    int i_seq = 0;

    printf("Please input:");
    while (ch_return = scanf("%c", &ch_sentence[i_seq++]))
    {
        printf("\ni_seq=%d, ch_return=%d, ch_sentence=%c\n", i_seq, ch_return, ch_sentence[i_seq - 1]);
    }

    printf("\n");

    for (size_t i = 0; i < i_seq; i++)
    {
        printf("%c", ch_sentence[i]);
    }

    return 0;
}
