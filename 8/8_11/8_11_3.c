#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    int i_lowerCount;
    int i_upperCount;

    int i_ch;

    i_lowerCount = 0;
    i_upperCount = 0;

    while (EOF != (i_ch = getchar()))
    {
        if (islower(i_ch))
        {
            i_lowerCount++;
        }

        if (isupper(i_ch))
        {
            i_upperCount++;
        }
    }

    printf("Lowercase Count: %d\nUppercase Count: %d\n", i_lowerCount, i_upperCount);

    return 0;
}
