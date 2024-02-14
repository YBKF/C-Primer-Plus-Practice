/**
 * 如果使用字段宽度，scanf()在字段末尾或第1个空白字符处停止读取。 无法利用字段宽度让只有一个%s的scanf()读取多个单词。
 */
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i_Num1;
    int i_Num2;
    int i_Num3;

    printf("Please input somethings:");
    scanf("%4d", &i_Num1);
    printf("%d\n", i_Num1);

    // scanf("%d", &i_Num2);          // 会接着读取上一个scanf函数剩下的数字
    // scanf(" %d", &i_Num2); // scanf会忽略第一个非空白字符前的所有空白字符
    // scanf("%d %d", &i_Num2, &i_Num3); // scanf读取了上一个scanf函数留在输入中的数字
    // scanf("%d%d", &i_Num2, &i_Num3); // scanf读取了上一个scanf函数留在输入中的数字
    scanf("%d,%d", &i_Num2, &i_Num3); // 格式化的scanf，须在相应位置输入前面的','scanf才能正常读取
    printf("%d %d", i_Num2, i_Num3);
    return 0;
}
