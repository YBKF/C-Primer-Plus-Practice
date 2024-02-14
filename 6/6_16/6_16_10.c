#include <stdio.h>

int squareSumFloor2Ceil(int i_floor, int i_ceiling);

int main(int argc, char const *argv[])
{
    int i_ceiling, i_floor; // 上限整数和下限整数

    printf("Enter lower and upper integer limits: ");
    while (2 == scanf("%d %d", &i_floor, &i_ceiling))
    {
        if (i_floor >= i_ceiling)
        {
            printf("Done");
            break;
        }

        printf("The sums of the squares from %d to %d is %d\n", i_floor * i_floor, i_ceiling * i_ceiling, squareSumFloor2Ceil(i_floor, i_ceiling));
        printf("Enter next set of limits: ");
    }
    return 0;
}

/**
 * 计算从上限到下限范围内所有整数的平方和
 */
int squareSumFloor2Ceil(int i_floor, int i_ceiling)
{
    int i_squareSum = 0;
    for (; i_floor <= i_ceiling; i_floor++)
    {
        i_squareSum += i_floor * i_floor;
    }

    return i_squareSum;
}