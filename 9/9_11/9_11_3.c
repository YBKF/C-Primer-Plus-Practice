#include <stdio.h>

void printCharline(char ch, int timesInaLine, int countOfLine);

int main(int argc, char const *argv[])
{
    printCharline('?', 5, 4);
    return 0;
}

void printCharline(char ch, int timesInaLine, int countOfLine)
{
    for (int i = 0; i < countOfLine; i++)
    {
        for (int i = 0; i < timesInaLine; i++)
        {
            printf("%c", ch);
        }
        putchar('\n');
    }
}
