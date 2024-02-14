#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

bool isPrime(unsigned long ul_num_input);

int main(int argc, char const *argv[])
{
    // int i_inspector; // 检查键盘第一个输入的字符是否为正整数

    unsigned long ul_num_head; // 储存键盘第一个输入的字符
    unsigned long ul_num_body; // 储存其他字符

    /** 储存最终结果，即ul_num_head * 10^x + ul_num_body。
     * x为ul_num_body转换字符串后的字符串的长度，即strlen(ch_arr_num_body).
     */
    unsigned long ul_num_data;

    unsigned long ul_num_;
    unsigned long ul_num_prime;

    char ch_arr_num_body[256]; // 用于储存被转换为字符后的ul_num_body

    printf("Please enter a number greater than zero:");

    ul_num_head = getchar(); // 接收键盘第一个输入的字符，并确保其为数字
    if ((ul_num_head >= '0') && (ul_num_head <= '9'))
    {
        ul_num_head -= '0'; // 确保为数字后将字符转换为整型
    }
    else
    {
        printf("Error!");
        return 0; // 如果不是数字则退出程序
    }

    scanf("%lu", &ul_num_body); // 接收并转换输入的第一个字符以外的其他字符

    itoa(ul_num_body, ch_arr_num_body, 10); // body转换为字符串，并储存在ch_arr_num_body中，等待使用strlen()用作后面10的指数
    ul_num_data = ul_num_body + ul_num_head * (int)pow(10, strlen(ch_arr_num_body));

    for (unsigned long ul = 1; ul <= ul_num_data; ul++)
    {
        if (isPrime(ul))
        {
            printf("%u ", ul);
        }
    }

    return 0;
}

/**
 * 判断是否为质数
 */
bool isPrime(unsigned long ul_num_input)
{
    if (ul_num_input <= 2)
    {
        return ul_num_input > 1;
    }

    for (unsigned long i = 2; i < ul_num_input; i++) // 所有自然数必被1和它本身整除
    {
        if (0 == ul_num_input % i)
        {
            return false;
        }
    }
    return true;
}
