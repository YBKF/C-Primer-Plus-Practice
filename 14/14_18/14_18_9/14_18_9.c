/**
 * 9.巨人航空公司（编程练习 8）需要另一架飞机（容量相同），每天飞4 班（航班 102、311、444 和519）。
 * 把程序扩展为可以处理4个航班。用一个顶层菜单提供航班选择和退出。
 * 选择一个特定航班，就会出现和编程练习8类似的菜单。但是该菜单要添加一个新选项：确认座位分配。
 * 而且，菜单中的退出是返回顶层菜单。每次显示都要指明当前正在处理的航班号。
 * 另外，座位分配显示要指明确认状态。
 *
 * "确认座位分配" 理解为：进入某航班的座位分配菜单，进行座位分配时先将分配的座位储存到一个临时航班数据中，
 * 执行 “确认座位分配” 后再存储到源航班数据中，若未执行 “确认座位分配” 就返回主菜单则丢弃临时航班数据
 *
 * TODO 添加新的菜单，根据新菜单的选项生成对应的参数，将参数传入 14_18_8 的主程序中
 *
 */
#include "14_18_9.h"

static const char *const strFlightNum[FLIGHT_COUNT] = {"102", "311", "444", "519"};

int flightMenu(Flight *pFlight);

int main(int argc, char const *argv[])
{
    Flight flightArr[FLIGHT_COUNT];

    for (int i = 0; i < FLIGHT_COUNT; i++)
    {
        FlightSeats flightSeatsTemp;

        initFlightSeats(&flightSeatsTemp, (unsigned int)SEATS_COUNT);
        numberTheFlightSeats(&flightSeatsTemp);
        initFlight(&flightArr[i], strFlightNum[i], &flightSeatsTemp);
    }

    char strOpt[STR_FLIGHTS_INDEX_LENGTH] = {""};

    bool isQuitted = false;
    while (!isQuitted)
    {
        showMainMenu(flightArr, FLIGHT_COUNT);

        if (s_gets(strOpt, STR_FLIGHTS_INDEX_LENGTH) == NULL)
        {
            fprintf(stderr, "\n\
Input interrupted. Exiting...\n");
            exit(EXIT_FAILURE);
        }

        // 检查是否只有一个字符，且这个字符是否为 'q'
        if (strOpt[1] == '\0' && strOpt[0] == 'q')
        {
            fprintf(stdout, "\
Quitted.\n");
            isQuitted = true;
            break;
        }

        // 确认字符串长度
        int iStrOptLength = -1;
        while (strOpt[++iStrOptLength])
            continue;

        // 检查字符串中是否全部为数字字符
        bool isAllDigit = true;
        while (iStrOptLength--)
        {
            if (!isdigit(strOpt[iStrOptLength]))
            {
                fprintf(stderr, "\
[ERROR]     Invalid option.\n");
                isAllDigit = false;
                break;
            }
        }

        // 字符串中有非数字字符，则重新开始
        if (!isAllDigit)
        {
            fprintf(stderr, "\
[ERROR]     Please input digit string.\n");
            continue;
        }

        int iParsedIndex = atoi(strOpt);

        if (iParsedIndex >= FLIGHT_COUNT || iParsedIndex < 0)
        {
            fprintf(stderr, "\
[ERROR]     Out of the list range.\n");
            continue;
        }

        flightMenu(&flightArr[iParsedIndex]);
    }

    return 0;
}

int flightMenu(Flight *pFlight)
{
    FlightSeats *pFlightSeats = &(pFlight->flightSeats);

    FlightSeats flightSeatsTemp;

    FlightSeats *pFlightSeatsTemp = &flightSeatsTemp;
    initFlightSeats(pFlightSeatsTemp, (unsigned int)SEATS_COUNT);

    // flightSeatsTemp 为 pFlight->flightSeats 的副本
    copyFlightSeats(pFlightSeatsTemp, pFlightSeats);

    char chOpt;

    bool isFlightSeatsConfirmed = false;
    bool isBackToMainMenu = false;
    while (!isBackToMainMenu)
    {
        if (showFlightMenu(pFlight->strFlightNum, isFlightSeatsConfirmed) == false)
        {
            fprintf(stderr, "\
An error occurred while handling the flight.\n");
            return ERROR_CODE_GOT_AN_ERROR;
        }

        chOpt = getcharOpt();

        switch (chOpt)
        {
        case 'a':
            showCountOfEmptySeats(pFlightSeatsTemp);
            break;

        case 'b':
            listEmptySeats(pFlightSeatsTemp);
            break;

        case 'c':
            listSeatsByAlphabeticalOrder(pFlightSeatsTemp);
            break;

        case 'd':
            SeatAssignmentMenu(pFlightSeatsTemp);
            isFlightSeatsConfirmed = false;
            break;

        case 'e':
            DelSeatAssignmentMenu(pFlightSeatsTemp);
            isFlightSeatsConfirmed = false;
            break;

        case 'f':
            if (confirmSeatsAssignment(pFlightSeats, &flightSeatsTemp) == true)
            {
                isFlightSeatsConfirmed = true;
            }
            break;

        case 'g':
            isBackToMainMenu = true;
            break;

        default:
            fprintf(stderr, "\
[ERROR]     Invalid option.\n");
            break;
        }
    }

    fprintf(stdout, "\
  Back to main menu.\n");

    return 0;
}
