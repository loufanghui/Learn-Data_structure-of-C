/* Dijkstra算法和图的基本操作 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

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

// 单源有权图的相关定义
int dist[MAX];
int path[MAX];
bool Dijkstra(int graph[][MAX], int dist[MAX], int path[MAX], int s);
                                                  // S表示出发的原点
void InitRoad(int graph[][MAX], int dist[MAX], int path[MAX], int s);
int FindMinDist(int graph[][MAX], int dist[MAX], vector<bool> Visited);
void ShowRoad(int path[MAX], int vertex);

int test()
{
    scanf("%d %d", &Nv, &Ne);
    int v, w, dis, source = 1;
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
    printf("\n请输入从哪个点寻找最短路径：");
    scanf("%d", &source);
    printf("\n");
    Dijkstra(graph, dist, path, source);          // 从某个点开始找最小边
    for(int v = 0; v < Nv; v++)
    {
        printf("%d到%d点的最短距离：%d \t打印路径：", source, v, dist[v]);
        ShowRoad(path, v);                        // 打印路径
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
        if(graph[v][j] < LIMIT && !Visited[j])
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
            if(graph[temp][w] < LIMIT && !Visited[w])
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

bool Dijkstra(int graph[][MAX], int dist[MAX], int path[MAX], int s)
{
    InitRoad(graph, dist, path, s);               // 将dist和path进行初始化
    InitVisited();                                // 将visited进行初始化，这里的visited就相当于collected
    int min_v;                                    // 表示还没收集的顶点中距离s最短的
    Visited[s] = true;
    dist[s] = 0;                                  // 将源点收入集合
    while(true)
    {
        min_v = FindMinDist(graph, dist, Visited);
        if(min_v == -1)
            break;
        Visited[min_v] = true;
        for(int w = 0; w < Nv; w++)
        {
            if(graph[min_v][w] < 0)
            {                                     // 如果存在负边，则返回错误
                return false;
            }
            if(dist[w] > dist[min_v] + graph[min_v][w] && !Visited[w])
            {                                     // 如果w和min_v相邻并且w没有被收集，则更新w的dist和path
                dist[w] = dist[min_v] + graph[min_v][w];
                path[w] = min_v;
            }
        }
    }
    return true;
}

void InitRoad(int graph[][MAX], int dist[MAX], int path[MAX], int s)
{
    for(int i = 0; i < MAX; i++)
    {
        dist[i] = graph[s][i];
        if(dist[i] < LIMIT)
            path[i] = s;
        else
            path[i] = -1;
    }
}

int FindMinDist(int graph[][MAX], int dist[MAX], vector<bool> Visited)
{
    int min_v = -1;
    int min_dist = LIMIT;
    for(int w = 0; w < Nv; w++)
    {
        if(!Visited[w] && dist[w] < min_dist)     // 如果没有点dist比min_dist小，就说明这些点都断开了
        {                                         // 如果w顶点没有被访问过，并且dist小于当前最小值
            min_dist = dist[w];
            min_v = w;
        }
    }
    return min_v;
}

void ShowRoad(int path[MAX], int vertex)
{
    stack<int> s;
    while(vertex != -1)
    {
        s.push(vertex);
        vertex = path[vertex];
    }
    while(!s.empty())
    {
        printf(" %d", s.top());
        s.pop();
    }
    printf("\n");
}
