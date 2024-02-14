#include <stdio.h>

int main(int argc, char const *argv[])
{
    float f_a, f_b;
    float f_result;

    printf("Please input somethings:\n");
    while (2 == scanf("%f %f", &f_a, &f_b))
    {
        f_result = (f_a - f_b) / (f_a * f_b);
        printf("%f\n", f_result);
        printf("Enter next pair of numbers('q' to exit):\n");
    }
    return 0;
}
