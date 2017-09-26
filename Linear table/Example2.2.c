/*                   例题2.2
 * 假设有一个循环链表的长度大于1，且表中既无头结点也无头指针。
 * 已知p为指向链表中某节点的指针，试编写算法在链表中删除指针p所指的前驱节点
 * */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

typedef int status;
typedef int elementype;

typedef struct node
{
    int isheader;                              //用于标记头结点，便于打印，其他节点为零
    elementype data;
    struct node *next;
}node, *linklist;

status createlinklist_l(linklist l, int n)
{
    srand((unsigned)time(NULL));
    linklist p, q;
    q = l;
    l->data = 0;                               //头结点的值设为零
    l->isheader = 1;                           //标记头结点
    int i;
    for(i = 0; i < n; i++)
    {
        p = (linklist)malloc(sizeof(node));
        p->data = rand()%20;                   //产生0-19之间的随机数，因为懒...
        q->next = p;
        q = p;
    }
    q->next = l;
}

void printlistlist_l(linklist l)
{
    linklist p = l;
    printf("\n打印节点数据：");
    do{
        printf("%2d\t", p->data);
        p = p->next;
    }while(p->isheader != 1);
}

linklist Del_l(linklist p)                     //主要算法函数，实现对节点前驱节点的删除
{
    linklist q, r;
    q = p->next;
    while(q->next != p)
    {
        r = q;                                 //使用指针r指向要删除节点的前一个节点
        q = q->next;
    }
    r->next = p;
    free(q);
    return p;
}

int main()
{
    linklist l, p;                             //p表示某节点指针
    int n;
    l = (linklist)malloc(sizeof(node));
    printf("请输入链表的长度（算入头节点）：");
    scanf("%d", &n);
    createlinklist_l(l, n);
    p = l->next;
    p = p->next;                              //这两步骤表示将要被删除的是第二个节点
    printlistlist_l(l);
    Del_l(p);
    printlistlist_l(l);
}

