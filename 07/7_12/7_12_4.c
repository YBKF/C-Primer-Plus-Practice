#include <stdio.h>

int main(int argc, char const *argv[])
{
    char ch_buffer;
    char ch_data;

    int i_count_replace;

    i_count_replace = 0;

    while (1)
    {
        if ((ch_buffer = getchar()) != '#')
        {
            ch_data = ch_buffer;
            if ('.' == ch_data)
            {
                printf("!");
                i_count_replace++;
            }
            else if ('!' == ch_data)
            {
                printf("!!");
                i_count_replace++;
            }
            else
            {
                printf("%c", ch_data);
            }
        }
        else
        {
            break;
        }
    }

    printf("count_replace = %d", i_count_replace);

    return 0;
}
