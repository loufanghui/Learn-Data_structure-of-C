#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> Add(vector<int> v1, vector<int> v2);
vector<int> Multi(vector<int> v1, vector<int> v2);

int main()
{
    int n, m, count = 0, flag = 0;       // flag用于记录是否是零多项式，count用于判断第一个，是否输出空格
    int e, f;
    scanf("%d", &n);
    vector<int> v1(1005, 0);
    vector<int> v2(1005, 0);
    vector<int> v3(1005, 0);
    vector<int> v4(1000100, 0);          // 防止溢出1000*1000 = 1000000
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d", &f, &e);
        v1[e] = f;
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i++)
    {
        scanf("%d %d", &f, &e);
        v2[e] = f;
    }
    v4 = Multi(v1, v2);
    for(int i = 1000000; i >= 0; i--)
    {
        if(v4[i] != 0)
        {
            flag = 1;
            if(count == 0)
            {
                printf("%d %d", v4[i], i);
                count = 1;
            }
            else
                printf(" %d %d", v4[i], i);
        }
    }
    if(flag == 0)
        printf("0 0");
    printf("\n");
    count = 0;
    flag = 0;
    v3 = Add(v1, v2);
    for(int i = 1000; i >= 0; i--)
    {
        if(v3[i] != 0)
        {
            flag = 1;
            if(count == 0)
            {
                printf("%d %d", v3[i], i);
                count = 1;
            }
            else
                printf(" %d %d", v3[i], i);
        }
    }
    if(flag == 0)
        printf("0 0");
    return 0;
}

vector<int> Add(vector<int> v1, vector<int> v2)
{
    for(int i = 0; i <= 1000; i++)
    {
        v1[i] += v2[i];
    }
    return v1;
}

vector<int> Multi(vector<int> v1, vector<int> v2)
{
    vector<int> v3(1000100, 0);
    int exp;
    for(int i = 0; i <= 1000; i++)
    {
        for(int j = 0; j <= 1000; j++)
        {
            exp = i + j;
            v3[exp] += v1[i] * v2[j];
        }
    }
    return v3;
}
