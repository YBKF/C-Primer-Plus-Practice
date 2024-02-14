#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i_ceiling, i_floor;

    printf("Please enter the floor and ceiling what you want(Use spaces between datas):\n");
    for (scanf("%d %d", &i_floor, &i_ceiling);
         i_floor <= i_ceiling;
         i_floor++)
    {
        printf("Num: %4d,\t Ceil: %6d,\t Floor: %6d\n", i_floor, i_floor * i_floor, i_floor * i_floor * i_floor);
    }
    return 0;
}
