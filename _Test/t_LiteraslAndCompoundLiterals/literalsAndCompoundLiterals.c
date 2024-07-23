#include <stdio.h>

int main(int argc, char const *argv[])
{
    int *a;

    // printf("%p %p\n", &1, &1);                  // error: lvalue required as unary '&' operand
    printf("%p %p %p\n", &(int){1}, &(int){1}, (a = &(int){1})); //

    return 0;
}
