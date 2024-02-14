/**
 * 2.在美国，通常以英里/加仑（每加仑跑多少英里）来计算油耗；
 * 在欧洲，以升/100公里（每一百公里消耗多少升）来计算。
 * 下面是程序的一部分，提示用户选择计算模式（美制或公制），然后接收数据并计算油耗。
*/
// pe12-2b.c
// 与 pe12-2a.c 一起编译
#include <stdio.h>
#include "pe12-2a.h"

int main(void)
{
    int mode;

    printf("Enter 0 for metric mode, 1 for US mode: ");
    scanf("%d", &mode);

    while (mode >= 0)
    {
        set_mode(mode);
        get_info();
        show_info();

        printf("Enter 0 for metric mode, 1 for US mode");
        printf(" (-1 to quit): ");
        scanf("%d", &mode);
    }

    printf("Done.\n");

    return 0;
}