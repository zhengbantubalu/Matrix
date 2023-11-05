#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "MatOper.h"
#include "MatRowOper.h"
#include "MatUtil.h"

/**
 * @brief   矩阵运算 – 矩阵加法
 * @param   matSource1  源矩阵1地址
 * @param   matSource2  源矩阵2地址
 * @param   matTarget   目标矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @note    将矩阵matSource1与矩阵matSource2的和赋值给矩阵matTarget，三矩阵须同型
 */
void matAdd(double **matSource1, double **matSource2, double **matTarget, int numRows, int numCols)
{
    int i = 0, j = 0;
    for (i = 0; i < numRows; i++)
    {
        for (j = 0; j < numCols; j++)
        {
            matTarget[i][j] = matSource1[i][j] + matSource2[i][j];
        }
    }
}

/**
 * @brief   矩阵运算 – 矩阵减法
 * @param   matMinu     被减矩阵地址
 * @param   matSub      减矩阵地址
 * @param   matTarget   目标矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @note    将矩阵matMinu减矩阵matSub的差赋值给矩阵matTarget，三矩阵须同型
 */
void matSub(double **matMinu, double **matSub, double **matTarget, int numRows, int numCols)
{
    int i = 0, j = 0;
    for (i = 0; i < numRows; i++)
    {
        for (j = 0; j < numCols; j++)
        {
            matTarget[i][j] = matMinu[i][j] - matSub[i][j];
        }
    }
}

/**
 * @brief   矩阵运算 – 矩阵数乘
 * @param   matSource   源矩阵地址
 * @param   matTarget   目标矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @param   multiplier  数乘倍数
 * @note    将矩阵matSource的multiplier倍赋值给矩阵matTarget，两矩阵须同型
 */
void matScaMul(double **matSource, double **matTarget, int numRows, int numCols, double multiplier)
{
    int i = 0, j = 0;
    for (i = 0; i < numRows; i++)
    {
        for (j = 0; j < numCols; j++)
        {
            matTarget[i][j] = matSource[i][j] * multiplier;
        }
    }
}

/**
 * @brief   矩阵运算 – 矩阵乘法
 * @param   matLeft     左矩阵地址
 * @param   matRight    右矩阵地址
 * @param   matTarget   目标矩阵地址
 * @param   numRowsL    左矩阵行数
 * @param   numColsL    左矩阵列数
 * @param   numColsR    右矩阵列数
 * @note    将矩阵matLeft与矩阵matRight的积赋值给矩阵matTarget，matLeft列数须等于matSouRight行数，
 *          matTarget行数须等于matLeft行数，matTarget列数须等于matRight列数
 */
void matMul(double **matLeft, double **matRight, double **matTarget,
            int numRowsL, int numColsL, int numColsR)
{
    int i = 0, j = 0, k = 0;
    double tempS = 0;
    for (i = 0; i < numRowsL; i++)
    {
        for (j = 0; j < numColsR; j++)
        {
            for (k = 0, tempS = 0; k < numColsL; k++)
            {
                tempS += matLeft[i][k] * matRight[k][j];
            }
            matTarget[i][j] = tempS;
        }
    }
}

/**
 * @brief   矩阵运算 – 求转置矩阵
 * @param   matSource   源矩阵地址
 * @param   matTarget   目标矩阵地址
 * @param   numRows     源矩阵行数
 * @param   numCols     源矩阵列数
 * @note    将矩阵matSource的转置赋值给矩阵matTarget，
 *          matSource行数须等于matTarget列数，matSource列数须等于matTarget行数
 */
void matTrans(double **matSource, double **matTarget, int numRows, int numCols)
{
    int i = 0, j = 0;
    for (i = 0; i < numRows; i++)
    {
        for (j = 0; j < numCols; j++)
        {
            matTarget[j][i] = matSource[i][j];
        }
    }
}

/**
 * @brief   矩阵运算 – 求逆矩阵
 * @param   matSource   源矩阵地址
 * @param   matTarget   目标矩阵地址
 * @param   numRows     矩阵行数
 * @return  SUCCESS – 求逆矩阵成功
 * @return  SINGULAR – 矩阵不可逆
 * @note    将矩阵matSource的逆矩阵赋值给矩阵matTarget，矩阵行列数须相等
 */
