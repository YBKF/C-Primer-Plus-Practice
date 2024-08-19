#include <stdio.h>
#define NUM1 100
#define NUM2 90
#define NUM3 80

int main()
{
    int n = NUM2;
    const int MaxNum1 = getNum(); // 运行时初始化
    const int MaxNum2 = n;        // 运行时初始化
    const int MaxNum3 = NUM3;     // 编译时初始化

    printf("%d, %d, %d\n", MaxNum1, MaxNum2, MaxNum3);

    return 0;
}
