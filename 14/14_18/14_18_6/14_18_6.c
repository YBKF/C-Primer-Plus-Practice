/**
 * 一个文本文件中保存着一个垒球队的信息。每行数据都是这样排列：
 * 4 Jessie Joybat 5 2 1 1
 * 第1项是球员号，为方便起见，其范围是0～18。
 * 第2项是球员的名。
 * 第3项是球员的姓。名和姓都是一个单词。
 * 第4项是官方统计的球员上场次数。
 * 接着3项分别是击中数、走垒数和打点（RBI）。
 *
 * 文件可能包含多场比赛的数据，所以同一位球员可能有多行数据，
 * 而且同一位球员的多行数据之间可能有其他球员的数据。
 *
 * 编写一个程序，把数据储存到一个结构数组中。
 * 该结构中的成员要分别表示球员的名、姓、上场次数、击中数、走垒数、打点和安打率（稍后计算）。
 * 可以使用球员号作为数组的索引。
 *
 * 该程序要读到文件结尾，并统计每位球员的各项累计总和。
 * 世界棒球统计与之相关。例如，一次走垒和触垒中的失误不计入上场次数，但是可能产生一个RBI。
 *
 * 但是该程序要做的是像下面描述的一样读取和处理数据文件，不会关心数据的实际含义。
 * 要实现这些功能，最简单的方法是把结构的内容都初始化为零，
 * 把文件中的数据读入临时变量中，然后将其加入相应的结构中。
 * 程序读完文件后，应计算每位球员的安打率，并把计算结果储存到结构的相应成员中。
 *
 * 计算安打率是用球员的累计击中数除以上场累计次数。这是一个浮点数计算。
 * 最后，程序结合整个球队的统计数据，一行显示一位球员的累计数据。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME ("list.test")

#define PLAYER_COUNT (19)
#define PLAYER_NUM_MAX (PLAYER_COUNT - 1)

#define NAME_FIRST_MAX_LENGTH (15)
#define NAME_FIRST_MAX_SIZE (NAME_FIRST_MAX_LENGTH + 1)
#define NAME_LAST_MAX_LENGTH (15)
#define NAME_LAST_MAX_SIZE (NAME_LAST_MAX_LENGTH + 1)

#define ERROR_CODE_OTHER_ERROR (0x0001)
#define ERROR_CODE_NULL_PARAM1 (0x0002)
#define ERROR_CODE_NULL_PARAM2 (0x0003)
#define ERROR_CODE_NULL_PARAM3 (0x0004)
#define ERROR_CODE_FILE_STREAM_ERROR (0x0005)
#define ERROR_CODE_SCANF_WRONG_COUNT (0x0006)
#define INFO_CODE_GOT_EOF (EOF)
#define INFO_CODE_SUCCESS (0x0000)

#define STR_INIT_VOID ("")

typedef struct _name NAME;
typedef struct _player PLAYER;

int parseALine(PLAYER *ppBuf, FILE *fp);
int initPlayer(PLAYER *ppPlayer);
int isPlayerUnnamed(const PLAYER *ppPlayer);
int mergePlayerInfo(PLAYER *ppTarget, const PLAYER *ppMerge);
void calculateBattingAverage(PLAYER *ppPlayer);
void printPlayerData(const PLAYER *ppPlayer);

typedef struct _name
{
    char first[NAME_FIRST_MAX_SIZE];
    char last[NAME_LAST_MAX_SIZE];
} NAME;

typedef struct _player
{
    unsigned int num;      // 球员号
    NAME name;             // 球员名
    unsigned int atBats;   // 上场次数
    unsigned int hits;     // 击中数
    unsigned int walks;    // 走垒数
    unsigned int rbis;     // 打点
    double battingAverage; // 安打率
} PLAYER;

int main(int argc, char const *argv[])
{
    FILE *fp;

    if ((fp = fopen(FILE_NAME, "r")) == NULL)
    {
        fprintf(stdout, "\
[ERROR] Cannot open file: %s\n",
                FILE_NAME);
        return EXIT_FAILURE;
    }

    PLAYER pBuf;
    PLAYER players[PLAYER_COUNT];          // 结构数组
    for (int i = 0; i < PLAYER_COUNT; i++) // 初始化结构数组中的各结构
        if (initPlayer(&players[i]) == 0)
        {
            fprintf(stderr, "\
[ERROR] Failed to initialization.\n");
            return EXIT_FAILURE;
        }

    int iParseRet = ERROR_CODE_OTHER_ERROR; // 存储函数返回值
    while ((iParseRet = parseALine(&pBuf, fp)) == INFO_CODE_SUCCESS && pBuf.num < PLAYER_NUM_MAX)
    {
        PLAYER *ppCurPlayer = &players[pBuf.num];

        if (isPlayerUnnamed(ppCurPlayer)) // 检测与缓存中对应的 球员结构数组中的结构是否为第一次被赋值
        {
            *ppCurPlayer = pBuf; // 第一次被赋值，则完全复制缓存中的数据到结构中
        }
        else
        {
            if (mergePlayerInfo(ppCurPlayer, &pBuf) == 0)
                return EXIT_FAILURE;
        }
    }

    // if (feof(fp))
    //     /* Do nothing */;

    // 解析函数返回值错误检查，ferror(fp) 包括在下方代码块中
    if (iParseRet > 0)
    {
        fprintf(stderr, "\
[ERROR] An error occurred while parse a line of the file.\n\
        ERROR_CODE: %#x\n",
                iParseRet);

        return EXIT_FAILURE;
    }

    // 计算所有球员的安打率并打印球员的数据
    if (iParseRet == EOF)
        for (int i = 0; i < PLAYER_COUNT; i++)
        {
            calculateBattingAverage(&players[i]);
            printPlayerData(&players[i]);
        }

    if (fclose(fp) != 0)
        fprintf(stderr, "\
[ERROR] Error in closing the file.\n");

    return 0;
}

