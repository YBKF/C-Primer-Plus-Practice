#include <stdio.h>

int main(int argc, char const *argv[])
{
    char ch_arr[26];

    for (int i = 0; i < 26; i++)
    {
        printf("%c", ch_arr[i] = i + 'a');
    }

    return 0;
}
