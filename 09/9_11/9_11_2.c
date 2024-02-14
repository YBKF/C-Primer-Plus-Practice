#include <stdio.h>

void chline(char ch, int i, int j)
{
    for (int i_count = 0; i_count < j; i_count++)
    {
        for (int i_inner = 0; i_inner < i; i_inner++)
        {
            putchar(ch);
        }
        putchar('\n');
    }
}

int main(int argc, char const *argv[])
{
    chline('@', 4, 3);
    return 0;
}
