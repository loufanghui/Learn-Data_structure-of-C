#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>

#define MAX_VERTEX_NUM 100                        // 定义最大顶点个数，注意没有分号

using namespace std;

vector<bool> Visited(MAX_VERTEX_NUM, false);

typedef int WeightType;                           // 定义权重的类型
typedef int Vertex;                               // 定义顶点的类型

/* 邻接矩阵，存放所有边的边权 */
typedef struct Node
{
    WeightType data;
}VMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// 定义一个图结构
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;                                       // 顶点数
    int Ne;                                       // 边数
    VMatrix G;                                    // 根据定点的类型，在图中定义邻接矩阵
};
typedef PtrToGNode MGraph;                        // 定义一个图类型

// 函数原型
MGraph CreateGraph(int VertexNum, int EdgeNUm);   // 初始化一个有VertexNum个顶点，EdgeNUm条边的图
void Insert(MGraph Graph, Vertex v, Vertex w, WeightType data);
                                                  // 对图进行边的插入操作， v，w分别表示两个顶点，data是插入的边权
void DFS(MGraph Graph, Vertex v);                 // 从某个顶点深度优先遍历
void BFS(MGraph Graph, Vertex v);                 // 从某个顶点广度优先遍历
void DFSInGraph(MGraph Graph);                    // 图的深度优先遍历
void BFSInGraph(MGraph Graph);                    // 图的广度优先遍历
void Visit(Vertex v);                             // 访问顶点函数

int test()
{
    int VertexNum, EdgeNUm;
    printf("请输入顶点的个数和边的个数：");
    scanf("%d %d", &VertexNum, &EdgeNUm);
    MGraph Graph = CreateGraph(VertexNum, EdgeNUm);
    DFSInGraph(Graph);
    return 0;
}

MGraph CreateGraph(int VertexNum, int EdgeNUm)
{
    MGraph Graph;
    Vertex v, w;                                  // 本质上v,w是表示两个顶点
    WeightType EdgeWeight;                            // 定义变量记录边权
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = EdgeNUm;
    for(v = 0; v < Graph->Nv; v++)         // 本质上v,w是遍历每个顶点
    {
        for(w = 0; w < Graph->Nv; w++)
        {
            Graph->G[v][w].data = 0;              // 或INFINITY，即给边权一个最大的值表示不存在，这里无权图边权为零
        }
    }
    printf("\n请在以下输入每条边的起止点和边权：\n");
    for(int i = 0; i < EdgeNUm; i++)
    {
        scanf("%d %d %d", &v, &w, &EdgeWeight);
        Insert(Graph, v, w, EdgeWeight);
    }
    return Graph;
}

void Insert(MGraph Graph, Vertex v, Vertex w, WeightType data)
{
    Graph->G[v][w].data = data;                   // 如果是有向图，则这一句就行了
    Graph->G[w][v].data = data;                   // 如果是无向图，加上这一句就，即顶点的边没有方向
}

void DFS(MGraph Graph, Vertex v)
{
    if(!Visited[v])
    {
        Visit(v);
        Visited[v] = true;
    }
    for(Vertex vx = 0; vx < Graph->Nv; vx++)
    {
        if(!Visited[vx] && Graph->G[v][vx].data > 0)
        {                                         // 如果vx是v的邻点，且没没有被访问过，则递归访问该vx点
            DFS(Graph, vx);
        }
    }
}

void DFSInGraph(MGraph Graph)
{
    for(Vertex v = 0; v < Graph->Nv; v++)
    {
        if(!Visited[v])
        {
            printf("\n--------连通集分割线--------\n");
            DFS(Graph, v);
        }
    }
}

void Visit(Vertex v)
{
    printf("正在访问节点：%d\n", v);
}
