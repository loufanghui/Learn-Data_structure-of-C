#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>

const int MaxData = 100;

using namespace std;

typedef int ElementType;

typedef struct HeapStruct
{
    int *Elements;        // 存储元素的数组
    int Size;             // 堆的当前元素个数
    int Capacity;         // 堆的最大容量
} *MaxHeap, *MinHeap;

// 函数原型
MaxHeap Create(int MaxSize);
void Insert(MaxHeap H, ElementType item);
bool IsFull(MaxHeap H);
bool IsEmpty(MaxHeap H);
ElementType DeleteMax(MaxHeap H);     // 删除树根
void ShowHeap(MaxHeap H, int size);

int test()
{
    srand((unsigned)time(NULL));
    int size = 5;
    MaxHeap H = Create(size);           // 初始化一个包含10个元素的堆
    ElementType e;
    for(int i = 0; i < size; i++)
    {
        e = (int)rand() % 100;
        Insert(H, e);                 // 将产生的随机元素插入到堆中
        cout << e << ' ';             // 打印产生的随机元素
    }
    cout << endl;
    ShowHeap(H, size);
    return 0;
}

MaxHeap Create(int MaxSize)
{  /* 创建容量为MaxSize的空的最大堆 */
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HeapStruct));
    H->Elements = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));  // 数组的第一个元素存储“哨兵”
    H->Elements[0] = MaxData;
    H->Size = 0;
    H->Capacity = MaxSize;
}

void Insert(MaxHeap H, ElementType item)
{
    int i;
    if(IsFull(H))
    {
        printf("最大堆已满");
        return;
    }
    i = ++H->Size;   // i指向最大堆中的最后一个元素的位置
    for(;item > H->Elements[i/2]; i /= 2)  // 将item与其父节点比较
        H->Elements[i] = H->Elements[i/2];  // 如果大于父节点，将两者交换位置
    H->Elements[i] = item;      // 经过很多交换到了需要的位置将item插入
}

bool IsFull(MaxHeap H)
{
    if(H->Size >= H->Capacity)
        return true;
    else
        return false;
}

bool IsEmpty(MaxHeap H)
{
    if(H->Size == 0)
        return true;
    else
        return false;
}

ElementType DeleteMax(MaxHeap H) {/* 从最大堆中取出键值（即Elements）最大的元素 */
    int parent, child;
    ElementType MaxItem, temp;
    if (IsEmpty(H)) {
        printf("最大堆已空");
        return 0;
    }
    MaxItem = H->Elements[1];   // 取出根节点，即最大值
    // 将最后一个元素取出，从上到下过滤结点
    temp = H->Elements[H->Size--];
    for (parent = 1; parent * 2 <= H->Size; parent = child)
    {/* 整个循环的功能就是从上到下找一个节点，这个节点的左右孩子都比他本身小。找这个节点的过程中，会将儿子中的较大的结点往上面提，即将较大child的值不断赋值给parent，因为第一个根结点是要被删除的（且这个值已经被保存），在不断过滤的过程中不会影响到整个堆的数据完整 */
        child = parent * 2;
        if ((child != H->Size) && (H->Elements[child] < H->Elements[child + 1]))
            child++;      // child更新为两个孩子中的较大者
        if (temp >= H->Elements[child])  // 如果temp的值大于两个孩子中的较大值，则说明调整结束
            break;
        else
            H->Elements[parent] = H->Elements[child];
    }
    H->Elements[parent] = temp;
    return MaxItem;
}

void ShowHeap(MaxHeap H, int size)
{
    for(int i = 1; i <= size; i++)
        cout << H->Elements[i] << " ";
}

