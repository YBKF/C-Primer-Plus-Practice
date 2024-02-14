#include <stdio.h>

/**
 * 如果把%c放在格式字符串中的空格前面，
 * scanf()便会跳过空格， 
 * 从第1个非空白字符开始读取。
 * 具体请运行程序。
*/
int main(int argc, char const *argv[])
{
    char c;
    char c1;
    scanf("%c", &c);        //从输入的一个字符开始读取
    scanf(" %c", &c1);      //从输入的第一个非空字符开始读取
    printf("%c, %c", c, c1);
    return 0;
}

