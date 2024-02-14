#include <stdio.h>
#include <stdbool.h>

#define FIRST_TAX_RATE 0.15
#define FIRST_TAX_PEAKING_SINGLE 17850.0
#define FIRST_TAX_PEAKING_HOUSEHOLDER 23900.0
#define FIRST_TAX_PEAKING_MUTAL 29750.0
#define FIRST_TAX_PEAKING_DIVORCED 14875.0
#define FIRST_TAX_SINGLE_MAX (FIRST_TAX_PEAKING_SINGLE * FIRST_TAX_RATE)
#define FIRST_TAX_HOUSEHOLDER_MAX (FIRST_TAX_PEAKING_HOUSEHOLDER * FIRST_TAX_RATE)
#define FIRST_TAX_MUTAL_MAX (FIRST_TAX_PEAKING_MUTAL * FIRST_TAX_RATE)
#define FIRST_TAX_DIVORCED_MAX (FIRST_TAX_PEAKING_DIVORCED * FIRST_TAX_RATE)
#define REST_TAX_RATE 0.28

void printAsterisk(long l_times);

bool printMenu();

bool isInclude1to4(int i_input);

int main(int argc, char const *argv[])
{
    int i_type_tax;
    double df_tax;
    double df_income;

    while (printMenu() && scanf("%d", &i_type_tax) && isInclude1to4((int)i_type_tax))
    {
        printf("Enter your pay:");
        scanf("%lf", &df_income);

        switch (i_type_tax)
        {
        case 1:
            if (df_income > FIRST_TAX_PEAKING_SINGLE)
                i_type_tax += 4;
            break;

        case 2:
            if (df_income > FIRST_TAX_PEAKING_HOUSEHOLDER)
                i_type_tax += 4;
            break;

        case 3:
            if (df_income > FIRST_TAX_PEAKING_MUTAL)
                i_type_tax += 4;
            break;

        case 4:
            if (df_income > FIRST_TAX_PEAKING_DIVORCED)
                i_type_tax += 4;
            break;

        default:
            return 0;
        }

        switch (i_type_tax)
        {
        case 1 + 4:
            df_tax = FIRST_TAX_SINGLE_MAX + (df_income - FIRST_TAX_PEAKING_SINGLE) * REST_TAX_RATE;
            break;

        case 2 + 4:
            df_tax = FIRST_TAX_HOUSEHOLDER_MAX + (df_income - FIRST_TAX_PEAKING_HOUSEHOLDER) * REST_TAX_RATE;
            break;

        case 3 + 4:
            df_tax = FIRST_TAX_MUTAL_MAX + (df_income - FIRST_TAX_PEAKING_MUTAL) * REST_TAX_RATE;

        case 4 + 4:
            df_tax = FIRST_TAX_DIVORCED_MAX + (df_income - FIRST_TAX_PEAKING_DIVORCED) * REST_TAX_RATE;

        default:
            df_tax = df_income * FIRST_TAX_RATE;
            break;
        }
        printf("Your tax: %lf\n", df_tax);
    }

    printf("Done.");

    return 0;
}

void printAsterisk(long l_times)
{
    for (long i = 0; i < l_times; i++)
    {
        putchar('*');
    }
    printf("\n");
}

bool printMenu()
{
    printf("\n1)Single\t\t2) Householder\n3)Mutal\t\t\n4)Divorced\n5)Quit\n");
    printf("Select a type of tax:");

    return true;
}

bool isInclude1to4(int i_input)
{
    if (i_input >= 1 && i_input <= 4)
    {
        return true;
    }

    return false;
}
