#include <stdio.h>
#define BONUS 100.0

int main(int argc, char const *argv[])
{
    int i_years;
    float f_balance_chuckie;

    for (i_years = 0, f_balance_chuckie = BONUS;
         f_balance_chuckie > 0;
         i_years++)
    {
        f_balance_chuckie += f_balance_chuckie * 0.08;
        f_balance_chuckie -= 10;
        printf("f_balance: %f\n", f_balance_chuckie);
    }

    printf("Chuckie take %d years to draw the bonus all out.", i_years);

    return 0;
}
