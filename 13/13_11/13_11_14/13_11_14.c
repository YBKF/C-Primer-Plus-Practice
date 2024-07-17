/**
 * 14.数字图像，尤其是从宇宙飞船发回的数字图像，可能会包含一些失真。
 * 为编程练习12添加消除失真的函数。该函数把每个值与它上下左右相邻的值作比较，
 * 如果该值与其周围相邻值的差都大于1，则用所有相邻值的平均值（四舍五入为整数）代替该值。
 * 注意，与边界上的点相邻的点少于4个，所以做特殊处理。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define INT_PIC_WIDTH (30)
#define INT_PIC_HEIGHT (20)

#define DISTORTION_TOLERANCE (1)

#define CHAR_PIC_WIDTH INT_PIC_WIDTH
#define CHAR_PIC_WIDTH_SIZE (CHAR_PIC_WIDTH + 1)
#define CHAR_PIC_HEIGHT INT_PIC_HEIGHT
#define CHAR_PIC_PIXEL_SIZE (4)
#define CHAR_PIC_STR_BUF_SIZE CHAR_PIC_PIXEL_SIZE
#define CHAR_PIC_STR_BUF_LENGTH (CHAR_PIC_STR_BUF_SIZE - 1)

#define CHAR_IS_OTHERS (0x0001)
#define CHAR_IS_DIGIT (0x0002)
#define CHAR_IS_SPACE (0x0004)
#define CHAR_IS_LF (0x0008)
#define CHAR_IS_EOF (0x0010)

#define PARSE_OTHERS CHAR_IS_OTHERS
#define PARSE_DIGIT CHAR_IS_DIGIT
#define PARSE_SPACE CHAR_IS_SPACE
#define PARSE_LF CHAR_IS_LF
#define PARSE_EOF CHAR_IS_EOF
#define DONT_SKIP (0x1000)

#define ON_TOP_BORDER (0x0001)
#define ON_LEFT_BORDER (0x0002)
#define ON_BOTTOM_BORDER (0x0004)
#define ON_RIGHT_BORDER (0x0008)

#define EXIST_UPPER_NEI_ELEM (0x0001)
#define EXIST_LEFT_NEI_ELEM (0x0002)
#define EXIST_BELOW_NEI_ELEM (0x0004)
#define EXIST_RIGHT_NEI_ELEM (0x0008)
#define EXIST_ALL_NEI_ELEM (0x000F)

int CharInfo(int iCh, unsigned int *uiInfo);
int isCharOnWhitelist(const char chPre, const unsigned int uiWhitelist);
int ParseAString(unsigned int uiOptions, char pchStr[], int *pchChar, unsigned int uiMaxCount, FILE *file);
int parseCharSourceIntoIntArr(int iPicWidth, int iPicHeight, int (*iPic)[INT_PIC_WIDTH], FILE *file);

char transInt2CharPixel(int i);
int transIntPic2CharPic(int iPicWidth, int iPicHeight, int (*iPic)[INT_PIC_WIDTH], char (*chPic)[CHAR_PIC_WIDTH_SIZE]);

// unsigned int transBorder2NeiElem(unsigned int uiBorder);

int isNeighbourDiffBiggerThan(const int DiffVal, const int iPicHeight, const int iPicWidth, const int (*iPic)[INT_PIC_WIDTH], const unsigned int uiNeighborElem);
int sumNeighbourVal(const int iPicHeight, const int iPicWidth, const int (*iPic)[INT_PIC_WIDTH], unsigned int uiNeighborElem);
int reduceDistortionIntPic(int iPicWidth, int iPicHeight, const int (*iPicSource)[INT_PIC_WIDTH], int (*iPicProcessed)[INT_PIC_WIDTH]);

/**
 * 源文件：字符形式存在的数字
 * 数字图：纯整型
 * 字符图：（数字转换为字符后的）字符
 */
