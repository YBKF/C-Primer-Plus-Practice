/**
 * 8.巨人航空公司的机群由 12 个座位的飞机组成。它每天飞行一个航班。
 * 根据下面的要求，编写一个座位预订程序。
 *
 * a.该程序使用一个内含 12 个结构的数组。每个结构中包括：一个成员表示座位编号、一个成员表示座位是否已被预订、一个成员表示预订人的名、一个成员表示预订人的姓。
 * b.该程序显示下面的菜单：
 * To choose a function, enter its letter label:
 * a) Show number of empty seats
 * b) Show list of empty seats
 * c) Show alphabetical list of seats
 * d) Assign a customer to a seat assignment
 * e) Delete a seat assignment
 * f) Quit
 * c.该程序能成功执行上面给出的菜单。选择d)和e)要提示用户进行额外输入，每个选项都能让用户中止输入。
 * d.执行特定程序后，该程序再次显示菜单，除非用户选择f)。
 */
/**
 * 假设这架飞机拥有两排座位，每排 6 座，总共 12 个座位，所以座位编号可以为 A1 - B6。
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define NAME_FIRST_MAX_LENGTH (25)
#define NAME_FIRST_MAX_SIZE (NAME_FIRST_MAX_LENGTH + 1)
#define NAME_LAST_MAX_LENGTH (25)
#define NAME_LAST_MAX_SIZE (NAME_LAST_MAX_LENGTH + 1)
#define SEATS_NUMBER_MAX_LENGTH (10)
#define SEATS_NUMBER_MAX_SIZE (SEATS_NUMBER_MAX_LENGTH + 1)

#define SEATS_COUNT (12)

#define STR_INIT_VOID ("")
#define STR_BOOL_TRUE ("Yes")
#define STR_BOOL_FALSE ("No")

#define STR_BOOL_LENGTH (3)
#define STR_BOOL_SIZE (STR_BOOL_LENGTH + 1)

typedef struct _Name
{
    char first[NAME_FIRST_MAX_SIZE];
    char last[NAME_LAST_MAX_SIZE];
} Name;

typedef struct _Seat
{
    char seatNumber[SEATS_NUMBER_MAX_SIZE];
    bool isSeatReserved;
    Name nameOfCustomer;
} Seat;

typedef struct _FlightSeats
{
    Seat *seatsList;
    unsigned int seatsCount;
} FlightSeats;

char *s_gets(char *st, int n);
char *getNSizeString(char *str, int n);
void transStrToUpperCase(char *str);
char *copyString(char *strTarget, char *strSource, int iSize);

bool InsertSort(FlightSeats *flightSeats);

bool initSeat(Seat *seat);
bool initFlightSeats(FlightSeats *flightSeats, Seat seats[], unsigned int uiSeatsCount);

void showMainMenu();

unsigned int getCountOfEmptySeats(const FlightSeats *flightSeats);
bool printSeatInfo(const Seat *seat);
bool numberTheFlightSeats(FlightSeats *flightSeats, int iCol, int iRow);
bool sortSeatsListInAlphabeticalOrder(FlightSeats *flightSeats);
Seat *findSeatByNum(const FlightSeats *flightSeats, const char *strNum);

// 主菜单操作
bool showCountOfEmptySeats(const FlightSeats *flightSeats);
bool listEmptySeats(const FlightSeats *flightSeats);
bool listSeatsByAlphabeticalOrder(const FlightSeats *flightSeats);

bool SeatAssignmentMenu(FlightSeats *flightSeats);
bool DelSeatAssignmentMenu(FlightSeats *flightSeats);

int main(int argc, char const *argv[])
{

    return 0;
}

char *s_gets(char *st, int n)
{
    char *ret_val;
    char *find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n'); // 查找换行符
        if (find)                // 如果地址不是 NULL，
            *find = '\0';        // 在此处放置一个空字符
        else
            while (getchar() != '\n')
                continue; // 清理输入行
    }

    return ret_val;
}

char *getNSizeString(char *str, int n)
{
    char *retVal;
    char *find;

    retVal = fgets(str, n, stdin);
    if (retVal)
    {
        find = strchr(str, '\n');
        if (find)
            *find = '\0';
    }

    return retVal;
}

void transStrToUpperCase(char *str)
{
    fprintf(stderr, "\
[ERROR]     Failed to trans the string to uppercase.\n\
            Null pointer.\n");

    int iStrLength = strlen(str);

    for (int i = 0; i < iStrLength; i++)
        str[i] = toupper(str[i]);
}

char *copyString(char *strTarget, char *strSource, int iSize)
{
    if (strTarget == NULL || strSource == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while copying a string.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return NULL;
    }

    char *retVal;
    retVal = strncpy(strTarget, strSource, iSize - 1);
    strTarget[iSize - 1] = '\0';

    return retVal;
}

/**
 * - [in, out] flightSeats
 *
 * 使用插入排序算法对座位列表按照“字母表顺序”进行排序。
 *
 */
