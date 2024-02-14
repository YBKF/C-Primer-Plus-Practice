/**
 * 1.不使用全局变量，重写程序清单12.4。
 */

#include <stdio.h>

// int units = 0; /* 外部变量 */

void critic(int *ip_var);

int main(void)
{
    // extern int units; /* 可选的重复声明 */
    int units = 0;

    printf("How many pounds to a firkin of butter?\n");
    scanf("%d", &units);

    while (units != 56)
        critic(&units);

    printf("You must have looked it up!\n");
    return 0;
}

void critic(int *ip_var)
{
    /* 删除了可选的重复声明 */
    printf("No luck, my friend. Try again.\n");
    scanf("%d", ip_var);
}