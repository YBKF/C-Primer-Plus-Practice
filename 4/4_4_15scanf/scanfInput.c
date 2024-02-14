#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i;
    char c;
    float f;
    char s[30];
    scanf("%d %f %s", &i, &f, &s);
    scanf("%c", &c);
    printf("Input: %d %f %s %c\n", i, f, s, c);
    return 0;
}