bool InsertSort(FlightSeats *flightSeats)
{
    if (flightSeats == NULL || flightSeats->seatsList == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failed to sort the list.\n\
            Null pointer or invalid memory region.\n");
        return false;
    }

    if (flightSeats->seatsCount < 2U)
    {
        fprintf(stderr, "\
[ERROR]     No need to sort.\n");
        return false;
    }

    unsigned int uiSeatsCount = flightSeats->seatsCount;
    Seat *pSeats = flightSeats->seatsList;

    Seat seatBuf;

    for (unsigned int uiI = 1; uiI < uiSeatsCount; uiI++)
        for (unsigned int uiJ = uiI; uiJ > 0 && strcmp(pSeats[uiJ].seatNumber, pSeats[uiJ - 1].seatNumber) < 0; uiJ--)
        {
            seatBuf = pSeats[uiJ];
            pSeats[uiJ] = pSeats[uiJ - 1];
            pSeats[uiJ - 1] = seatBuf;
        }

    return true;
}

/**
 * - [out] seat
 */
bool initSeat(Seat *seat)
{
    if (seat == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while initialing the seat.\n\
            Null pointer.\n");
        return false;
    }

    *seat = (Seat){
        .seatNumber = STR_INIT_VOID,
        .isSeatReserved = 0,
        .nameOfCustomer = (Name){.first = STR_INIT_VOID,
                                 .last = STR_INIT_VOID}};

    return true;
}

/**
 * - [out] flightSeats
 * - [in] seats
 * - [in] uiSeatsCount
 *
 * 新建的 FlightSeats 结构在初次使用前，应使用此函数进行初始化。
 * 若结构成功初始化，则返回 true，否则返回 false。
 *
 * [out] flightSeats
 * flightSeats 是一个 FlightSeats 类型的指针，
 * 此指针应指向一个（新创建的）未初始化的 FlightSeats 类型的结构。
 *
 * [in] seats
 * seats 是一个 Seat 类型的数组，
 * 赋给 flightSeats 作为其成员结构。
 *
 * [in] uiSeatsCount
 * uiSeatsCount 是一个无符号整型类型的值，
 * 赋给 flightSeats 作为其成员结构。
 *
 */
bool initFlightSeats(FlightSeats *flightSeats, Seat seats[], unsigned int uiSeatsCount)
{
    if (flightSeats == NULL || seats == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while initialing the flightSeats.\n\
            Null pointer.\n");
        return false;
    }

    *flightSeats = (FlightSeats){
        .seatsList = seats,
        .seatsCount = uiSeatsCount};

    return true;
}

void showMainMenu()
{
    fprintf(stdout, "\
To choose a function, enter its letter label:\n\
a) Show number of empty seats\n\
b) Show list of empty seats\n\
c) Show alphabetical list of seats\n\
d) Assign a customer to a seat assignment\n\
e) Delete a seat assignment\n\
f) Quit\n");
}

/**
 * - [in] flightSeats
 *
 * 计算并返回参数结构中空座位的数量。
 *
 */
unsigned int getCountOfEmptySeats(const FlightSeats *flightSeats)
{
    if (flightSeats == NULL || flightSeats->seatsList == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while counting empty seats.\n\
            Null pointer or invalid memory region.\n");
        return 0;
    }

    unsigned int uiEmptySeatsCount = 0;

    for (int i = 0; i < flightSeats->seatsCount; i++)
    {
        if (flightSeats->seatsList[i].isSeatReserved == 0)
            uiEmptySeatsCount++;
    }

    return uiEmptySeatsCount;
}

