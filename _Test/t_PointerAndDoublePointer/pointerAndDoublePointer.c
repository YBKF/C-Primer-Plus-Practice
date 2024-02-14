#include <stdio.h>

int main(int argc, char const *argv[])
{
    int(*ip)[5];
    int **idp;

    int i[2][5] = {{11, 12, 13, 14, 15}, {21, 22, 23, 24, 25}};

    int *ip_arr[2] = {i[0], i[1]};

    ip = i;
    idp = ip_arr;

     

    return 0;
}
