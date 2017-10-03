// 构造一个空链式队列q

#include <stdio.h>
#include <malloc.h>
#include <time.h>

typedef int status;
typedef int elementype;

typedef struct lnode
{
    elementype data;
    struct lnode *next;
}lnode, *linkdot;

typedef struct Linkque
{
    lnode *front;
    lnode *rear;
}que, *linkque;                                                       //这里为了方便，采用两种声明方式

status Queinit(linkque q)                                             //这函数的意思是为队列中头（节点）指针和尾指针分配空间（初始化）
{
    q->front = (linkdot)malloc(sizeof(lnode));
    if(!q->front)
    {
        printf("头指针分配空间失败");
        return 0;
    }
    q->rear = q->front;                                               //空队列中队首指针和队尾指针共同指向首节点
    q->front->next = NULL;                                            //这实际上是队尾指针的下个节点为空，而初始队首队尾指针指向同一个域
    return (1);
}

status Queinsert(linkque q, elementype e)                             //将新元素e插入到队q的尾部
{                                                                     //修改队尾指针使之指向新链入的元素
    linkdot p = (linkdot)malloc(sizeof(lnode));
    if(!p)
    {
        printf("新节点分配空间失败！");
        return (0);
    }
    p->data = e;
    p->next = NULL;
    q->rear->next = p;
    q->rear = p;
    return (1);
}

void print_q(linkque q)
{
    linkdot p = q->front->next;                                       //队列的首节点不插入元素
    printf("\n队列中的元素一次为：");
    while(p)
    {
        printf("%3d\t", p->data);
        p = p->next;
    }
}

status Quedestroy(linkque q)                                          //销毁队列
{
    while(q->front)
    {
        q->rear = q->front->next;
        free(q->front);
        q->front = q->rear;
    }
    printf("\n正在销毁对队列。。。\n队列销毁成功!\n");
    return (1);
}

status Quedel(linkque q)                                              //若队q非空，则删除队q的队首元素，用e返回其值，修改队首指针
{                                                                     //队列设置了头结点，当队列只有一个元素时，执行删除操作也要修改尾指针
    linkdot p;
    elementype e;
    if(q->front == q->rear)
        return (0);
    p = q->front->next;                                               //p指针指向队首元素
    q->front->next = p->next;                                         //将队首节点域的next指向队列中的第二个节点
    if(q->rear == p)
        q->rear = q->front;                                           //队列的尾指针也消失了，此时应对尾指针重新赋值，令其指向头结点
    e = p->data;
    free(p);
    return e;
}

status Quelength(linkque q)
{
    int i = 0;
    linkdot p = q->front->next;
    while(p)
    {
        i++;
        p = p->next;
    }
    return (i);
}

int main()
{
    srand((unsigned)time(NULL));
    linkque q;
    elementype e;
    int count = 10;
    q = (linkque)malloc(sizeof(que));
    Queinit(q);
    while(count--)
    {
        e = rand() % 100;
        Queinsert(q, e);                                              //对队列进行插入元素操作
    }
    print_q(q);
    printf("\n队列长度为：%d", Quelength(q));
    printf("\n删除队首元素：%d", Quedel(q));
    print_q(q);
    printf("\n队列长度为：%d", Quelength(q));
    Quedestroy(q);
}
