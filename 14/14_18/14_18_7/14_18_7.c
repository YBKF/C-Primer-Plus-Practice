/**
 * 7.修改程序清单 14.14，
 * 从文件中读取每条记录并显示出来，允许用户 删除记录 或 修改记录 的内容。
 * 如果删除记录，把空出来的空间留给下一个要读入的记录。
 * 要修改现有的文件内容，必须用"r+b"模式，而不是"a+b"模式。
 * 而且，必须更加注意定位文件指针，防止新加入的记录覆盖现有记录。
 * 最简单的方法是改动储存在内存中的所有数据，然后再把最后的信息写入文件。
 * 跟踪的一个方法是在book结构中添加一个成员表示是否该项被删除。
 */
/* INSERT, DELETE, UPDATE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 10 /* 最大书籍数量 */

#define STACK_MAX_SIZE (MAXBKS)
#define STACK_ERROR_CODE (-1)

#define OPTION_STR
#define VOID_STR ("")
#define INIT_STR VOID_STR

enum MainMenuOption
{
    MENU_OPT_INSERT = 1,
    MENU_OPT_DELETE,
    MENU_OPT_UPDATE,
    MENU_OPT_EXIT
};

enum UpdateMenuOption
{
    MENU_OPT_TITLE = 1,
    MENU_OPT_AUTHOR,
    MENU_OPT_VALUE,
    MENU_OPT_RET

};
struct book
{ /* 建立 book 模板 */
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
    int isDeleted;
};

typedef struct _stack
{ /* 创建一个用于存取数组中“已删除”元素下标的后进先出的结构模版 */
    const int *data;
    int *top;
    const int *limit;
} STACK;

// struct book;
// typedef struct _stack STACK;

char *s_gets(char *st, int n);
char *copyString(char *strTarget, char *strSource, int iSize);

STACK *initStack(int iArr[], int iSize, STACK *pStack);
int pushStack(int iData, STACK *pStack);
int popStack(STACK *pStack);
int isEmptyStack(STACK *pStack);
int getStackSize(STACK *pStack);
int getStackTop(STACK *pStack);

int INSERT(struct book books[], STACK *psDelList, int *piHighCount);
int DELETE(struct book books[], STACK *psDelList, int *piHighCount);
int UPDATE(struct book books[], const int *piHighCount);

int listBooks(const struct book books[], int iCount);
void showMenu();
int scanfOption(int *piOption);

