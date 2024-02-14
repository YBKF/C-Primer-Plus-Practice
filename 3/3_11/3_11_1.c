#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i_i = 0x7FFFFFFF;
    float d_f = 0xFFFFFFp0f;
    printf("i_i = %d\nd_f = %f\ni_i + 1 =%d\nd_f + 1.0 = %f\n",
        i_i, d_f, i_i+1, d_f+1.0);
    return 0;
}
