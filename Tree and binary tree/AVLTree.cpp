#include "iostream"
#include <cstdio>

using namespace std;

typedef struct TNode
{
    int data;
    struct TNode * Left;
    struct TNode * Right;
    int Height;
} *AVLTree;

// 函数原型
AVLTree Insert(int X, AVLTree A);
AVLTree SingleLeftRotation(AVLTree A);
AVLTree DoubleLeftRightRotation(AVLTree A);
AVLTree SingleRightRotation(AVLTree A);
AVLTree DoubleRightLeftRotation(AVLTree A);
int Max(int a, int b);
int GetHeight(AVLTree A);

int test()
{
    AVLTree A = NULL;
    int N, e;
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> e;
        A = Insert(e, A);
    }
    cout << A->data << endl;
    return 0;
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

int GetHeight(AVLTree A)
{
    int Height = -1;                                      // 初始值应该设置为-1.因为有后面更新树高需要加1，正好为零
    if(A)
        Height = A->Height;
    return Height;
}

AVLTree SingleLeftRotation(AVLTree A)
{
    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(A), GetHeight(B->Left)) + 1;
    return B;
}

AVLTree SingleRightRotation(AVLTree A)
{
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Right), A->Height) + 1;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{/* 先做A的左子树做一次右单旋，再对A做一次左单旋 */
    A->Left = SingleRightRotation(A->Left);

    return SingleLeftRotation(A);                                   // 返回第三个结点C
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{/* 先做A的右子树做一次左单旋，再对A做一次右单旋 */
    A->Right = SingleLeftRotation(A->Right);

    return SingleRightRotation(A);
}

AVLTree Insert(int X, AVLTree A)
{
    if(!A)
    {
        A = (AVLTree)malloc(sizeof(struct TNode));
        A->data = X;
        A->Height = 0;
        A->Left = A->Right = NULL;
    }
    else
    {
        if(X < A->data)                                             // 插入A的左子树
        {
            A->Left = Insert(X, A->Left);
            if(GetHeight(A->Left) - GetHeight(A->Right) == 2)        // 如果左子树插入元素后左边比右边高2
            {/* 需要进行左*单（双）旋 */
                if(X < A->Left->data)
                    /* 如果元素插入后小于左子树的值，则说明需要进行左左旋转 */
                    A = SingleLeftRotation(A);                      // 左单旋
                else
                    A = DoubleLeftRightRotation(A);                      // 进行左右双旋
            }/* 插入左子树结束 */
        }
        else if(X > A->data)
        {
            A->Right = Insert(X, A->Right);
            if(GetHeight(A->Right) - GetHeight(A->Left) == 2)
            {/* 需要进行右*单（双）旋 */
                if(X > A->Right->data )
                    /* 如果元素插入后大于右子树的值，则说明需要进行右右旋转 */
                    A = SingleRightRotation(A);                 // 右右单旋
                else
                    A = DoubleRightLeftRotation(A);                 // 右左双旋
            }
        }
    }/* 最后不忘了更新树高 */
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;    // 树高取左右子树中最大值+1
    return A;
}
