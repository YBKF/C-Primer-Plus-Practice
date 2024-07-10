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

#define INT_PIC_WIDTH (30)
#define INT_PIC_HEIGHT (20)
#define CHAR_PIC_WIDTH INT_PIC_WIDTH
#define CHAR_PIC_WIDTH_SIZE (CHAR_PIC_WIDTH + 1)
#define CHAR_PIC_HEIGHT INT_PIC_HEIGHT
#define CHAR_PIC_PIXEL_SIZE (4)
#define CHAR_PIC_STR_BUF_SIZE CHAR_PIC_PIXEL_SIZE

#define CHAR_IS_OTHERS (0x0001)
#define CHAR_IS_DIGIT (0x0002)
#define CHAR_IS_SPACE (0x0004)
#define CHAR_IS_LF (0x0008)
#define CHAR_IS_EOF (0x0010)

#define PARSE_OTHERS (0x0001)
#define PARSE_DIGIT (0x0002)
#define PARSE_SPACE (0x0004)
#define PARSE_LF (0x0008)
#define PARSE_EOF (0x0010)

int CharInfo(int iCh, unsigned int *uiInfo);
int parseCharPictureIntoIntArr(int iPicWidth, int iPicHeight, FILE *file, int iPic[][INT_PIC_WIDTH]);

/**
 * 源文件：字符形式存在的数字
 * 数字图：纯整型
 * 字符图：（数字转换为字符后的）字符
 */
int main(int argc, char const *argv[])
{
    int iPic[INT_PIC_HEIGHT][INT_PIC_WIDTH] = {};

    parseCharPictureIntoIntArr(INT_PIC_WIDTH, INT_PIC_HEIGHT, iPic, stdin);

    return 0;
}

/**
 * Param:
 * - [in] iCh
 * - [out] uiInfo
 *
 * 分析输入的字符参数 [in] iCh 的类型，将得到的结果存储到参数 [out] uiInfo 中，并返回 iCh
 * 支持的字符类型：
 * - CHAR_IS_OTHERS (0x0001)
 * - CHAR_IS_DIGIT (0x0002)
 * - CHAR_IS_SPACE (0x0004)
 * - CHAR_IS_LF (0x0008)
 * - CHAR_IS_EOF (0x0010)
 */
int CharInfo(int iCh, unsigned int *uiInfo)
{
    if (isdigit(iCh))
        *uiInfo = CHAR_IS_DIGIT;
    else if (iCh == ' ')
        *uiInfo = CHAR_IS_SPACE;
    else if (iCh == '\n')
        *uiInfo = CHAR_IS_LF;
    else if (iCh == EOF)
        *uiInfo = CHAR_IS_EOF;
    else
        *uiInfo = CHAR_IS_OTHERS;

    return iCh;
}

/**
 * - [in] uiOptions
 * - [out] pchStr
 * - [out] pchChar
 * - [in] iMaxCount
 * - [in] file
 *
 * 根据 uiOptions 参数设定的读取规则来依次连续读取指定文件 file 中的指定类型的字符，
 * 符合规则的字符将存储到 pchStr 字符串中，直到遇到读取规则外的其他类型的字符或是到达读取上限 iMaxCount。
 *
 * [in] uiOptions 支持的参数：
 * - PARSE_OTHERS (0x0001)
 * - PARSE_DIGIT (0x0002)
 * - PARSE_SPACE (0x0004)
 * - PARSE_LF (0x0008)
 * - PARSE_EOF (0x0010)
 * 支持复合参数，如 "PARSE_DIGIT | PARSE_SPACE"
 *
 * [out] pchStr 应当为一个指针，指向一串字符串，参数可为 NULL；
 * 为 NULL 时，函数仅读取字符而不存储。
 *
 * [out] pchChar 存储函数返回时最后读取到的字符
 *
 * [in] iMaxCount
 * 存储字符的数量上限
 *
 * [in] file
 * 读取的文件
 *
 * 调用成功返回 1
 * 发生错误时返回 0
 */
int ParseAString(unsigned int uiOptions, char *pchStr, int *pchChar, int iMaxCount, FILE *file)
{
    if (file == NULL)
    {
        fputs("ERROR: NULL File.\n", stderr);
        return 0;
    }

    if (pchStr == NULL)
    {
        fputs("ERROR: NULL Pointer *pchStr\n", stderr);
        return 0;
    }

    if (pchChar == NULL)
    {
        fputs("ERROR: NULL Pointer *pchChar\n", stderr);
        return 0;
    }
}

/**
 * 检查源文件中每行的字符数量是否符合用户对图像长度的要求(?==iPicWidth)，
 * 一行中读取的字符的数量不超过要求的长度(iPicWidth);
 * 一行中字符的数量未到达要求的长度(iPicWidth)的，
 * 则在存储到图像(iPic)中时会将剩下的空位填充为数字0，
 * 一直读到文件结尾为止;
 *
 * 检查源文件读取的行的数量是否符合用户对图像宽度的要求(?==iPicHeight)，
 * 最多读取到要求的行的数量(iPicHeight);
 * 若读完整个文件时，读取到的行的行数低于要求的行数(iPicHeight)，
 * 则读取到的行数到要求行数之间的所有空行均被填充为数字0。
 *
 * 以上过程中读取到的内容，均保存到用户指定的图像（二维整型数组iPic）中;
 * 读取完毕后将返回成功读取到的元素的数量，
 * 读取过程中遇到任何错误则报告错误并返回当前已读取到的值
 */
