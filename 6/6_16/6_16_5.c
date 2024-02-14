#include <stdio.h>

int minusCharA(int i_input);

int main(int argc, char const *argv[])
{
    int i_outer, i_inner;
    int i_space;
    int i_inputMinusCharA;
    char ch_input;

    printf("Input a character: ");
    scanf("%c", &ch_input);

    i_inputMinusCharA = minusCharA(ch_input);

    for (i_outer = 0; i_outer <= i_inputMinusCharA; i_outer++)
    {
        for (i_space = i_outer; i_space < i_inputMinusCharA; i_space++)
        {
            printf(" ");
        }

        for (i_inner = 0; i_inner < i_outer; i_inner++)
        {
            printf("%c", 'A' + i_inner);
        }

        for (; i_inner >= 0; i_inner--)
        {
            printf("%c", 'A' + i_inner);
        }

        printf("\n");
    }

    return 0;
}

/**
 * return  参数减去'A'的值，当参数小于'A'时会直接返回0
 * */
int minusCharA(int i_input)
{
    if (i_input < 'A')
    {
        printf("Warnning: The entered data is less than the minimum value.\n");
        return 0;
    }

    return i_input - 'A';
}
