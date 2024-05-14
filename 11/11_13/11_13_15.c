/*
15.使用字符分类函数实现atoi()函数。如果输入的字符串不是纯数字，该函数返回0。
*/
#include <stdio.h>
#include <ctype.h>

#define DEC_BASE 10

int ischnum(int c);
int powi(int iBase, int iExpo);
int my_atoi(const char *str);

int main(int argc, char const *argv[])
{
    printf("%d\n%d\n%d\n%d\n%d\n%d\n",
           my_atoi("+555666"), my_atoi("12345"), my_atoi("007"), my_atoi("-996"), my_atoi("omo"), my_atoi("233^_^"));

    return 0;
}

int ischnum(int c)
{
    if ((char)c >= '0' && (char)c <= '9')
        return 1;
    else
        return 0;
}

// 计算参数的整型幂。仅在字符数字转换为整型的算法中作为辅助函数，故不支持基数<0或指数<0的计算，若基数<0或指数<0则将返回0
int powi(int iBase, int iExpo)
{
    if (iBase < 0 || iExpo < 0)
    {
        fputs("The base and exponential must be greater than 0.\n", stderr);
        return 0;
    }

    if (iExpo == 0)
        return 1;

    if (iBase == 0)
        return 0;

    int iResult = iBase;

    while (--iExpo)
        iResult *= iBase;

    return iResult;
}

int my_atoi(const char *str)
{
    int iNum = 0;               // 字符串下标，检测到的字符的数量
    const int iBase = DEC_BASE; // 基数，十进制
    int iDig = 0;               // 检测到的字符数字的数量，表示数字位数
    int iExpo = 0;              // 协助转换的幂运算的指数，从最小位开始转换
    int iResult = 0;            // 返回的结果值
    int isNegative = 0;         // 用来标记输入数据是否为负数的标志

    /* 首先，检查str第一个字符是否为纯字符数字或正负号，如果均不是则直接返回0 */
    if (ischnum(str[iNum]))
    {
        iNum++;
        iDig++;
    }
    else if (str[iNum] == '-')
    {
        iNum++;
        isNegative = 1;
    }
    else if (str[iNum] == '+')
    {

        iNum++;
    }
    else
        return 0;

    /* 其次，向后计算字符数字的位数，每检测到一位数字则iExpo++，直到检测到'\0'，
    若在检测过程中检测到非字符串数字则返回0 */
    while (ischnum(str[iNum]))
    {
        iNum++;
        iDig++;
    }

    if (str[iNum] != '\0')
        return 0;

    /* 开始将字符数字转化为整型，从最小位开始转换 */
    /* iNum != iDig 则表示在之前的检测中，检测到字符串中带有符号 */
    if (iNum != iDig)
    {
        while (iNum-- > 1)
            iResult += (str[iNum] - '0') * powi(DEC_BASE, iExpo++);
    }
    else
    {
        while (iDig--)
            iResult += (str[iDig] - '0') * powi(DEC_BASE, iExpo++);
    }

    /* 在之前的检测中如果检测为负数，即isNegative == true，则在结果前方加上负号再返回结果，
    如果不为负数，即isNegative == false，则返回结果*/
    if (isNegative)
        iResult = -iResult;

    return iResult;
}
