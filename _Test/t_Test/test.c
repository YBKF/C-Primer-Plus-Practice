/**
 * 11.编写一个函数，读入10个字符串或者读到EOF时停止。
 * 该程序为用户提供一个有5个选项的菜单：
 * 打印源字符串列表、以ASCII中的顺序打印字符串、按长度递增顺序打印字符串、
 * 按字符串中第1个单词的长度打印字符串、退出。
 * 菜单可以循环显示，除非用户选择退出选项。
 * 当然，该程序要能真正完成菜单中各选项的功能。
 */
#include <stdio.h>
#include <string.h>

#define STR_LENGTH 100
#define STR_COUNT 10

char *s_gets(char *str, int maxCount);
char *strarrcpy_addr(char *pt_arr_target, char (*str_arr_source)[STR_LENGTH], int n);

int get10Str(char (*str_arr)[STR_LENGTH]);
int strcmp_ascii(const char *s1, const char *s2);
char *pt_sort_str_byASCII(char *pt_arr_source, int n);
void pt_printslist(char *pt_arr_source[], int n);

int main(int argc, char const *argv[])
{
    char str_arr_test[STR_COUNT][STR_LENGTH] = {
        {"increasing"},
        {"nowhere"},
        {"create"},
        {"random"},
        {"error"},
        {"analog"},
        {"string"},
        {"identify"},
        {"neighbor"},
        {"google"}};

    char str_arr_source[STR_COUNT][STR_LENGTH] = {{""}};
    char *pt_str_arr[STR_COUNT];
    char *p;
    int readed_count = 0;
    int i = 0;

    for (int i = 0; i < 10; i++)
    {
        printf("pt: %p\n", pt_str_arr[i]);
    }
    putchar('\n');

    for (int i = 0; i < 10; i++)
    {
        pt_str_arr[i] = str_arr_test[i];
        // printf("pt_str_arr: \t\t%p\n", &(pt_str_arr[i]));
        // printf("pt_str_arr[i]: \t\t%p\n", pt_str_arr[i]);
        // printf("str_arr_test[i]: \t%p\n", str_arr_test[i]);
        // puts("");
    }
    putchar('\n');

    for (int i = 0; i < 10; i++)
    {
        printf("pt: %p\n", pt_str_arr[i]);
    }
    printf("test[0]: %s, addr: %p\n", str_arr_test[0], str_arr_test[0]);
    printf("ptar[0]: %s, addr: %p\n", pt_str_arr[0], pt_str_arr[0]);
    // printf("ptar: %s, addr: %p\n", pt_str_arr, pt_str_arr);

    printf("test: %s, addr: %p\n", str_arr_test, str_arr_test);
    printf("ptar: %s, addr: %p\n", pt_str_arr, pt_str_arr);

    // p = pt_str_arr;

    // for (int i = 0; i < 10; i++)
    // {
    //     printf("p: %p\n", p);
    //     printf("p: %p\n", p);
    //     p++;
    //     puts("");
    // }

    // strarrcpy_addr(pt_str_arr, str_arr_test, 10);

    // pt_printslist(pt_str_arr, 10);

    return 0;
}

char *s_gets(char *s, int n)
{
    char *p = s;

    if (s == NULL || n <= 0)
        return NULL;

    int c = 0;

    while (--n > 0 && (c = getchar()) != EOF)
        if (c == '\n')
            break;
        else
            *p++ = c;

    if (n == 0)
        while (getchar() != '\n')
            continue;

    *p = '\0';

    if (c == EOF && p == s)
        return NULL;

    return s;
}

/**
 * 拷贝一个字符串数组的地址到一个指针数组中，n为指定的拷贝数
 */
// char *strarrcpy_addr(char *pt_arr_target, char (*str_arr_source)[STR_LENGTH], int n)
// {
//     int i_strNum = 0;

//     /**
//      * 当拷贝数n小于或等于0时函数返回空指针
//      */
//     if (n <= 0)
//         return NULL;

//     /**
//      *
//      */
//     while (i_strNum < n)
//     {
//         if (str_arr_source[i_strNum] && str_arr_source[i_strNum][0] != '\0')
//             pt_arr_target[i_strNum] = str_arr_source[i_strNum];
//         else
//             break;

//         i_strNum++;
//     }

//     return pt_arr_target;
// }

/**
 * 读取从键盘输入的字符串，最多读取10个字符串，读到EOF时停止读取
 * 返回成功读取到的字符串的数量
 */
int get10Str(char (*str_arr)[STR_LENGTH])
{
    int i_strNum = 0;

    // 读入10个字符串遇到EOF停止
    while (i_strNum < 10)
        if (s_gets(str_arr[i_strNum], STR_LENGTH))
            i_strNum++;
        else
            break;

    return i_strNum;
}

/**
 * 比较字符串s1和s2，返回两者第一个不相等的字符的ascii差值
 */
int strcmp_ascii(const char *s1, const char *s2)
{
    const char *pc_cmp_a = s1;
    const char *pc_cmp_b = s2;

    while (*pc_cmp_a == *pc_cmp_b)
    {
        if (*pc_cmp_a == '\0')
            return *pc_cmp_a - *pc_cmp_b;

        pc_cmp_a++;
        pc_cmp_b++;
    }

    return *pc_cmp_a - *pc_cmp_b;
}

char *pt_sort_str_byASCII(char *pt_arr_source, int n)
{

    return pt_arr_source;
}

/**
 * 根据指定的次数，打印指针数组指向的源字符串列表.
 * 注意：须传送指针数组
 */
void pt_printslist(char *pt_arr_source[], int n)
{
    char **p = pt_arr_source;

    if (n > 0)
    {
        puts(*p);
        --n;
    }

    // 如果--n不大于0则不会对p指针进行其他不必要的操作。
    while (n > 0)
    {
        puts(*++p);
        --n;
    }
}
