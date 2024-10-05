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
#include <stdbool.h>

#define NAME_FIRST_MAX_LENGTH (25)
#define NAME_FIRST_MAX_SIZE (NAME_FIRST_MAX_LENGTH + 1)
#define NAME_LAST_MAX_LENGTH (25)
#define NAME_LAST_MAX_SIZE (NAME_LAST_MAX_LENGTH + 1)
#define SEATS_NUMBER_MAX_LENGTH (10)
#define SEATS_NUMBER_MAX_SIZE (SEATS_NUMBER_MAX_LENGTH + 1)

#define SEATS_COUNT (12)

#define STR_INIT_VOID ("")

typedef Seat Item;

typedef struct _Name
{
    char first[NAME_FIRST_MAX_SIZE];
    char last[NAME_LAST_MAX_SIZE];
} Name;

typedef struct _Seat
{
    char seatNumber[SEATS_NUMBER_MAX_SIZE];
    bool isSeatReserved;
    Name nameOfBooker;
} Seat;

typedef struct _FlightSeats
{
    Seat *seatsList;
    unsigned int seatsCount;
} FlightSeats;

char *s_gets(char *st, int n);

bool initSeat(Seat *seat);
bool initFlightSeats(FlightSeats *flightSeats, Seat seats[], unsigned int uiSeatsCount);

void showMainMenu();

unsigned int getCountOfEmptySeats(const FlightSeats *flightSeats);
bool printSeatInfo(const Seat *seat);
bool isSeatReserved(const Seat *seat);
bool sortSeatsListByTo(void (*sortFun)(Item itemList), const FlightSeats *flightSeats, FlightSeats *flightSeatsBuf);

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
        .nameOfBooker = (Name){STR_INIT_VOID, STR_INIT_VOID}};

    return true;
}

/**
 * - [out] flightSeats
 * - [in] seats
 * - [in] uiSeatsCount
 *
 * 新建的 FlightSeats 结构在初次使用前，应使用此函数进行初始化。
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

unsigned int getCountOfEmptySeats(const FlightSeats *flightSeats)
{
    if (flightSeats == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while getting the count of the empty seats.\n\
            Null pointer.\n");
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
