#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char ch_arr_target[40];

    char *s1 = "This is a string. \0Can you see it?";
    char *s2 = "Another string.";

    strcat(ch_arr_target, s1);
    strcat(ch_arr_target, s2);

    puts(ch_arr_target);

    return 0;
}