int main()
{
    int iPic[INT_PIC_HEIGHT][INT_PIC_WIDTH];
    int iPicProcessed[INT_PIC_HEIGHT][INT_PIC_WIDTH];
    char chPic[CHAR_PIC_HEIGHT][CHAR_PIC_WIDTH_SIZE];
    int iCountTotalSaved;
    char *filenameIn = "pic.test";
    char *filenameOut = "picOut.test";
    FILE *fileIn;
    FILE *fileOut;

    if ((fileIn = fopen(filenameIn, "r")) == NULL)
    {
        fprintf(stderr, "ERROR: Cannot open file: %s\n", filenameIn);
        exit(EXIT_FAILURE);
    }

    memset(iPic, 0, sizeof(int) * INT_PIC_WIDTH * INT_PIC_HEIGHT);

    iCountTotalSaved = parseCharSourceIntoIntArr(INT_PIC_WIDTH, INT_PIC_HEIGHT, iPic, fileIn);
    if (iCountTotalSaved != (INT_PIC_HEIGHT * INT_PIC_WIDTH))
    {
        if (iCountTotalSaved == 0)
            fputs("WARNING: Failed to parse the file.\n", stderr);
        else
            fputs("WARNING: Illegal file, read attempted.\n", stderr);
    }

    // for (int h = 0; h < INT_PIC_HEIGHT; h++)
    // {
    //     for (int w = 0; w < INT_PIC_WIDTH; w++)
    //     {
    //         printf("%d ", iPic[h][w]);
    //     }
    //     putchar('\n');
    // }

    if (reduceDistortionIntPic(INT_PIC_WIDTH, INT_PIC_HEIGHT, iPic, iPicProcessed) == 0)
    {
        fputs("ERROR: An error occurred when reducing the distortion of the IntPic", stderr);
        exit(EXIT_FAILURE);
    }

    // for (int h = 0; h < INT_PIC_HEIGHT; h++)
    // {
    //     for (int w = 0; w < INT_PIC_WIDTH; w++)
    //     {
    //         printf("%d ", iPicProcessed[h][w]);
    //     }
    //     putchar('\n');
    // }

    transIntPic2CharPic(CHAR_PIC_WIDTH, CHAR_PIC_HEIGHT, iPicProcessed, chPic);

    if ((fileOut = fopen(filenameOut, "w")) == NULL)
    {
        fprintf(stderr, "ERROR: Cannot open file: %s\n", filenameOut);
        exit(EXIT_FAILURE);
    }

    for (int h = 0; h < CHAR_PIC_HEIGHT; h++)
    {
        for (int w = 0; w < CHAR_PIC_WIDTH; w++)
        {
            putc(chPic[h][w], fileOut);
            putc(chPic[h][w], stdout);
        }
        putc('\n', fileOut);
        putc('\n', stdout);
    }

    int fcRetO, fcRetI;
    if (((fcRetO = fclose(fileOut)) | (fcRetI = fclose(fileIn))) != 0)
    {
        if (fcRetO != 0)
            fprintf(stderr, "ERROR: Error in closing file: %s\n", filenameOut);

        if (fcRetI != 0)
            fprintf(stderr, "ERROR: Error in closing file: %s\n", filenameIn);

        exit(EXIT_FAILURE);
    }

    return 0;
}

/**
 * - [in] iCh
 * - [out] uiInfo
 *
 * 分析输入的字符参数 [in] iCh 的类型，将得到的结果存储到参数 [out] uiInfo 中，并返回 iCh；
 * 参数 2 uiInfo 为空时，将返回 EOF
 *
 * [out] uiInfo 支持的字符类型：
 * - CHAR_IS_OTHERS (0x0001)
 * - CHAR_IS_DIGIT (0x0002)
 * - CHAR_IS_SPACE (0x0004)
 * - CHAR_IS_LF (0x0008)
 * - CHAR_IS_EOF (0x0010)
 */
