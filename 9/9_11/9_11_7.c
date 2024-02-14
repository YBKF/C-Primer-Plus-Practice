#include <stdio.h>
#include <ctype.h>

int upper2lower(int i_ch_letter);

int getPositionInAlphabet(char ch_letter);

int main(int argc, char const *argv[])
{
    char ch;
    int i_positionOfch;

    while (scanf("%c", &ch) != EOF)
    {
        if (ch == ' ' || ch == '\n')
        {
            continue;
        }

        i_positionOfch = getPositionInAlphabet(ch);
        printf("Position of \'%c\' in the alphabet is %d\n", ch, i_positionOfch);
    }

    return 0;
}

/**
 * 当参数为大写字母将其转换为小写字母并返回, 若参数为小写字母则直接返回参数不进行任何操作
 */
int upper2lower(int i_ch_letter)
{
    if (isupper(i_ch_letter))
    {
        i_ch_letter += 32;
    }
    return i_ch_letter;
}

int getPositionInAlphabet(char ch_letter)
{
    // printf("in the getpia\n");
    int i_position;

    if (isalpha(ch_letter))
    {
        ch_letter = upper2lower(ch_letter);
    }
    else
    {
        return -1;
    }

    i_position = ch_letter - 'a' + 1;

    return i_position;
}