/**
 * - [out] ppBuf
 * - [in] fp
 *
 * 从指针 fp 指向的文件中读取的一行字符串，解析后存入指针 ppBuf 指向的结构缓存中；
 * 读取成功时返回 0；若读到文件结尾，则返回 EOF；若函数运行过程中遇到错误，则返回一个 大于 0 的值。
 *
 * [out] ppBuf
 * 参数应为一个指向 PLAYER 结构类型变量的指针，此结构作为缓存用于存储从文件中读取并解析后的球员数据。
 *
 * [in] fp
 * 参数为一个指向文件的指针。
 *
 * 各返回值表示的意义：
 * - 返回值 == -1，表示函数读到文件结尾；
 * - 返回值 == 0，表示函数读取成功；
 * - 返回值 > 0，表示函数读取过程中出现错误，具体值依据错误类型而定；
 * - 返回值 为其他值，其意义未定义。
 *
 * 相关的错误的返回值（错误码）：
 * - ERROR_CODE_OTHER_ERROR (0x0001)
 * - ERROR_CODE_NULL_PARAM1 (0x0002)
 * - ERROR_CODE_NULL_PARAM2 (0x0003)
 * - ERROR_CODE_FILE_STREAM_ERROR (0x0005)
 * - ERROR_CODE_SCANF_WRONG_COUNT (0x0006)
 *
 */
int parseALine(PLAYER *ppBuf, FILE *fp)
{
    if (ppBuf == NULL)
    {
        fprintf(stderr, "\
[ERROR] Got a NULL buffer pointer while parsing a line.\n");
        return ERROR_CODE_NULL_PARAM1;
    }
    if (fp == NULL)
    {
        fprintf(stderr, "\
[ERROR] NULL File. Cannot open a file while parsing a line.\n");
        return ERROR_CODE_NULL_PARAM2;
    }

    int iScfRetVal;
    iScfRetVal = fscanf(fp, " %u %s %s %u %u %u %u",
                        &ppBuf->num,
                        ppBuf->name.first,
                        ppBuf->name.last,
                        &ppBuf->atBats,
                        &ppBuf->hits,
                        &ppBuf->walks,
                        &ppBuf->rbis);

    if (iScfRetVal == 7)
    {
        return INFO_CODE_SUCCESS;
    }
    else if (feof(fp))
    {
        return INFO_CODE_GOT_EOF;
    }
    else
    {
        if (ferror(fp))
        {
            return ERROR_CODE_FILE_STREAM_ERROR;
        }
        else if (iScfRetVal != 7)
        {
            return ERROR_CODE_SCANF_WRONG_COUNT;
        }
        else
        {
            return ERROR_CODE_OTHER_ERROR;
        }
    }
}

