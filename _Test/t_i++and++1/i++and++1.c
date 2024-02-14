/**
 *i++是先把当前i的值作为参数传递给函数，函数调用结束后再自加1；
 *++i是先自加1，再把i的值传递给函数。
 */
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i;

    i = 0;
    printf("i = %d (past)\t", i);
    printf("i++ = %d    i = %d (now)\n\n", i++, i);
    i = 0;
    printf("i = %d (past)\t", i);
    printf("++i = %d    i = %d (now)\n\n", ++i, i);

    return 0;
}
