#include <stdio.h>
/**
 * friend=5;
 * friend=(friend-seq)*2;
 */

int main(int argc, char const *argv[])
{
    int i_friend;
    int i_week;
    for (i_week = 1, i_friend = 5; i_friend < 150; i_week++)
    {
        i_friend = (i_friend - i_week) * 2;
        printf("Week: %d, Friend: %d\n", i_week, i_friend);
    }
    return 0;
}
