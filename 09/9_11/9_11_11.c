#include <stdio.h>

void Fibonacci(unsigned long item);

int main(int argc, char const *argv[])
{
    Fibonacci(50);

    return 0;
}

void Fibonacci(unsigned long item)
{
    unsigned long u_f[item];

    u_f[0] = 1;
    u_f[1] = 1;

    printf("%u %u ", u_f[0], u_f[1]);

    for (int i = 2; i < item; i++)
    {
        u_f[i] = u_f[i - 1] + u_f[i - 2];
        printf("%u ", u_f[i]);
    }

    return;
}
