#include <stdio.h>

int main(int argc, char const *argv[])
{
    char ch_buffer, ch_data;
    int i_numSpace, i_numLinebreak, i_numOthers;

    i_numSpace = 0;
    i_numLinebreak = 0;
    i_numOthers = 0;

    while (ch_buffer = getchar())
    {
        if (ch_buffer == '#')
        {
            break;
        }
        else
        {
            ch_data = ch_buffer;
        }

        switch (ch_data)
        {
        case ' ':
            i_numSpace++;
            break;

        case '\n':
            i_numLinebreak++;
            break;

        default:
            i_numOthers++;
            break;
        }
    }

    printf("numSpace=%d\nnumLinebreak=%d\nnumOthers=%d\n", i_numSpace, i_numLinebreak, i_numOthers);

    return 0;
}
