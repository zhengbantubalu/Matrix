#include "MatHead.h"

/**
 * @brief   矩阵初等变换 – 对换变换
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @param   index1      目标1行索引
 * @param   index2      目标2行索引
 * @param   isRowOper   为真表示行变换，为假表示列变换
 * @note    将矩阵matrix第index1行与第index2行对换(列变换同理)
 */
void matRowSwap(double **matrix, int numRows, int numCols, int index1, int index2, bool isRowOper)
{
    int i = 0;
    double *tempArr = NULL;
    if (isRowOper)
    {
        tempArr = (double *)malloc(sizeof(double) * numCols);
        for (i = 0; i < numCols; i++)
        {
            tempArr[i] = matrix[index1][i];
            matrix[index1][i] = matrix[index2][i];
            matrix[index2][i] = tempArr[i];
        }
    }
    else
    {
        tempArr = (double *)malloc(sizeof(double) * numRows);
        for (i = 0; i < numRows; i++)
        {
            tempArr[i] = matrix[i][index1];
            matrix[i][index1] = matrix[i][index2];
            matrix[i][index2] = tempArr[i];
        }
    }
    free(tempArr);
    tempArr = NULL;
}

/**
 * @brief   矩阵初等变换 – 数乘变换
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @param   index       目标行索引
 * @param   multiplier  数乘倍数
 * @param   isRowOper   为真表示行变换，为假表示列变换
 * @note    将矩阵matrix第index行乘以multiplier(列变换同理)
 */
void matRowScaMul(double **matrix, int numRows, int numCols, int index, double multiplier, bool isRowOper)
{
    int i = 0;
    if (isRowOper)
    {
        for (i = 0; i < numCols; i++)
        {
            matrix[index][i] *= multiplier;
        }
    }
    else
    {
        for (i = 0; i < numRows; i++)
        {
            matrix[i][index] *= multiplier;
        }
    }
}

/**
 * @brief   矩阵初等变换 – 倍加变换
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @param   indexSource 源行索引
 * @param   indexTarget 目标行索引
 * @param   multiplier  数乘倍数
 * @param   isRowOper   为真表示行变换，为假表示列变换
 * @note    将矩阵matrix第indexSource行的multiplier倍加到第indexTarget行上(列变换同理)
 */
void matRowAdd(double **matrix, int numRows, int numCols,
               int indexSource, int indexTarget, double multiplier, bool isRowOper)
{
    int i = 0;
    if (isRowOper)
    {
        for (i = 0; i < numCols; i++)
        {
            matrix[indexTarget][i] += matrix[indexSource][i] * multiplier;
        }
    }
    else
    {
        for (i = 0; i < numRows; i++)
        {
            matrix[i][indexTarget] += matrix[i][indexSource] * multiplier;
        }
    }
}