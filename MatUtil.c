#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "MatUtil.h"

/**
 * @brief   矩阵工具 – 矩阵初始化
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @return  矩阵地址
 * @note    申请矩阵的存储空间，并赋值为零矩阵
 */
double **matInit(int numRows, int numCols)
{
    int i = 0, j = 0;
    double **matrix = (double **)malloc(sizeof(double *) * numRows);
    for (i = 0; i < numRows; i++)
    {
        matrix[i] = (double *)malloc(sizeof(double) * numCols);
        for (j = 0; j < numCols; j++)
        {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

/**
 * @brief   矩阵工具 – 矩阵存储空间释放
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @note    释放矩阵matrix的存储空间
 */
void matFree(double **matrix, int numRows)
{
    int i = 0;
    for (i = 0; i < numRows; i++)
    {
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);
}

/**
 * @brief   矩阵工具 – 矩阵整体输入
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @note    输入矩阵matrix
 */
void matEnIn(double **matrix, int numRows, int numCols)
{
    matLoIn(matrix, 0, numRows - 1, 0, numCols - 1);
}

/**
 * @brief   矩阵工具 – 矩阵局部输入
 * @param   matrix      矩阵地址
 * @param   rowStart    起始行
 * @param   rowEnd      终止行
 * @param   colStart    起始列
 * @param   colEnd      终止列
 * @note    输入矩阵matrix的指定范围
 */
void matLoIn(double **matrix, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            scanf("%lf", &matrix[i][j]);
        }
    }
}

/**
 * @brief   矩阵工具 – 矩阵整体输出
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @note    输出矩阵matrix
 */
void matEnOut(double **matrix, int numRows, int numCols)
{
    matLoOut(matrix, 0, numRows - 1, 0, numCols - 1);
}

/**
 * @brief   矩阵工具 – 矩阵局部输出
 * @param   matrix      矩阵地址
 * @param   rowStart    起始行
 * @param   rowEnd      终止行
 * @param   colStart    起始列
 * @param   colEnd      终止列
 * @note    输出矩阵matrix的指定范围
 */
void matLoOut(double **matrix, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            if (fabs(matrix[i][j] - (int)matrix[i][j]) < ZEROTHRES ||
                fabs(matrix[i][j] - (int)matrix[i][j] + 1) < ZEROTHRES ||
                fabs(matrix[i][j] - (int)matrix[i][j] - 1) < ZEROTHRES)
            {
                if (fabs(matrix[i][j]) < 0.001)
                {
                    printf("%6d ", 0);
                }
                else
                {
                    printf("%6.0lf ", matrix[i][j]);
                }
            }
            else
            {
                printf("%6.3lf ", matrix[i][j]);
            }
        }
        putchar('\n');
    }
}

/**
 * @brief   矩阵工具 – 矩阵整体复制
 * @param   matSource   源矩阵地址
 * @param   matTarget   目标矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @note    将矩阵matSource复制到矩阵matTarget，源矩阵与目标矩阵行列数须相等
 */
void matEnCopy(double **matSource, double **matTarget, int numRows, int numCols)
{
    if (matSource != matTarget)
    {
        matLoCopy(matSource, matTarget, 0, numRows - 1, 0, numRows - 1, 0, numCols - 1, 0, numCols - 1);
    }
}

/**
 * @brief   矩阵工具 – 矩阵局部复制
 * @param   matSource   源矩阵地址
 * @param   matTarget   目标矩阵地址
 * @param   rowSouStart 源矩阵起始行
 * @param   rowSouEnd   源矩阵终止行
 * @param   rowTarStart 目标矩阵起始行
 * @param   rowTarEnd   目标矩阵终止行
 * @param   colSouStart 源矩阵起始列
 * @param   colSouEnd   源矩阵终止列
 * @param   colTarStart 目标矩阵起始列
 * @param   colTarEnd   目标矩阵终止列
 * @return  SUCCESS – 复制成功
 * @return  ERROR – 范围行列数不相等
 * @note    将矩阵matSource的指定范围复制到矩阵matTarget的指定范围，两矩阵范围行列数须相等
 */
