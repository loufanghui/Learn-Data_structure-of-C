#Mergelinklist.c
#合并两个链表

#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elementype;

typedef struct node
{
    elementype data;
    struct node *next;
}node, *linklist;

status creatlist_l(linklist l, int n)
{
    linklist p, q;
    int i;
    q = l;
    for(i = 0; i < n; i++)
    {
        p = (linklist)malloc(sizeof(node));
        printf("请输入第%d个节点的数据：", i + 1);
        scanf("%d", &p->data);
        q->next = p;
        q = p;
    }
    q->next = NULL;
    return (1);
}

void printlist_l(linklist l)
{
    linklist p;
    p = l->next;
    int i = 1;
    while(p != NULL)
    {
        printf("第%d个节点的数据是：%d\n", i, p->data);
        p = p->next;
        i++;
    }
}

status mergelist_l(linklist l1, linklist l2)
{
    linklist p = l1;             //使用尾指针，将l1与l2头尾相接
    while(p->next)
        p = p->next;
    p->next = l2->next;         //将l1的尾节点指针指向l2的的第一个节点，非头结点
    return (1);
}

int main() {
    linklist l1, l2;
    int n, index;
    elementype e;
    l1 = (linklist)malloc(sizeof(node));
    l2 = (linklist)malloc(sizeof(node));
    printf("请输入节点的个数：");
    scanf("%d", &n);
    creatlist_l(l1, n);
    creatlist_l(l2, n);
    printf("\n打印链表1：\n");
    printlist_l(l1);
    printf("\n打印链表2：\n");
    printlist_l(l2);
    printf("\n对两个链表进行合并，即为l1\n");
    mergelist_l(l1, l2);        //打印合并后的链表
    printlist_l(l1);
    return 0;
}
