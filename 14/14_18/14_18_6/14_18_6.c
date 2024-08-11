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

#define PLAYER_COUNT (19)
#define PLAYER_NUM_MAX (PLAYER_COUNT - 1)

#define NAME_FIRST_MAX_LENGTH (15)
#define NAME_FIRST_MAX_SIZE (NAME_FIRST_MAX_LENGTH + 1)
#define NAME_LAST_MAX_LENGTH (15)
#define NAME_LAST_MAX_SIZE (NAME_LAST_MAX_LENGTH + 1)

typedef struct _name NAME;
typedef struct _player PLAYER;

int parseALine(PLAYER *buf, FILE *file);
int isPlayerInitialized(PLAYER *player);
void initPlayer(PLAYER *player, PLAYER *buf);

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

    return 0;
}

/**
 * - [out] buf
 * - [in] file
 *
 * 读取文件中的一行字符串，解析后存入指针 pBuf 指向的结构缓存中；
 * 读取成功时返回 0，若读到文件结尾返回 -1，
 * 若函数运行过程中出现错误，则返回一个大于 0 的值，具体值依据错误类型而定。
 *
 *
 */
int parseALine(PLAYER *buf, FILE *file)
{
}

/**
 * - [in] player
 *
 * 检查 player 是否已初始化；
 * 已初始化，则返回 1，
 * 未初始化，则返回 0。
 *
 * 函数仅检查
 *
 */
int isPlayerInitialized(PLAYER *player)
{
}
