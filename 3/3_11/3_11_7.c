#include <stdio.h>

int main(int argc, char const *argv[])
{
    float const inch_cm = 2.54;
    float f_inch_high;
    float f_cm_high;
    printf("Please enter your high(inch): ");
    scanf("%f", &f_inch_high);
    f_cm_high = f_inch_high * inch_cm;
    printf("Your high(cm): %.2fcm\n", f_cm_high);
    return 0;
}