int CharInfo(int iCh, unsigned int *uiInfo)
{
    if (uiInfo == NULL)
    {
        fputs("ERROR: Cannot get information of the character because of null pointers.\n", stderr);
        return EOF;
    }

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
 * - [in] chPre
 * - [in] uiWhitelist
 *
 * 根据 uiWhitelist 参数设定的字符类型白名单检测字符 chPre，
 * 符合白名单 uiWhitelist 的字符将返回字符本身，否则返回空字符 0。
 *
 * [in] uiWhitelist 支持的参数：
 * - PARSE_OTHERS (0x0001)
 * - PARSE_DIGIT (0x0002)
 * - PARSE_SPACE (0x0004)
 * - PARSE_LF (0x0008)
 * - PARSE_EOF (0x0010)
 * 支持复合参数，如 "PARSE_DIGIT | PARSE_SPACE"
 */
int isCharOnWhitelist(const char chPre, const unsigned int uiWhitelist)
{
    unsigned int uiCharType;

    CharInfo(chPre, &uiCharType);

    return (uiCharType & uiWhitelist) ? chPre : 0;
}

/**
 * - [in] uiOptions
 * - [out] pchStr
 * - [out] pchChar
 * - [in] iMaxCount
 * - [in] file
 *
 * 根据 uiOptions 参数设定的读取规则来依次连续读取指定文件 file 中的指定类型的字符，
 * 符合规则的字符将存储到 pchStr 字符串中，直到遇到读取规则外的其他类型的字符或是到达读取上限 iMaxCount；
 * 如果参数中未设置 DONT_SKIP，开始正式读取前将默认跳过所有不在白名单中的字符类型，直到遇到白名单字符类型或到达文件结尾，
 * 如果在正式读取前便遇到文件结尾，则返回 EOF。
 *
 * 成功读取时返回 1
 * 未读取到单词或遇到错误时返回 0
 * 其他返回原因时 返回值 > 1
 *
 * [in] uiOptions 支持的参数：
 * - DONT_SKIP (0x1000)
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
 * [out] pchChar 存储函数返回的返回原因，通常为最后读取到的字符，参数可为 NULL；
 * 为 NULL 时，将不存储字符
 *
 * [in] iMaxCount
 * 存储字符的数量上限
 *
 * [in] file
 * 读取的文件
 */
int ParseAString(unsigned int uiOptions, char pchStr[], int *pchChar, unsigned int uiMaxCount, FILE *file)
{
    if (file == NULL)
    {
        fputs("ERROR: NULL File. Cannot open a file while parsing the string.\n", stderr);
        return 0;
    }

    int isNULLpchStr = 0;
    int isNULLpchChar = 0;
    int dontSkip = 0;

    if (pchStr == NULL)
        isNULLpchStr = 1;

    if (pchChar == NULL)
        isNULLpchChar = 1;

    if (uiOptions & DONT_SKIP)
        dontSkip = 1;

    char *pchCurChar = pchStr;
    int chBuf = 0;

    // 开始正式读取前将默认跳过所有不在白名单中的字符类型，并检测当前行是否有还有有效字符（是否检测到换行符）
    if (!dontSkip)
    {
        // 跳过所有不在白名单中的字符类型，直到遇到白名单字符类型或到达文件结尾
        while (!isCharOnWhitelist(chBuf = getc(file), uiOptions | PARSE_LF | PARSE_EOF))
            continue;

        if (chBuf == EOF)
        {
            if (ferror(file))
            {
                fputs("ERROR: An error occurred while reading the file.\n", stderr);
                return 0;
            }
            else
            {
                if (!isNULLpchChar)
                    *pchChar = chBuf;
                return EOF; // 正式读取前就遇到文件结尾，则返回 EOF
            }
        }
        else if (chBuf == '\n') // 遇到换行符，表示本行无有效字符，返回
        {
            if (!isNULLpchChar)
                *pchChar = chBuf;
            return chBuf;
        }

        // 若 chBuf 缓存中的字符类型在函数设置的白名单中，则将此字符重新放回流中
        if (isCharOnWhitelist(chBuf, uiOptions))
            ungetc(chBuf, file);
    }

    for (unsigned int ui = 0; ui < uiMaxCount; ui++)
    {
        chBuf = getc(file);
        if (ferror(file))
        {
            *pchCurChar = '\0';
            fputs("ERROR: An error occurred while reading the file.\n", stderr);
            return 0;
        }

        // 若缓存中字符的类型不在白名单中或检测到文件结尾则退出循环
        if (isCharOnWhitelist(chBuf, uiOptions) <= 0)
            break;
        else if (!isNULLpchStr)
            *pchCurChar++ = chBuf;
    }

    if (!isNULLpchStr)
        *pchCurChar = '\0';

    if (!isNULLpchChar)
        *pchChar = chBuf;

    return 1;
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
int parseCharSourceIntoIntArr(int iPicWidth, int iPicHeight, int (*iPic)[INT_PIC_WIDTH], FILE *file)
{
    if (file == NULL)
    {
        fputs("ERROR: NULL File.\n", stderr);
        return 0;
    }

    if (iPic == NULL)
    {
        fputs("ERROR: NULL Pointer iPic at function parseCharSourceIntoIntArr.\n", stderr);
        return 0;
    }

    if (iPicWidth <= 0 || iPicHeight <= 0)
        return 0;

    /**
     * 大致流程：
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

    int chBuf = 0;                      // 字符缓存
    char strBuf[CHAR_PIC_STR_BUF_SIZE]; // 用于存储待转换字符串的缓存

    int iRetVal;

    for (iRowIndex = 0; iRowIndex < iPicHeight; iRowIndex++)
    {
        for (iColIndex = 0; iColIndex < iPicWidth; iColIndex++)
        {
            // 在循环开始处设置文件结尾标志检测；若 isEOF 为真，则表示文件已读到结尾但是 iPic 数组仍未满，则将此行元素填充为 0
            if (isEOF)
            {
                memset(&iPic[iRowIndex][iColIndex], 0, sizeof(int) * (size_t)(iPicWidth - iColIndex));
                break;
            }

            // 获取一串字符串
            iRetVal = ParseAString(PARSE_DIGIT, strBuf, &chBuf, CHAR_PIC_STR_BUF_LENGTH, file);

            if (iRetVal == 1) // 字符串读取成功时，将字符串缓存转换为整型
            {
                iPic[iRowIndex][iColIndex] = atoi(strBuf);
                iCountTotalSaved++;
            }
            else if (iRetVal == EOF) // iRetVal == EOF 表示函数在开始读取前便遇到文件结尾， strBuf 中未存储任何字符
            {
                fputs("WARNING: Got EOF before reading a string.\n", stderr);
            }
            else if (iRetVal == 0)
            {
                fputs("ERROR: An error occurred while parsing a string from the file.\n", stderr);
                return 0;
            }

            if (chBuf == '\n') // 缓存中为换行符表示已读完文件中的一行
            {
                // 若 iColIndex < iPicWidth 表示 iPic 数组的当前行未存储满，将此行未赋值元素填充为 0
                if (iColIndex < iPicWidth)
                {
                    if (iRetVal == 1)
                        iColIndex++;
                    memset(&iPic[iRowIndex][iColIndex], 0, sizeof(int) * (size_t)(iPicWidth - iColIndex));
                }
                break;
            }
            else if (chBuf == EOF)
            {
                isEOF = 1;
                // 若 iColIndex < iPicWidth 表示 iPic 数组的当前行未存储满，将此行未赋值元素填充为 0
                if (iColIndex < iPicWidth)
                {
                    if (iRetVal == 1)
                        iColIndex++;
                    memset(&iPic[iRowIndex][iColIndex], 0, sizeof(int) * (size_t)(iPicWidth - iColIndex));
                }
                break;
            }
            else if (isdigit(chBuf))
            {
                /* 若缓存 chBuf 中为数字字符，则表示数字字符串 strBuf 读到数组大小的上限 CHAR_PIC_STR_BUF_LENGTH 后依旧有连续的数字字符，
                此时抛弃这些数字字符，直到遇到一个空格、换行符或到达文件结尾 */
                int discard;
                while (1)
                {
                    discard = getc(file);
                    if (discard == ' ' || discard == '\n' || discard == EOF)
                        break;
                }
            }
        }
    }

    return iCountTotalSaved;
}

