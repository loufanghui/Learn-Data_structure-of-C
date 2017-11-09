#include <ctime>
#include <iostream>
#include <stack>

using namespace std;

typedef struct Bitnode
{
    int data;
    struct Bitnode *lchild, *rchild;
}Bitnode, *Bitree;

stack<Bitnode> S;

Bitree CreateTree()
{
    Bitree tree;
    int e;
    cin >> e;
    if(e != -1)
    {
        tree = new Bitnode;
        tree->data = e;
        tree->lchild = CreateTree();
        tree->rchild = CreateTree();
    }
    else
        tree = NULL;
    return tree;
}

void PreOrderTraverse(Bitree tree)
{
    if(tree)
    {
        cout << tree->data << " ";
        PreOrderTraverse(tree->lchild);
        PreOrderTraverse(tree->rchild);
    }
}

void InOrderTraverse(Bitree tree)
{
    Bitnode *p = tree;
    while(p != NULL || !S.empty())
    {
        if(p != NULL) {
            S.push(*p);
            p = p->lchild;
        }
        else{
            p = &S.top();
            cout << p->data << " ";
            S.pop();
            p = p->rchild;
        }
    }
}

void PostOrderTraverse(Bitree tree)
{
    if(tree)
    {
        PostOrderTraverse(tree->lchild);
        PostOrderTraverse(tree->rchild);
        cout << tree->data << " ";
    }
}

void printBitree()
{
    Bitree tree;
    tree = CreateTree();
    cout << "前序遍历（递归）：" << endl;
    PreOrderTraverse(tree);
    cout << "\n中序遍历（非递归）：" << endl;
    InOrderTraverse(tree);
    cout << "\n后序遍历（递归）：" << endl;
    PostOrderTraverse(tree);
}
