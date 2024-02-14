#include <stdio.h>
#define NUM1 100
#define NUM2 90
#define NUM3 80

int getNum();

int main()
{
    int n = NUM2;
    const int MaxNum1 = getNum(); // 运行时初始化
    const int MaxNum2 = n;        // 运行时初始化
    const int MaxNum3 = NUM3;     // 编译时初始化

    printf("%d, %d, %d\n", MaxNum1, MaxNum2, MaxNum3);

    // 把const数据或非const数据的地址初始化为指向const的指针或为其赋值是合法的
    double rates[5] = {88.99, 100.12, 59.45, 183.11, 340.5};
    const double locked[4] = {0.08, 0.075, 0.0725, 0.07};
    const double *pc = rates; // 有效
    pc = locked;              // 有效
    pc = &rates[3];           // 有效

    double *pnc = rates; // 有效
    pnc = locked;        // 无效，非const指针无法指向const数组，即通过指针也无法更改const数组中的数据
    pnc = &rates[3];     // 有效

    return 0;
}

int getNum()
{
    return NUM1;
}