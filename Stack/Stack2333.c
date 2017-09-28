//栈的基本实现和插入操作
#include "stdio.h"
#include "malloc.h"
#include "time.h"

#define STACK_INIT_SIZE 100                           //定义栈初始空间的容量
#define STACKINCREMENT 10                             //存储空间的分配增量（以元素个数为基本单位）

typedef int elementype;

typedef struct sqstack
{
    elementype *base;                                 //当栈不存在时base的值为NULL
    elementype *top;                                  //这里的top和base分配的空间和类型与用来存储元素的一样
    int stacksize;                                    //空间，但是以元素个数为单位，不算入.top
}lnode, *sqstack;

int Stackinit(sqstack s)
{
    s->base = (elementype *)malloc(STACK_INIT_SIZE * sizeof(elementype));        //申请的是栈储存元素的整个空间
    s->top = s->base;                                 //栈初始化时为空，所以栈顶指针与栈底指针相同
    s->stacksize = STACK_INIT_SIZE;                   //栈的初始容量（指的是储存元素的个数）
    return (1);
}

int Push(sqstack s, elementype e)                    //向栈顶插入一个元素
{
    if(s->top - s->base >= s->stacksize)             //如果栈满了，需要增加储存空间
    {
        s->base = (elementype *)realloc(s->base, (s->stacksize + STACKINCREMENT) * sizeof(elementype));
        s->top = s->base + s->stacksize;             //如果栈满了，那栈顶指针必定在（s->base + s->stacksize）的位置上或者更多
        s->stacksize += STACKINCREMENT;              //增加栈的容量（这里和上面的s->stacksize都是值元素的个数）
    }
    *s->top = e;
    printf("%x：%d\n", s->top, *s->top);
    s->top++;                                        //先给s->top赋值，再让他移动到下个位置
}

void Printsqstack(sqstack s)                         //打印栈中的所有元素
{
    elementype *p = s->base;                         //让一个同类型的指针p指向s->base所在的区域
    for(;p != s->top; p++)
        printf("%2d\t", *p);                         //移动p打印栈中所有的元素
}

int main()
{
    srand((unsigned)time(NULL));
    sqstack s;
    int i;
    elementype e = rand()%100;
    s = (sqstack)malloc(sizeof(lnode));
    Stackinit(s);
    for(i = 0; i < s->stacksize; i++)
    {
        e = rand()%100;                               //我是不是超级懒
        Push(s, e);
    }
    Printsqstack(s);
}
