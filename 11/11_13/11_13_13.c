/*
13.编写一个程序，反序显示命令行参数的单词。例如，命令行参数是
see you later，该程序应打印later you see。
*/
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int argCount = argc;

    while (--argCount)
        printf("%s ", argv[argCount]);

    return 0;
}
