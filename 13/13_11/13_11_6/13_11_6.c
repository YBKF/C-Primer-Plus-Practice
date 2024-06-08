/**
 * 6.使用命令行参数的程序依赖于用户的内存如何正确地使用它们。重写程序清单 13.2 中的程序，不使用命令行参数，而是提示用户输入所需信息。
 */
#include <stdio.h>
#include <stdlib.h> // 提供 exit()的原型
#include <string.h> // 提供 strcpy()、strcat()的原型
#define LEN 40

char *s_gets(char *s, int n);

int main()
{
    FILE *in, *out; // 声明两个指向 FILE 的指针
    int ch;
    char filename_src[LEN + 1]; // 储存源文件名
    char filename_out[LEN];     // 储存输出文件名
    int count = 0;              // 检查命令行参数

    fputs("Enter name of source file:\n", stdout);

    // 验证文件名长度
    s_gets(filename_src, LEN + 1);
    if (strnlen(filename_src, LEN) >= LEN)
        fputs("ERROR: Filename too long.\n", stderr);

    // 设置输入
    if ((in = fopen(filename_src, "r")) == NULL)
    {
        fprintf(stderr, "I couldn't open the file \"%s\"\n",
                filename_src);
        exit(EXIT_FAILURE);
    }

    // 设置输出
    strncpy(filename_out, filename_src, LEN - 5); // 拷贝文件名
    filename_out[LEN - 5] = '\0';
    strcat(filename_out, ".red"); // 在文件名后添加.red
    if ((out = fopen(filename_out, "w")) == NULL)
    { // 以写模式打开文件fprintf(stderr, "Can't create output file.\n");
        exit(3);
    }

    // 拷贝数据
    while ((ch = getc(in)) != EOF)
        if (count++ % 3 == 0)
            putc(ch, out); // 打印3个字符中的第1个字符

    // 收尾工作
    if (fclose(in) != 0 || fclose(out) != 0)
        fprintf(stderr, "Error in closing files\n");

    return 0;
}

/**
 * 从标准输入中读取字符，并将读取到的字符存入 st，
 * 直到读到新的一行或读取了 n-1 个字符又或是读取到文件结尾（EOF），
 * 功能类似于 gets() 但可以设置最大读取字符数。
 * 读取结束后，在字符串结尾添加一个空字符并返回 st 的地址，
 * 如果还未向 st 存入任何字符便读到文件结尾（EOF）则返回NULL且不向字符串结尾添加空字符。
 * 一旦在读取过程中出现错误则返回NULL。
 */
char *s_gets(char *st, int n)
{
    char *ret_val;
    char *find;
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n'); // 查找换行符
        if (find)                // 如果地址不是NULL，
            *find = '\0';        // 在此处放置一个空字符
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}