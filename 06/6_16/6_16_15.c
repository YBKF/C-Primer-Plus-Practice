#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    char ch_content[255];
    bool bool_isEqualEnter = false;
    int i_seq;

    printf("Please enter a string of characters:\n");
    for (i_seq = 0; bool_isEqualEnter != true; i_seq++)
    {
        scanf("%c", &ch_content[i_seq]);
        bool_isEqualEnter = '\n' == ch_content[i_seq];
        // printf("isEqualEnter=%d\n", bool_isEqualEnter);
    }
    // printf("Done. And seq=%d. strlen=%d", i_seq, strlen(ch_content));
    for (i_seq = strlen(ch_content); i_seq >= 0; i_seq--)
    {
        printf("%c", ch_content[i_seq]);
    }

    return 0;
}