int parseCharPictureIntoIntArr(int iPicWidth, int iPicHeight, FILE *file, int iPic[][INT_PIC_WIDTH])
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

    if (iPicWidth <= 0 || iPicHeight <= 0)
        return 0;

    /**
     * *1:  首先，检测 [二维整型数组表示列的下标] 是否小于要求的长度(iPicWidth)；
     * *a1:     小于要求的长度(iPicWidth)，则从文件中读取一个字符并把这个字符存储到一个临时的 [字符缓存] 中，
     * *a2:     然后，检测 [字符缓存] 中的字符是否为数字字符，且 [字符串缓存下标] 是否小于 [字符串缓存的大小]；
     * *aa1:        为数字字符，则将 [字符缓存] 中的字符存储到 [字符串缓存] 数组中（此数组只有4个元素，最多存储3个有效字符，多余字符将被抛弃），\
     * *aa2:        然后，goto a1；
     * *ab1:        不为数字字符，则检测此字符:
     * *aba1:           - 为空格字符，则将 [字符串缓存] 中的字符转换为整型，并保存到 [二维整型数组] 中 [二维整型数组表示列的下标] + 1，[已保存的字符串的总量] + 1，\
     * *aba2:           然后 goto 1；
     * *abb1:           - 为换行符，则将 [字符串缓存] 中的字符转换为整型，并保存到 [二维整型数组] 中，\
     * *abb2:           然后，检测 [二维整型数组表示列的下标] 是否小于要求的长度(iPicWidth)；
     * *abba1:              小于要求的长度，则将 [二维整型数组] 当前行剩下的所有元素填充为 0（通过操作 [二维整型数组表示列的下标] ），\
     * *abba2:              然后，goto 1；
     * *abc1:           - 为文件结尾(EOF)，则 [文件结尾标志] 设为 true，\
     * *abc2:           然后，检测 [二维整型数组表示列的下标] 是否小于要求的长度(iPicWidth)；
     * *abca1:              小于要求的长度，则将 [二维整型数组] 当前行剩下的所有元素填充为 0（通过操作 [二维整型数组表示列的下标] ），\
     * *abca2:              然后，goto 1；
     * *abd1:           - 为数字字符（表示 [字符串缓存下标] 不小于 [字符串缓存的大小]） 或 其他字符，则抛弃此字符，直到遇到下一个非数字字符，\
     * *abd2:           然后，goto 1；
     * *b1:     不小于要求的长度(iPicWidth)，即当前行已满，检测 [二维整型数组表示行的下标] 是否小于要求的行数(iPicHeight)；
     * *ba1:        小于要求的行数(iPicHeight)，则检测 [文件结尾标志] 是否为 true；
     * *baa1:           [文件结尾标志] 为 true，则将剩余行填充为0，然后，返回 [已保存的字符串的总量]；
     * *bab1:           [文件结尾标志] 不为 true，则 [二维整型数组表示行的下标] + 1， [二维整型数组表示列的下标] 与 [二维整型数组表示列的下标] 置零，\
     * *bab2:           然后，goto 1；
     * *bb1:        不小于要求的行数(iPicHeight)，即已到达行底，则返回 [已保存的字符串的总量]；
     */
    /**
     * 到达一行的指定长度，表示此行已满，需要跳转到下一行
     * 此时检测当前行是否为行底，一旦到达行底，则表示所有行已填充完毕，不再检测是否为文件结尾（文件结尾标识符是否设置）即可返回
     * 若不为行底，则检测是否到达文件结尾，到达文件结尾（文件结尾标识符为true），则将剩余行填充为0，然后返回
     * 未到达文件结尾，则表示此行已满，跳转到下一行继续读取
     */

    int iCountTotalSaved = 0; // 已保存的字符串的总量
    int isEOF = 0;            // 文件结尾标志

    int iRowIndex = 0; // 行数，用于操作二维整型数组
    int iColIndex = 0; // 列数，用于操作二维整型数组

    int chBuf = 0;                           // 字符缓存
    char strBuf[CHAR_PIC_STR_BUF_SIZE] = {}; // 用于存储待转换字符串的缓存
    int strBufIndex = 0;                     // 字符串缓存的下标

    unsigned int uiCharType = CHAR_IS_OTHERS;

    /**
     * 根据字符类型行动
     */
    while (1)
    {
        if (iColIndex < iPicWidth)
        {

            do
            {
                // 从文件获取一个字符
                chBuf = getc(file);
                CharInfo(chBuf, uiCharType);

                if (uiCharType == CHAR_IS_DIGIT)
                    strBuf[strBufIndex++] = chBuf;
                else if (strBufIndex == 0 && chBuf != EOF)
                    continue;
                else
                    break;

            } while (strBufIndex < (CHAR_PIC_STR_BUF_SIZE - 1));

            // 若读取流时发生错误则报告错误并返回当前已保存的字符串的总量
            if (ferror(file))
            {
                fputs("ERROR: An error occurred while reading a file.\n", stderr);
                return iCountTotalSaved;
            }

            strBuf[strBufIndex] = '\0';

            switch (uiCharType)
            {
            case CHAR_IS_SPACE:
                iPic[iRowIndex][iColIndex] = atoi(strBuf);
                iColIndex++;
                iCountTotalSaved++;
                break;

            case CHAR_IS_LF:
                iPic[iRowIndex][iColIndex] = atoi(strBuf);
                while (iColIndex < iPicWidth)
                    iPic[iRowIndex][iColIndex++] = 0;
                break;

            case CHAR_IS_EOF:
                isEOF = 1;
                while (iColIndex < iPicWidth)
                    iPic[iRowIndex][iColIndex++] = 0;
                break;

            default:

                break;
            }

            strBufIndex = 0;
        }
    }
}