/**
 * - [in] seat
 *
 * 打印座位的信息，此函数通常不独立使用，主要在其他函数中被调用。
 * 调用成功时返回 true，否则返回 false。
 *
 */
bool printSeatInfo(const Seat *seat)
{
    if (seat == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while printing seat information.\n\
            Null pointer.\n");
        return false;
    }

    const char *pstrIsSeatReserved = NULL;

    if (seat->isSeatReserved == true)
        pstrIsSeatReserved = STR_BOOL_TRUE;
    else
        pstrIsSeatReserved = STR_BOOL_FALSE;

    fprintf(stdout, "\
  SeatNumber: %.2s, Reserved: %-3s, CustomerName: %s\n",
            seat->seatNumber, pstrIsSeatReserved, seat->nameOfCustomer);

    return true;
}

/**
 * - [out] flightSeats
 *
 * 对座位列表以字母表顺序进行排序。
 *
 */
bool sortSeatsListInAlphabeticalOrder(FlightSeats *flightSeats)
{
    if (flightSeats == NULL || flightSeats->seatsList == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failed to sort the list.\n\
            Null pointer or invalid memory region.\n");
        return false;
    }

    if (InsertSort(flightSeats) == false)
        return false;

    return true;
}

/**
 * - [in] flightSeats
 * - [in] strNum
 *
 * 通过编号来查找座位列表中是否有匹配的座位，匹配则返回此座位的地址，否则返回空指针。
 *
 */
Seat *findSeatByNum(const FlightSeats *flightSeats, const char *strNum)
{
    if (flightSeats == NULL || flightSeats->seatsList == NULL || strNum == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while finding a seat.\n\
            Null pointer or invalid memory region.\n");
        return NULL;
    }

    for (unsigned int ui = 0; ui < flightSeats->seatsCount; ui++)
    {
        if (0 == strcmp(flightSeats->seatsList[ui].seatNumber, strNum))
            return (&flightSeats->seatsList[ui]);
    }

    return NULL;
}

/**
 * - [in] flightSeats
 *
 * 向标准输出打印座位列表中空座位的数量。
 *
 */
bool showCountOfEmptySeats(const FlightSeats *flightSeats)
{
    if (flightSeats == NULL || flightSeats->seatsList == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while counting empty seats.\n\
            Null pointer or invalid memory region.\n");
        return false;
    }

    fprintf(stdout, "\
  Empty Seats: %u\n",
            getCountOfEmptySeats(flightSeats));

    return true;
}

/**
 * - [in] flightSeats
 *
 * 列出列表中空座位的信息。
 *
 */
bool listEmptySeats(const FlightSeats *flightSeats)
{
    if (flightSeats == NULL || flightSeats->seatsList == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failed to list the empty seats.\n\
            Null pointer or invalid memory region.\n");
        return false;
    }

    unsigned int uiSeatsCount = flightSeats->seatsCount;
    const Seat *pSeats = flightSeats->seatsList;

    for (unsigned int ui = 0; ui < uiSeatsCount; ui++)
        printSeatInfo(&pSeats[ui]);

    return true;
}

/**
 * - [in] flightSeats
 *
 * 按座位编号的字母顺序打印列表中所有座位的信息。
 *
 */
bool listSeatsByAlphabeticalOrder(const FlightSeats *flightSeats)
{
    if (flightSeats == NULL || flightSeats->seatsList == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failed to list the seats.\n\
            Null pointer or invalid memory region.\n");
        return false;
    }

    Seat seatsTemp[SEATS_COUNT];
    FlightSeats flightSeatsTemp;

    // 选择最小的，以防止数组下标“溢出”
    unsigned int uiSeatsCount = SEATS_COUNT < flightSeats->seatsCount
                                    ? SEATS_COUNT
                                    : flightSeats->seatsCount;

    if (initFlightSeats(&flightSeatsTemp, seatsTemp, uiSeatsCount) == false)
        return false;

    for (unsigned int ui = 0; ui < uiSeatsCount; ui++)
        flightSeatsTemp.seatsList[ui] = flightSeats->seatsList[ui];

    sortSeatsListInAlphabeticalOrder(&flightSeatsTemp);
    for (unsigned int ui = 0; ui < uiSeatsCount; ui++)
        printSeatInfo(&flightSeatsTemp.seatsList[ui]);

    return true;
}

