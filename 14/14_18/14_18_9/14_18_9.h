#ifndef _INC_14_18_9_H
#define _INC_14_18_9_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define FLIGHT_NUM_STR_SIZE (3)
#define FLIGHT_COUNT (4)

#define STR_FLIGHTS_INDEX_LENGTH (8)

#define NAME_FIRST_MAX_LENGTH (25)
#define NAME_FIRST_MAX_SIZE (NAME_FIRST_MAX_LENGTH + 1)
#define NAME_LAST_MAX_LENGTH (25)
#define NAME_LAST_MAX_SIZE (NAME_LAST_MAX_LENGTH + 1)
#define STR_NUM_MAX_LENGTH (4)
#define STR_NUM_MAX_SIZE (STR_NUM_MAX_LENGTH + 1)

#define SEATS_COUNT (12)

#define STR_VOID ("")
#define STR_INIT_VOID STR_VOID
#define STR_BOOL_TRUE ("Yes")
#define STR_BOOL_FALSE ("No")

#define STR_BOOL_LENGTH (3)
#define STR_BOOL_SIZE (STR_BOOL_LENGTH + 1)

#define ERROR_CODE_GOT_AN_ERROR (-1)

typedef struct _Name
{
    char first[NAME_FIRST_MAX_SIZE];
    char last[NAME_LAST_MAX_SIZE];
} Name;

typedef struct _Seat
{
    unsigned int seatNumber;
    bool isSeatReserved;
    Name nameOfCustomer;
} Seat;

typedef struct _FlightSeats
{
    Seat seatsList[SEATS_COUNT];
    unsigned int seatsCount;
} FlightSeats;

typedef struct _Flight
{
    const char *strFlightNum;
    FlightSeats flightSeats;
} Flight;

typedef struct _StrToIntPair
{
    char *chFirst;
    int iSecond;
} StrToIntPair;

char *s_gets(char *st, int n);
char getcharOpt();

void transStrToUpperCase(char *str);
char *copyString(char *strTarget, char *strSource, int iSize);
FlightSeats *copyFlightSeats(FlightSeats *pFlightSeatsTarget, const FlightSeats *pFlightSeatsSource);
Flight *copyFlight(Flight *pFlightTarget, const Flight *pFlightSource);

bool InsertSort(FlightSeats *flightSeats);

bool initSeat(Seat *seat);
bool initFlightSeats(FlightSeats *flightSeats, unsigned int uiSeatsCount);

bool showFlightMenu(const char *strFlightNum, const bool isFlightSeatsConfirmed);

unsigned int getCountOfEmptySeats(const FlightSeats *flightSeats);
bool printSeatInfo(const Seat *seat);
bool numberTheFlightSeats(FlightSeats *flightSeats);
bool sortSeatsListInAlphabeticalOrder(FlightSeats *flightSeats);
Seat *findSeatByNum(FlightSeats *flightSeats, unsigned int uiNum);

// 主菜单操作

bool showCountOfEmptySeats(const FlightSeats *flightSeats);
bool listEmptySeats(const FlightSeats *flightSeats);
bool listSeatsByAlphabeticalOrder(const FlightSeats *flightSeats);
bool confirmSeatsAssignment(FlightSeats *flightSeats, const FlightSeats *flightSeatsTemp);

bool SeatAssignmentMenu(FlightSeats *flightSeats);
bool DelSeatAssignmentMenu(FlightSeats *flightSeats);

bool showFlightNum(const int iFlightIndex, const char *strFlightNum);
bool listFlights(const Flight flightArr[], const int arrSize);
bool showMainMenu(const Flight flightArr[], const int arrSize);

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

/**
 * 从标准输入中仅获取一个字符，
 * 输入仅为一个字符时，将返回输入的这个字符；
 * 输入多于一个字符时，将返回一个空字符，且缓冲区中的其他字符将被清除。
 */
