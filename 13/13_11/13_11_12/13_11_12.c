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
// TODO: 可有malloc()动态数组版本

#include <stdio.h>
#include <stdlib.h>

#define INT_PIC_LENGTH (20)
#define INT_PIC_WIDTH (30)
#define CHAR_PIC_LENGTH_SIZE (INT_PIC_LENGTH + 1)
#define CHAR_PIC_WIDTH INT_PIC_WIDTH

int **checkAndGetPic(int picLength, int picWidth, int (*iPic)[INT_PIC_LENGTH], FILE *file);
void transFile2IntPic(FILE *file, int (*iPic)[INT_PIC_LENGTH]);
void transIntPic2CharPic(int (*iPic)[INT_PIC_LENGTH], char (*chPic)[CHAR_PIC_LENGTH_SIZE]);

int main(int argc, char const *argv[])
{
    return 0;
}


/**
 * 检查源文件中每行的字符数量是否符合用户对图像长度的要求(?==picLength)，
 * 一行中读取的字符的数量不超过要求的长度(picLength);
 * 一行中字符的数量未到达要求的长度(picLength)的，
 * 则在存储到图像(iPic)中时会将剩下的空位填充为数字0，
 * 一直读到文件结尾为止;
 *
 * 检查源文件读取的行的数量是否符合用户对图像宽度的要求(?==picWidth)，
 * 最多读取到要求的行的数量(picWidth);
 * 若读完整个文件时，读取到的行的行数低于要求的行数(picWidth)，
 * 则读取到的行数到要求行数之间的所有空行均被填充为数字0。
 *
 * 以上过程中读取到的内容，均保存到用户指定的图像（二维整型数组iPic）中;
 * 读取完毕后将返回第三个参数地址，
 * 读取过程中遇到任何错误则返回空指针(NULL)
 */
int **checkAndGetPic(int picLength, int picWidth, int iPic[][], FILE *file)
{
}