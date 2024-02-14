#include <stdio.h>
#define D_PER_WEEK 7

int main(int argc, char const *argv[])
{
    int i_days_before;
    int i_days_converted, i_weeks_converted;

    while (1)
    {
        printf("Days -> Weeks&Days (0 to exit):");
        scanf("%d", &i_days_before);

        if (i_days_before <= 0)
        {
            printf("Error or exit.");
            break;
        }

        i_weeks_converted = i_days_before / D_PER_WEEK;
        i_days_converted = i_days_before % D_PER_WEEK;
        printf("%d days are %d weeks, %d days.\n", i_days_before, i_weeks_converted, i_days_converted);
    }

    return 0;
}
