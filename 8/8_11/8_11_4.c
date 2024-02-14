#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define idle 0
#define inspecting 1
#define complete 2

// bool inspectaWord(char ch, bool status);

int main(int argc, char const *argv[])
{
    int i_ch;

    int flag_status; // 1代表idle状态，0代表inspecting状态，大于2运行完一次

    int i_totalAlphaCount; // 总字母数量
    int i_totalWordsCount; // 总单词数量

    i_totalAlphaCount = 0;
    i_totalWordsCount = 0;

    flag_status = idle;

    /**
     * ? 检测到一个字母时切换到inspecting状态，在此状态下直到检测到一个非字母字符时切换到检测完毕状态(>2)，单词计数+1，状态重置为idle.
     */
    while (EOF != (i_ch = getchar()))
    {
        switch (flag_status)
        {
        case idle:
        {
            if (isalpha(i_ch))
            {
                i_totalAlphaCount++;
                flag_status = inspecting;
            }

            break;
        }

        case inspecting:
        {
            if (isalpha(i_ch))
            {
                i_totalAlphaCount++;
            }
            else
            {
                i_totalWordsCount++;
                flag_status = idle;
            }

            break;
        }

        default:
            printf("Error");
            break;
        }

        // if (isalpha(i_ch))
        // {
        //     flag_status = inspecting;
        //     i_totalAlphaCount++;
        // }
        // else
        // {
        //     /**
        //      * * 当处于inspecting状态时检测到非字母字符则说明一个单词检测完毕
        //      * ? 处于inspecting状态时
        //      */
        //     if (inspecting == flag_status)
        //     {
        //         flag_status += complete;
        //     }

        //     /**
        //      * * 当处于idle状态检测到非字母字符则说明连续检测到非字母字符或刚刚从检测完毕状态切换过来
        //      * ? 处于idle状态
        //      */
        //     if (idle == flag_status)
        //     {
        //         continue;
        //     }
        // }

        // if (flag_status > complete)
        // {
        //     i_totalWordsCount++;
        //     flag_status = idle;
        // }

        // }
    }

    printf("Alphabet Count: %d\nWords Count: %d\n", i_totalAlphaCount, i_totalWordsCount);

    return 0;
}

// /**
//  * 检测到第一个字母时切换到inspecting状态,直到检测到一个非字母字符，此时单词计数量+1并切换到idle状态.
//  *
//  */
// bool inspectaWord(char ch, bool status)
// {
//     if (!isalpha(ch) && (status == inspecting))
//     {
//     }

//     return false;
// }
