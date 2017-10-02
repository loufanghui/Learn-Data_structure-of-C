// 使用栈实现数制的转换

#include <stdio.h>
#include <malloc.h>

#define STACK_SIZE 100                                                       //栈的初始容量
#define STACK_SIZE_ADD 10                                                   //栈容量增量

typedef int elementype;

typedef struct Sqstack
{
    elementype *top;
    elementype *base;
    int stacksize;
}snode, *sqstack;

void initstack(sqstack s)
{
    s->base = (elementype *)malloc(STACK_SIZE * sizeof(elementype));         //给栈分配空间
    s->stacksize = STACK_SIZE;                                               //设定栈的容量
    s->top = s->base;                                                         //栈的初始化
}

void push(sqstack s, elementype e)
{
    if(s->top - s->base >= s->stacksize)                                       //如果栈的元素满了，则增加空间
    {
        s->base = (elementype *)malloc((s->stacksize + STACK_SIZE_ADD) * sizeof(elementype));
        s->top = s->base + s->stacksize;
        s->stacksize += STACK_SIZE_ADD;
    }
    *s->top = e;
    s->top++;
}

elementype pop(sqstack s)
{
    elementype e = *(s->top - 1);                                            //取栈顶元素
    s->top--;
    return e;
}

int stackempty(sqstack s)
{
    if(s->top == s->base)                                                     //当栈是空的，返回1，否则返回0
        return 1;
    else
        return 0;
}

void conversion(sqstack s, int n, int r)                                    //将n转换成进制r的数字，并存入栈中
{
    while(n)
    {
        push(s, n % r);
        n = n / r;
    }
    while(!stackempty(s))
    {
        printf("%d", pop(s));
    }
}

int main()
{
    sqstack s;
    s = (sqstack)malloc(sizeof(snode));                                     //这里切记，应该先给定义的结构体分配空间
    initstack(s);
    conversion(s, 1024, 2);
}