int matLoCopy(double **matSource, double **matTarget,
              int rowSouStart, int rowSouEnd, int rowTarStart, int rowTarEnd,
              int colSouStart, int colSouEnd, int colTarStart, int colTarEnd)
{
    int i = 0, j = 0;
    if (rowSouEnd - rowSouStart != rowTarEnd - rowTarStart ||
        colSouEnd - colSouStart != colTarEnd - colTarStart)
    {
        return ERROR;
    }
    for (i = 0; i <= rowSouEnd - rowSouStart; i++)
    {
        for (j = 0; j <= colSouEnd - colSouStart; j++)
        {
            matTarget[i + rowTarStart][j + colTarStart] = matSource[i + rowSouStart][j + colSouStart];
        }
    }
    return SUCCESS;
}

/**
 * @brief   矩阵工具 – 矩阵整体相等判断
 * @param   matrix1     矩阵1地址
 * @param   matrix2     矩阵2地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @return  EQUAL – 两矩阵相等
 * @return  UNEQUAL – 两矩阵不相等
 * @note    判断矩阵matrix1与矩阵matrix2是否相等，两矩阵行列数须相等
 */
int matEnEqual(double **matrix1, double **matrix2, int numRows, int numCols)
{
    return matLoEqual(matrix1, matrix2, 0, numRows - 1, 0, numRows - 1, 0, numCols - 1, 0, numCols - 1);
}

/**
 * @brief   矩阵工具 – 矩阵局部相等判断
 * @param   matrix1     矩阵1地址
 * @param   matrix2     矩阵2地址
 * @param   rowStart1   矩阵1起始行
 * @param   rowEnd1     矩阵1终止行
 * @param   rowStart2   矩阵2起始行
 * @param   rowEnd2     矩阵2终止行
 * @param   colStart1   矩阵1起始列
 * @param   colEnd1     矩阵1终止列
 * @param   colStart2   矩阵2起始列
 * @param   colEnd2     矩阵2终止列
 * @return  EQUAL – 两矩阵范围相等
 * @return  UNEQUAL – 两矩阵范围不相等
 * @return  ERROR – 范围行列数不相等
 * @note    判断矩阵matrix1与矩阵matrix2指定范围是否相等，两矩阵范围行列数须相等
 */
int matLoEqual(double **matrix1, double **matrix2,
               int rowStart1, int rowEnd1, int rowStart2, int rowEnd2,
               int colStart1, int colEnd1, int colStart2, int colEnd2)
{
    int i = 0, j = 0;
    if (rowEnd1 - rowStart1 != rowEnd2 - rowStart2 ||
        colEnd1 - colStart1 != colEnd2 - colStart2)
    {
        return ERROR;
    }
    for (i = 0; i <= rowEnd1 - rowStart1; i++)
    {
        for (j = 0; j <= colEnd1 - colStart1; j++)
        {
            if ((matrix1[i + rowStart1][j + colStart1] - matrix2[i + rowStart2][j + colStart2]) > ZEROTHRES)
            {
                return UNEQUAL;
            }
        }
    }
    return EQUAL;
}

/**
 * @brief   矩阵工具 – 整体赋值为单位矩阵
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @note    将矩阵matrix赋值为单位矩阵，矩阵行列数须相等
 */
void matEnAssignE(double **matrix, int numRows)
{
    matLoAssignE(matrix, 0, numRows - 1, 0, numRows - 1);
}

/**
 * @brief   矩阵工具 – 局部赋值为单位矩阵
 * @param   matrix      矩阵地址
 * @param   rowStart    起始行
 * @param   rowEnd      终止行
 * @param   colStart    起始列
 * @param   colEnd      终止列
 * @return  SUCCESS – 赋值成功
 * @return  ERROR – 范围行列数不相等
 * @note    将矩阵matrix的指定范围赋值为单位矩阵，范围行列数须相等
 */
int matLoAssignE(double **matrix, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    if (rowEnd - rowStart != colEnd - colStart)
    {
        return ERROR;
    }
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            matrix[i][j] = (i - rowStart) == (j - colStart) ? 1 : 0;
        }
    }
    return SUCCESS;
}