char transInt2CharPixel(int i)
{
    // if (i >= 0 && i <= 9)
    //     return (char)(i += ' ');
    // else
    //     return 0;

    return (i >= 0 && i <= 9) ? (char)(i + ' ') : (char)0;
}

int transIntPic2CharPic(int iPicWidth, int iPicHeight, int (*iPic)[INT_PIC_WIDTH], char (*chPic)[CHAR_PIC_WIDTH_SIZE])
{
    if (iPic == NULL)
    {
        fputs("ERROR: NULL Pointer iPic at function transIntPic2CharPic.\n", stderr);
        return 0;
    }

    if (chPic == NULL)
    {
        fputs("ERROR: NULL Pointer chPic at function transIntPic2CharPic.\n", stderr);
        return 0;
    }

    if (iPicWidth <= 0 || iPicHeight <= 0)
        return 0;

    int iRowIndex, iColumnIndex;

    for (iRowIndex = 0; iRowIndex < iPicHeight; iRowIndex++)
    {
        for (iColumnIndex = 0; iColumnIndex < iPicWidth; iColumnIndex++)
            chPic[iRowIndex][iColumnIndex] = transInt2CharPixel(iPic[iRowIndex][iColumnIndex]);

        chPic[iRowIndex][iColumnIndex + 1] = '\0';
    }

    return 1;
}

/**
 * 将元素边界位置的代表值转换为元素相邻的其他元素存在的代表值
 */
// unsigned int transBorder2NeiElem(unsigned int uiBorder)
// {
//     return ~uiBorder;
// }

