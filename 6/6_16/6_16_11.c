#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i_arr[8];
    int i_count;

    printf("Enter eight numbers:\n");
    for (i_count = 0; i_count < 8; i_count++)
    {
        scanf("%d", &i_arr[i_count]);
    }

    for (i_count = 7; i_count >= 0; i_count--)
    {
        printf("%d", i_arr[i_count]);
    }

    return 0;
}
