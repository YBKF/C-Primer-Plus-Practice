/**
 * 7.编写一个程序打开两个文件。可以使用命令行参数或提示用户输入文件名。
 *
 * a.该程序以这样的顺序打印：
 * 打印第1个文件的第1行，第2个文件的第1行，第1个文件的第2行，第2个文件的第2行，
 * 以此类推，打印到行数较多文件的最后一行。
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int print_a_file_line(FILE *file);
int print_files_lineByline(FILE *file_a, FILE *file_b);

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

    if (print_files_lineByline(fp_a, fp_b) == EOF)
        fputs("ERROR: Unknown error when reading files.\n", stderr);

    fclose(fp_a);
    fclose(fp_b);

    return 0;
}

/**
 * 打印文本文件中的一行，
 * 一个一个打印文件中的字符直到遇到换行符或文件结尾，
 * 遇到换行符或文件结尾时，结束当前的读取和输出（此时读取遇到换行符时不会打印此换行符），
 * 并打印一个换行符，
 * 若读取遇到的是文件结尾则返回EOF，
 * 若读取遇到的是换行符则返回读取到的字符的个数（包括换行符，一般情况下必定是正数）。
 */
int print_a_file_line(FILE *file)
{
    if (file == NULL)
        return 0;

    int ch;
    int count = 1; // 参数经检测后，此函数至少会打印一个换行符，换行符列入计数

    while ((ch = getc(file)) != '\n' && ch != EOF)
    {
        putc(ch, stdout);
        count++;
    }
    putc('\n', stdout);

    if (ch == EOF)
        return EOF;

    return count;
}

/**
 * 一行一行地分别打印两个文件的文本
 * 打印中遇到错误时返回EOF，否则返回0。
 */
int print_files_lineByline(FILE *file_a, FILE *file_b)
{
    if (file_a == NULL || file_b == NULL)
        return EOF;

    FILE *file_cur = file_a;
    int ret_val;

    while (1)
    {
        ret_val = print_a_file_line(file_cur);

        if (file_cur == file_a)
            file_cur = file_b;
        else
            file_cur = file_a;

        if (ret_val > 0)
            continue;
        else if (ret_val == EOF)
            break;
        else
            return EOF;
    }

    while (print_a_file_line(file_cur) != EOF)
        continue;

    return 0;
}
