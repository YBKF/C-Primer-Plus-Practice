/**
 * 3.重新设计编程练习2，要求只使用自动变量。
 * 该程序提供的用户界面不变，即提示用户输入模式等。
 * 但是，函数调用要作相应变化。
 */
// 与12_9_3FC_func.c一同编译
#include <stdio.h>
#include "12_9_3FC_func.h"

int main(void)
{
    int iMode;
    int iLastUsedMode = 0;
    int iChekcedMode = 0;
    double dfDistanceTraveled = 0.0;
    double dfFuelConsumption = 0.0;

    printf("Enter 0 for metric mode, 1 for US mode: ");
    scanf("%d", &iMode);

    while (iMode >= 0)
    {
        iChekcedMode = set_mode(iMode, iLastUsedMode);
        iLastUsedMode = iChekcedMode;
        get_info(iChekcedMode, &dfDistanceTraveled, &dfFuelConsumption);
        show_info(iChekcedMode, &dfDistanceTraveled, &dfFuelConsumption);

        printf("Enter 0 for metric mode, 1 for US mode");
        printf(" (-1 to quit): ");
        scanf("%d", &iMode);
    }

    printf("Done.\n");

    return 0;
}