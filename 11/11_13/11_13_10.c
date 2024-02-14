/**
 * 10.编写一个函数接受一个字符串作为参数，并删除字符串中的空格。
 * 在一个程序中测试该函数，使用循环读取输入行，直到用户输入一行空行。
 * 该程序应该应用该函数只每个输入的字符串，并显示处理后的字符串。
 */
#include <stdio.h>

char *strDelSpace(char *str);
int printHead();

int main(int argc, char const *argv[])
{
    char str[100];

    while (printHead() && fgets(str, 99, stdin) && *str != '\n')
    {
        strDelSpace(str);
        fputs(str, stdout);
    }

    return 0;
}

char *strDelSpace(char *str)
{
    char *pc_inspect = str;
    char *pc_locate = str;

    // 检查两个指针是否指向相同地址且这个地址是否指向空字符
    while (pc_inspect == pc_locate && *pc_inspect)
    {
        // 检测到空格时，inspect指针跳过所有空格，直到指向字符串第一个非空格字符
        if (*pc_inspect == ' ')
        {
            while (*pc_inspect == ' ')
                pc_inspect++;
        }
        else
        {
            pc_inspect++;
            pc_locate++;
        }
    }

    // （inspect和locate指针不再指向同一个地址，即检测到了空格）对字符串逐个进行赋值
    while (*pc_inspect)
    {
        // 跳过空格
        while (*pc_inspect == ' ')
            pc_inspect++;

        *pc_locate = *pc_inspect;

        pc_locate++;
        pc_inspect++;
    }

    // 在字符串末尾添加空字符
    *pc_locate = '\0';

    return str;
}

int printHead()
{
    puts("Please enter a string (Re-Enter to exit):");

    return 1;
}
