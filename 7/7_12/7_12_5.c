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

            switch (ch_data)
            {
            case '.':
                printf("!");
                i_count_replace++;
                break;

            case '!':
                printf("!!");
                i_count_replace++;
                break;

            default:
                printf("%c", ch_data);
                break;
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
