/**
 * 7.编写一个程序打开两个文件。可以使用命令行参数或提示用户输入文件名。
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // 检查参数数量
    if (argc != 3)
    {
        if (argc < 3)
            fputs("ERROR: Too few arguments.\n", stderr);
        else
            fputs("ERROR: Too many arguments.\n", stderr);

        exit(EXIT_FAILURE);
    }

    // 检查文件名长度
    for (int i = 1; i < argc; i++)
    {
        if (argv[i] == NULL || strnlen(argv[i], FILENAME_MAX) >= FILENAME_MAX)
        {
            fprintf(stderr, "ERROR: Invalid filename: \"%s\"\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    FILE *fp_a;
    FILE *fp_b;
    const char *filename_a = argv[1];
    const char *filename_b = argv[2];

    if ((fp_a = fopen(filename_a, "r")) == NULL)
    {
        fprintf(stderr, "ERROR: Cannot open file: \"%s\"\n", filename_a);
        exit(EXIT_FAILURE);
    }
    else
        fprintf(stdout, "File opened: \"%s\"\n", filename_a);

    if ((fp_b = fopen(filename_b, "r")) == NULL)
    {
        fprintf(stderr, "ERROR: Cannot open file: \"%s\"\n", filename_b);
        exit(EXIT_FAILURE);
    }
    else
        fprintf(stdout, "File opened: \"%s\"\n", filename_b);

    if (fclose(fp_a) != 0)
        fprintf(stderr, "ERROR: Error in closing file %s\n", filename_a);

    if (fclose(fp_b) != 0)
        fprintf(stderr, "ERROR: Error in closing file %s\n", filename_b);

    return 0;
}
