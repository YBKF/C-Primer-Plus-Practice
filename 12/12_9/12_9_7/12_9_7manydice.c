/**
 * 7.编写一个程序，按照程序清单12.13输出示例后面讨论的内容，修改该程序。
 * 使其输出类似：
 * Enter the number of sets; enter q to stop :
 * 18
 * How many sides and how many dice?
 * 6 3
 * Here are 18 sets of 3 6-sided throws.
 * 12 10 6 9 8 14 8 15 9 14 12 17 11 7 10 13 8 14
 * How many sets? Enter q to stop :
 * q
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "diceroll.h"

int main(void)
{
    int dice;            // 骰子的数量
    int sides;           // 骰子的边数
    int rollTimes;       // 投掷骰子的次数
    int rollTimesStatus; // “状态值”，存储投掷骰子次数 rollTimes scanf() 的返回值
    int diceStatus;      // “状态值”，存储骰子属性信息 sidesNum 和 diceNum scanf() 的返回值
    int *diceResults;    // 存储投掷骰子的结果

    srand((unsigned int)time(0)); /* 随机种子 */

    printf("Enter the number of sets; enter q to stop :\n");

    while ((rollTimesStatus = scanf("%d", &rollTimes)) && rollTimes > 0)
    {
        printf("rollTimes: %d\n", rollTimes);

        /* 循环内的输入返回值检测代码块 start */
        if (rollTimesStatus == 1) // 读入成功时
        {
            while (getchar() != '\n')
                continue;
        }
        else if (rollTimesStatus == EOF) // 读入时遭遇错误（类型不匹配，通常是输入了字符）或EOF时
        {
            /* 错误输入流中获取到第一个字符为q则退出循环，不为q则打印错误信息并重新输入 */
            if (getchar() != 'q')
            {
                while (getchar() != '\n')
                    continue;
                break;
            }
            else
            {
                fputs("Cannot match this parameter.\nPlease enter a number to continue, or 'q' to stop:\n",
                      stdout);
                while (getchar() != '\n')
                    continue;

                continue;
            }
        }
        else if (rollTimesStatus == 0) // rollTimes 值读入失败时
        {
            /* 打印错误信息并重新输入 */
            fputs("Fail to get a value of \"rollTimes\".\nPlease enter a number to continue, or 'q' to stop:\n",
                  stdout);
            while (getchar() != '\n')
                continue;

            continue;
        }
        else // 其他原因的不合法输入
        {
            fputs("Invalid input.\nPlease enter a number to continue, or 'q' to stop :\n",
                  stdout);
            while (getchar() != '\n')
                continue;

            continue;
        }
        /* 循环内的输入返回值检测代码块 end */

        printf("How many sides and how many dice?\n");

        /* 此处的代码尽量与原代码的逻辑保持一致 */
        if ((diceStatus = scanf("%d %d", &sides, &dice)) != 2)
        {
            if (diceStatus == EOF)
                break; /* 退出循环 */
            else
            {
                printf("You should have entered two integer.");
                printf(" Let's begin again.\n");

                while (getchar() != '\n')
                    continue; /* 处理错误的输入 */

                printf("How many sets? Enter q to stop :\n");

                continue; /* 进入循环的下一轮迭代 */
            }
        }

        diceResults = (int *)malloc(rollTimes * sizeof(int));
        if (diceResults == NULL)
        {
            fputs("Error: malloc failed.\n", stderr);
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < rollTimes; i++)
            diceResults[i] = roll_n_dice(dice, sides);

        printf("Here are %d sets of %d %d-sided throws.\n",
               rollTimes, dice, sides);

        for (int i = 0; i < rollTimes; i++)
            printf("%d ", diceResults[i]);
        putchar('\n');
        free(diceResults);

        printf("How many sets? Enter q to stop :\n");
    }

    /* TODO: Do something, when rollTimes < 0. */

    return 0;
}
