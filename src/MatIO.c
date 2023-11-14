#include "..\include\MatIO.h"
#include "..\include\MatConst.h"
#include <stdio.h>
#include <math.h>

/**
 * @brief   矩阵工具 – 矩阵输入
 * @param   matrix      矩阵
 * @return  SUCCESS – 输入成功
 * @return  BREAK – 输入中断
 * @note    输入矩阵matrix
 */
int matInput(Mat matrix)
{
    return matInLocal(matrix.address, 0, matrix.numRows - 1, 0, matrix.numCols - 1);
}

/**
 * @brief   矩阵工具 – 矩阵局部输入
 * @param   matAdd      矩阵地址
 * @param   rowStart    起始行
 * @param   rowEnd      终止行
 * @param   colStart    起始列
 * @param   colEnd      终止列
 * @return  SUCCESS – 输入成功
 * @return  BREAK – 输入中断
 * @note    输入矩阵的指定范围
 */
int matInLocal(double **matAdd, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    char ch;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            ungetc(ch = getchar(), stdin);
            if ((ch < '0' || ch > '9') && ch != ' ' && ch != '\n' && ch != '\t')
            {
                return BREAK;
            }
            scanf("%lf", &matAdd[i][j]);
        }
    }
    return SUCCESS;
}

/**
 * @brief   矩阵工具 – 矩阵输出
 * @param   matrix      矩阵
 * @note    输出矩阵matrix
 */
void matOutput(Mat matrix)
{
    matOutLocal(matrix.address, 0, matrix.numRows - 1, 0, matrix.numCols - 1);
}

/**
 * @brief   矩阵工具 – 矩阵局部输出
 * @param   matAdd      矩阵
 * @param   rowStart    起始行
 * @param   rowEnd      终止行
 * @param   colStart    起始列
 * @param   colEnd      终止列
 * @note    输出矩阵的指定范围
 */
void matOutLocal(double **matAdd, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            if (fabs(matAdd[i][j] - (int)matAdd[i][j]) < ZEROTHRES ||
                fabs(matAdd[i][j] - (int)matAdd[i][j] + 1) < ZEROTHRES ||
                fabs(matAdd[i][j] - (int)matAdd[i][j] - 1) < ZEROTHRES)
            {
                if (fabs(matAdd[i][j]) < 0.001)
                {
                    printf("%6d ", 0);
                }
                else
                {
                    printf("%6.0lf ", matAdd[i][j]);
                }
            }
            else
            {
                printf("%6.3lf ", matAdd[i][j]);
            }
        }
        putchar('\n');
    }
}