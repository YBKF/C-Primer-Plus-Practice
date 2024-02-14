#include <stdio.h>
#include <stdbool.h>

int limitTo2(int i_num);

void sortByOrder(double *df_num_1, double *df_num_2, double *df_num_3);

int main(int argc, char const *argv[])
{
    double df_num_1, df_num_2, df_num_3;

    printf("Please input:\n");

    scanf("%lf %lf %lf", &df_num_1, &df_num_2, &df_num_3);

    printf("before:\t1=%f, 2=%f, 3=%f\n", df_num_1, df_num_2, df_num_3);

    sortByOrder(&df_num_1, &df_num_2, &df_num_3);

    printf("now:\t1=%f, 2=%f, 3=%f\n", df_num_1, df_num_2, df_num_3);

    return 0;
}

int limitTo2(int i_num)
{
    if (i_num < 0)
    {
        i_num = 2;
    }

    if (i_num > 2)
    {
        i_num = 0;
    }

    return i_num;
}

void sortByOrder(double *df_num_1, double *df_num_2, double *df_num_3)
{
    double df_buffer[3];
    double df_num[3];
    int pow;

    df_buffer[0] = *df_num_1;
    df_buffer[1] = *df_num_2;
    df_buffer[2] = *df_num_3;

    for (int i = 0, pow = 0; i < 3; i++, pow = 0)
    {
        if (df_buffer[i] < df_buffer[limitTo2(i - 1)])
        {
            pow++;
        }
        if (df_buffer[i] < df_buffer[limitTo2(i + 1)])
        {
            pow++;
        }

        switch (pow)
        {
        case 0:
            *df_num_1 = df_buffer[i];
            break;

        case 1:
            *df_num_2 = df_buffer[i];
            break;

        case 2:
            *df_num_3 = df_buffer[i];
            break;

        default:
            printf("funcation > sortByOrder > Error!");
            break;
        }
    }
}