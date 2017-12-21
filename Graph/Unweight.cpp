/* 尝试直接使用二维数组创建图 */
/* 并对无权图求最小路径 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

#define MAX 100
#define LIMIT 9999

int graph[MAX][MAX];
vector<bool> Visited(MAX, false);
int Nv, Ne;

// 函数原型
void InitGraph(int graph[][MAX]);
void InitVisited();

/* 深度优先遍历 */
void DFS(int graph[][MAX], int Nv, int v);
void DFS_Graph(int graph[][MAX], int Nv);
/* 广度优先遍历 */
void BFS(int graph[][MAX], int Nv, int v);
void BFS_Graph(int graph[][MAX], int Nv);

// 单源无权图的相关定义
int dist[MAX];
int path[MAX];
void InitRoad();
void Unweight(int graph[][MAX], int dist[MAX], int path[MAX], int s);
                                                  // S表示出发的原点

int test()
{
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
    /* 求无权图的最短路径 */
    printf("\n");
    Unweight(graph, dist, path, 0);      // 从零开始
    for(int v = 0; v < Nv; v++)
    {
        printf("0到%d点的最短距离%d\n", v, dist[v]);
    }
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

void Unweight(int graph[MAX][MAX], int dist[MAX], int path[MAX], int s)
{
    InitRoad();
    dist[s] = 0;
    queue<int> queue2;
    InitVisited();
    int temp;                                     // temp表示
    queue2.push(s);
    while(!queue2.empty())
    {
        temp = queue2.front();
        queue2.pop();
        for(int w = 0; w < Nv; w++)
        {
            if(graph[temp][w] < LIMIT && (dist[w] == -1))
            {
                dist[w] = dist[temp] + 1;
                path[w] = temp;
                queue2.push(w);
            }
        }
    }
}

void InitRoad()
{
    for(int i = 0; i < MAX; i++)
    {
        dist[i] = -1;
        path[i] = -1;
    }
}
