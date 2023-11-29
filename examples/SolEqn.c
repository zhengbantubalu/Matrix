/**
 * @file    SolEqn.c
 * @brief   示例 – 求解线性方程组
 */

#include "./include/SolEqn.h"
#include "../include/MatOper.h"   //求行最简形矩阵、求矩阵的秩
#include "../include/MatUtil.h"   //初始化矩阵、释放矩阵存储空间
#include "../include/MatIO.h"     //矩阵输入、浮点数输出
#include "../include/MatStruct.h" //矩阵结构体
#include "../include/MatConst.h"  //零阈值、浮点数输出参数、函数返回状态码
#include <stdio.h>                //scanf,printf,getchar,putchar,ungetc
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

void solEqn(void)
{
    int i = 0, j = 0, k = 0, l = 0, m = 0; // 循环计数器
    // 声明Mat类型的矩阵，用于存储增广矩阵
    Mat matrix;
    int numRows = 0,        // 矩阵行数
        numCols = 0,        // 矩阵列数
        rankCof = 0,        // 系数矩阵的秩
        rankAug = 0;        // 增广矩阵的秩
    int *pivot = NULL;      // 用于存储主元所在列索引的动态数组
    bool isHomo = false,    // 是齐次线性方程组
        isFullRank = false; // 系数矩阵是列满秩矩阵，即n=r
    printf("求解线性方程组\n\n");
    printf("未知数个数: ");
    // 未知数个数是系数矩阵的列数
    while (scanf("%d", &numCols) != 1)
    {
        clear();
        printf("未知数个数: ");
    }
    clear();
    printf("方程个数: ");
    // 方程个数是系数矩阵的行数
    while (scanf("%d", &numRows) != 1)
    {
        clear();
        printf("方程个数: ");
    }
    clear();
    numCols++; // 增广矩阵的列数是系数矩阵列数+1
    // 初始化增广矩阵
    matInit(&matrix, numRows, numCols);
    // 申请主元数组存储空间，元素数实际应当取rankCof，但为方便，取行列数中较小的一个即可
    pivot = (int *)malloc(sizeof(int) * (numRows < numCols ? numRows : numCols));
    printf("请输入增广矩阵:\n");
    // 输入增广矩阵，若返回状态码为成功则继续，否则显示输入中断
    if (matInput(matrix) == SUCCESS)
    {
        putchar('\n');
        // 遍历最后一列，以判断方程组是否是齐次线性方程组
        for (i = 0, isHomo = true; i < numRows && isHomo == true; i++)
        {
            // 判断浮点数是否为0可以使用MatConst.h中的ZEROTHRES，便于统一控制
            if (fabs(matrix.data[i][numCols - 1]) > ZEROTHRES)
            {
                isHomo = false;
            }
        }
        // 将matrix通过初等行变换化成行最简形
        // 此处不需要保留matrix的原始数据，因此可以向source和target都传入matrix
        matRedEche(matrix, matrix, false);
        // 给主元数组pivot赋值，同时求得系数矩阵的秩rankCof
        // 例如，5行6列的矩阵第0、2、3列是主元所在列，则pivot为{0,2,3,*,*}，'*'代表无效数据
        for (rankCof = 0, i = 0; rankCof < numRows && i < numCols - 1; i++)
        {
            if (fabs(matrix.data[rankCof][i]) > ZEROTHRES)
            {
                pivot[rankCof] = i;
                rankCof++;
            }
        }
        isFullRank = (rankCof == numCols - 1); // 记录系数矩阵是否列满秩，后面会多次用到
        // 是齐次线性方程组且系数矩阵列满秩，则方程组只有零解
        if (isHomo && isFullRank)
        {
            printf("通解:\nξ = 0\n");
            matFree(&matrix);
            clear();
            pause();
            return;
        }
        // 如果是非齐次线性方程组，则先求出其特解
        if (!isHomo)
        {
            // 求增广矩阵的秩，因为此前已经将matrix化成行最简形，行最简形也是行阶梯形，所以向isEche传入true
            matRank(matrix, true, &rankAug);
            // 系数矩阵的秩小于增广矩阵的秩，则方程组无解
            if (rankCof < rankAug)
            {
                printf("方程组无解\n");
                matFree(&matrix);
                clear();
                pause();
                return;
            }
            // 求出一个特解，这里所有自由未知量都取0
            // 此处逻辑较复杂，且与库本身的应用关系不大，可以略过
            else
            {
                printf("特解:\nη* = ( ");
                j = 0;
                if (pivot[0] == 0)
                {
                    // 为使浮点数输出对齐，调用浮点数输出函数
                    // 可以传入MatConst.h中的参数PRECISION和WIDTH，也可以自定义
                    prtDouble(matrix.data[0][numCols - 1], PRECISION, WIDTH, false);
                    putchar(' ');
                    j++;
                }
                else
                {
                    prtDouble(0, 0, WIDTH, false);
                    putchar(' ');
                }
                for (i = 1; i < numCols - 1; i++)
                {
                    if (j < rankCof && pivot[j] == i)
                    {
                        printf(", ");
                        prtDouble(matrix.data[j][numCols - 1], PRECISION, WIDTH, false);
                        putchar(' ');
                        j++;
                    }
                    else
                    {
                        printf(", ");
                        prtDouble(0, 0, WIDTH, false);
                        putchar(' ');
                    }
                }
                printf(")T\n");
                // 如果非齐次线性方程组的系数矩阵不列满秩，则还需要求导出组的基础解系
                // 这部分和求齐次线性方程组的基础解系完全一致，所以合并到一起操作
                // 在这里多输出“导出组的”四个字，与后面的“基础解系”合并，可以组成“导出组的基础解系”
                if (!isFullRank)
                {
                    printf("导出组的");
                }
            }
        }
        // 求齐次线性方程组的基础解系，或非齐次线性方程组导出组的基础解系
        // 这里分别取自由未知量为(1,0,...,0),(0,1,0,...,0),...,(0,...,0,1)
        // 此处逻辑较复杂，且与库本身的应用关系不大，可以略过
        if (!isFullRank)
        {
            printf("基础解系:\n");
        }
        for (i = pivot[0], j = 0, m = 1; i < numCols - 1; i++)
        {
            if (j == rankCof || pivot[j] != i)
            {
                printf("ξ%d = ( ", m);
                l = 0;
                if (pivot[0] == 0)
                {
                    prtDouble(-matrix.data[0][i], PRECISION, WIDTH, false);
                    putchar(' ');
                    l++;
                }
                else
                {
                    prtDouble(0, 0, WIDTH, false);
                    putchar(' ');
                }
                for (k = 1; k < numCols - 1; k++)
                {
                    if (l < rankCof && pivot[l] == k && k != i)
                    {
                        printf(", ");
                        prtDouble(-matrix.data[l][i], PRECISION, WIDTH, false);
                        putchar(' ');
                        l++;
                    }
                    else if (k == i)
                    {
                        printf(", ");
                        prtDouble(1, 0, WIDTH, false);
                        putchar(' ');
                    }
                    else
                    {
                        printf(", ");
                        prtDouble(0, 0, WIDTH, false);
                        putchar(' ');
                    }
                }
                printf(")T\n");
                m++;
            }
            else
            {
                j++;
            }
        }
        // 输出通解
        if (!isHomo)
        {
            printf("通解:\nη = η*");
            if (!isFullRank)
            {
                printf(" + k1ξ1");
            }
        }
        else
        {
            printf("通解:\nξ = k1ξ1");
        }
        for (i = 2; i < m; i++)
        {
            printf(" + k%dξ%d", i, i);
        }
        putchar('\n');
    }
    else
    {
        printf("\n输入中断\n");
    }
    matFree(&matrix); // 释放矩阵存储空间
    free(pivot);      // 释放动态数组存储空间
    clear();
    pause();
}