char getcharOpt()
{
    char chBuf;
    chBuf = getchar();
    if (getchar() != '\n')
    {
        while (getchar() != '\n')
            continue;
        return '\0';
    }
    return chBuf;
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
 * 拷贝 pFlightSeatsSource (源) 的数据至 pFlightSeatsTarget (目标)，
 * 为保证内存安全，此函数实际上仅从源中复制 pFlightSeatsTarget->seatsCount 大小的 pFlightSeatsSource->seatsList 至目标，
 * 若源中 seatsList 数组大小 seatsCount 小于目标 seatsList 数组大小 seatsCount，则将剩余的空间填为默认值
 *
 * - [out] pFlightSeatsTarget
 * - [in] pFlightSeatsSource
 */
FlightSeats *copyFlightSeats(FlightSeats *pFlightSeatsTarget, const FlightSeats *pFlightSeatsSource)
{
    if (NULL == pFlightSeatsTarget || NULL == pFlightSeatsSource)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while copying a FlightSeats.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return NULL;
    }

    if (NULL == pFlightSeatsTarget->seatsList || NULL == pFlightSeatsSource->seatsList)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while copying a FlightSeats.\n\
            seatsList of the FlightSeats is a null pointer.\n");
        return NULL;
    }

    int iValidDataSize;

    const int iSeatsCountSource = (int)pFlightSeatsSource->seatsCount;
    const int iSeatsCountTarget = (int)pFlightSeatsTarget->seatsCount;

    if (iSeatsCountSource < iSeatsCountTarget)
    {
        iValidDataSize = iSeatsCountSource;
    }
    else
    {
        iValidDataSize = iSeatsCountTarget;
    }

    int iValidDataIndex = 0;

    Seat *seatsListTarget = pFlightSeatsTarget->seatsList;
    const Seat *seatsListSource = pFlightSeatsSource->seatsList;

    while (iValidDataIndex < iValidDataSize)
    {
        seatsListTarget[iValidDataIndex] = seatsListSource[iValidDataIndex];
        iValidDataIndex++;
    }

    if (iValidDataIndex < iSeatsCountTarget)
    {
        Seat seatDefault;
        initSeat(&seatDefault);

        for (int i = iValidDataIndex; i < iSeatsCountTarget; i++)
        {
            seatsListTarget[i] = seatDefault;
        }
    }

    return pFlightSeatsTarget;
}

Flight *copyFlight(Flight *pFlightTarget, const Flight *pFlightSource)
{
    if (NULL == pFlightTarget || NULL == pFlightSource)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while copying a FlightSeats.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return NULL;
    }

    pFlightTarget->strFlightNum = pFlightSource->strFlightNum;
    copyFlightSeats(&pFlightTarget->flightSeats, &pFlightSource->flightSeats);
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
        for (unsigned int uiJ = uiI; uiJ > 0 && pSeats[uiJ].seatNumber < pSeats[uiJ - 1].seatNumber; uiJ--)
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
        .seatNumber = 0U,
        .isSeatReserved = 0,
        .nameOfCustomer = (Name){.first = STR_INIT_VOID,
                                 .last = STR_INIT_VOID}};

    return true;
}

/**
 * - [out] flightSeats
 * - [in] uiSeatsCount
 *
 * 新建的 FlightSeats 结构在初次使用前，应使用此函数进行初始化。
 * 若结构成功初始化，则返回 true，否则返回 false。
 *
 * [out] flightSeats
 * flightSeats 是一个 FlightSeats 类型的指针，
 * 此指针应指向一个（新创建的）未初始化的 FlightSeats 类型的结构。
 *
 * [in] uiSeatsCount
 * uiSeatsCount 是一个无符号整型类型的值，
 * 赋给 flightSeats 作为其成员结构。
 *
 */
bool initFlightSeats(FlightSeats *flightSeats, unsigned int uiSeatsCount)
{
    if (flightSeats == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while initialing the flightSeats.\n\
            Null pointer.\n");
        return false;
    }

    Seat defaultSeat;

    initSeat(&defaultSeat);

    Seat *seatsList = flightSeats->seatsList;
    flightSeats->seatsCount = uiSeatsCount;

    for (int i = 0; i < uiSeatsCount; i++)
    {
        seatsList[i] = defaultSeat;
    }

    return true;
}

bool initFlight(Flight *pFlight, const char *strFlightNum, const FlightSeats *pFlightSeats)
{
    if (NULL == pFlight || NULL == strFlightNum || NULL == pFlightSeats)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while initialing the flight.\n\
            Null pointer.\n");
        return false;
    }

    *pFlight = (Flight){
        .strFlightNum = strFlightNum,
        .flightSeats = *pFlightSeats};

    return true;
}

bool showFlightNum(const int iFlightIndex, const char *strFlightNum)
{
    if (NULL == strFlightNum)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while showing the flight menu.\n\
            The flight is not exist.\n");
        return false;
    }

    fprintf(stdout, "\
  %d) %s\n",
            iFlightIndex, strFlightNum);

    return true;
}

bool listFlights(const Flight flightArr[], const int arrSize)
{
    if (NULL == flightArr)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while list the flight info.\n\
            The FlightList is null.\n");
        return false;
    }

    if (arrSize <= 0)
    {
        fprintf(stdout, "\
  There have nothing about any flights here.\n");
        return false;
    }

    for (int i = 0; i < arrSize; i++)
    {
        showFlightNum(i, flightArr[i].strFlightNum);
    }

    return true;
}

