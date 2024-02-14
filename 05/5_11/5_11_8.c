#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i_opera_nd;
    int i_opera_st;

    printf("This program computes moduli.\n");
    printf("Enter an integer to serve as the second operand: ");
    scanf("%d", &i_opera_nd);
    printf("Now enter the first operand: ");
    scanf("%d", &i_opera_st);
    printf("%d %% %d is %d\n", i_opera_st, i_opera_nd, i_opera_st % i_opera_nd);

    while (i_opera_st > 0)
    {
        printf("Enter next number for first operand (<= 0 to quit): ");
        scanf("%d", &i_opera_st);
        if (i_opera_st > 0)
        {
            printf("%d %% %d is %d\n", i_opera_st, i_opera_nd, i_opera_st % i_opera_nd);
        }
        else
        {
            printf("Done\n");
        }
    }

    return 0;
}
