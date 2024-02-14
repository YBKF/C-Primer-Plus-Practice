#include <stdio.h>

int main(int argc, char const *argv[])
{
    char ch_buffer, ch_data;
    int i_numPrinted;

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

        printf("%c: %-4d ", ch_data, ch_data);
        i_numPrinted++;

        if (i_numPrinted >= 8)
        {
            printf("\n");
            i_numPrinted = 0;
        }
    }

    return 0;
}