bool showMainMenu(const Flight flightArr[], const int arrSize)
{
    if (NULL == flightArr)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while list the flight info.\n\
            The FlightList is null.\n");
        return false;
    }

    if (arrSize <= 0)
    {
        fprintf(stdout, "\
  There have nothing about any flights here.\n");
        return false;
    }

    fprintf(stdout, "\
Select a flight number: \n");
    if (listFlights(flightArr, arrSize) == false)
    {
        return false;
    }

    fprintf(stdout, "\
  q) Quit.\n");

    return true;
}

bool showFlightMenu(const char *strFlightNum, const bool isFlightSeatsConfirmed)
{
    if (NULL == strFlightNum)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while showing the flight menu.\n\
            The flight is not exist.\n");
        return false;
    }

    char *strIsFlightSeatsConfirmed;

    if (isFlightSeatsConfirmed == true)
    {
        strIsFlightSeatsConfirmed = "Yes";
    }
    else
    {
        strIsFlightSeatsConfirmed = "No";
    }

    fprintf(stdout, "\
Selected Flight: %s\n\
Flight Seats Confirmed: %s\n\
\n\
To choose a function, enter its letter label:\n\
  a) Show number of empty seats\n\
  b) Show list of empty seats\n\
  c) Show alphabetical list of seats\n\
  d) Assign a customer to a seat assignment\n\
  e) Delete a seat assignment\n\
  f) Confirm the seats assignment\n\
  g) Back to main menu.\n",
            strFlightNum, strIsFlightSeatsConfirmed);

    return true;
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
        if (flightSeats->seatsList[i].isSeatReserved == false)
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
  SeatNumber: %.3u, Reserved: %-3s, CustomerName: %s %s\n",
            seat->seatNumber,
            pstrIsSeatReserved,
            seat->nameOfCustomer.first,
            seat->nameOfCustomer.last);

    return true;
}

/**
 * - [out] flightSeats
 *
 * 自动为座位列表中各座位进行编号，通常以 1 为编号起始值。
 * 通常在对 FlightSeats 类型的结构进行初始化后，应调用这个函数。
 *
 */