/**
 * - [in] pName
 *
 * 检查 pName 指向的结构中的两个成员变量是否为空字符串。
 * 为空字符串，则返回 1；
 * 否则返回 0。
 *
 */
int isVoidName(const NAME *pName)
{
    if (pName->first[0] == '\0' && pName->last[0] == '\0')
        return 1;
    else
        return 0;
}

/**
 * - [in] ppPlayer
 *
 * 检查 ppPlayer 指向的结构是否为“未命名”，
 * 即，检查成员结构变量 name 中的两个成员变量是否为空字符串。
 * 主要用于检测结构是否是第一次被赋值。
 * 为空字符串，则返回 1；
 * 否则返回 0。
 *
 */
int isPlayerUnnamed(const PLAYER *ppPlayer)
{
    return isVoidName(&ppPlayer->name);
}

/**
 * - [out] ppPlayer
 *
 * 初始化 ppPlayer 指向的 Player 结构。
 * 初始化成功返回 1，
 * 否则返回 0
 *
 */
int initPlayer(PLAYER *ppPlayer)
{
    if (ppPlayer == NULL)
    {
        fprintf(stderr, "\
[ERROR] NULL Pointer. Cannot initial the Player.\n");
        return 0;
    }

    *ppPlayer = (PLAYER){
        .num = 0U,
        .name = (NAME){STR_INIT_VOID, STR_INIT_VOID},
        .atBats = 0U,
        .hits = 0U,
        .walks = 0U,
        .rbis = 0U,
        .battingAverage = 0.0};

    return 1;
}

/**
 * - [out] ppTarget
 * - [in] ppMerge
 *
 * 融合结构的数据，
 * 将 ppMerge 指向的结构的上场次数、击中数、走垒数、打点数据融合到 ppTarget 指向的结构中
 *
 */
int mergePlayerInfo(PLAYER *ppTarget, const PLAYER *ppMerge)
{
    if (ppTarget == NULL || ppMerge == NULL)
    {
        fprintf(stderr, "\
[ERROR] NULL Pointer. Cannot merge the data.\n");
        return 0;
    }

    ppTarget->atBats += ppMerge->atBats;
    ppTarget->hits += ppMerge->hits;
    ppTarget->walks += ppMerge->walks;
    ppTarget->rbis += ppMerge->rbis;

    return 1;
}

/**
 * - [in, out] ppPlayer
 */
void calculateBattingAverage(PLAYER *ppPlayer)
{
    if (ppPlayer == NULL)
    {
        fprintf(stderr, "\
[ERROR] NULL Pointer. Cannot calculate the BattingAverage.\n");
        return;
    }

    if (ppPlayer->atBats != 0)
        ppPlayer->battingAverage = (double)ppPlayer->hits / (double)ppPlayer->atBats;
}

/**
 * - [in] ppPlayer
 */
void printPlayerData(const PLAYER *ppPlayer)
{
    if (ppPlayer == NULL)
    {
        fprintf(stderr, "\
[ERROR] NULL Pointer. Cannot print the player data.\n");
        return;
    }

    fprintf(stdout, "\
[Number] %2u, [Name] %s %s, [AtBats] %u, [Hits] %u, [Walks] %u, [RBIS] %u, [BattingAverage] %.2lf\n",
            ppPlayer->num,
            ppPlayer->name.first,
            ppPlayer->name.last,
            ppPlayer->atBats,
            ppPlayer->hits,
            ppPlayer->walks,
            ppPlayer->rbis,
            ppPlayer->battingAverage);
}
