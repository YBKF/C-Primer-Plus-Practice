#include <stdio.h>
#define MAX_LENGTH 100

// #define TEST
int printHead();
char *findChar(char *s_str, char ch);
char *s_gets(char *str, int maxcount);
int c_scanf(char *ch);

int main(int argc, char const *argv[])
{
#ifdef TEST
    char str[] = "albert";
    char str2[] = "";
    char find = 'b';
    char find1 = 'z';
    char find2 = '\0';
    char *pc;

    pc = findChar(str, find);

    printf("str: %s, strp: %p\n", str, str);
    printf("isNULL? %d\n", pc == NULL);
    printf("char: %c, charp: %p\n\n", *pc, pc);

    pc = findChar(str, 'z');

    printf("str: %s, strp: %p\n", str, str);
    printf("isNULL? %d\n\n", pc == NULL);

    pc = findChar(str2, find2);

    printf("str: %s, strp: %p\n", str2, str2);
    printf("isNULL? %d\n\n", pc == NULL);
#endif

    char str_input[MAX_LENGTH];
    char ch_find;
    char *pc;

    while (printHead() && s_gets(str_input, MAX_LENGTH) && str_input[0] != EOF)
    {
        puts("Which character do you want to find:");
        c_scanf(&ch_find);
        pc = findChar(str_input, ch_find);

        printf("isNULL? %d\n", pc == NULL);
        printf("str: %s, strp: %p\n", str_input, str_input);
        if (pc != NULL)
            printf("char: %c, charp: %p\n\n", *pc, pc);
    }

    return 0;
}

int printHead()
{
    puts("Please enter a string (Type ^Z to exit):");
    return 1;
}

char *findChar(char *s_str, char ch)
{
    char *pc_find = s_str;

    while (*pc_find != '\0')
    {
        if (*pc_find == ch) // 找到后返回
            return pc_find;
        pc_find++;
    }

    return NULL;
}

char *s_gets(char *str, int maxcount)
{
    char *ret_val;
    int i = 0;

    ret_val = fgets(str, maxcount, stdin);

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

int c_scanf(char *ch)
{
    int ret_val;
    ret_val = scanf(" %c", ch);
    while (getchar() != '\n')
        continue;

    return ret_val;
}
