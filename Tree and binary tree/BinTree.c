/*
 * 二叉树的实现以及前序、中序、后序遍历，以及非递归方式的中序遍历
 */

#include <stdio.h>
#include <malloc.h>

#define STACK_SIZE 100
#define STACK_SIZE_ADD 100

typedef int elementype;

typedef struct BitNode
{
    elementype data;
    struct BitNode *lchild, *rchild;
}bitnode, *bintree;

typedef struct Sqstack
{
    bintree *base;                                                     //栈中存放的是二叉树中每个节点的地址
    bintree *top;                                                      //数据类型应采用二叉树节点的指针类型
    int stacksize;
}snode, *sqstack;

bintree CreateTree();                                                 //创建二叉树
//递归的方式进行遍历
void PreOrderTraverse(bintree tree);                                  //前序遍历二叉树
void InOrderTraverse(bintree tree);                                   //中序遍历二叉树
void PostOrderTraverse(bintree tree);                                 //后序遍历二叉树

/*
 * 非递归的方式进行遍历
 * 哈哈，我懒
 * 等我下次复习栈吧2333
 */
//非递归的方式进行中序遍历
void InOrder(bintree tree);

//栈的相关函数
void initstack(sqstack s);                                            //初始化栈
void push(sqstack s, bintree e);                                      //元素入栈
void pop(sqstack s, bintree *p);                                      //元素出栈
int stackempty(sqstack s);                                            //检查是否是空栈
void stackclear(sqstack s);                                           //将栈清空并摧毁


int main()
{
    bintree tree;
    tree = CreateTree();
    printf("前序遍历二叉树：");
    PreOrderTraverse(tree);
    printf("\n中序遍历二叉树：");
    InOrderTraverse(tree);
    printf("\n后序遍历二叉树：");
    PostOrderTraverse(tree);
    printf("\n非递归方法中序遍历二叉树：");
    InOrder(tree);
    return 0;
}

bintree CreateTree()
{
    bintree tree;
    elementype e;
    scanf("%d", &e);
    if(e == -1)
        tree = NULL;
    else
    {
        tree = (bintree)malloc(sizeof(bitnode));
        tree->data = e;
        tree->lchild = CreateTree();
        tree->rchild = CreateTree();
    }
    return tree;
}

void PreOrderTraverse(bintree tree)
{
    if(tree)
    {
        printf("%d\t", tree->data);
        PreOrderTraverse(tree->lchild);
        PreOrderTraverse(tree->rchild);
    }
}

void InOrderTraverse(bintree tree)
{
    if(tree)
    {
        InOrderTraverse(tree->lchild);
        printf("%d\t", tree->data);
        InOrderTraverse(tree->rchild);
    }
}

void PostOrderTraverse(bintree tree)
{
    if(tree)
    {
        PostOrderTraverse(tree->lchild);
        PostOrderTraverse(tree->rchild);
        printf("%d\t", tree->data);
    }
}

void InOrder(bintree tree)
{
    sqstack s;
    s = (sqstack)malloc(sizeof(snode));
    initstack(s);
    bintree p = tree;
    while(p != NULL || !stackempty(s))
    {
        if(p != NULL)
        {
            push(s, p);
            p = p->lchild;
        }
        else
        {
            pop(s, &p);
            printf("%d\t", p->data);
            p = p->rchild;
        }
    }
    stackclear(s);
}

/*--------------------以下是对栈的基本操作-----------------------*/

void initstack(sqstack s)
{
    s->base = (bintree *)malloc(STACK_SIZE * sizeof(bintree));
    s->top = s->base;
    s->stacksize = STACK_SIZE;
}

void push(sqstack s, bintree e)
{
    if(s->top - s->base >= s->stacksize)                              //如果栈满了，则需要增加空间
    {
        s->base = (bintree *)malloc((s->stacksize + STACK_SIZE_ADD) * sizeof(bintree));
        s->top = s->base + s->stacksize;
        s->stacksize += STACK_SIZE_ADD;
    }
    *s->top = e;
    s->top++;
}

void pop(sqstack s, bintree *p)
{
    *p = *(s->top - 1);
    s->top--;
}

int stackempty(sqstack s)
{
    if(s->top == s->base)
        return 1;
    else
        return 0;
}

void stackclear(sqstack s)
{
    s->top = s->base;
    free(s->base);
    free(s);
}
