#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i_charCount;
    int i_ch;

    for (i_ch = 0, i_charCount = 0;
         (i_ch = getchar()) != EOF;
         i_charCount++)
        continue;

    printf("Character Count: %d", i_charCount);

    return 0;
}
