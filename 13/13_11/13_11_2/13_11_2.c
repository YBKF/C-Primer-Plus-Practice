/**
 * 2.编写一个文件拷贝程序，该程序通过命令行获取原始文件名和拷贝文件名。
 * 尽量使用标准I/O和二进制模式。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE (8192)

FILE *openfileAndCheck(const char *filename, const char *mode);
void copy(FILE *file_source, FILE *file_dest);

int main(int argc, char const *argv[])
{
    FILE *file_source;
    FILE *file_dest;
    const char *const file_name_source = argv[1];
    const char *const file_name_dest = argv[2];

    /* 对命令行参数进行检查 */
    if (argc != 3)
    {
        if (argc < 3)
            fputs("ERROR: Too few arguments.\n", stderr);
        else if (argc > 3)
            fputs("ERROR: Too many arguments.\n", stderr);
        fputs("Expected 2 arguments.\n", stderr);
        exit(EXIT_FAILURE);
    }

    if (strcmp(file_name_dest, file_name_source) == 0)
    {
        fputs("ERROR: Can't copy file to itself.\n", stderr);
        exit(EXIT_FAILURE);
    }

    // // 期望获取的“文件名”参数可能并非单纯文件名而是一长串带有文件名的地址，所以此处语句并不能保证其按照期望中运行
    // if (strlen(file_name_dest) > (FILENAME_MAX - 1) || strlen(file_name_source) > (FILENAME_MAX - 1))
    // {
    //     fputs("ERROR: Invalid Filename. It's too long.\n", stderr);
    //     exit(EXIT_FAILURE);
    // }

    file_source = openfileAndCheck(file_name_source, "rb");
    file_dest = openfileAndCheck(file_name_dest, "wb");

    copy(file_source, file_dest);
    if (ferror(file_source) != 0)
        fprintf(stderr, "An error in reading file: %s.\n", file_name_source);

    if (ferror(file_dest) != 0)
        fprintf(stderr, "An error in writing file: %s.\n", file_name_dest);

    fprintf(stdout, "File %s copied to %s.\n", file_name_source, file_name_dest);

    fclose(file_dest);
    fclose(file_source);

    return 0;
}

FILE *openfileAndCheck(const char *filename, const char *mode)
{
    FILE *file_check;

    if ((file_check = fopen(filename, mode)) == NULL)
    {
        fprintf(stderr, "Can't open %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Opened file: %s.\n", filename);

    if (setvbuf(file_check, NULL, _IOFBF, BUF_SIZE) != 0)
    {
        fputs("Can't create buffer.\n", stderr);
        exit(EXIT_FAILURE);
    }

    return file_check;
}

void copy(FILE *file_source, FILE *file_dest)
{
    size_t bytes;
    static char temp[BUF_SIZE];
    while ((bytes = fread(temp, sizeof(char), BUF_SIZE, file_source)) > 0)
        fwrite(temp, sizeof(char), bytes, file_dest);
}
