// 两个栈共享存储空间
// 这里采用的是数组的形式实现，也可以用指针

#include <stdio.h>
#include <malloc.h>
#include <time.h>

typedef int elementype;
typedef int status;

int top1, top2, m;

void Stackinit_w(elementype tws[], int m)             //共享栈的初始化，让两个栈都为空
{
    top1 = 0;                                         //top1首先在第一个栈的栈底（事实上0处不存放元素）
    top2 = m + 1;                                     //top2首先在第二个栈的栈底（事实上m+1处不存放元素）
}

void Push(elementype tws[], int i, elementype x)      //入栈操作，i的设定值表示插入第一个栈或第二个栈
{
    if(top1 == top2 - 1)
        printf("Over flow!");                         //溢出
    else
    {
        if(i == 1)                                    //插入第一个栈
        {
            top1++;
            tws[top1] = x;
        }
        else
        {
            top2--;
            tws[top2] = x;
        }
    }
}

void Pop(elementype tws[], int i, elementype y)
{
    if(i == 1)                                        //表示对第一个栈进行操作
    {
        if(top1 == 0)
            printf("Stack1 underflow");               //第一个栈空
        else                                          //非空，删除顶元素
        {
            y = tws[top1];
            top1--;
        }
    }
    else
    {
        if(top2 == m + 1)
            printf("Stack1 underflow");
        else
        {
            y = tws[top2];
            top2++;
        }
    }
}

void Print_stack(elementype tws[])
{
    int i;
    printf("\n栈1：");
    for(i = 1; i <= top1; i++)
        printf("%2d\t", tws[i]);
    printf("\n栈2：");
    for(i = top2; i <= m; i++)
        printf("%2d\t", tws[i]);
}

int main()
{
    srand((unsigned)time(NULL));
    int i, j;
    elementype e;
    m = 10;
    elementype tws[m+1];
    Stackinit_w(tws, m);
    for(i = 0; i < 10; i++)
    {
        e = rand()%20;
        printf("%2d\t", e);
        j = 1 + rand()%2;
        Push(tws, j, e);
    }
    Print_stack(tws);
}