bool numberTheFlightSeats(FlightSeats *flightSeats)
{
    if (flightSeats == NULL || flightSeats->seatsList == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failed to number the seats.\n\
            Null pointer or invalid memory region.\n");
        return false;
    }

    if (flightSeats->seatsCount == 0)
    {
        fprintf(stderr, "\
  There aren't any seats.\n");
        return false;
    }

    for (unsigned int ui = 0; ui < flightSeats->seatsCount; ui++)
        flightSeats->seatsList[ui].seatNumber = ui + 1;

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
 * - [in] uiNum
 *
 * 通过编号来查找座位列表中是否有匹配的座位，匹配则返回此座位的地址，否则返回空指针。
 *
 */
Seat *findSeatByNum(FlightSeats *flightSeats, unsigned int uiNum)
{
    if (flightSeats == NULL || flightSeats->seatsList == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while finding a seat.\n\
            Null pointer or invalid memory region.\n");
        return NULL;
    }

    for (unsigned int ui = 0; ui < flightSeats->seatsCount; ui++)
    {
        if (flightSeats->seatsList[ui].seatNumber == uiNum)
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
        if (pSeats[ui].isSeatReserved == false)
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

    FlightSeats flightSeatsTemp;

    // 选择最小的，以防止数组下标“溢出”
    unsigned int uiSeatsCount = SEATS_COUNT < flightSeats->seatsCount
                                    ? SEATS_COUNT
                                    : flightSeats->seatsCount;

    if (initFlightSeats(&flightSeatsTemp, uiSeatsCount) == false)
        return false;

    for (unsigned int ui = 0; ui < uiSeatsCount; ui++)
        flightSeatsTemp.seatsList[ui] = flightSeats->seatsList[ui];

    sortSeatsListInAlphabeticalOrder(&flightSeatsTemp);
    for (unsigned int ui = 0; ui < uiSeatsCount; ui++)
        printSeatInfo(&flightSeatsTemp.seatsList[ui]);

    return true;
}

/**
 * - [out] flightSeats
 * - [in] flightSearsTemp
 *
 * 确认指定航班的座位分配情况，将当前临时的座位分配存储到指定航班数据中。
 */
bool confirmSeatsAssignment(FlightSeats *flightSeats, const FlightSeats *flightSeatsTemp)
{
    if (flightSeats == NULL || flightSeats->seatsList == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failed to get the flight infomation.\n\
            Null pointer or invalid memory region.\n");
        return false;
    }

    if (flightSeatsTemp == NULL || flightSeatsTemp->seatsList == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failed to get the temp flight infomation.\n\
            Null pointer or invalid memory region.\n");
        return false;
    }

    const FlightSeats *copyResult = copyFlightSeats(flightSeats, flightSeatsTemp);

    if (NULL == copyResult)
    {
        fprintf(stderr, "\
[ERROR]     Failed to copy the temp flight seats to the source flight seats.");
        return false;
    }

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

    // 开始输入名字
    bool isNameDone = false; // 用于区分输入中被取消还是输入成功
    while (!isNameDone)
    {
        fprintf(stdout, "\
  Enter your first name: (Enter [Ctrl] + [z] to cancel)\n");
        char *pchRetValFi = s_gets(seatBuf.nameOfCustomer.first, NAME_FIRST_MAX_SIZE);
        if (pchRetValFi == NULL)
            break;

        fprintf(stdout, "\
  Enter your last name: (Enter [Ctrl] + [z] to cancel)\n");
        char *pchRetValLa = s_gets(seatBuf.nameOfCustomer.last, NAME_LAST_MAX_SIZE);
        if (pchRetValLa == NULL)
            break;

        isNameDone = true;
    }

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
    bool isNumberDone = false; // 用于区分输入中被取消还是输入成功
    while (!isNumberDone)
    {
        // 显示空座位信息
        listEmptySeats(flightSeats);

        fprintf(stdout, "\
  Enter the number of the seat you wish to reserve: (Enter [Ctrl] + [z] to cancel)\n");
        unsigned int uiNumBuf;
        char strNumUnconverted[STR_NUM_MAX_SIZE];

        char *pchRetVal = s_gets(strNumUnconverted, STR_NUM_MAX_SIZE);
        if (pchRetVal == NULL)
            break;

        uiNumBuf = (unsigned int)atoi(strNumUnconverted);

        Seat *pSeatFind;

        if ((pSeatFind = findSeatByNum(flightSeats, uiNumBuf)) == NULL)
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
  The seat \"%.3u\" has already reserved.",
                    pSeatFind->seatNumber);
            fprintf(stdout, "\
  Please re-enter.\n");
            continue;
        }
        pSeatFound = pSeatFind; // 将查找到的座位的地址传出到循环外部
        seatBuf.seatNumber = uiNumBuf;

        isNumberDone = true;
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
  Seat number reserved: \"%.3u\"\n",
                seatBuf.seatNumber);
        seatBuf.isSeatReserved = true;
    }

    // 完成所有步骤后，最后将座位缓存中的信息复制到已查找到的座位的地址处
    *pSeatFound = seatBuf;

    fprintf(stdout, "\
  Done. Seat number %.3u has reserved.\n",
            pSeatFound->seatNumber);

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

    bool isNumberDone = false; // 用于区分输入中被取消还是输入成功
    while (!isNumberDone)
    {
        fprintf(stdout, "\
  All seats:\n");
        listSeatsByAlphabeticalOrder(flightSeats);

        fprintf(stdout, "\
  Enter the number of the seat you wish to delete: (Enter [Ctrl] + [z] to cancel)\n");
        unsigned int uiNumBuf;
        char strNumUnconverted[STR_NUM_MAX_SIZE];

        char *pchRetVal = s_gets(strNumUnconverted, STR_NUM_MAX_SIZE);
        if (pchRetVal == NULL)
            break;

        uiNumBuf = (unsigned int)atoi(strNumUnconverted);

        Seat *pSeatFind;

        if ((pSeatFind = findSeatByNum(flightSeats, uiNumBuf)) == NULL)
        {
            fprintf(stderr, "\
[ERROR] Such a seat not found.\n");
            fprintf(stdout, "\
  Please re-enter.\n");
            continue;
        }

        // 当座位未被预定时且客户的名字为空，不对座位进行删除
        if (pSeatFind->isSeatReserved == false &&
            strcmp(pSeatFind->nameOfCustomer.first, STR_VOID) == 0 &&
            strcmp(pSeatFind->nameOfCustomer.last, STR_VOID) == 0)
        {
            fprintf(stdout, "\
  The seat \"%.3u\" has not reserved.\n",
                    pSeatFind->seatNumber);
            fprintf(stdout, "\
  Please re-enter.\n");
            continue;
        }

        pSeatFind->isSeatReserved = false;
        copyString(pSeatFind->nameOfCustomer.first, STR_VOID, NAME_FIRST_MAX_SIZE);
        copyString(pSeatFind->nameOfCustomer.last, STR_VOID, NAME_LAST_MAX_SIZE);

        isNumberDone = true;
    }

    if (!isNumberDone)
    {
        fprintf(stdout, "\
  Canceled.\n");
        return false;
    }

    fprintf(stdout, "\
  Done.\n");

    return true;
}

#endif