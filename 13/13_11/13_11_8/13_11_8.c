/**
 * 8.编写一个程序，以一个字符和任意文件名作为命令行参数。
 * 如果字符后面没有参数，该程序读取标准输入；
 * 否则，程序依次打开每个文件并报告每个文件中该字符出现的次数。
 * 文件名和字符本身也要一同报告。程序应包含错误检查，以确定参数数量是否正确和是否能打开文件。
 * 如果无法打开文件，程序应报告这一情况，然后继续处理下一个文件。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 检查参数数量
    if (argc < 2)
    {
        fputs("ERROR: Too few arguments.\n", stderr);
        exit(EXIT_FAILURE);
    }
    else if (strnlen(argv[1], 2) > 1)
    {
        // 检查第一个参数是否为单字符
        fputs("The first argument is invalid.\n", stderr);
        exit(EXIT_FAILURE);
    }
    else if (argc > 2) // 命令行参数多于一个参数时
    {
        // 检查文件名长度
        for (int i = 2; i < argc; i++)
        {
            if (argv[i] == NULL || strnlen(argv[i], FILENAME_MAX) >= FILENAME_MAX) // 检测文件名
            {
                fprintf(stderr, "ERROR: Invalid filename found \"%s\"\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        }
    }

    char ch_find = *argv[1];
    FILE *fp = stdin; // 默认指向标准输入

    if (argc > 2)
    {
        for (int i = 2; i < argc; i++)
        {
            int count = 0;

            if ((fp = fopen(argv[i], "r")) == NULL)
            {
                // 若无法打开文件，则报告错误并继续处理下一个文件
                fprintf(stderr, "Cannot open file: %s\n", argv[i]);
                continue;
            }

            int ch_temp = 0;

            /* 成功打开文件 */
            while ((ch_temp = getc(fp)) != EOF)
                if (ch_temp == ch_find)
                    count++;

            printf("Found %3d \"%c\" in the file \"%s\"\n", count, ch_find, argv[i]);

            if (ferror(fp))
                fprintf(stderr, "ERROR: An error occurred in reading file: %s\n", argv[i]);

            if (fclose(fp) != 0)
                fprintf(stderr, "ERROR: Failed to close file: %s\n", argv[i]);
        }
    }
    else
    {
        int count = 0;

        int ch_temp = 0;

        while ((ch_temp = getc(fp)) != EOF)
            if (ch_temp == ch_find)
                count++;

        if (ferror(fp))
            fputs("ERROR: An error occurred in reading stdin.\n", stderr);

        printf("Found %3d \"%c\" in stdin\n", count, ch_find);
    }

    return 0;
}
