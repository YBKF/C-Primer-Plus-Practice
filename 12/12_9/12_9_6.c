/**
 * 6.编写一个程序，生成1000个1～10范围内的随机数。不用保存或打印
 * 这些数字，仅打印每个数出现的次数。用 10 个不同的种子值运行，生成的
 * 数字出现的次数是否相同？可以使用本章自定义的函数或ANSI C的rand()和
 * srand()函数，它们的格式相同。这是一个测试特定随机数生成器随机性的方
 * 法。
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    srand((unsigned)time(NULL));

    int numArr[10];
    int randNum = 0;

    for (int n = 0; n < 10; n++)
        numArr[n] = 0;

    for (int i = 0; i < 1000; i++)
    {
        randNum = rand() % 10 + 1;

        for (int j = 0; j < 10; j++)
            if ((j + 1) == randNum)
                numArr[j]++;
    }

    for (int k = 0; k < 10; k++)
        printf("%d: %d\n", (k + 1), numArr[k]);

    return 0;
}