/**
 * 判断所选元素与其相邻的所有元素的值的差是否大于一个特定值 DiffVal
 * 大于特定值返回 1
 * 否则返回 0
 *
 * 使用 uiNeighborElem 获取并解析所选元素存在哪些相邻的元素
 *
 * [in] uiNeighborElem 接受的代表值：
 * EXIST_UPPER_NEI_ELEM (0x0001)
 * EXIST_LEFT_NEI_ELEM (0x0002)
 * EXIST_BELOW_NEI_ELEM (0x0004)
 * EXIST_RIGHT_NEI_ELEM (0x0008)
 * EXIST_ALL_NEI_ELEM (0x000F)
 * 接受复合参数，如：EXIST_UPPER_NEI_ELEM | EXIST_LEFT_NEI_ELEM
 */
int isNeighbourDiffBiggerThan(const int DiffVal, const int iPicHeight, const int iPicWidth, const int (*iPic)[INT_PIC_WIDTH], const unsigned int uiNeighborElem)
{
    if (iPic == NULL)
    {
        fputs("ERROR: NULL Pointer iPic at function isNeighbourDiffBiggerThan.\n", stderr);
        return 0;
    }

    unsigned int uiDiffIsBigger = 0x0000;

    if (uiNeighborElem & EXIST_UPPER_NEI_ELEM)
        if (abs(iPic[iPicHeight][iPicWidth] - iPic[iPicHeight - 1][iPicWidth]) > DiffVal)
            uiDiffIsBigger = uiDiffIsBigger | EXIST_UPPER_NEI_ELEM;

    if (uiNeighborElem & EXIST_LEFT_NEI_ELEM)
        if (abs(iPic[iPicHeight][iPicWidth] - iPic[iPicHeight][iPicWidth - 1]) > DiffVal)
            uiDiffIsBigger = uiDiffIsBigger | EXIST_LEFT_NEI_ELEM;

    if (uiNeighborElem & EXIST_BELOW_NEI_ELEM)
        if (abs(iPic[iPicHeight][iPicWidth] - iPic[iPicHeight + 1][iPicWidth]) > DiffVal)
            uiDiffIsBigger = uiDiffIsBigger | EXIST_BELOW_NEI_ELEM;

    if (uiNeighborElem & EXIST_RIGHT_NEI_ELEM)
        if (abs(iPic[iPicHeight][iPicWidth] - iPic[iPicHeight][iPicWidth + 1]) > DiffVal)
            uiDiffIsBigger = uiDiffIsBigger | EXIST_RIGHT_NEI_ELEM;

    if (uiDiffIsBigger == uiNeighborElem && uiNeighborElem != 0x0000)
        return 1;
    else
        return 0;
}

/**
 * 根据 uiNeighborElem 设定的值，把指定元素的相邻元素（解析 uiNeighborElem 后的相邻元素）相加，
 * 返回这些元素的和，
 * 若发生错误或不存在相邻元素返回 0
 *
 * [in] uiNeighborElem 接受的代表值：
 * EXIST_UPPER_NEI_ELEM (0x0001)
 * EXIST_LEFT_NEI_ELEM (0x0002)
 * EXIST_BELOW_NEI_ELEM (0x0004)
 * EXIST_RIGHT_NEI_ELEM (0x0008)
 * EXIST_ALL_NEI_ELEM (0x000F)
 * 接受复合参数，如：EXIST_UPPER_NEI_ELEM | EXIST_LEFT_NEI_ELEM
 */
int sumNeighbourVal(const int iPicHeight, const int iPicWidth, const int (*iPic)[INT_PIC_WIDTH], unsigned int uiNeighborElem)
{
    if (iPic == NULL)
    {
        fputs("ERROR: NULL Pointer iPic at function sumNeighbourVal.\n", stderr);
        return 0;
    }

    if (iPicWidth <= 0 || iPicHeight <= 0)
        return 0;

    int sum = 0;

    if (uiNeighborElem & EXIST_UPPER_NEI_ELEM)
        sum += iPic[iPicHeight - 1][iPicWidth];

    if (uiNeighborElem & EXIST_LEFT_NEI_ELEM)
        sum += iPic[iPicHeight][iPicWidth - 1];

    if (uiNeighborElem & EXIST_BELOW_NEI_ELEM)
        sum += iPic[iPicHeight + 1][iPicWidth];

    if (uiNeighborElem & EXIST_RIGHT_NEI_ELEM)
        sum += iPic[iPicHeight][iPicWidth + 1];

    return sum;
}

