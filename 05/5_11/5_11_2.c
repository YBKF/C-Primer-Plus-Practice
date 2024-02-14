#include <stdio.h>

int main(void)
{
    int i_input;
    int i_seq;
    printf("Please input a number:\n");
    scanf("%d", &i_input);
    i_seq = i_input + 10;
    while (i_input <= i_seq)
    {
        printf("%d\n", i_input);
        i_input++;
    }

    return 0;
}