/*
 * 线索二叉树的实现以及中序遍历
 * 我们规定：
 * ltag = 0，lchild域指向结点的左孩子
 * ltag = 1，lchild域指向结点的前驱
 * rtag = 0，rchild域指向结点的右孩子
 * rtag = 1，rchild域指向结点的后继
 */

#include <stdio.h>
#include <malloc.h>

typedef char elementype;
typedef int status;

typedef enum{link, thread}PointerTag;                                 //link = 0，thread = 1
typedef struct BiThrNode
{
    elementype data;
    struct BiThrNode *lchild, *rchild;
    PointerTag Ltag, Rtag;
}bithrnode, *bithrtree;

bithrtree pre;                                                        //全局变量，指向刚刚访问过的结点

status CreateThrTree(bithrtree tree);
void InitThrTree(bithrtree tree);

int main()
{
    bithrtree tree;
    CreateThrTree(tree);
    InitThrTree(tree);
    InOrderTraverse_Thr(tree);
    return 0;
}

status CreateThrTree(bithrtree tree)
{
    elementype e;
    scanf("%d", &e);
    if(e == '#')
        tree = NULL;
    else
    {
        tree = (bithrtree)malloc(sizeof(bithrnode));
        tree->data = e;
        CreateThrTree(tree->lchild);
        CreateThrTree(tree->rchild);
    }
    return (1);
}

void InitThrTree(bithrtree tree)
{
    if(tree)
    {
        InitThrTree(tree->lchild);                                    //左子树线索化
        if(!tree->lchild)                                             //如果左子树为空，则将其线索化为前驱
        {
            tree->Ltag = thread;                                      //则将其左子树线索化
            tree->lchild = pre;                                       //pre记录了前一个结点的指针
        }
        if(!pre->rchild)                                              //如果前一个结点的右子树为空，将其线索化为后继
        {
            pre->Rtag = thread;
            pre->lchild = tree;
        }
        pre = tree;
        InitThrTree(tree);                                            //对右子树进行线索化
    }
}

status InOrderTraverse_Thr(bithrtree tree)
{
    bithrtree p;
    p = tree->lchild;
    while(p != tree) {
        while (p->Ltag == link)
            p = p->lchild;
        printf("%c\t", p->data);                                          //访问左子树为空的结点
        while (p->Rtag == thread && p->rchild != tree) {
            p = p->lchild;
            printf("%c\n", p->data);                                       //访问后续节点
        }
    }
    return (1);
}
