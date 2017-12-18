/* 尝试直接使用二维数组创建图 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

#define MAX 100
#define LIMIT 9999

int graph[MAX][MAX];
vector<bool> Visited(MAX, false);

// 函数原型
void InitGraph(int graph[][MAX]);
void InitVisited();

/* 深度优先遍历 */
void DFS(int graph[][MAX], int Nv, int v);
void DFS_Graph(int graph[][MAX], int Nv);
/* 广度优先遍历 */
void BFS(int graph[][MAX], int Nv, int v);
void BFS_Graph(int graph[][MAX], int Nv);

int test()
{
    int Nv, Ne;
    scanf("%d %d", &Nv, &Ne);
    int v, w, dis;
    InitGraph(graph);
    for(int i = 0; i < Ne; i++)
    {
        scanf("%d %d %d", &v, &w, &dis);
        graph[v][w] = dis;
    }/* 以上代码成功建立图 */
    /* 进行遍历 */
    printf("DFS\n");
    DFS_Graph(graph, Nv);
    InitVisited();
    printf("\n\nBFS\n");
    BFS_Graph(graph, Nv);
    return 0;
}

void DFS_Graph(int graph[][MAX], int Nv)
{
    for(int v = 0; v < Nv; v++)
    {
        if(!Visited[v])
        {
            printf("\n---------连通集分界线---------\n");
            printf("{ ");
            DFS(graph, Nv, v);
            printf("}");
        }
    }
}

void DFS(int graph[][MAX], int Nv, int v)
{
    Visited[v] = true;
    printf("%d ", v);
    for(int j = 0; j < Nv; j++)
    {
        if(graph[v][j] < LIMIT)
        {
            DFS(graph, Nv, j);
        }
    }
}

void BFS_Graph(int graph[][MAX], int Nv)
{
    for(int v = 0; v < Nv; v++)
    {
        if(!Visited[v])
        {
            printf("\n---------连通集分界线---------\n");
            printf("{ ");
            BFS(graph, Nv, v);
            printf("}");
        }
    }
}

void BFS(int graph[][MAX], int Nv, int v)
{
    queue<int> queue1;
    int temp;
    Visited[v] = true;
    printf("%d ", v);
    queue1.push(v);
    while(!queue1.empty())
    {
        temp = queue1.front();
        queue1.pop();
        for(int w = 0; w < Nv; w++)
        {
            if(graph[temp][w] < LIMIT)
            {
                Visited[w] = true;
                printf("%d ", w);
                queue1.push(w);
            }
        }
    }
}

void InitGraph(int graph[][MAX])
{
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            graph[i][j] = LIMIT;
}

void InitVisited()
{
    for(auto iter = Visited.begin(); iter != Visited.end(); iter++)
        (*iter) = false;
}
