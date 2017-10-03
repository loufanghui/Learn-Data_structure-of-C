// 实现链栈的基本操作、初始化、进栈和出栈等

#include <stdio.h>
#include <malloc.h>

typedef int status;
typedef int elementype;

typedef struct lnode
{
    elementype data;
    struct lnode *next;
}lnode, *linkstack;

status push(linkstack top, elementype e)
{
    linkstack p;
    p = (linkstack)malloc(sizeof(lnode));                                   //给链栈的新节点分配空间
    p->next = top->next;
    top->next = p;
    p->data = e;
    return (1);
}

void print_s(linkstack top)                                                 //打印栈中的所有元素
{
    linkstack p = top->next;
    if(p) {
        printf("\n打印栈中的元素：");
        while (p) {
            printf("%3d\t", p->data);
            p = p->next;
        }
    }
    else
        printf("空栈 请插入元素!");
}

status gettop(linkstack top)                                                //取栈顶元素
{
    if(!top->next)
    {
        printf("该栈为空栈，请插入元素！\n");
        return (0);
    }
    return (top->next)->data;
}

status pop(linkstack top)
{
    elementype y;
    linkstack p = top->next;
    if(!top->next)
    {
        printf("该栈为空栈，请插入元素！\n");
        return (0);
    }
    y = p->data;
    top->next = p->next;
    free(p);
    return y;
}

int main()
{
    linkstack top = (linkstack)malloc(sizeof(lnode));
    elementype a = -9999;
    top->data = a;
    top->next = NULL;
    int choice = 0;
    if(!top)
        printf("分配空间失败！");
    printf("/*****************************************/\n");
    printf("            链栈的实现与基本操作               ");
    printf("/*****************************************/\n");
    do{
        a = -9999;
        printf("\n1.进栈\n");
        printf("2.取栈顶元素\n");
        printf("3.出栈\n");
        printf("4.结束\n");
        printf("请输入你的选择：");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                printf("请输入插入栈的元素：");
                scanf("%d", &a);
                push(top, a);
                break;
            case 2:
                a = gettop(top);
                printf("\n栈顶元素：%d\n", a);
                break;
            case 3:
                a = pop(top);
                printf("\n出栈的元素为：%d\n", a);
                break;
            case 0:
                exit(0);
        }
        print_s(top);
    }while(choice != 0);
}
