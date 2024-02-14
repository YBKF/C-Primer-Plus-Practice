/**
 * ? 仅输入空格
 */
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i = 0;

    printf("Please input:");
    scanf("%c", &i); // scanf函数对于%c，当%c前无空格scanf会从第一个字符开始读取
    printf("*%c*\n", i);
    printf("And next:");
    scanf(" %c", &i); // 当%c前有空格scanf会从第一个非空白字符开始读取
    printf("*%d*", i);
    return 0;
}
