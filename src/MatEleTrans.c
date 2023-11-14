#include "..\include\MatEleTrans.h"
#include <stdlib.h>

/**
 * @brief   矩阵初等变换 – 对换变换
 * @param   matrix      矩阵
 * @param   index1      目标1行索引
 * @param   index2      目标2行索引
 * @param   isRow       为真则行变换，为假则列变换
 * @note    将矩阵matrix的第index1行与第index2行对换(列变换同理)
 */
void matEleSwap(Mat matrix, int index1, int index2, bool isRow)
{
    int i = 0;
    double *tempArr = NULL;
    if (isRow)
    {
        tempArr = (double *)malloc(sizeof(double) * matrix.numCols);
        for (i = 0; i < matrix.numCols; i++)
        {
            tempArr[i] = matrix.address[index1][i];
            matrix.address[index1][i] = matrix.address[index2][i];
            matrix.address[index2][i] = tempArr[i];
        }
    }
    else
    {
        tempArr = (double *)malloc(sizeof(double) * matrix.numRows);
        for (i = 0; i < matrix.numRows; i++)
        {
            tempArr[i] = matrix.address[i][index1];
            matrix.address[i][index1] = matrix.address[i][index2];
            matrix.address[i][index2] = tempArr[i];
        }
    }
    free(tempArr);
    tempArr = NULL;
}

/**
 * @brief   矩阵初等变换 – 数乘变换
 * @param   matrix      矩阵
 * @param   index       目标行索引
 * @param   multer      数乘倍数
 * @param   isRow       为真则行变换，为假则列变换
 * @note    将矩阵matrix第index行乘以multer(列变换同理)
 */
void matEleScaMul(Mat matrix, int index, double multer, bool isRow)
{
    int i = 0;
    if (isRow)
    {
        for (i = 0; i < matrix.numCols; i++)
        {
            matrix.address[index][i] *= multer;
        }
    }
    else
    {
        for (i = 0; i < matrix.numRows; i++)
        {
            matrix.address[i][index] *= multer;
        }
    }
}

/**
 * @brief   矩阵初等变换 – 倍加变换
 * @param   matrix      矩阵
 * @param   indexS      源行索引
 * @param   indexT      目标行索引
 * @param   multer      数乘倍数
 * @param   isRow       为真则行变换，为假则列变换
 * @note    将矩阵matrix第indexS行的multer倍加到第indexT行上(列变换同理)
 */
void matEleAdd(Mat matrix, int indexS, int indexT, double multer, bool isRow)
{
    int i = 0;
    if (isRow)
    {
        for (i = 0; i < matrix.numCols; i++)
        {
            matrix.address[indexT][i] += matrix.address[indexS][i] * multer;
        }
    }
    else
    {
        for (i = 0; i < matrix.numRows; i++)
        {
            matrix.address[i][indexT] += matrix.address[i][indexS] * multer;
        }
    }
}