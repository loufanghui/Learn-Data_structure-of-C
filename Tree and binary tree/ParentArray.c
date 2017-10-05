/*
 * 树的存储表示——双亲数组表示法
 * 除了根节点外，树中每一个节点有且仅有一个双亲，上述表示法正式利用了这一性质。
 * 在双亲数组中，寻找一个节点的双亲，我们只要访问它的parent域，便可立即找到它的双亲的存储位置。
 * 因此，若求任一节点的双亲，只要常量时间便可完成。但是，在双亲树数组中，若寻找节点的孩子，则需要扫面整个数组
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXSIZE 100                                                   //最大节点的个数

typedef int status;
typedef char TreeData;

typedef struct                                                        //树的节点的定义
{
    TreeData data;                                                    //节点数据域
    int parent;                                                       //双亲位置于
}TreeNode;

typedef TreeNode Tree[MAXSIZE];                                       //定义一个tree的数组类型

int Create_Tree(Tree tree, int n)                                     //这里虽然没有使用引用或者是指针，但是也达到了传址的目的
{
    srand((unsigned)time(NULL));
    int i;
    for(i = 1; i < n; i++)
    {
        tree[i].data = 'A' + rand() % 25;
        tree[i].parent = rand() % i;
    }
}

void Print_Tree(Tree tree, int n)
{
    int i;
    printf("打印各节点的信息:\n");
    printf("%4s\t%5s\t%5s\n", "序号", "data", "parent");
    for(i = 1; i < n; i++)
    {
        printf("%4d\t  %c  \t%3d\n", i, tree[i].data, tree[i].parent);
    }
}

int main()
{
    Tree tree;
    int n = 21;                                                       //20个节点
    Create_Tree(tree, n);
    Print_Tree(tree, n);
}
