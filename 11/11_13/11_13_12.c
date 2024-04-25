/*
12.编写一个程序，读取输入，直至读到 EOF，报告读入的单词数、大
写字母数、小写字母数、标点符号数和数字字符数。使用ctype.h头文件中的
函数。
*/
#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    char checking;
    int numOfWords = 0;
    int numOfUpper = 0;
    int numOfLower = 0;
    int numOfPunct = 0;
    int numOfAlnum = 0;
    int isinWord = 0;

    fputs("Type something, and type 'EOF' to end:\n", stdout);

    // 读取并分析
    while ((checking = getc(stdin)) != EOF)
    {
        if (isalpha(checking))
        {
            isinWord = 1;
            if (isupper(checking))
                numOfUpper++;
            else
                numOfLower++;
        }
        else
        {
            if (isinWord)
            {
                isinWord = 0;
                numOfWords++;
            }

            if (ispunct(checking))
                numOfPunct++;
            else if (isalnum(checking))
                numOfAlnum++;
        }
    }

    // 若离开循环后 isinWord == 1，则表示循环中有一个单词未检测完毕便遇到EOF，这时需在循环外结束单词检测并将单词计数+1
    if (isinWord)
        numOfWords++;

    // 报告
    printf("Number of words: %d,\n", numOfWords);
    printf("Number of Uppercase letters: %d,\n", numOfUpper);
    printf("Number of Lowercase letters: %d\n", numOfLower);
    printf("Number of Punctuations: %d\n", numOfPunct);
    printf("Number of Alnum: %d\n", numOfAlnum);

    return 0;
}
