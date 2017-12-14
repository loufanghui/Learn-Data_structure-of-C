#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <ctime>


using namespace std;

// 定义个哈夫曼树
typedef struct TreeNode
{
    int Weight;
    
};

// 函数原型
bool cmp(int a, int b);

int test()
{
    srand((unsigned)time(NULL));
    vector<int> v;
    int n = 6, e;
    for(int i = 0; i < n; i++)
    {
        e = rand() % 100;
        cout << e << ',';
        v.push_back(e);
    }
    cout << endl;
    make_heap(v.begin(), v.end(), cmp);
    cout << "打印生成的堆：" << endl;
    for(vector<int>::iterator it = v.begin(); it < v.end(); it++)
        cout << *it << ' ';
    cout << endl;
    v.push_back(20);
    push_heap(v.begin(), v.end(), cmp);
    cout << "打印插入20后生成的新堆：" << endl;
    for(vector<int>::iterator it = v.begin(); it < v.end(); it++)
        cout << *it << ' ';
    cout << endl;
    //删除数据  要先调用pop_heap()，再在容器中删除
    pop_heap(v.begin(), v.end());
    v.pop_back();
    cout << "打印pop根节点后，生成的新堆：" << endl;
    for(vector<int>::iterator it = v.begin(); it < v.end(); it++)
        cout << *it << ' ';
    return 0;
}

bool cmp(int a, int b)
{/* 这里生成的是最大堆，改成大于号生成的是最小堆 */
    return a < b;
}
