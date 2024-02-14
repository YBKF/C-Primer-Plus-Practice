#include "stdio.h"

/**
 * 需要实现的功能：进行英寸与厘米的转化
 * 要求：提示用户输入英寸值
 * 1 inch equals 2.54 cm
 * 
 * 定义2个双精度的值，valInch 和 resultCM
 * 用户输入需要转换的英寸的值，使用此值对valInch定义
 * resultCM的值定义为：valInch *= 2.54
 * 输出转换完成后的结果
 */

double transform(double valInch)
{
    double resultCM;
    if (valInch > 0)
    {
        resultCM = valInch * 2.54;
        return resultCM;
    }
    return 0;
}

int main()
{
    double valInch;
    double resultCM;
    printf("Please type the inch-value which you want to transform:\n");
    scanf("%lf", &valInch); //注意：对double类型变量使用进行赋值时需要使用 %lf
    resultCM = transform(valInch);
    printf("Result: %.3f\n", resultCM);
    return 0;
}
