#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define NEGATIVE_DIRECTION 0
#define POSITIVE_DIRECTION 1

int getAlpha();

int upper2lower(int i_ch_input);

int takeMedian(int i_base, int i_limit, int i_direction);

int main(void)
{
    double guess = 50.0;
    double limit = 50.0;
    double median;
    char response;
    bool flag_selected = false;

    printf("Pick an integer from 1 to 100.I willtry to guess it.\n");
    printf("Respond with a y if my guess is right and with\n");
    printf("an n if it is wrong.\n");
    printf("Uh...is your number %d?\n", (int)guess);

    while ((response = getAlpha()) != 'y')
    {
        if (response == 'n')
        {
            flag_selected = false;

            printf("Well, then, is it bigger or smaller than this number?\n");

            // printf("response1: *%c*%d*\n", response, response);

            while (flag_selected == false)
            {
                response = getAlpha();
                // printf("response2: *%c*%d*\n", response, response);
                switch (response)
                {
                case 's':
                    flag_selected = true;

                    median = takeMedian(guess, limit, NEGATIVE_DIRECTION);
                    guess = median;

                    if (limit < 2)
                        guess--;
                    else
                        limit /= 2.0;
                    printf("limit: %f\n", limit);

                    break;

                case 'b':
                    flag_selected = true;

                    median = takeMedian(guess, limit, POSITIVE_DIRECTION);
                    guess = median;

                    if (limit < 2)
                        guess++;
                    else
                        limit /= 2.0;
                    printf("limit: %f\n", limit);

                    break;

                default:
                    printf("Error. Please re-input.\n");
                    break;
                }
            }
            printf("is it %d?\n", (int)guess);
        }
        else
        {
            printf("Sorry, I understand only y or n.\n");
        }
    }

    printf("I knew I could do it!\n");

    return 0;
}

/**
 * 在一定范围内取输入参数的中值
 * @param i_base 取值的基值
 * @param i_limit 以基值为基础，向上或向下取值的范围的限制
 * @param i_direction 取值的方向，默认为正方向(Positive)
 */
int takeMedian(int i_base, int i_limit, int i_direction)
{
    if (NEGATIVE_DIRECTION == i_direction)
    {
        i_limit = -i_limit;
    }
    else
    {
        i_limit = +i_limit;
    }

    return i_base + i_limit / 2;
}

int upper2lower(int i_ch_input)
{
    if (i_ch_input >= 'A' && i_ch_input <= 'Z')
    {
        i_ch_input += 'a' - 'A';
    }

    return i_ch_input;
}

int getAlpha(void)
{
    char ch;
    int i_scanf_return;
    int i_ch_buffer = 0;
    int i_ch_data = 0;

    i_scanf_return = scanf(" %c", &ch);

    i_ch_buffer = (int)ch;

    if (isalpha(i_ch_buffer))
    {
        i_ch_data = i_ch_buffer;
    }
    else if (i_scanf_return == EOF)
    {
        return EOF;
    }

    return upper2lower(i_ch_data);
}
