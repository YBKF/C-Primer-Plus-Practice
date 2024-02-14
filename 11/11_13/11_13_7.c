#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char *mystrncpy(char *target, char *source, size_t count);
char *s_gets(char *str, int maxCount);
bool printHead();

int main(int argc, char const *argv[])
{
    char source[20] = "";
    char target[20] = "";

    while (printHead() && s_gets(source, 20) && source[0] != EOF)
    {
        mystrncpy(target, source, 20);
        for (size_t i = 0; i < 20; i++)
            printf("%d ", source[i]);
        putchar('\n');

        printf("target str: *%s*\n", target);
    }

    return 0;
}

char *mystrncpy(char *target, char *source, size_t count)
{
    size_t i = 0;
    for (i = 0; i < count; i++)
        target[i] = source[i];

    return target;
}

char *s_gets(char *str, int maxCount)
{
    char *ret_val;
    int i = 0;

    ret_val = fgets(str, maxCount, stdin);

    if (ret_val)
    {
        while (str[i] != '\0' && str[i] != '\n')
            i++;

        if (str[i] == '\n')
            str[i] = '\0';
        else
            while (getchar() == '\n')
                continue;
    }

    return ret_val;
}

bool printHead()
{
    puts("Please enter a source string (Type ^Z to exit):");
    return true;
}
