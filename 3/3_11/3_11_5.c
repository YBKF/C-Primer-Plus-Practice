#include <stdio.h>

int main(int argc, char const *argv[])
{
    unsigned char uc_age_year;
    printf("Please enter your age: ");
    scanf("%d", &uc_age_year);
    double const cYearToSecond = 3.156e7;
    double ld_age_second = cYearToSecond * uc_age_year;
    printf("Your age(second): %Lf\n", ld_age_second);
    return 0;
}