int main(void)
{
    struct book library[MAXBKS]; /* 结构数组 */
    int count = 0;
    FILE *pbooks;
    int size = sizeof(struct book);

    if ((pbooks = fopen("book.dat", "r+b")) == NULL)
    {
        fputs("Can't find book.dat file\n", stderr);
        if ((pbooks = fopen("book.dat", "w+b")) == NULL)
        {
            fputs("Can't create book.dat file\n", stderr);
            exit(1);
        }
        // exit(1);
    }

    rewind(pbooks); /* 定位到文件开始 */
    while (count < MAXBKS && fread(&library[count], size, 1, pbooks) == 1)
    {
        if (count == 0)
            puts("Current contents of book.dat:");
        printf("%s by %s: $%.2f\n",
               library[count].title, library[count].author, library[count].value);
        count++;
    }

    int iDelList[MAXBKS];
    STACK stackDel;

    memset((int *)iDelList, 0, sizeof(int) * MAXBKS);
    initStack(iDelList, MAXBKS, &stackDel);

    int isEXIT = 0;
    while (!isEXIT)
    {
        showMenu();

        int option;
        if (scanfOption(&option) != 1)
        {
            fprintf(stderr, "\
[ERROR]     Failed to get the option.\n\
            Please enter a number.\n");
            continue;
        }

        int iOpRet = 0;

        switch (option)
        {
        case MENU_OPT_INSERT:
            iOpRet = INSERT(library, &stackDel, &count);
            break;

        case MENU_OPT_DELETE:
            iOpRet = DELETE(library, &stackDel, &count);
            break;

        case MENU_OPT_UPDATE:
            iOpRet = UPDATE(library, &count);
            break;

        case MENU_OPT_EXIT:
            isEXIT = 1;
            break;

        default:
            fprintf(stderr, "\
[ERROR]     Invalid option.\n");
            break;
        }

        if (iOpRet == 0 && isEXIT != 1)
        {
            fprintf(stderr, "\
[ERROR]     Failure of operation.\n");
        }
    }

    // TODO 先将数组中未被删除的书目拷贝到另一个数组中，再将这个新的数组写入到文件
    // TODO 或者定位到已删除的数组并将其删除

    fseek(pbooks, 0L, SEEK_SET);

    for (int i = 0; i < count; i++)
        if (library[i].isDeleted == 0)
            fwrite(&library[i], size, 1, pbooks);

    listBooks(library, count);

    puts("Bye.\n");
    fclose(pbooks);

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

STACK *initStack(int iArr[], int iSize, STACK *pStack)
{
    if (iArr == NULL || pStack == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while initialing the stack.\n\
            Null pointer.\n");
        return NULL;
    }

    *pStack = (STACK){
        .data = iArr,
        .top = iArr - 1,
        .limit = iArr + (iSize - 1)};

    return pStack;
}

int pushStack(int iData, STACK *pStack)
{
    if (pStack == NULL || pStack->data == NULL || pStack->limit == NULL || pStack->top == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while pushing data onto the stack.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    if (pStack->top >= pStack->limit || pStack->top < (pStack->data - 1))
    {
        if (pStack->top == pStack->limit)
        {
            fprintf(stderr, "\
[ERROR]     The stack is full.\n");
        }
        else
        {
            fprintf(stderr, "\
[ERROR]     The stack has overflowed.\n");
        }
        return STACK_ERROR_CODE;
    }

    *(++pStack->top) = iData;

    return 0;
}

int popStack(STACK *pStack)
{
    if (pStack == NULL || pStack->data == NULL || pStack->top == NULL)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while popping data from the stack.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    if (pStack->top < pStack->data)
    {
        fprintf(stderr, "\
[ERROR]     Empty stack.\n\
            No data popped from the stack.\n");
        return STACK_ERROR_CODE;
    }

    int iRetVal = *(pStack->top--);
    return iRetVal;
}

int isEmptyStack(STACK *pStack)
{
    if (pStack == NULL || pStack->data == NULL || pStack->limit == NULL || pStack->top == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Cannot check if the stack is empty.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    if (pStack->top == pStack->data - 1)
    {
        return 1;
    }
    else if (pStack->top >= pStack->data && pStack->top <= pStack->limit)
    {
        return 0;
    }
    else
    {
        fprintf(stderr, "\
[ERROR]     The stack has overflowed.\n");
        return STACK_ERROR_CODE;
    }
}

int getStackSize(STACK *pStack)
{
    if (pStack == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Unable to get the stack size.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    return pStack->top - pStack->data + 1;
}

int getStackTop(STACK *pStack)
{
    if (pStack == NULL || pStack->data == NULL || pStack->limit == NULL || pStack->top == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Unable to get data at the top of the stack.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return STACK_ERROR_CODE;
    }

    if (pStack->top >= pStack->data && pStack->top <= pStack->limit)
    {
        return *pStack->top;
    }
    else if (pStack->top == pStack->data - 1)
    {
        fprintf(stderr, "\
[ERROR]     Empty stack.\n");
        return STACK_ERROR_CODE;
    }
    else
    {
        fprintf(stderr, "\
[ERROR]     The stack has overflowed.\n");
        return STACK_ERROR_CODE;
    }
}

int INSERT(struct book books[], STACK *psDelList, int *piHighCount)
{
    if (books == NULL || psDelList == NULL || piHighCount == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failure of INSERT operation.\n\
            Because one of the parameters is a null pointer or invalid memory region.\n");
        return 0;
    }

    if (*piHighCount >= MAXBKS)
    {
        fprintf(stderr, "\
[ERROR]     Failure of INSERT operation.\n\
            The library is full.\n");
        return 0;
    }

    struct book bookBuf = {
        .title = INIT_STR,
        .author = INIT_STR,
        .value = 0.0,
        .isDeleted = 0};

    // 输入数据并存入临时结构
    puts("  Please add new book titles.");
    puts("  Press [enter] at the start of a line to return to the menu.");
    if (s_gets(bookBuf.title, MAXTITL) != NULL && bookBuf.title[0] != '\0')
    {
        puts("Now enter the author.");
        s_gets(bookBuf.author, MAXAUTL);

        puts("Now enter the value.");
        scanf("%f", &bookBuf.value);
        while (getchar() != '\n')
            continue; /* 清理输入行 */
    }
    else
    {
        fprintf(stdout, "\
  INSERT canceled.\n");
        return 1;
    }

    // 调用并检查 isEmptyStack() 函数的合法性
    int iRetIsEmpty = 0;
    if ((iRetIsEmpty = isEmptyStack(psDelList)) != 0 && iRetIsEmpty != 1)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while checking if the stack is empty.\n\
            Error code: %d\n",
                iRetIsEmpty);
        return 0;
    }

    // 判断“已删除”列表是否为空，然后执行相应操作
    if (iRetIsEmpty == 1)
    {
        books[*piHighCount] = bookBuf;

        // 仅在“已删除”列表为空时增加书目最高数量，此变量主要表示从数组起始元素到最后一个非“已删除”元素的总数
        (*piHighCount)++;
    }
    else // iRetIsEmpty == 0
    {
        int iRetGetTop = 0;
        if ((iRetGetTop = getStackTop(psDelList)) < 0)
        { // 对这个程序来说，从栈顶获取到的整型值只要小于 0 那就是不合法的
            fprintf(stderr, "\
[ERROR]     An error occurred while getting data at the top of the stack.\n\
            Error code: %d\n",
                    iRetGetTop);
            return 0;
        }
        if (popStack(psDelList) == STACK_ERROR_CODE)
        {
            fprintf(stderr, "\
[ERROR]     Error code: %d\n",
                    STACK_ERROR_CODE);
            return 0;
        }

        // 只在下标获取成功且栈顶数据出栈成功的情况下进行赋值
        books[iRetGetTop] = bookBuf;
    }

    return 1;
}

int DELETE(struct book books[], STACK *psDelList, int *piHighCount)
{
    if (books == NULL || psDelList == NULL || piHighCount == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failure of DELETE operation.\n\
            Because one of the parameters is a null pointer or invalid memory region.\n");
        return 0;
    }

    if (*piHighCount <= 0)
    {
        fprintf(stderr, "\
[ERROR]     Failure of DELETE operation.\n\
            The library is empty.\n");
        return 0;
    }

    fprintf(stdout, "\
  Please enter the index of the book you want to delete(index start at 0).\n");
    int iIndexEntered = 0;
    if (scanf("%d", &iIndexEntered) != 1)
    {
        fprintf(stderr, "\
[ERROR]     Failed to enter the index of the book.\n\
            Please enter a number.\n");
        return 0;
    }
    while (getchar() != '\n')
        continue;

    // 判断输入的数组下标是否合法
    if (iIndexEntered < 0 || iIndexEntered > MAXBKS - 1)
    {
        fprintf(stderr, "\
[ERROR]     The index you entered is out of range.\n\
            Please enter a number between 0 and %d.\n\
            Returned to the menu.\n",
                MAXBKS - 1);
        return 0;
    }

    if (books[iIndexEntered].isDeleted == 1)
    {
        fprintf(stderr, "\
[ERROR]     The book you want to delete has been deleted.\n\
            Returned to the menu.\n");
        return 0;
    }
    else if (books[iIndexEntered].isDeleted != 0 && books[iIndexEntered].isDeleted != 1)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while deleting the book.\n\
            The book you want to delete is invalid.\n");
        return 0;
    }

    if (pushStack(iIndexEntered, psDelList) == STACK_ERROR_CODE)
    {
        fprintf(stderr, "\
[ERROR]     Error code: %d\n",
                STACK_ERROR_CODE);
        return 0;
    }
    books[iIndexEntered].isDeleted = 1;

    // 仅在“已删除”列表为空时减少书目最高数量，此变量主要表示从数组起始元素到最后一个非“已删除”元素的总数
    if (isEmptyStack(psDelList))
        (*piHighCount)--;

    return 1;
}

int UPDATE(struct book books[], const int *piHighCount)
{
    if (books == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failure of UPDATE operation.\n\
            Because of the parameter is a null pointer or invalid memory region.\n");
        return 0;
    }

    if (*piHighCount <= 0)
    {
        fprintf(stderr, "\
[ERROR]     Failure of UPDATE operation.\n\
            The library is empty.\n");
        return 0;
    }

    fprintf(stdout, "\
  Please enter the index of the book you want to update(index start at 0).\n");
    int iIndexEntered = 0;
    if (scanf("%d", &iIndexEntered) != 1)
    {
        fprintf(stderr, "\
[ERROR]     Failed to enter the index of the book.\n\
            Please enter a number.\n");
        return 0;
    }
    while (getchar() != '\n')
        continue;

    // 判断输入的数组下标是否合法
    if (iIndexEntered < 0 || iIndexEntered > *piHighCount - 1)
    {
        fprintf(stderr, "\
[ERROR]     The index you entered is out of range.\n\
            Please enter a number between 0 and %d.\n\
            Returned to the menu.\n",
                *piHighCount - 1);
        return 0;
    }

    // 检查当前选择的书目是否被标记为“已删除”
    if (books[iIndexEntered].isDeleted == 1)
    {
        fprintf(stderr, "\
[ERROR]     The book you want to update has been deleted.\n\
            Returned to the menu.\n");
        return 0;
    }
    else if (books[iIndexEntered].isDeleted != 0 && books[iIndexEntered].isDeleted != 1)
    {
        fprintf(stderr, "\
[ERROR]     An error occurred while updating the book.\n\
            The book you want to update is invalid.\n");
        return 0;
    }

    // 开始更新数据
    int isUpdateDone = 0;
    while (isUpdateDone)
    {
        fprintf(stdout, "\
  Please enter the number of the item you want to update.\n\
  1. Title\n\
  2. Author\n\
  3. Value\n\
  4. Return to the menu\n");

        int option;
        if (scanfOption(&option) != 1)
        {
            fprintf(stderr, "\
[ERROR]     Failed to get the option.\n\
            Please enter a number.\n");
            return 0;
        }

        switch (option)
        {
        case MENU_OPT_TITLE:
            fprintf(stdout, "\
  Please enter the new title.\n\
  Press [enter] at the start of a line to cancel.");
            char strTitleBuf[MAXTITL];

            if (s_gets(strTitleBuf, MAXTITL) == NULL)
            {
                fprintf(stderr, "\
[ERROR]     Failed to get the new title.\n\
            Please enter a string of length less than %d.\n",
                        MAXTITL);
                break;
            }
            else if (strTitleBuf[0] == '\0')
            {
                fprintf(stdout, "\
  Operation canceled.\n");
                break;
            }

            if (copyString(books[iIndexEntered].title, strTitleBuf, MAXTITL) == NULL)
                fprintf(stderr, "\
  Operation failed, no data changed.\n");
            else
                fprintf(stdout, "\
  Title updated.\n");
            break;

        case MENU_OPT_AUTHOR:
            fprintf(stdout, "\
  Please enter the new author.\n\
  Press [enter] at the start of a line to cancel.");
            char strAuthorBuf[MAXAUTL];

            if (s_gets(strAuthorBuf, MAXAUTL) == NULL)
            {
                fprintf(stderr, "\
[ERROR]     Failed to get the new author.\n\
            Please enter a string of length less than %d.\n",
                        MAXAUTL);
                break;
            }
            else if (strAuthorBuf[0] == '\0')
            {
                fprintf(stdout, "\
  Operation canceled.\n");
                break;
            }

            if (copyString(books[iIndexEntered].author, strAuthorBuf, MAXAUTL) == NULL)
                fprintf(stderr, "\
  Operation failed, no data changed.\n");
            else
                fprintf(stdout, "\
  Author updated.\n");
            break;

        case MENU_OPT_VALUE:
            fprintf(stdout, "\
  Please enter the new value.\n");

            double lfValueBuf = 0.0;
            int iRetVal = scanf("%lf", &lfValueBuf);
            while (getchar() != '\n')
                continue;

            if (iRetVal != 1)
            {
                fprintf(stderr, "\
[ERROR]     Failed to get the new value.\n\
            Please enter a number.\n");
                return 0;
            }
            books[iIndexEntered].value = lfValueBuf;

            fprintf(stdout, "\
  Value updated.\n");
            break;

        default:
            isUpdateDone = 1;
            break;
        }
    }

    return 1;
}

int listBooks(const struct book books[], int iCount)
{
    if (books == NULL)
    {
        fprintf(stderr, "\
[ERROR]     Failed to list the books.\n\
            Because one of the parameters is a null pointer.\n");
        return 0;
    }

    puts("\nHere is the list of your books:");

    if (iCount <= 0)
    {
        puts("No books? Too bad.\n");
        return 0;
    }

    int iIndex;

    for (iIndex = 0; iIndex < iCount; iIndex++)
        if (books[iIndex].isDeleted == 0)
            printf("%s by %s: $%.2f\n\n",
                   books[iIndex].title, books[iIndex].author, books[iIndex].value);
}
void showMenu()
{
    fprintf(stdout, "\
  What should we do?\n\
  Please enter the number of the operation you want to execute.\n\
  1. INSERT\n\
  2. DELETE\n\
  3. UPDATE\n\
  4. EXIT\n");
}

int scanfOption(int *piOption)
{
    int iRetVal = scanf("%d", piOption);
    while (getchar() != '\n')
        continue;

    return iRetVal;
}
