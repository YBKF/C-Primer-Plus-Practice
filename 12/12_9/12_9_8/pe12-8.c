/**
 * 8.提供make_array()和show_array()函数的定义，完成该程序。
 * make_array()函数接受两个参数，第1个参数是int类型数组的元素个数，第2个参数是要赋给每个元素的值。
 * 该函数调用malloc()创建一个大小合适的数组，将其每个元素设置为指定的值，并返回一个指向该数组的指针。
 * show_array()函数显示数组的内容，一行显示8个数。
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int *make_array(int elem, int val);
void show_array(const int ar[], int n);
int main(void)
{
    int *pa;
    int size;
    int value;

    printf("Enter the number of elements: ");
    while (scanf("%d", &size) == 1 && size > 0)
    {
        printf("Enter the initialization value: ");
        scanf("%d", &value);
        pa = make_array(size, value);
        if (pa)
        {
            show_array(pa, size);
            free(pa);
        }
        printf("Enter the number of elements (<1 to quit): ");
    }

    printf("Done.\n");

    return 0;
}

int *make_array(int elem, int val)
{
    if (elem < 1)
        return NULL;

    int *piArr = (int *)malloc(elem * sizeof(int));
    if (piArr == NULL)
    {
        fputs("Error: memory allocation failed.\n", stderr);
        return NULL;
    }

    for (int i = 0; i < elem; i++)
        piArr[i] = val;

    return piArr;
}

void show_array(const int ar[], int n)
{
    if (ar == NULL || n < 1)
        return;

    /*不使用for循环而使用与之等效的while循环，
    是因为while中除条件判断外，其他的语句都可以在同一个代码块中，每一步的流程更加清晰。*/
    int i = 0;
    while (i < n)
    {
        printf("%d ", ar[i]);

        if ((i + 1) % 8 == 0)
            putchar('\n');

        i++;
    }

    printf("%d\n", i);

    // 若输出的最后一行不满8个数，则进行换行，以确保输出的最后一行有换行符
    if (n % 8 != 0)
        putchar('\n');
}
