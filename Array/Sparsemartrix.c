/*
 * 矩阵的压缩存储
 * 稀疏矩阵的三元组表示方法和转置的操作
 */

#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define SMAX 101                                                      //允许的最大非零元素的个数为100

typedef int elementype;
typedef int status;

typedef struct
{
    int i, j;                                                         //非零元素的行号和列号
    elementype v;                                                     //元素的值（value）
}triple;

typedef struct
{
    int mu, nu, tu;                                                   //矩阵的行数、列数和非零元素个数
    triple data[SMAX];                                                //非零元素三元组表
}spmatrix;

spmatrix create_trix(spmatrix a)                                      //原谅我特别懒，不像一个个输入，只能构造生成函数啦
{
    srand((unsigned)time(NULL));
    int data[a.mu][a.nu], i, j;
    int sign;
    int count = 0;
    printf("打印原矩阵a的三元组表示方式：\n");
    printf("%2d\t%2d\t%2d\n", a.mu, a.nu, a.tu);
    for(i = 0; i < a.mu; i++)
    {
        for(j = 0; j < a.nu; j++)
        {
            sign = rand()%10 - 5;                                     //生成随机数字，用来随机产生零或者大于零的元素
            if(sign > 0 && count < a.tu)                              //达到随机不寒生零和非零的目的
            {
                data[i][j] = rand() % 50;                             //随机的元素，但也可能是零，这样尽可能提高零元素的个数
                a.data[count+1].v = data[i][j];
                a.data[count+1].i = i + 1;
                a.data[count+1].j = j + 1;
                printf("%2d\t%2d\t%2d\n", a.data[count+1].i, a.data[count+1].j,a.data[count+1].v);
                count++;
            }
            else
                data[i][j] = 0;
        }
    }
    return a;
}

spmatrix transmat(spmatrix a, spmatrix b)
{
    int col, p, q, t;                                                 //col表示按照b的行顺序（a的列顺序）作为转置的循环变量
    b.mu = a.nu;                                                      //p作为a.data[p]的索引
    b.nu = a.mu;                                                      //q作为b.data[q]的索引
    b.tu = a.tu;
    t = a.tu;
    if(t)
    {
        printf("打印转置矩阵b的三元组表示方式：\n");
        printf("%2d\t%2d\t%2d\n", b.mu, b.nu, b.tu);
        q = 1;
        for(col = 1; col <= a.nu; col++)                              //按照b的行序号进行转置操作
        {
            for(p = 1; p <= a.tu; p++)                                //将a中列序号为col的元素依次赋值给b
            {
                if(a.data[p].j == col)
                {
                    b.data[q].i = a.data[p].j;
                    b.data[q].j = a.data[p].i;
                    b.data[q].v = a.data[p].v;
                    printf("%2d\t%2d\t%2d\n", b.data[q].i, b.data[q].j, b.data[q].v);
                    q++;
                }
            }
        }
    }
    return b;
}

int main()
{
    srand((unsigned)time(NULL));
    spmatrix a, b;
    a.mu = 6;
    a.nu = 6;
    a.tu = 8;
    a = create_trix(a);
    b = transmat(a, b);
}
