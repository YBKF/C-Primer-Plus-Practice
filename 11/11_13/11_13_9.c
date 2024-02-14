#include <stdio.h>
#include <string.h>

char *reverse_str(char *str_source);
char *s_gets(char *str, int maxCount);
int printHead();

int main(int argc, char const *argv[])
{
    char str_entered[100];

    while (printHead() && s_gets(str_entered, 100) && *str_entered != EOF)
    {
        reverse_str(str_entered);
        printf("Reversed: %s\n", str_entered);
    }

    return 0;
}

char *reverse_str(char *str_source)
{
    char *pc_head = str_source;
    char *pc_tail = str_source;
    char ch_temp;

    while (*(pc_tail + 1))
        pc_tail++;

    while (pc_head < pc_tail)
    {
        ch_temp = *pc_head;
        *pc_head++ = *pc_tail;
        *pc_tail-- = ch_temp;
    }

    return str_source;
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
            while (getchar() != '\n')
                continue;
    }

    return ret_val;
}

int printHead()
{
    puts("Please enter a string (Enter ^Z to exit):");

    return 1;
}
