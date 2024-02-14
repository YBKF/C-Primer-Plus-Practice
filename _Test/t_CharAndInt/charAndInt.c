/*
C语言将字符常量视为int类型而非char类型，
在int为32位、char为8位的ASCII系统中定义一个字符常量'FATE'，即把4个独立的8位ASCII码储存在一个32位存储单元中。
如果把这样的字符常量赋给char类型变量，则只有最后8位生效。输出的值将为'E'。
*/
#include <stdio.h>
int main(int argc, char const *argv[])
{
    char c = 'FATE';
    printf("%c\n", c);
    return 0;
}
