// 括号匹配的检测

#include <stdio.h>
#include <malloc.h>

#define STACK_SIZE 100                                                       //栈的初始容量
#define STACK_SIZE_ADD 10                                                   //栈容量增量

typedef char elementype;

typedef struct Sqstack
{
    elementype *top;
    elementype *base;
    int stacksize;
}snode          , *sqstack;

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
    if(s->top == s->base)                                                   //当栈是空的，返回1，否则返回0
        return 1;
    else
        return 0;
}

int correct(sqstack s, char exp[])                                          //判断匹配的核心函数
{
    char *p = exp, e;                                                       //指针p在字符串上移动
    int tag = 1;                                                            //tag标记是否匹配
    printf("出栈的元素：");
    while(*p != '#' && tag)                                                 //如果指针没有移动到字符串某尾，则继续循环
    {
        if(*p == '{' || *p == '(' || *p == '[')                             //遇到左括号则入栈
        {
            push(s, *p);
        }
        else                                                                
        {
            if(*p == '}')
            {
                if(*(s->top - 1) == '{')                                    //遇到右括号弹出栈顶元素，判断是否为同一种括号
                {
                    e = pop(s);
                    printf("%c\t", e);
                }
                else
                    tag = 0;
            }
            else if(*p == ')')
            {
                if(*(s->top - 1) == '(')
                {
                    e = pop(s);
                    printf("%c\t", e);
                }
                else
                    tag = 0;
            }
            else if(*p == ']')
            {
                if(*(s->top - 1) == '[')
                {
                    e = pop(s);
                    printf("%c\t", e);
                }
                else
                    tag = 0;
            }
        }
        p++;                                                                //移动字符指针
    }
    if(tag == 0 || !stackempty(s))                                          //如果栈不为空或者tag标记为0，则不是正确配对
        return 0;
    else
        return 1;
}

int main()
{
    sqstack s;
    char exp[20];
    int flag;
    s = (sqstack)malloc(sizeof(snode));                                     //这里切记，应该先给定义的结构体分配空间
    initstack(s);
    printf("请输入字符串(以#为结尾)：");
    scanf("%s", exp);
    flag = correct(s, exp);
    if(flag == 1)
        printf("\n匹配成功");
    else
        printf("\n匹配失败");
}
