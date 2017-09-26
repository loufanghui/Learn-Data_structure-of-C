#2-3-2SimpleLinkedList.c

#include <stdio.h>
#include <malloc.h>

typedef int status;                              //status可以表示函数返回的状态，1或者0
typedef int elementype;

//创建节点
typedef struct node
{
    elementype data;
    struct node *next;
}node, *linklist;                                 //node和linklist都可以表示节点，但表示的方法不同，后者实现类似于引用的功能


//创建链表
status creatlist_l(linklist l, int n)
{
    linklist p, q;                                //q表示指向节点的指针，p表示节点类型的指针，用于临时存放数据
    int i;
    q = l;
    for(i = 1; i <= n; i++)
    {
        p = (linklist)malloc(sizeof(node));
        printf("请输入第%d个节点的数据：", i);
        scanf("%d", &p->data);
        q->next = p;
        q = p;
    }
    q->next = NULL;
    return (1);
}

//打印链表
void printlist_l(linklist l)
{
    linklist p = l->next;
    printf("各节点的数据：");
    while(p != NULL)
    {
        printf("%5d", p->data);
        p = p->next;
    }
}

status insertlist_l(linklist l, int n, elementype e)
{
    linklist q = l, p;                            //p为新的节点的指针
    p = (linklist)malloc(sizeof(node));
    int i = 1;
    while(i < n && q != NULL)                     //q指针走到要插入节点的上一个节点
    {
        q = q->next;
        i++;
    }
    if(!q)
    {
        printf("不能超过链表长度！\n");
        return (0);
    }
    p->data = e;                                  //给新节点的数据属性赋值
    p->next = q->next;                            //让新节点next指向下个节点（其实就是原第n个节点）
    q->next = p;                                  //让上一个节点指向新节点
    return (1);
}

status deletelist_l(linklist l, int n)
{
    linklist p, q;
    int i = 1;
    q = l;
    while(q->next && i < n)                      //使指针q移动到要删除节点的上一个节点
    {                                            //如果删除的节点位置超过链表长度，则q->next节点为空
        q = q->next;
        i++;
    }
    if(!q->next)                                 //如果删除的节点位置超过链表长度，则返回错误信息
    {
        printf("插入位置超过列表长度");
        return (0);
    }
    p = q->next;                                 //1.p指针指向要删除的节点
    q->next = p->next;                           //2.删除节点的上一个节点的next指针指向删除节点的下一个节点
    free(p);                                     //3.在第二步被删除节点被隔离出链表的基础上，将该节点空间释放，达到删除的目的
    return (1);
}

int main()
{
    linklist l;
    int n, choice, i;
    elementype e;
    l = (node *)malloc(sizeof(node));
    if(!l)
        printf("给链表分配空间失败！");
    l->next = NULL;
    printf("请输入节点的个数：");
    scanf("%d", &n);
    creatlist_l(l, n);
    printlist_l(l);
    printf("\n接下来对链表进行操作\n");
    printf("1.插入元素\n2.删除元素\n3.结束\n");
    printf("请选择操作的序号：");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
            printf("请输入要插入的位置和元素值：");
            scanf("%d %d", &i, &e);
            insertlist_l(l, i, e);
            break;
        case 2:
            printf("请输入要删除元素的位置");
            scanf("%d", &i);
            deletelist_l(l, i);
            break;
        default:
            printf("操作结束！");
            break;
    }
    printf("打印操作后的数据\n");
    printlist_l(l);
    return 0;
}
