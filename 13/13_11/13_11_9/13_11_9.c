/**
 * 9.修改程序清单 13.3 中的程序，从 1 开始，根据加入列表的顺序为每个单词编号。
 * 当程序下次运行时，确保新的单词编号接着上次的编号开始。
 *
 * 1 first
 * 2 second
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 41

/**
 * 文件中文本的合法格式：
 * [文件开始] + [一行(一个单词)] + [下一行(下一个单词)] + ... + [文件结束]
 *
 * 文件中“一行（一个单词）”合法格式：
 * [数字（编号）] + [一个制表符\t] + [一串字符串(中间不允许有空格)] + [一个换行符\n]
 *
 * 程序打开文件后，
 * 首先读取并验证文件第一行的内容的格式是否合法并且是否为空
 *      不合法，则继续检查文件是否为空
 *          不为空，则报告错误、关闭文件并退出程序
 *          为空，则准备进行单词输入
 *      如果格式合法，则继续验证本行编号是否合法（是否为1），
 *
 *          如果本行编号为1，则继续
 *
 * BEGIN:   程序打开文件，
 * *1:  首先读取并验证文件第一行的内容的格式是否合法并且是否为空
 * *a1:     格式合法，则继续验证本行编号是否合法
 * *aa1:    
 * *
 */
int main(void)
{
    FILE *fp;
    char words[MAX];

    if ((fp = fopen("wordy", "a+")) == NULL)
    {
        fprintf(stdout, "Can't open \"wordy\" file.\n");
        exit(EXIT_FAILURE);
    }

    puts("Enter words to add to the file; press the #");
    puts("key at the beginning of a line to terminate.");

    while ((fscanf(stdin, "%40s", words) == 1) && (words[0] != '#'))
        fprintf(fp, "%s\n", words);

    puts("File contents:");
    rewind(fp); /* 返回到文件开始处 */

    while (fscanf(fp, "%s", words) == 1)
        puts(words);

    puts("Done!");

    if (fclose(fp) != 0)
        fprintf(stderr, "Error closing file\n");

    return 0;
}