int matInverse(double **matSource, double **matTarget, int numRows)
{
    int i = 0, j = 0;
    double **matOper = NULL, **matE = NULL;
    matOper = matInit(numRows, 2 * numRows);
    matLoCopy(matSource, matOper, 0, numRows - 1, 0, numRows - 1, 0, numRows - 1, 0, numRows - 1);
    matE = matInit(numRows, numRows);
    matAssignE(matE, numRows);
    matLoCopy(matE, matOper, 0, numRows - 1, 0, numRows - 1, 0, numRows - 1, numRows, 2 * numRows - 1);
    matFree(matE, numRows);
    matE = NULL;
    if (fabs(matEchelon(matOper, matOper, numRows, 2 * numRows)) < ZEROTHRES)
    {
        return SINGULAR;
    }
    matRedEche(matOper, matOper, numRows, 2 * numRows, true);
    matLoCopy(matOper, matTarget, 0, numRows - 1, 0, numRows - 1, numRows, 2 * numRows - 1, 0, numRows - 1);
    matFree(matOper, numRows);
    matOper = NULL;
    return SUCCESS;
}

/**
 * @brief   矩阵运算 – 求伴随矩阵
 * @param   matSource   源矩阵地址
 * @param   matTarget   目标矩阵地址
 * @param   numRows     矩阵行数
 * @note    将矩阵matSource的伴随矩阵赋值给矩阵matTarget，矩阵行列数须相等
 */
void matAdj(double **matSource, double **matTarget, int numRows)
{
    int i = 0, j = 0;
    if (matInverse(matSource, matTarget, numRows) == SUCCESS)
    {
        matScaMul(matTarget, matTarget, numRows, numRows, matDet(matSource, numRows));
    }
    else
    {
        for (i = 0; i < numRows; i++)
        {
            for (j = 0; j < numRows; j++)
            {
                matTarget[i][j] = matAlgMin(matSource, numRows, j, i);
            }
        }
    }
}

/**
 * @brief   矩阵运算 – 求行阶梯形矩阵
 * @param   matSource   源矩阵地址
 * @param   matTarget   目标矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @return  如果源矩阵为方阵，则返回值为行列式
 * @note    将矩阵matSource的行阶梯形赋值给矩阵matTarget，两矩阵须为同型方阵
 */
double matEchelon(double **matSource, double **matTarget, int numRows, int numCols)
{
    int i = 0, j = 0, tempI = 0, echelon = 0;
    double det = 1;
    bool nonZero = false;
    matEnCopy(matSource, matTarget, numRows, numCols);
    while (i < numRows && i + echelon < numCols)
    {
        nonZero = true;
        if (fabs(matTarget[i][i + echelon]) <= ZEROTHRES)
        {
            nonZero = false;
            for (tempI = i + 1; tempI < numRows && !nonZero; tempI++)
            {
                if (fabs(matTarget[tempI][i + echelon]) > ZEROTHRES)
                {
                    matRowSwap(matTarget, numRows, numCols, i, tempI, true);
                    nonZero = true;
                }
            }
            if (!nonZero)
            {
                det = 0;
                echelon++;
            }
        }
        if (nonZero)
        {
            det *= matTarget[i][i + echelon];
            matRowScaMul(matTarget, numRows, numCols, i, 1 / matTarget[i][i + echelon], true);
            for (j = i + 1; j < numRows; j++)
            {
                matRowAdd(matTarget, numRows, numCols, i, j, -matTarget[j][i + echelon], true);
            }
            i++;
        }
    }
    return det;
}

/**
 * @brief   矩阵运算 – 求行最简形矩阵
 * @param   matSource   源矩阵地址
 * @param   matTarget   目标矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @param   isEche      matSource是否为行阶梯形矩阵
 * @note    将矩阵matSource的行最简形赋值给矩阵matTarget，两矩阵须同型
 */
