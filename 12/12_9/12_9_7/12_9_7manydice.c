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

int main(int argc, char const *argv[])
{
    int iDiceNum;   // Number of dice.
    int iSidesNum;  // Number of sides of the dice.
    int iRollTimes; // Number of times the dice were rolled.
    int iStatus;    // Store scanf() return value.

    srand((unsigned)time(NULL)); // Random seed.

    fputs("Enter the number of sets; enter q to stop :\n", stdout);

    // If not EOF, then enter the while loop.
    while ((iStatus = scanf("%d", &iRollTimes)) == 1)
    {
        // Check iRollTimes.
        if (iRollTimes < 1)
        {
            fputs("Please enter a number, or the number of sets you entered must be bigger than 0, please input again.\n", stdout);

            // Clean
            while (getchar() != '\n')
                continue;

            fputs("Please enter the number of sets; enter q to stop :\n", stdout);

            continue;
        }

        fputs("How many sides and how many dice? ", stdout);

        while ((iStatus = scanf("%d %d", &iSidesNum, &iDiceNum)) == 2)
        {
        }

        if (scanf("%d %d", &iSidesNum, &iDiceNum) == 2)
        {
        }
        else
        {
            fputs("Please enter two correct numbers.\n", stdout);
        }
    }

    return 0;
}
