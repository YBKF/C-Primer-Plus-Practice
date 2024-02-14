#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n;
    int m;
    scanf("%da%d", &n, &m);         //输入的两个数字中必须加入一个'a'，输入的第一个数字必须检索到一个a才会把第一个数字储到a中
    printf("%d, %d", n, m);
    return 0;
}
