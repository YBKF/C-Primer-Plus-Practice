#include <stdio.h>
#include <math.h>
#define CM_PER_INCH 2.54
#define CM_PER_FEET 30.48
#define INCH_PER_FEET 12

double mod(double df_a, double df_b)
{
    double df_output;
    df_output = df_a - df_b * floor(df_a / df_b);
    // printf("df_a=%lf, df_b=%lf, df_output=%lf\n", df_a, df_b, df_output);

    return df_output;
}

int main(int argc, char const *argv[])
{
    float fl_cm_before;
    float fl_inch_converted;
    float fl_feet_converted;
    float fl_inch_moded;

    while (1)
    {
        printf("Enter a height in centimeters (<=0 to quit): ");
        scanf("%f", &fl_cm_before);

        if ((int)fl_cm_before <= 0)
        {
            printf("bye");
            break;
        }

        fl_inch_converted = fl_cm_before / CM_PER_INCH;
        fl_feet_converted = fl_inch_converted / INCH_PER_FEET;
        fl_inch_moded = mod(fl_inch_converted, INCH_PER_FEET);

        // printf("fl_inch_converted = %f\n", fl_inch_converted);

        printf("%.1f cm = %d feet, %.1f inches\n", fl_cm_before, (int)fl_feet_converted, fl_inch_moded);
    }

    return 0;
}
