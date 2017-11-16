#include <iostream>
#include <ctime>

#define ElementType int

using namespace std;

typedef struct Node
{
    ElementType data;
    struct Node *Right, *Left;
} *BinTree, TreeNode;

typedef BinTree Position;

// 函数原型
Position Find(ElementType X, BinTree BST);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);
void InOrderTraverse(BinTree BST);
BinTree Insert(ElementType X, BinTree BST);
BinTree Delete(ElementType X, BinTree BST);

void test()
{
    srand((unsigned)time(NULL));
    BinTree BST = NULL;                     /* 首先建立一颗空树 */
    ElementType e;
    cout << "产生的随机元素：\n";
    for(int i = 0; i < 20; i++)
    {
        e = (int)(rand() % 100);
        BST = Insert(e, BST);
        cout << e << " ";
    }
    cout << "\n打印二叉搜索树，中序遍历：" << endl;
    InOrderTraverse(BST);
    cout << "\n请输入要查找的元素：";
    cin >> e;
    cout << "\n查找到的元素为\n\t" << Find(e, BST) << ":" << Find(e, BST)->data;
    cout << "\n找到的最大值\n\t" << FindMax(BST) << ":" << FindMax(BST)->data;
    cout << "\n找到的最小值\n\t" << FindMin(BST) << ":" << FindMin(BST)->data;
    cout << "\n请输入要删除的元素：";
    cin >> e;
    cout << "\n被删除的元素：" << e << endl;
    Delete(e, BST);
    cout << "打印删除后的二叉树（中序）：\n";
    InOrderTraverse(BST);
}

BinTree Insert(ElementType X, BinTree BST)
{
    if(!BST){/* 若原树为空，生成并返回一个节点的二叉搜索树 */
        BST = (BinTree)malloc(sizeof(TreeNode));
        BST->data = X;
        BST->Left = BST->Right = NULL;
    }else{/* 开始找要插入的位置 */
        if(X > BST->data)  /* 如果大于，则将元素插入右子树 */
            BST->Right = Insert(X, BST->Right);
        else if(X < BST->data) /* 如果小于，则将元素插入左子树 */
            BST->Left = Insert(X, BST->Left);
        /* 如果相等，则什么都不做 */
    }
    return BST;
}

void InOrderTraverse(BinTree BST)
{
    if(BST)
    {
        InOrderTraverse(BST->Left);
        cout << BST->data << " ";
        InOrderTraverse(BST->Right);
    }
}

Position Find(ElementType X, BinTree BST)
{
    if(!BST)
        return NULL;
    if(X > BST->data)
    {
        return Find(X, BST->Right);
    }
    else if(X < BST->data)
        return Find(X, BST->Left);
    else
        return BST;
}

Position FindMax(BinTree BST)
{
    if(BST)
        while(BST->Right)
            BST = BST->Right;
    return BST;
}

Position FindMin(BinTree BST) {
    if (BST->Left)
        return FindMin(BST->Left);
    else
        return BST;
}

BinTree Delete(ElementType X, BinTree BST)
{
    Position tmp;
    if(!BST)
        printf("要删除的元素未找到！");
    else if(X < BST->data) {                    /* 左子树递归删除 */
        BST->Left = Delete(X, BST->Left);             /* 右子树递归删除 */
    }else if(X > BST->data){
        BST->Right = Delete(X, BST->Right);
    }else{
        if(BST->Right && BST->Left){            /* 被删除的结点有两个子节点 */
            tmp = FindMin(BST->Right);          /* 找右子树中的最小节点填充被删除的节点 */
            BST->data = tmp->data;
            BST->Right = Delete(BST->data, BST->Right);      /* 在被删除结点的右子树中删除最小元素 */
        }else{                                  /* 被删除的节点只有一个结点或者无结点 */
            tmp = BST;
            if(!BST->Right){                    /* 只有左孩子或者无子节点 */
                BST = BST->Left;
            }else if(!BST->Left){               /* 只有右孩子或者无子节点 */
                BST = BST->Right;
            }
            free(tmp);                          /* tmp代替BST被删除 */
        }
    }
    return BST;
}
