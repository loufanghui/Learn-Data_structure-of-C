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
    struct dnode *llink;
    struct dnode *rlink;
}dnode, *dulinklist;

status createlist_l(dulinklist l, int n)
{
    srand((unsigned)time(NULL));
    dulinklist p, q;
    int i;
    q = l;
    l->rlink = NULL;                                  //如果不是循环链表的话这是NULL，如果普通双链表的话rlink指向尾节点
    for(i = 0; i < n; i++)
    {
        p = (dulinklist)malloc(sizeof(dnode));
        p->data = rand()%100;
        q->llink = p;
        p->rlink = q;
        q = p;
    }
    q->llink = NULL;                                  //不是循环双链表尾节点没有下一个节点
    return (1);
}

void printlist_l(dulinklist l)
{
    dulinklist p = l->llink;
    printf("\n各节点的数据：");
    while(p)
    {
        printf("%2d\t", p->data);
        p = p->llink;
    }
}

int main()
{
    dulinklist l;
    int n;
    l = (dulinklist)malloc(sizeof(dnode));
    printf("请输入链表节点的个数：");
    scanf("%d", &n);
    createlist_l(l, n);
    printlist_l(l);
}
