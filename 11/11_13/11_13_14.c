/*
14.编写一个通过命令行运行的程序计算幂。第1个命令行参数是double
类型的数，作为幂的底数，第2个参数是整数，作为幂的指数。
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        fputs("The arguments should be 2.\n", stderr);
        exit(EXIT_FAILURE);
    }

    double dfBase;
    int iExpo;
    double dfResult;

    dfBase = atof(argv[1]);
    iExpo = atoi(argv[2]);

    /* a^b = e^(ln(a)*b) (a > 0)*/
    dfResult = exp(log(dfBase) * (double)iExpo);
    printf("%lf^%d = %.2lf\n", dfBase, iExpo, dfResult);

    return 0;
}
