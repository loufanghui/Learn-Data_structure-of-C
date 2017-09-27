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

status createlist_l(dulinklist l, int n)
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

void printlist_l(dulinklist l)
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

int main()
{
    dulinklist l;
    int n;
    l = (dulinklist)malloc(sizeof(dnode));
    l->isheader = 1;
    printf("请输入链表节点的个数：");
    scanf("%d", &n);
    createlist_l(l, n);
    printlist_l(l);
}
