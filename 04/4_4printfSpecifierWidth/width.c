#include <stdio.h>
#define PAGES 959

int main(int argc, char const *argv[])
{
    printf("*%d*\n", PAGES);
    printf("*%2d*\n", PAGES);
    printf("*%10d*\n", PAGES);
    printf("*%-10d*", PAGES);
    return 0;
}
