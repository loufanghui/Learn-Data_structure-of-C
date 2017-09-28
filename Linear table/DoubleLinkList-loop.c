/*
 * （循环）双向链表的实现和基本操作
 */
#include <stdio.h>
#include <malloc.h>
#include <time.h>

typedef int status;
typedef int elementype;

typedef struct
{
    elementype data;
    int isheader;                                     //标记首节点
    struct dnode *llink;
    struct dnode *rlink;
}dnode, *dulinklist;

status createlist_l(dulinklist l, int n)              //创建链表
{
    srand((unsigned)time(NULL));
    dulinklist p, q;
    int i;
    q = l;
    for(i = 0; i < n; i++)
    {
        p = (dulinklist)malloc(sizeof(dnode));
        p->data = rand()%100;                         //我太懒了，自己输入数字太麻烦，用了随机函数2333
        q->llink = p;
        p->rlink = q;
        q = p;
    }
    q->llink = l;                                     //循环链表让尾节点的llink指针指向首节点
    l->rlink = q;                                     //循环链表让首节点的rlink指针指向尾节点
    p = l->llink;
    printf("\n前节点：%x，节点：%x 后节点：%x\n", l->rlink, l, l->llink);
    while(p->isheader != 1)
    {
        printf("\n前节点：%x，节点：%x 后节点：%x\n", p->rlink, p, p->llink);
        p = p->llink;
    }
    return (1);
}

void printlist_l(dulinklist l)                        //打印链表
{
    dulinklist p = l->llink, q = l;
    printf("\n各节点的数据（正向打印）：");
    while(p->isheader != 1)
    {
        printf("%2d\t", p->data);
        q = q->llink;
        p = p->llink;
    }
    printf("\n各节点的数据（反向打印）：");
    while(q->isheader != 1)
    {
        printf("%2d\t", q->data);
        q = q->rlink;
    }
}

status listinsert_l(dulinklist l, elementype e)       //循环双链表的元素插入操作
{
    dulinklist p, q;
    p = (dulinklist)malloc(sizeof(dnode));
    q = l->llink;
    p->data = e;
    p->llink = q;                                     //新节点的llink指针指向首节点的后一个节点
    q->rlink = p;                                     //首节点的后一个节点的rlink指针指向新节点
    l->llink = p;                                     //首节点的llink指针指向新节点
    p->rlink = l;                                     //新节点的rlink指针指向首节点
    return (1);                                       //将新节点插入到尾节点之后（即第一个有效节点）
}

int main()
{
    dulinklist l;
    int n;
    elementype e;
    l = (dulinklist)malloc(sizeof(dnode));
    l->isheader = 1;
    printf("请输入链表节点的个数：");
    scanf("%d", &n);
    createlist_l(l, n);
    printlist_l(l);
    printf("\n请输入要插入的元素值：");
    scanf("%d", &e);
    listinsert_l(l, e);
    printf("\n插入后：\n");
    printlist_l(l);
}
