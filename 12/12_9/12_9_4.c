/**
 * 4.在一个循环中编写并测试一个函数，该函数返回它被调用的次数。
 */
#include <stdio.h>

int fun();

int main(int argc, char const *argv[])
{
    int iCalledNum = 0;

    for (int i = 0; i < 11; i++)
    {
        iCalledNum = fun();
    }

    printf("%d", iCalledNum);

    return 0;
}

int fun()
{
    // save the number of times the function has been called
    static int s_iFunCalledTimes = 0;
    s_iFunCalledTimes++;

    // printf("function \"fun\" has been called: %d\n", s_iFunCalledTimes);

    return s_iFunCalledTimes;
}
