/**
 * 12.创建一个文本文件，内含20行，每行30个整数。
 * 这些整数都在0～9 之间，用空格分开。
 * 该文件是用数字表示一张图片，0～9表示逐渐增加的灰度。
 * 编写一个程序，把文件中的内容读入一个20×30的int数组中。
 * 一种把这些数字转换为图片的粗略方法是：该程序使用数组中的值初始化一个 20×31 的字符数组，
 * 用值 0 对应空格字符，1 对应点字符，以此类推。
 * 数字越大表示字符所占的空间越大。例如，用#表示9。
 * 每行的最后一个字符（第31个）是空字符，这样该数组包含了20个字符串。
 * 最后，程序显示最终的图片（即，打印所有的字符串），并将结果储存在文本文件中。
 */

/**
 * 首先，读取文件中的一行，尝试将此行的所有数字字符转换为整型，读到单行字符上限（30）为止，重复调用至要求的次数（20）；
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INT_PIC_LENGTH (30)
#define INT_PIC_WIDTH (20)
#define CHAR_PIC_LENGTH INT_PIC_LENGTH
#define CHAR_PIC_LENGTH_SIZE (CHAR_PIC_LENGTH + 1)
#define CHAR_PIC_WIDTH INT_PIC_WIDTH
#define CHAR_PIC_PIXEL_SIZE (4)

int parseCharPicture2Int(int iPicLength, int iPicWidth, int iPic[][INT_PIC_LENGTH], FILE *file);

/**
 * 源文件：字符形式存在的数字
 * 数字图：纯整型
 * 字符图：（数字转换为字符后的）字符
 */
int main(int argc, char const *argv[])
{
    int iPic[INT_PIC_WIDTH][INT_PIC_LENGTH] = {};

    parseCharPicture2Int(INT_PIC_LENGTH, INT_PIC_WIDTH, iPic, stdin);

    return 0;
}

/**
 * 检查源文件中每行的字符数量是否符合用户对图像长度的要求(?==iPicLength)，
 * 一行中读取的字符的数量不超过要求的长度(iPicLength);
 * 一行中字符的数量未到达要求的长度(iPicLength)的，
 * 则在存储到图像(iPic)中时会将剩下的空位填充为数字0，
 * 一直读到文件结尾为止;
 *
 * 检查源文件读取的行的数量是否符合用户对图像宽度的要求(?==iPicWidth)，
 * 最多读取到要求的行的数量(iPicWidth);
 * 若读完整个文件时，读取到的行的行数低于要求的行数(iPicWidth)，
 * 则读取到的行数到要求行数之间的所有空行均被填充为数字0。
 *
 * 以上过程中读取到的内容，均保存到用户指定的图像（二维整型数组iPic）中;
 * 读取完毕后将返回成功读取到的元素的数量，
 * 读取过程中遇到任何错误则报告错误并返回当前已读取到的值
 */
int parseCharPicture2Int(int iPicLength, int iPicWidth, int iPic[][INT_PIC_LENGTH], FILE *file)
{
    if (file == NULL)
    {
        fputs("ERROR: NULL File.\n", stderr);
        return 0;
    }

    if (iPic == NULL)
    {
        fputs("ERROR: NULL Pointer.\n", stderr);
        return 0;
    }

    if (iPicLength <= 0 || iPicWidth <= 0)
        return 0;

    /**
     * *1:  首先，检测 [本行已保存的字符串的数量] 是否小于要求的长度(iPicLength)；
     * *a1:     小于要求的长度(iPicLength)，则从文件中读取一个字符并把这个字符存储到一个临时的 [字符缓存] 中，
     * *a2:     然后，检测 [字符缓存] 中的字符是否为数字字符；
     * *aa1:        为数字字符，则将 [字符缓存] 中的字符存储到 [字符串缓存] 数组中（此数组只有4个元素，最多存储3个有效字符），\
     * *aa2:        然后，goto a1；
     * *ab1:        不为数字字符，则检测此字符:
     * *aba1:           - 为空格字符，则将 [字符串缓存] 中的字符转换为整型，并保存到 [二维整型数组] 中 [二维整型数组] 列数+1，[本行已保存的字符串的数量] + 1，[以保存的字符串的总量] + 1，\
     * *aba2:           然后 goto 1；
     * *abb1:           - 为换行符，则将 [字符串缓存] 中的字符转换为整型，并保存到 [二维整型数组] 中，\
     * *abb2:           然后，检测 [本行已保存的字符串的数量] 是否小于要求的长度(iPicLength)；
     * *abba1:              小于要求的长度，则将 [二维整型数组] 当前行剩下的所有元素填充为 0，\
     * *abba2:              然后，goto 1；
     * *abbb1:              不小于要求的长度，则 goto 1；
     * *abc1:           - 为文件结尾(EOF)，则 [文件结尾标志] 设为 true，
     * *abc2:           然后，若 [本行已保存的字符串的数量] 小于要求的长度(iPicLength)，则将 [二维整型数组] 当前行剩下的所有元素填充为 0
     * *abc3:           最后，goto 1；
     * *abd1:           - 为其他字符，则抛弃此字符，goto a1；
     * *b1:     不小于要求的长度(iPicLength)，检测是否到达文件结尾（检测 [文件结尾标志] 是否为 true）；
     * *ba1:        为true，则返回 [以保存的字符串的总量]；
     * *bb1:        不为true，则 [二维整型数组] 行数+1， [本行已保存的字符串的数量] 置零
     */
}