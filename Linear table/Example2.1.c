/*                       例题2.1
 * 已知单链表表示的线性表中含有三类字符数据：字母字符、数字字符和其他字符。
 * 试设计一个算法构造三个循环链表来表示这个线性表，使得每一个表中只含有同一个字符。
 * 且利用原表中的结点空间作为这三个表的结点空间，头结点可另辟空间
 * */

#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef char elementype;

typedef struct node
{
    elementype data;
    int isLoopList_h;
    struct node *next;
}node, *linklist;

status createlist_l(linklist l, int n)
{
    linklist p, q;
    int i;
    q = l;
    printf("请输入一串字符：");
    for(i = 1; i <= n; i++)
    {
        p = (linklist)malloc(sizeof(node));
        scanf("%c", &p->data);
        q->next = p;
        q = p;
    }
    q->next = NULL;
}

void printlist_l(linklist l)
{
    linklist p = l->next;
    printf("各节点的数据为：");
    while(p && p->isLoopList_h != 1)                                  //循环链表遇到头结点时终止循环
    {
        printf("%c\t", p->data);
        p = p->next;
    }
    printf("\n");
}

void Separate(linklist s, linklist d, linklist c, linklist r)
{
    linklist p, q;
    char ch;
    q = s->next;
    p = s;
    while(q) {
        ch = q->data;
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            p = q->next;                             //如果该节点的字符符合条件，则用指针p指向该节点的下一个节点，便于接着对字符串的后续操作
            q->next = c->next;                       //将该节点的尾指针指向字母链表的尾节点
            c->next = q;                             //这一步和上一步一起实现将该节点加入字母链表
            q = p;                                   //再次将q指针指向原链表的下一个节点
        }                                            //以下同理
        else if (ch >= '0' && ch <= '9') {
            p = q->next;
            q->next = d->next;
            d->next = q;
            q = p;
        } else {
            p = q->next;
            q->next = r->next;
            r->next = q;
            q = p;
        }
    }
}

int main()
{
    linklist l, d, c, r;                         //l表示原链表，d、c、r分别表示储存数字、字母、其他字符的链表
    l = (linklist)malloc(sizeof(node));
    d = (linklist)malloc(sizeof(node));
    d->next = d;
    c = (linklist)malloc(sizeof(node));
    c->next = c;
    r = (linklist)malloc(sizeof(node));
    r->next = r;
    d->isLoopList_h = 1;
    c->isLoopList_h = 1;
    r->isLoopList_h = 1;                        //将三个循环链表的头结点isLoopList_h值设为1，可以打印时进行区分
    int n;
    printf("请输入节点个数（即字符串长度）：");
    scanf("%d", &n);
    getchar();                                  //这个字符串用来接收前面输入n时的回车
    createlist_l(l, n);
    printf("\n原链表中");
    printlist_l(l);
    Separate(l, d, c, r);
    printf("\n字母链表中");
    printlist_l(d);
    printf("\n数字链表中");
    printlist_l(c);
    printf("\n其他字符链表中");
    printlist_l(r);
    return 0;
}
