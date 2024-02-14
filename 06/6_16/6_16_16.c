#include <stdio.h>

int main(void)
{
    const float INVESTMENT_DAPHNE = 100.0;
    const float INVESTMENT_DEIRDRE = 100.0;
    float f_balance_Daphne, f_balance_Deirdre;
    int i_year;

    for (i_year = 0, f_balance_Daphne = INVESTMENT_DAPHNE, f_balance_Deirdre = INVESTMENT_DEIRDRE;
         f_balance_Daphne >= f_balance_Deirdre;
         i_year++)
    {
        f_balance_Daphne += INVESTMENT_DAPHNE * 0.1;
        f_balance_Deirdre += f_balance_Deirdre * 0.05;
        printf("Daphne: %f\nDeirdre: %f\n\n", f_balance_Daphne, f_balance_Deirdre);
    }

    printf("It take %d years to bring Deirdre's balance above Daphne's.\n", i_year);
    printf("Daphne: %f\nDeirdre: %f\n", f_balance_Daphne, f_balance_Deirdre);
}