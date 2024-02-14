#include <stdio.h>

int main(int argc, char const *argv[])
{
    unsigned int ui_quart;
    unsigned int ui_gram;
    double uli_numQuart;
    
    double const ld_cWaterMoleculeMass = 3.0e-23;
    printf("Please enter the mass of water(quart): ");
    scanf("%d", &ui_quart);
    ui_gram = 950 * ui_quart;
    uli_numQuart = ui_gram / ld_cWaterMoleculeMass;
    printf("The number of water molecule is: %.0lf", uli_numQuart);
    // printf("%e", ld_cWaterMoleculeMass);
    return 0;
}
