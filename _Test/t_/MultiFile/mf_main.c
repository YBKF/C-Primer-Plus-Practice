#include <stdio.h>
#include "mf_mod.h"

int main(int argc, char const *argv[])
{
    int added = 0;

    printlnString("hello world.");

    added = add(1, 2);
    printlnInt(added);

    return 0;
}
