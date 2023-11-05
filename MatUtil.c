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
 * @return  ERROR – 行列数不匹配
 * @note    将矩阵matSource的指定范围复制到矩阵matTarget的指定范围
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
 * @brief   矩阵工具 – 赋值为单位矩阵
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @note    将矩阵matrix赋值为单位矩阵，矩阵行列数须相等
 */
void matAssignE(double **matrix, int numRows)
{
    int i = 0, j = 0;
    for (i = 0; i < numRows; i++)
    {
        for (j = 0; j < numRows; j++)
        {
            matrix[i][j] = i == j ? 1 : 0;
        }
    }
}