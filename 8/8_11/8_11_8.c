#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool printMenu(void);

bool isRightChoice(char ch);

float getCorrectFloat(void);

float arithmetic(char operation, float f_first_num, float f_second_num);

float arithmeticAddition(float f_first_num, float f_second_num);
float arithmeticSubtraction(float f_first_num, float f_second_num);
float arithmeticMultiplication(float f_first_num, float f_second_num);
float arithmeticDivision(float f_first_num, float f_second_num);

void printAsterisk(long l_times);

int main(int argc, char const *argv[])
{
    char ch_choice;
    char ch_operation;
    float f_first_num, f_second_num;
    float f_result;

    while (printMenu() && scanf(" %c", &ch_choice))
    {
        while (getchar() != '\n')
        {
            continue;
        }

        if (ch_choice == 'q')
            break;

        if (!isRightChoice(ch_choice))
        {
            printf("Error. Please re-enter a correct choice: \n");
            continue;
        }

        switch (ch_choice)
        {
        case 'a':
            ch_operation = '+';
            break;

        case 's':
            ch_operation = '-';
            break;

        case 'm':
            ch_operation = '*';
            break;

        case 'd':
            ch_operation = '/';
            break;

        default:
            break;
        }

        printf("Enter first number: ");
        f_first_num = getCorrectFloat();

        printf("Enter second number: ");
        while ((f_second_num = getCorrectFloat()) == 0 && ch_choice == 'd')
        {
            printf("Enter a number other than 0: ");
        }

        f_result = arithmetic(ch_choice, f_first_num, f_second_num);
        printf("%f %c %f = %f\n", f_first_num, ch_operation, f_second_num, f_result);
    }

    printf("Bye.\n");

    return 0;
}

bool printMenu()
{
    printAsterisk(38);
    printf("Enter the operation of your choice: \n");
    printf("a. add\t\t\ts. subtract\n");
    printf("m. multiply\t\td. divide\n");
    printf("q. quit\n");
    printAsterisk(38);

    return true;
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
    putchar('\n');
}

bool isRightChoice(char ch)
{
    if (ch == 'q' || ch == 'a' || ch == 's' || ch == 'm' || ch == 'd')
    {
        return true;
    }

    return false;
}

float getCorrectFloat(void)
{
    float f_result;
    char ch_getInvalidChar;

    /*用来捕捉错误的输入*/
    while (!scanf("%f", &f_result)) // 若此scanf捕捉到字符（例如，'A'），则不会进行转换而是一直放到输入中。
    {
        putchar('\"');
        while ((ch_getInvalidChar = getchar()) != '\n')
        {
            putchar(ch_getInvalidChar);
        }
        putchar('\"');

        printf(", What your entered is not a valid number.\n");
        printf("Please enter a number, such as 2.5, -1.78E8, or 3: \n");

        // printf("result: %f, return: %d", f_result, i_return_scanf);
    }

    return f_result;
}

float arithmetic(char operation, float f_first_num, float f_second_num)
{
    float f_result;
    switch (operation)
    {
    case 'a':
        f_result = arithmeticAddition(f_first_num, f_second_num);
        break;

    case 's':
        f_result = arithmeticSubtraction(f_first_num, f_second_num);
        break;

    case 'm':
        f_result = arithmeticMultiplication(f_first_num, f_second_num);
        break;

    case 'd':
        f_result = arithmeticDivision(f_first_num, f_second_num);
        break;

    default:
        printf("Funcation > arithmetic: Error! Invalid operation.");
        break;
    }

    return f_result;
}

float arithmeticAddition(float f_first_num, float f_second_num)
{
    return f_first_num + f_second_num;
}

float arithmeticSubtraction(float f_first_num, float f_second_num)
{
    return f_first_num - f_second_num;
}

float arithmeticMultiplication(float f_first_num, float f_second_num)
{
    float f_result;

    f_result = f_first_num * f_second_num;

    return f_result;
}

float arithmeticDivision(float f_first_num, float f_second_num)
{
    float f_result;

    f_result = f_first_num / f_second_num;

    return f_result;
}
