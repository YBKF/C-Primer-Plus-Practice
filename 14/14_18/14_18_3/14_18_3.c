/**
 * 3.修改程序清单 14.2 中的图书目录程序，
 * 使其按照输入图书的顺序输出图书的信息，
 * 然后按照标题字母的声明输出图书的信息，
 * 最后按照价格的升序输出图书的信息。
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct book;

char *s_gets(char *st, int n);
void transStrToLowerCase(char *str);
void sortBooksByTitle(struct book *books[], int iMaxCount);
void sortBooksByValue(struct book *books[], int iMaxCount);
void sortBooks(struct book *books[], int iMaxCount, void (*funSort)(struct book *books[], int iMaxCount));

#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100 /* 书籍的最大数量 */

struct book
{ /* 简历 book 模板 */
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
};

/* TODO 将 library 数组中每个元素的地址存储到一个指针数组中，指针指向顺序默认为元素在 library 数组中的顺序，指针数组元素数量为 MAXBKS
    a. 不进行任何处理；
    b. 将 library.title 先转换为小写（如果可以的话），然后按照 ASCII 的值的顺序进行排序；
    c. 元素按照 library.value 的值进行排序 */

int main(void)
{
    /* book 类型结构的数组 */
    struct book library[MAXBKS];
    struct book *pLibrary[MAXBKS]; /* 存储 book 结构的地址的指针数组 */
    int count = 0;
    int index;

    printf("Please enter the book title.\n");
    printf("Press [enter] at the start of a line to stop.\n");
    while (count < MAXBKS && s_gets(library[count].title, MAXTITL) != NULL && library[count].title[0] != '\0')
    {
        printf("Now enter the author.\n");
        s_gets(library[count].author, MAXAUTL);

        printf("Now enter the value.\n");
        scanf("%f", &library[count++].value);
        while (getchar() != '\n')
            continue; /* 清理输入行*/

        if (count < MAXBKS)
            printf("Enter the next title.\n");
    }

    if (count > 0)
    {
        // 将 book 数组中每个元素的地址存储到指针数组中
        for (int i = 0; i < count; i++)
            pLibrary[i] = &library[i];

        printf("Here is the list of your books:\n");
        for (index = 0; index < count; index++)
            printf("# %s by %s: $%.2f\n", library[index].title,
                   library[index].author, library[index].value);

        sortBooks(pLibrary, count, sortBooksByTitle);
        printf("\nHere is the list of your books sorted by title:\n");
        for (int i = 0; i < count; i++)
            printf("# %s by %s: $%.2f\n", pLibrary[i]->title,
                   pLibrary[i]->author, pLibrary[i]->value);

        sortBooks(pLibrary, count, sortBooksByValue);
        printf("\nHere is the list of your books sorted by value:\n");
        for (int i = 0; i < count; i++)
            printf("# %s by %s: $%.2f\n", pLibrary[i]->title,
                   pLibrary[i]->author, pLibrary[i]->value);
    }
    else
        printf("No books? Too bad.\n");

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
                continue; // 处理输入行中剩余的字符
    }
    return ret_val;
}

void transStrToLowerCase(char *str)
{
    if (str == NULL)
    {
        fputs("ERROR: Found a null pointer at transStrToLowerCase", stderr);
        return;
    }

    int iStrLength = strlen(str);

    for (int i = 0; i < iStrLength; i++)
        str[i] = tolower(str[i]);
}

void sortBooksByTitle(struct book *books[], int iMaxCount)
{
    if (books == NULL)
    {
        fputs("ERROR: Found a null pointer at function sortBooksByTitle.\n", stderr);
        return;
    }
    if (iMaxCount <= 0)
        return;

    struct book *pBookBuf;
    char titleBufHi[MAXTITL];
    char titleBufLo[MAXTITL];
    memset(titleBufHi, 0, MAXTITL);
    memset(titleBufLo, 0, MAXTITL);

    for (int i = 1; i < iMaxCount; i++)
        for (int j = i; j > 0; j--)
        {
            transStrToLowerCase(strcpy(titleBufHi, books[j]->title));
            transStrToLowerCase(strcpy(titleBufLo, books[j - 1]->title));

            if (strcmp(titleBufHi, titleBufLo) < 0)
            {
                pBookBuf = books[j];
                books[j] = books[j - 1];
                books[j - 1] = pBookBuf;
            }
        }
}

void sortBooksByValue(struct book *books[], int iMaxCount)
{
    if (books == NULL)
    {
        fputs("ERROR: Found a null pointer at function sortBooksByValue.\n", stderr);
        return;
    }
    if (iMaxCount <= 0)
        return;

    struct book *pBookBuf;

    for (int i = 1; i < iMaxCount; i++)
        for (int j = i; j > 0 && books[j]->value < books[j - 1]->value; j--)
        {
            pBookBuf = books[j];
            books[j] = books[j - 1];
            books[j - 1] = pBookBuf;
        }
}

void sortBooks(struct book *books[], int iMaxCount, void (*funSort)(struct book *books[], int iMaxCount))
{
    if (books == NULL)
    {
        fputs("ERROR: Found a null pointer at function sortBooks.\n", stderr);
        return;
    }

    funSort(books, iMaxCount);
}