bool SeatAssignmentMenu(FlightSeats *flightSeats)
{
    if (flightSeats == NULL || flightSeats->seatsList == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failed to access the seat assignment menu.\n\
            Null pointer or invalid memory region.\n");
        return false;
    }

    if (getCountOfEmptySeats(flightSeats) == 0)
    {
        fprintf(stderr, "\
[ERROR]     Full list.\n");
        return false;
    }

    Seat *pSeatFound;

    Seat seatBuf;
    initSeat(&seatBuf);

    // TODO 先提示输入名字，然后显示空座位，输入座位编号后检查座位是否已被预订，若已被预订则继续提示输入编号，输入成功后返回主菜单，输入随时可以被取消

    // 开始输入名字
    bool isNameDone = false;
    while (!isNameDone)
    {
        fprintf(stdout, "\
  Enter your name: (Enter [Ctrl] + [z] to cancel)\n");
        fgets(seatBuf.nameOfCustomer.first, NAME_FIRST_MAX_LENGTH, stdin);
        int iRetValFi = getNSizeString(seatBuf.nameOfCustomer.first, NAME_FIRST_MAX_SIZE);
        if (iRetValFi == NULL)
            break;

        int iRetValLa = getNSizeString(seatBuf.nameOfCustomer.last, NAME_LAST_MAX_SIZE);
        if (iRetValLa == NULL)
            break;

        while (getchar() != '\n')
            continue;

        isNameDone = true;
    }
    while (getchar() != '\n')
        continue;

    if (!isNameDone)
    {
        fprintf(stdout, "\
  Canceled.\n");
        return false;
    }
    else
    {
        fprintf(stdout, "\
  Your name: \"%s %s\"\n",
                seatBuf.nameOfCustomer.first, seatBuf.nameOfCustomer.last);
    }

    // 开始输入编号
    bool isNumberDone = false;
    while (!isNumberDone)
    {
        // 显示空座位信息
        listEmptySeats(&flightSeats);

        fprintf(stdout, "\
  Enter the number of the seat you wish to reserve: (Enter [Ctrl] + [z] to cancel)\n");
        char strNumBuf[SEATS_NUMBER_MAX_SIZE];

        int iNumRetVal = getNSizeString(strNumBuf, SEATS_NUMBER_MAX_SIZE);
        while (getchar() != '\n')
            continue;
        if (iNumRetVal == NULL)
            break;

        transStrToUpperCase(strNumBuf);
        Seat *pSeatFind;

        if ((pSeatFind = findSeatByNum(flightSeats, strNumBuf)) == NULL)
        {
            fprintf(stderr, "\
[ERROR] Such a seat not found.\n");
            fprintf(stdout, "\
  Please re-enter.\n");
            continue;
        }

        if (pSeatFind->isSeatReserved == true)
        {
            fprintf(stdout, "\
  The seat \"%s\" has already reserved.",
                    pSeatFind->seatNumber);
            fprintf(stdout, "\
  Please re-enter.\n");
            continue;
        }
        pSeatFound = pSeatFind;
        copyString(seatBuf.seatNumber, strNumBuf, SEATS_NUMBER_MAX_SIZE);

        isNumberDone == true;
    }

    if (!isNumberDone)
    {
        fprintf(stdout, "\
  Canceled.\n");
        return false;
    }
    else
    {
        fprintf(stdout, "\
  Seat number reserved: \"%s\"\n",
                seatBuf.seatNumber);
        seatBuf.isSeatReserved = true;
    }

    *pSeatFound = seatBuf;

    fprintf(stdout, "\
  Done. Seat number %s has reserved.\n");

    return true;
}

bool DelSeatAssignmentMenu(FlightSeats *flightSeats)
{
    if (flightSeats == NULL || flightSeats->seatsList == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failed to access the seat assignment deletion menu.\n\
            Null pointer or invalid memory region.\n");
        return false;
    }

    if (getCountOfEmptySeats(flightSeats) >= flightSeats->seatsCount)
    {
        fprintf(stderr, "\
[ERROR]     Empty list.\n");
        return false;
    }
}
