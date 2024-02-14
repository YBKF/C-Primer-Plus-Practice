#include <stdio.h>

int main(int argc, char const *argv[])
{
    float in_cup;
    printf("Please enter: ");
    scanf("%f", &in_cup);
    float pint = 0.5 * in_cup;
    float ounce = 8 * in_cup;
    float big_spoon = 2 * ounce;
    float tea_spoon = 3 * big_spoon;
    printf("pint: %.2f\n", pint);
    printf("ounce: %.2f\n", ounce);
    printf("big spoon: %.2f\n", big_spoon);
    printf("tea spoon: %.2f\n", tea_spoon);
    return 0;
}
