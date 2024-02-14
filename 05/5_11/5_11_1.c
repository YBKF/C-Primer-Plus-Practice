#include <stdio.h>
#define M_PER_H 60

int main(void)
{
    int i_min_before;
    int i_min_converted;
    int i_hour_converted;

    while (1)
    {
        printf("Please input a number you want to convert (M -> H&M)(0 to exit):\n");
        scanf("%d", &i_min_before);

        if (i_min_before <= 0)
        {
            printf("Error or exit.");
            break;
        }

        i_hour_converted = i_min_before / M_PER_H;
        i_min_converted = i_min_before % M_PER_H;
        printf("Converted: %02d hour %02d min\n", i_hour_converted, i_min_converted);
    }

    return 0;
}