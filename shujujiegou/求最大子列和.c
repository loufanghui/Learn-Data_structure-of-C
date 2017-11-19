#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> v;

int MaxSubseqSum(vector<int> v, int N);

int main()
{
    int N, e, MaxSum;
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &e);
        v.push_back(e);
    }
    MaxSum = MaxSubseqSum(v, N);
    printf("%d", MaxSum);
    return 0;
}

int MaxSubseqSum(vector<int> v, int N)
{
    int MaxSum, ThisSum;
    MaxSum = ThisSum = 0;
    for(int i = 0; i < N; i++)
    {
        ThisSum += v[i];
        if(ThisSum > MaxSum)
            MaxSum = ThisSum;
        else if(ThisSum < 0)
            ThisSum = 0;
    }
    return MaxSum;
}
