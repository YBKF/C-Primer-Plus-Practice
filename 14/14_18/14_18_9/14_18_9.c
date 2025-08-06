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
#include <stdio.h>
#include "14_18_9.h"

static const char *const strFlightNum[FLIGHT_COUNT] = {"102", "311", "444", "519"};

int flightMenu(FlightSeats *flightSeats);

int main(int argc, char const *argv[])
{
    for (int i = 0; i < FLIGHT_COUNT; i++)
    {
        fprintf(stdout, "\
Flight Number: %s\n",
                strFlightNum[i]);
    }

    return 0;
}

int flightMenu(FlightSeats *pFlightSeats)
{
    Seat seatsTemp[SEATS_COUNT];
    for (int i = 0; i < SEATS_COUNT; i++)
        initSeat(&seatsTemp[i]);

    FlightSeats flightSeatsTemp;
    initFlightSeats(&flightSeatsTemp, seatsTemp, (unsigned int)SEATS_COUNT);
    numberTheFlightSeats(&flightSeatsTemp);

    char chOpt;

    bool isBackToMainMenu = false;
    while (!isBackToMainMenu)
    {
        showMainMenu();
        chOpt = getcharOpt();

        switch (chOpt)
        {
        case 'a':
            showCountOfEmptySeats(pFlightSeats);
            break;

        case 'b':
            listEmptySeats(pFlightSeats);
            break;

        case 'c':
            listSeatsByAlphabeticalOrder(pFlightSeats);
            break;

        case 'd':
            SeatAssignmentMenu(pFlightSeats);
            break;

        case 'e':
            DelSeatAssignmentMenu(pFlightSeats);
            break;

        case 'f':
            confirmSeatsAssignment(pFlightSeats, &flightSeatsTemp);
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
