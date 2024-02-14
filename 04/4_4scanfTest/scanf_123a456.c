/**
 * 请运行程序并输入"123a456"
 * 如果使用字段宽度，scanf()会在字段结尾或第1个空白字符处停止读取 （满足两个条件之一便停止）。
 * 如果第1个非空白字符是A而不是数字，会发生什么情况？scanf()将停在那里，并把A放回输入中，不会把值赋给指定变量。
 * 程序在下一次读取输入时，首先读到的字符是A。如果程序只使用%d转换说明，scanf()就一直无法越过A读下一个字符。
 * 另外，如果使用带多个转换说明的scanf()，C规定在第1个出错处停止读取输入。
 */
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i = 0;
    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    printf("please input:");
    scanf("%d", &i);
    scanf("%d", &i1);
    // scanf("%c", &i1);
    printf("%d, %d\n", i, i1);
    scanf("%d %d", &i2, &i3);
    printf("%d, %d\n", i2, i3);
    return 0;
}
