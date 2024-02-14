#include <stdio.h>
#include <ctype.h>

// #define DEBUG
// #define SKIP_SPACE

void storeaWord(char ch_arr[]);

int main(int argc, char const *argv[])
{
    char arr[100];
    char arr2[100];
    storeaWord(arr);
    storeaWord(arr2);

    puts(arr);
    puts(arr2);

    return 0;
}

void storeaWord(char ch_arr[])
{
    char ch_temp;
    unsigned u_seq = 0;

    while (scanf("%c", &ch_temp) && ch_temp != '\n')
    {

#ifdef DEBUG
        printf("%d: *%c*\n", ch_temp, ch_temp);
#endif

#ifdef SKIP_SPACE
        if (ch_temp == ' ')
            break;
#endif

        if (isalpha(ch_temp))
        {
            ch_arr[u_seq] = ch_temp;

#ifdef DEBUG
            printf("%u: %c\n", u_seq, ch_arr[u_seq]);
#endif
            u_seq++;
        }
    }
    ch_arr[u_seq] = '\0';
    while (getchar() != '\n')
        continue;
    puts("Done!");
}
