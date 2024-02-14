#include <stdio.h>

#define BASE_HOURLY_PAY 1000.0
#define OVERTIME_TIME 40.0
#define OVERTIME_RATIO 1.5
#define FIRST_TAX_RATE 0.15
#define FIRST_TAX_RATE_PEAKING 300.0
#define FIRST_TAX_MAX (FIRST_TAX_RATE_PEAKING * FIRST_TAX_RATE)
#define EXTEND_TAX_RATE 0.2
#define EXTEND_TAX_RATE_PEAKING 450.0
#define EXTEND_TAX_MAX (FIRST_TAX_MAX + (EXTEND_TAX_RATE_PEAKING - FIRST_TAX_RATE_PEAKING) * EXTEND_TAX_RATE)
#define REST_TAX_RATE 0.25

int main(int argc, char const *argv[])
{
    double df_work_hours;
    double df_total_salary;
    double df_tax;
    double df_net_income;

    printf("Hours of work in a week: ");
    scanf("%f", &df_work_hours);

    if (df_work_hours > OVERTIME_TIME)
    {
        df_work_hours = OVERTIME_TIME + (df_work_hours - OVERTIME_TIME) * OVERTIME_RATIO;
    }

    df_total_salary = df_work_hours * BASE_HOURLY_PAY;

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

    return 0;
}
