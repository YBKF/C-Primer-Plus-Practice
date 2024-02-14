#include <stdio.h>
#define MAX_LENGTH 100

int is_within(char find, char *str);
char *s_gets(char *str, int maxCount);
int c_scanf(char *ch);
int printHead();

int main(int argc, char const *argv[])
{
    char str_input[MAX_LENGTH];
    char ch_find;

    while (printHead() && s_gets(str_input, MAX_LENGTH) && str_input[0] != EOF)
    {
        puts("Which character do you want to find:");
        c_scanf(&ch_find);

        if (is_within(ch_find, str_input))
            puts("Yes\n");
        else
            puts("No\n");
    }

    return 0;
}

int is_within(char find, char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == find)
            return i + 1;
        i++;
    }

    return 0;
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
        {
            str[i] = '\0';
        }
        else
        {
            while (getchar() == '\n')
                continue;
        }
    }

    return ret_val;
}

int c_scanf(char *ch)
{
    int ret_val;
    ret_val = scanf(" %c", ch);
    while (getchar() != '\n')
        continue;

    return ret_val;
}

int printHead()
{
    puts("Please a string (Type ^Z to exit):");
    return 1;
}