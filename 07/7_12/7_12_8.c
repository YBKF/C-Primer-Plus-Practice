#include <stdio.h>
#include <stdbool.h>

// #define BASE_HOURLY_PAY 1000.0
#define OVERTIME_TIME 40.0
#define OVERTIME_RATIO 1.5
#define FIRST_TAX_RATE 0.15
#define FIRST_TAX_RATE_PEAKING 300.0
#define FIRST_TAX_MAX (FIRST_TAX_RATE_PEAKING * FIRST_TAX_RATE)
#define EXTEND_TAX_RATE 0.2
#define EXTEND_TAX_RATE_PEAKING 450.0
#define EXTEND_TAX_MAX (FIRST_TAX_MAX + (EXTEND_TAX_RATE_PEAKING - FIRST_TAX_RATE_PEAKING) * EXTEND_TAX_RATE)
#define REST_TAX_RATE 0.25

#define PAY_RATE1 8.75
#define PAY_RATE2 9.33
#define PAY_RATE3 10.00
#define PAY_RATE4 11.20

void printAsterisk(long l_times);

void printMenu();

// bool printWkhrEntryPrompt();

bool printMenuSelectPrompt();

int main(int argc, char const *argv[])
{
    int i_id_pay_rate;
    double df_pay_rate;

    double df_work_hours;
    double df_total_salary;
    double df_tax;
    double df_net_income;

    printMenu();

    while (printMenuSelectPrompt() && scanf("%1d", &i_id_pay_rate))
    {
        switch (i_id_pay_rate)
        {
        case 1:
            df_pay_rate = PAY_RATE1;
            break;

        case 2:
            df_pay_rate = PAY_RATE2;
            break;

        case 3:
            df_pay_rate = PAY_RATE3;
            break;

        case 4:
            df_pay_rate = PAY_RATE4;
            break;

        default:
            return 0;
        }

        printf("Hours of work in a week: ");
        scanf("%lf", &df_work_hours);

        if (df_work_hours > OVERTIME_TIME)
        {
            df_work_hours = OVERTIME_TIME + (df_work_hours - OVERTIME_TIME) * OVERTIME_RATIO;
        }

        // df_total_salary = df_work_hours * BASE_HOURLY_PAY;
        df_total_salary = df_work_hours * df_pay_rate;

        if (df_total_salary <= FIRST_TAX_RATE_PEAKING)
        {
            df_tax = df_total_salary * FIRST_TAX_RATE;
        }
        else if ((df_total_salary > FIRST_TAX_RATE_PEAKING) && (df_total_salary <= EXTEND_TAX_RATE_PEAKING))
        {
            df_tax = FIRST_TAX_MAX + (df_total_salary - FIRST_TAX_RATE_PEAKING) * EXTEND_TAX_RATE;
        }
        else if (df_total_salary > EXTEND_TAX_RATE_PEAKING)
        {
            df_tax = EXTEND_TAX_MAX + (df_total_salary - EXTEND_TAX_RATE_PEAKING) * REST_TAX_RATE;
        }

        df_net_income = df_total_salary - df_tax;

        printf("Total salary: %lf\nTax: %lf\nNet Income: %lf\n", df_total_salary, df_tax, df_net_income);
    }

    return 0;
}

/**
 * 根据参数打印相应次数的星号。
 */
void printAsterisk(long l_times)
{
    for (long i = 0; i < l_times; i++)
    {
        putchar('*');
    }
}

/**
 * 打印工资等级选择菜单。
 */
void printMenu()
{
    printAsterisk(65);
    printf("\nEnter the number corresponding to the desired pay rate or action:\n");
    printf("1) $%.2f/hr\t\t2) $%.2f/hr\n", PAY_RATE1, PAY_RATE2);
    printf("3) $%.2f/hr\t\t4) $%.2f/hr\n", PAY_RATE3, PAY_RATE4);
    printf("5) quit\n");
    printAsterisk(65);
}

// /**
//  * 打印请输入工时的提示语。
//  * 使用布尔变量作为返回值，以便与scanf()函数集成到while循环中。
//  */
// bool printWkhrEntryPrompt()
// {
//     printf("Hours of work in a week: ");
//     return true;
// }

/**
 * ? 打印请选择菜单选项的提示语。
 * * 使用布尔变量作为返回值，以便与scanf()函数集成到while循环中。
 */
bool printMenuSelectPrompt()
{
    printf("\nPlease select(\"5\" to quit): ");
    return true;
}
