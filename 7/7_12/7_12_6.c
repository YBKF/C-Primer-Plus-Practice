#include <stdio.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    char ch_buffer;
    char ch_data;

    int i_count;
    int i_num_ei;

    bool bl_flag_iseEntered;

    i_num_ei = 0;

    while ((ch_buffer = getchar()) != '#')
    {
        ch_data = ch_buffer;
        printf("%c", ch_data);

        if ((true == bl_flag_iseEntered) && ('i' == ch_data))
        {
            i_num_ei++;
            bl_flag_iseEntered = false;
        }
        else
        {
            bl_flag_iseEntered = false;
        }

        if ('e' == ch_data) // 当检测到e时
        {
            bl_flag_iseEntered = true;
            continue;
        }
    }
    printf("\n");
    printf("'ei' appears %d times.", i_num_ei);

    return 0;
}
