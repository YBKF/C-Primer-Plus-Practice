#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i;
    printf("Please enter three numbers: ");
    scanf("%*d %*d %d", &i);            //跳过输入的前两个数字，只把第三个数字存储到i中
    printf("%d\n", i);
    return 0;
}
