/**
 * 序列点（sequence point）是程序执行的点，在该点上，所有的副作用都在进入下一步之前发生。
 * C语言中，语句中的分号标记了一个序列点。另外，任何一个完整表达式的结束也是一个序列点。
 * 完整表达式（full expression），就是指这个表达式不是另一个更大表达式的子表达式。
 * 例如，表达式语句中的表达式和while循环中的作为测试条件的表达式，都是完整表达式。
 *
 * 下面代码中表达式 i_num++ < 10 就是一个完整表达式。
 */
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i_num = 0;
    while (i_num++ < 10)
        printf("%d\n", i_num);

    return 0;
}
