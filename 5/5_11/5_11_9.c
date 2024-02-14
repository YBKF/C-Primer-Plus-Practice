#include <stdio.h>

void Temperatures(double df_fahrenheit)
{
    double df_celsius, df_kelvin;
    const double C2K = 273.16;

    df_celsius = 5.0 / 9.0 * (df_fahrenheit - 32.0);
    df_kelvin = df_celsius + C2K;

    printf("%.2lfF = %.2lfC = %.2lfK\n", df_fahrenheit, df_celsius, df_kelvin);
}

int main(int argc, char const *argv[])
{
    double df_fahrenheit;
    char ch_isInputaNumber;

    /*下面While循环函数的等效的另一个版本*/
    // printf("Input a number:");
    // while (ch_isInputaNumber = scanf("%lf", &df_fahrenheit))
    // {
    //     if (ch_isInputaNumber == 0)
    //     {
    //         printf("Error or Exit.");
    //         break;
    //     }

    //     Temperatures(df_fahrenheit);
    //     printf("Input a number:");
    // }

    while (1)
    {
        printf("Input a number:");
        ch_isInputaNumber = scanf("%lf", &df_fahrenheit);
        if (ch_isInputaNumber == 0)
        {
            printf("Error or Exit.");
            break;
        }

        Temperatures(df_fahrenheit);
    }

    /*上方While函数的精简版*/
    // while (scanf("%lf", &df_fahrenheit))
    // {
    //     Temperatures(df_fahrenheit);
    // }

    return 0;
}
