/**
 * 9.编写一个符合以下描述的函数。
 * 首先，询问用户需要输入多少个单词。
 * 然后，接收用户输入的单词，并显示出来，
 * 使用malloc()并回答第1个问题（即要输入多少个单词），创建一个动态数组，该数组内含相应的指向char的指针
 * （注意，由于数组的每个元素都是指向char的指针，所以用于储存malloc()返回值的指针应该是一个指向指针的指针，且它所指向的指针指向char）。
 * 在读取字符串时，该程序应该把单词读入一个临时的char数组，
 * 使用malloc()分配足够的存储空间来储存单词，并把地址存入该指针数组（该数组中每个元素都是指向 char 的指针）。
 * 然后，从临时数组中把单词拷贝到动态分配的存储空间中。
 * 因此，有一个字符指针数组，每个指针都指向一个对象，该对象的大小正好能容纳被储存的特定单词。
 * 下面是该程序的一个运行示例：
 * How many words do you wish to enter? 5
 * Enter 5 words now:
 * I enjoyed doing this exercise
 * Here are your words:
 * I
 * enjoyed
 * doing
 * this
 * exercise
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH (3)
#define MAX_WORD_DATASIZE (MAX_WORD_LENGTH + 1)

int get_words_number();
char **get_words(int words_num);
void free_words_set(char **words_set, int words_num);

int main(int argc, char const *argv[])
{
    int words_num;

    words_num = get_words_number();
    printf("Enter %d words now:\n", words_num);

    /* 用于存储输入中每个单词（字符串）首字符地址的动态数组 */
    char **words_set = get_words(words_num);
    if (words_set == NULL)
        exit(EXIT_FAILURE);

    fputs("Here are your words:\n", stdout);
    for (int i = 0; i < words_num; i++)
        if (words_set[i] != NULL)
            printf("%s\n", words_set[i]);

    free_words_set(words_set, words_num);

    return 0;
}

int get_words_number()
{
    int num;
    int parsed;

    fputs("How many words do you wish to enter? ", stdout);

    while (1)
    {
        parsed = scanf("%d", &num);

        if (parsed == 1)
        {
            if (num > 1)
                break;
            else
                fputs("ERROR: Number entered must bigger than 1.\nPlease retry: ", stdout);
        }
        else
            fputs("ERROR: Fail to get a number.\nPlease retry: ", stdout);

        // 清理输入缓冲区，确保下一次循环的输入不受影响
        while (getchar() != '\n')
            continue;

        // char discard;
        // while (discard = getchar())
        //     if (discard == '\n')
        //         break;
    }

    return num;
}

/**
 * 读取用户输入，跳过开头的非字母字符，
 * 当读到第一个字符串时，开始向临时字符串中依次存入字符直到遇到第一个非字母字符为止，在当前停止位置添加'\0'作为“单词”结尾，
 * 然后，测量临时字符串的长度，并为此字符串动态分配大小为 (strnlen(str_temp, MAX_WORD_LENGTH) + 1) 的内存空间；
 * 其次，将临时字符串中的字符复制到动态分配的存储空间中，这个存储空间中的所有字符即表示为“一个单词”；
 * 最后，创建一个用于存储“单词”首地址的指针数组，将指针数组中的指针指向当前刚刚被分配存储空间的单词的首地址；
 * 结束后，使用循环继续读取并处理下一个单词，直到读完指定数量的单词。
 */
char **get_words(int words_num)
{
    // 检测参数是否合法
    if (words_num <= 0)
    {
        fputs("ERROR: Words number must bigger than 0. Function exited.\n", stderr);
        return NULL;
    }

    // 用于存储一个单词的临时字符串
    char word_temp[MAX_WORD_DATASIZE] = {};

    // 用于暂时存储用户输入的字符，经过检测后再存储到字符串中
    int ch_temp;

    // 指向临时字符串以便于操作
    char *ptr_word;

    // 指向临时字符串最末端，用于越界检测
    char *ptr_word_limit = &word_temp[MAX_WORD_DATASIZE - 1];

    /* 用于存储输入中每个单词（字符串）首字符地址的动态数组 */
    char **words_set = (char **)malloc(words_num * sizeof(char *));
    if (words_set == NULL)
    {
        fputs("ERROR: Fail to allocate memory.\n", stderr);
        return NULL;
    }

    // 暂不考虑读到EOF时的情况
    for (int i = 0; i < words_num; i++)
    {
        // 当第一次开始读取或上一个单词读完时，清空临时字符串（操作临时字符串的top指针重新指向临时字符串首地址）
        ptr_word = word_temp;

        // 丢弃单词前的非字母字符，将读到的第一个字母存储到临时字符串的头部
        while (!isalpha(ch_temp = getchar()))
            continue;
        *ptr_word++ = ch_temp;

        // 继续读取字符直到遇到非字母字符或读取到单词字符数量上限
        while (ptr_word < ptr_word_limit && isalpha(ch_temp = getchar()))
            *ptr_word++ = ch_temp;

        // 若读取到单词字符数量上限则清除缓冲区中与此单词连续的剩余字母，确保不影响下一个单词的读取
        if (ptr_word == ptr_word_limit)
            while (isalpha(getchar()))
                continue;

        // 读取完毕时在字符串结尾添加'\0'，表示一个单词已读取完毕
        *ptr_word = '\0';

        // 将临时字符串中的字符复制到动态分配的存储空间中，并将此字符串的首地址存入指针数组中
        size_t str_length = strnlen(word_temp, MAX_WORD_LENGTH);

        // strlen() + '\0'
        size_t str_size = str_length + 1;

        words_set[i] = (char *)malloc((str_size) * sizeof(char));
        if (words_set[i] == NULL)
        {
            fputs("ERROR: Fail to allocate memory.\n", stderr);
            return NULL;
        }
        strncpy(words_set[i], word_temp, str_size);
    }

    return words_set;
}

void free_words_set(char **words_set, int words_num)
{
    for (int i = 0; i < words_num; i++)
        free(words_set[i]);
    free(words_set);
}