void matRedEche(double **matSource, double **matTarget, int numRows, int numCols, bool isEche)
{
    int i = 0, j = 0, k = 0;
    bool operated = false;
    if (isEche)
    {
        matEnCopy(matSource, matTarget, numRows, numCols);
    }
    else
    {
        matEchelon(matSource, matTarget, numRows, numCols);
    }
    for (i = numRows - 1; i >= 0; i--)
    {
        for (j = 0, operated = false; j < numCols && !operated; j++)
        {
            if (fabs(matTarget[i][j]) > ZEROTHRES)
            {
                if (fabs(matTarget[i][j] - 1) > ZEROTHRES)
                {
                    matRowScaMul(matTarget, numRows, numCols, i, 1 / matTarget[i][j], true);
                }
                for (k = i - 1; k >= 0; k--)
                {
                    matRowAdd(matTarget, numRows, numCols, i, k, -matTarget[k][j], true);
                }
                operated = true;
            }
        }
    }
}

/**
 * @brief   矩阵运算 – 求矩阵的秩
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @param   isEche      matSource是否为行阶梯形矩阵
 * @return  矩阵的秩
 * @note    求矩阵matrix的秩
 */
int matRank(double **matrix, int numRows, int numCols, bool isEche)
{
    int rank = numRows, i = 0, j = 0;
    bool hasNonZero = false;
    double **matOper = NULL;
    if (isEche)
    {
        for (i = numRows - 1; i >= 0 && !hasNonZero; i--)
        {
            for (j = 0; j < numCols && !hasNonZero; j++)
            {
                if (fabs(matrix[i][j]) > ZEROTHRES)
                {
                    hasNonZero = true;
                }
            }
            if (!hasNonZero)
            {
                rank--;
            }
        }
    }
    else
    {
        matOper = matInit(numRows, numCols);
        matEchelon(matrix, matOper, numRows, numCols);
        for (i = numRows - 1; i >= 0 && !hasNonZero; i--)
        {
            for (j = 0; j < numCols && !hasNonZero; j++)
            {
                if (fabs(matOper[i][j]) > ZEROTHRES)
                {
                    hasNonZero = true;
                }
            }
            if (!hasNonZero)
            {
                rank--;
            }
        }
        matFree(matOper, numRows);
        matOper = NULL;
    }
    return rank;
}

/**
 * @brief   矩阵运算 – 求矩阵的行列式
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @return  矩阵的行列式
 * @note    求矩阵matrix的行列式，矩阵须为方阵
 */
double matDet(double **matrix, int numRows)
{
    double det = 0;
    double **matOper = matInit(numRows, numRows);
    det = matEchelon(matrix, matOper, numRows, numRows);
    matFree(matOper, numRows);
    matOper = NULL;
    return det;
}

/**
 * @brief   矩阵运算 – 求元素的余子式
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @param   indexRow    元素行索引
 * @param   indexCol    元素列索引
 * @return  矩阵对应元素的余子式
 * @note    求矩阵matrix第indexRow行第indexCol列的余子式，矩阵须为方阵
 */
double matMinor(double **matrix, int numRows, int indexRow, int indexCol)
{
    double minor = 0;
    double **matOper = matInit(numRows - 1, numRows - 1);
    matLoCopy(matrix, matOper, 0, indexRow - 1, 0, indexRow - 1, 0, indexCol - 1, 0, indexCol - 1);
    matLoCopy(matrix, matOper, indexRow + 1, numRows - 1, indexRow, numRows - 2,
              0, indexCol - 1, 0, indexCol - 1);
    matLoCopy(matrix, matOper, 0, indexRow - 1, 0, indexRow - 1,
              indexCol + 1, numRows - 1, indexCol, numRows - 2);
    matLoCopy(matrix, matOper, indexRow + 1, numRows - 1, indexRow, numRows - 2,
              indexCol + 1, numRows - 1, indexCol, numRows - 2);
    minor = matDet(matOper, numRows - 1);
    matFree(matOper, numRows - 1);
    matOper = NULL;
    return minor;
}

/**
 * @brief   矩阵运算 – 求元素的代数余子式
 * @param   matrix      矩阵地址
 * @param   numRows     矩阵行数
 * @param   indexRow    元素行索引
 * @param   indexCol    元素列索引
 * @return  矩阵对应元素的代数余子式
 * @note    求矩阵matrix第indexRow行第indexCol列的代数余子式，矩阵须为方阵
 */
double matAlgMin(double **matrix, int numRows, int indexRow, int indexCol)
{
    double algMin = 0;
    algMin = matMinor(matrix, numRows, indexRow, indexCol);
    if ((indexRow + indexCol) % 2 == 0)
    {
        return algMin;
    }
    else
    {
        return -algMin;
    }
}