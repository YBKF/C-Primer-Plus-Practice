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
#define BUF_SIZE (4096)

/**
 * 文件中文本的合法格式：
 * [文件开始] + [一行(一个单词)] + [下一行(下一个单词)] + ... + [文件结束]
 *
 * 文件中“一行（一个单词）”合法格式：
 * [数字（编号）] + [空白字符] + [一串字符串(中间不允许有空格)] + [一个换行符\n]
 *
 * STATIC:  number = 0; 存储程序运行时检测到的最新的合法编号
 * BEGIN:   程序以读写模式打开文件，
 * *1:  读取并验证文件[第一行]的内容的格式是否合法
 * *a1:     格式合法，则继续验证本行编号是否合法
 * *aa1:        编号合法（检测是否为 number + 1），number = 当前编号
 * *aa2:            然后，goto 1，验证下一行
 * *ab1:        编号不合法（!= number + 1），则报告错误、关闭文件并退出程序
 * *b1:     格式不合法，则继续检查本行是否为空
 * *ba1:        为空，则准备进行单词输入
 * *bb1:        不为空，则报告错误、关闭文件并退出程序
 */

int check_file_line(FILE *file);
int check_file(FILE *file);

int main(void)
{
    FILE *fp;
    char words[MAX] = {};

    if ((fp = fopen("wordy.test", "a+")) == NULL)
    {
        fprintf(stdout, "Can't open \"wordy.test\" file.\n");
        exit(EXIT_FAILURE);
    }

    int ret_val_check;
    int word_num;

    // check_file() 返回值>=0时，表示文件合法，此时的返回值为最后一个单词的编号
    if ((ret_val_check = check_file(fp)) < 0)
    {
        fprintf(stderr, "ERROR: Invalid file: %s\n", "\"wordy.test\"");
        exit(EXIT_FAILURE);
    }

    word_num = ret_val_check;
    word_num++;

    puts("Enter words to add to the file; press the #");
    puts("key at the beginning of a line to terminate.");

    while ((fscanf(stdin, "%40s", words) == 1) && (words[0] != '#'))
    {
        fprintf(fp, "%d %s\n", word_num, words);
        word_num++;
    }

    puts("File contents:");
    rewind(fp); /* 返回到文件开始处 */

    while (fscanf(fp, "%d %s\n", &word_num, words) == 2)
        fprintf(stdout, "%d %s\n", word_num, words);

    puts("Done!");

    if (fclose(fp) != 0)
        fprintf(stderr, "Error closing file\n");

    return 0;
}

/**
 * ! 注意：此函数将返回值用作多种用途，在此处可能并不是一个好的实现，可能会因疏忽而导致诸多的漏洞
 *
 * 检查文件中一行格式的合法性，
 * 返回值：
 * > 0  ，此行合法，返回值为此行的编号；
 * == 0 ，读取文件时遇到错误（无法读取文件）；
 * EOF  ，遇到文件结尾；
 * < -1  ，遇到错误。
 *
 * 文件中“一行（一个单词）”合法格式：
 * [数字（编号）] + [空白字符（空格）] + [一串字符串（中间不允许有空格）] + [一个换行符\n]
 */
int check_file_line(FILE *file)
{
    if (file == NULL)
        return 0;

    int num_line;
    char word_temp[MAX];
    int status; // 用于获取fscanf()函数的返回值，当在函数中检测到文件的不合规的错误时便于进行分析处理

    /*
    一行的合法性检测分为两步，
    1、使用fscanf()函数检测换行符之前的格式的合法性；
    2、检测第一步之后的连续的字符是否为换行符，如果为换行符则合法。
    在此处先进行第一步检测，第一步通过后再进行第二步检测。

    fscanf() 返回值为 2 且第二步检测到换行符时，则表示本行合法（由于此处简单使用了fscanf(file, " %d %s\n", &num_line, word_temp)，所以并不保证严格合法）
    fscanf() 返回值为 -1 时，则表示顺利检测到文件结尾；
    其他返回值都表示本行不合法，需要在调用函数处报告错误。 */
    if ((status = fscanf(file, " %d %s\n", &num_line, word_temp)) == 2)
    {
        if (num_line <= 0)
        {
            fprintf(stderr, "ERROR: Invalid line number %d\n", num_line);
            return -4;
        }

        fseek(file, -1L, SEEK_CUR);
        if (getc(file) != '\n') // 未检测到换行符，本行不合法
        {
            fprintf(stderr, "ERROR: Failed to find a line break after the word at line %d\n", num_line);
            return -3;
        }
        else
            return num_line;
    }
    else if (status == EOF && !ferror(file))
    {
        return EOF;
    }
    else
    {
        fputs("ERROR: Invalid file formation.\n", stderr);
        return -2;
    }
}

/**
 * 检查文件合法性并返回文件中最后一个单词的编号（>=0），
 * 编号为 0 表示当前文件为空。
 * 若文件不合法则返回 EOF
 *
 * 文件中“一行（一个单词）”合法格式：
 * [数字（编号）] + [空白字符（空格）] + [一串字符串（中间不允许有空格）] + [一个换行符\n]
 */
int check_file(FILE *file)
{
    if (file == NULL)
        return EOF;

    static int word_number = 0; // 单词的编号，文件合法时将存储文件最后一个单词的编号，也用于检测单词编号是否合法
    int number_temp;
    int status;

    // 检查每一行的内容的合法性
    while ((status = check_file_line(file)) > 0)
    {
        // 进入循环的 status 值为当前行的编号
        number_temp = status;

        // 格式检测通过，然后检查编号合法性
        if (number_temp == (word_number + 1))
            word_number = number_temp;
        else
        {
            status = 0;
            fprintf(stderr, "ERROR: Invalid word number: %d\n", number_temp);
            break;
        }
    }

    if (status == EOF && !ferror(file))
    {
        return word_number;
    }
    else // status == 0 || status < -1
    {
        fputs("ERROR: An error ocurred while checking the file.\n", stderr);
        return EOF;
    }
}
