/**
 * @file    MaxInd.c
 * @brief   示例 – 极大线性无关组计算器
 */

#include "./include/MaxInd.h"
#include "../include/MatOper.h"   //求行最简形矩阵
#include "../include/MatUtil.h"   //初始化矩阵、释放矩阵存储空间
#include "../include/MatIO.h"     //矩阵局部输入、浮点数输出
#include "../include/MatStruct.h" //矩阵结构体
#include "../include/MatConst.h"  //零阈值、浮点数输出参数、函数返回状态码
#include <stdio.h>                //scanf,printf,getchar,putchar
#include <stdlib.h>               //malloc
#include <stdbool.h>              //bool,ture,false
#include <math.h>                 //fabs

// 清空输入缓冲区至'\n'
void static clear(void)
{
    while (getchar() != '\n')
        ;
}

// 暂停
void static pause(void)
{
    ungetc('0', stdin);
    printf("\n按回车键继续...");
    getchar();
    clear();
    putchar('\n');
}

void maxInd(void)
{
    int i = 0, j = 0, k = 0; // 循环计数器
    // 声明Mat类型的矩阵，用于以列向量形式存储向量组
    Mat matrix;
    int numRows = 0,      // 矩阵行数
        numCols = 0,      // 矩阵列数
        rank = 0;         // 矩阵的秩
    int *pivot = NULL;    // 用于存储主元所在列索引的动态数组
    bool isFirst = false; // 是第一个输出的向量，用于输出以极大线性无关组表示其他向量的表达式
    printf("极大线性无关组计算器\n\n");
    printf("向量维数: ");
    // 列向量维数是矩阵行数
    while (scanf("%d", &numRows) != 1)
    {
        clear();
        printf("向量维数: ");
    }
    clear();
    printf("向量个数: ");
    // 列向量个数是矩阵列数
    while (scanf("%d", &numCols) != 1)
    {
        clear();
        printf("向量个数: ");
    }
    clear();
    matInit(&matrix, numRows, numCols); // 初始化矩阵
    // 申请主元数组存储空间，元素数实际应当取rank，但为方便，取行列数中较小的一个即可
    pivot = (int *)malloc(sizeof(int) * (numRows < numCols ? numRows : numCols));
    // 输入向量组
    for (i = 0; i < numCols; i++)
    {
        printf("a%d: ", i + 1);
        // 调用矩阵局部输入，每次只输入矩阵的一列，即一个列向量
        // 使用返回状态码确认输入状态，如果输入中断则重新输入
        while (matInLocal(matrix.data, 0, numRows - 1, i, i) == BREAK)
        {
            printf("a%d: ", i + 1);
            clear();
        }
        clear();
    }
    // 将matrix通过初等行变换化成行最简形
    // 此处不需要保留matrix的原始数据，因此可以向source和target都传入matrix
    matRedEche(matrix, matrix, false);
    // 给主元数组pivot赋值，同时求得系数矩阵的秩rank
    // 例如，5行6列的矩阵第0、2、3列是主元所在列，则pivot为{0,2,3,*,*}，'*'代表无效数据
    for (rank = 0, i = 0; rank < numRows && i < numCols; i++)
    {
        // 判断浮点数是否为0可以使用MatConst.h中的ZEROTHRES，便于统一控制
        if (fabs(matrix.data[rank][i]) > ZEROTHRES)
        {
            pivot[rank] = i;
            rank++;
        }
    }
    // 输出极大线性无关组
    printf("\n极大线性无关组:");
    for (i = 0; i < rank; i++)
    {
        printf(" a%d", pivot[i] + 1);
    }
    putchar('\n');
    // 输出以极大线性无关组表示其他向量的表达式
    // 此处逻辑较复杂，且与库本身的应用关系不大，可以略过
    for (i = 0, j = 0; i < numCols; i++)
    {
        if (j == rank || pivot[j] != i)
        {
            printf("a%d = ", i + 1);
            isFirst = true;
            for (k = 0; k < rank; k++)
            {
                if (fabs(matrix.data[k][i]) > ZEROTHRES)
                {
                    if (isFirst)
                    {
                        isFirst = false;
                        if (matrix.data[k][i] < 0)
                        {
                            printf("- ");
                        }
                    }
                    else if (matrix.data[k][i] > 0)
                    {
                        printf(" + ");
                    }
                    else
                    {
                        printf(" - ");
                    }
                    if (fabs(fabs(matrix.data[k][i]) - 1) > ZEROTHRES)
                    {
                        // 为统一浮点数输出精度，调用浮点数输出函数，传入MatConst.h中的PRECISION
                        // 无需控制宽度，因此向width传入0
                        // 因为已经输出了正负号，在这里只需输出绝对值，因此向isAbs传入true
                        prtDouble(matrix.data[k][i], PRECISION, 0, true);
                        putchar(' ');
                    }
                    printf("a%d", pivot[k] + 1);
                }
            }
            putchar('\n');
        }
        else
        {
            j++;
        }
    }
    matFree(&matrix); // 释放矩阵存储空间
    free(pivot);      // 释放动态数组存储空间
    pause();
}