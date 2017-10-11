/*
 * 二叉树的实现以及前序、中序、后序遍历
 */

#include <stdio.h>
#include <malloc.h>

typedef int elementype;

typedef struct BitNode
{
    elementype data;
    struct BitNode *lchild, *rchild;
}bitnode, *bintree;

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
