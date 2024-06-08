/**
 * 7.编写一个程序打开两个文件。可以使用命令行参数或提示用户输入文件名。
 *
 * b.修改该程序，把行号相同的行打印成一行。
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int print_a_file_line(FILE *file);
int print_files_same_num_line(FILE *file_a, FILE *file_b);

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

    if (print_files_same_num_line(fp_a, fp_b) == EOF)
        fputs("ERROR: Unknown error when reading files.\n", stderr);

    fclose(fp_a);
    fclose(fp_b);

    return 0;
}

/**
 * 打印文本文件中的一行，
 * 一个一个打印文件中的字符直到遇到换行符或文件结尾，
 * 遇到换行符或文件结尾时，结束当前的读取和输出（此时读取遇到换行符时不会打印此换行符），
 * 若读取遇到的是文件结尾则返回EOF，
 * 若读取遇到的是换行符则返回读取到的字符的个数（包括换行符，一般情况下必定是正数）。
 */
int print_a_file_line(FILE *file)
{
    if (file == NULL)
        return 0;

    int ch;
    int count = 1;

    while ((ch = getc(file)) != '\n' && ch != EOF)
    {
        putc(ch, stdout);
        count++;
    }

    if (ch == EOF)
        return EOF;

    return count;
}

/**
 * 把两个文件中行数相同的行打印到同一行中（文件中一行中即使只是空行也算作一行），
 * 打印中遇到错误时返回EOF，否则返回0。
 */
int print_files_same_num_line(FILE *file_a, FILE *file_b)
{
    int ret_val_a;
    int ret_val_b;

    while (1)
    {
        if ((ret_val_a = print_a_file_line(file_a)) > 0)
            /* Do nothing. */;
        else if (ret_val_a == EOF)
            break;
        else
            return EOF;

        if ((ret_val_b = print_a_file_line(file_b)) > 0)
            /* Do nothing. */;
        else if (ret_val_b == EOF)
            break;
        else
            return EOF;

        putc('\n', stdout);
    }

    return 0;
}
