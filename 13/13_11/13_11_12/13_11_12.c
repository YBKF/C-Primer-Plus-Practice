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

int CharInfo(int iCh, unsigned int *uiInfo);
int isCharOnWhitelist(const char chPre, const unsigned int uiWhitelist);
int ParseAString(unsigned int uiOptions, char pchStr[], int *pchChar, unsigned int uiMaxCount, FILE *file);
int parseCharSourceIntoIntArr(int iPicWidth, int iPicHeight, int (*iPic)[INT_PIC_WIDTH], FILE *file);

char transInt2CharPixel(int i);
int transIntPic2CharPic(int iPicWidth, int iPicHeight, int (*iPic)[INT_PIC_WIDTH], char (*chPic)[CHAR_PIC_WIDTH_SIZE]);

/**
 * 源文件：字符形式存在的数字
 * 数字图：纯整型
 * 字符图：（数字转换为字符后的）字符
 */
int main()
{
    int iPic[INT_PIC_HEIGHT][INT_PIC_WIDTH];
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

    transIntPic2CharPic(CHAR_PIC_WIDTH, CHAR_PIC_HEIGHT, iPic, chPic);

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

    return (i >= 0 && i <= 9) ? (char)(i += ' ') : (char)0;
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