/**
 * 把每个值与它上下左右相邻的值作比较，
 * 如果该值与其周围相邻值的差都大于1，则用所有相邻值的平均值（四舍五入为整数）代替该值。
 * 操作成功返回 1，
 * 否则返回 0
 *
 * 判断一个元素是否位于边界：
 * 位于上边界 <-> RowIndex == 0
 * 位于左边界 <-> ColIndex == 0
 * 位于下边界 <-> RowIndex == (MaxRow - 1)
 * 位于右边界 <-> ColIndex == (ColMax - 1)
 *
 * 边界位置代表值：
 * ON_TOP_BORDER (0x0001)
 * ON_LEFT_BORDER (0x0002)
 * ON_BOTTOM_BORDER (0x0004)
 * ON_RIGHT_BORDER (0x0008)
 *
 * 判断一个元素周围不存在哪些相邻的元素：
 * 不存在上元素 <-> 位于上边界 <-> RowIndex == 0
 * 不存在左元素 <-> 位于左边界 <-> ColIndex == 0
 * 不存在下元素 <-> 位于下边界 <-> RowIndex == (MaxRow - 1)
 * 不存在右元素 <-> 位于右边界 <-> ColIndex == (ColMax - 1)
 *
 * 相邻元素存在代表值：
 * EXIST_UPPER_NEI_ELEM (0x0001)
 * EXIST_LEFT_NEI_ELEM (0x0002)
 * EXIST_BELOW_NEI_ELEM (0x0004)
 * EXIST_RIGHT_NEI_ELEM (0x0008)
 * EXIST_ALL_NEI_ELEM (0x000F)
 *
 * 每检测到一个边界，检测到的边界数量 + 1；
 * 元素最终值 = 总检测到的相邻的元素的值 / 检测到的边界数量
 */
int reduceDistortionIntPic(int iPicWidth, int iPicHeight, const int (*iPicSource)[INT_PIC_WIDTH], int (*iPicProcessed)[INT_PIC_WIDTH])
{
    if (iPicProcessed == NULL)
    {
        fputs("ERROR: NULL Pointer iPicSource at function reduceDistortionIntPic.\n", stderr);
        return 0;
    }

    if (iPicProcessed == NULL)
    {
        fputs("ERROR: NULL Pointer iPicProcessed at function reduceDistortionIntPic.\n", stderr);
        return 0;
    }

    if (iPicWidth <= 0 || iPicHeight <= 0)
        return 0;

    int RowIndex = 0;
    int ColIndex = 0;

    // unsigned int uiBorder = 0x0000;
    // int iBorderCount = 0;
    unsigned int uiExistNeiElem = EXIST_ALL_NEI_ELEM;
    int iNeiElemCount = 4;

    // 未经性能优化
    for (RowIndex = 0; RowIndex < iPicHeight; RowIndex++)
    {
        // TODO 顶行与底行的判断可以仅在外部循环执行，顶行底行减少的元素数量亦同
        for (ColIndex = 0, uiExistNeiElem = EXIST_ALL_NEI_ELEM, iNeiElemCount = 4; ColIndex < iPicWidth; ColIndex++)
        {
            if (RowIndex == 0)
            {
                uiExistNeiElem = uiExistNeiElem & ~EXIST_UPPER_NEI_ELEM;
                iNeiElemCount--;
            }

            if (ColIndex == 0)
            {
                uiExistNeiElem = uiExistNeiElem & ~ON_LEFT_BORDER;
                iNeiElemCount--;
            }

            if (RowIndex == (iPicHeight - 1))
            {
                uiExistNeiElem = uiExistNeiElem & ~ON_BOTTOM_BORDER;
                iNeiElemCount--;
            }

            if (ColIndex == (iPicWidth - 1))
            {
                uiExistNeiElem = uiExistNeiElem & ~ON_RIGHT_BORDER;
                iNeiElemCount--;
            }

            if (isNeighbourDiffBiggerThan(DISTORTION_TOLERANCE, RowIndex, ColIndex, iPicSource, uiExistNeiElem) && iNeiElemCount != 0)
                iPicProcessed[RowIndex][ColIndex] = sumNeighbourVal(RowIndex, ColIndex, iPicSource, uiExistNeiElem) / iNeiElemCount;
            else
                iPicProcessed[RowIndex][ColIndex] = iPicSource[RowIndex][ColIndex];
        }
    }

    return 1;
}
