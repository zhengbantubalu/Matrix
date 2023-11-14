#include "..\include\MatUtil.h"
#include "..\include\MatConst.h"
#include <stdlib.h>

/**
 * @brief   矩阵工具 – 矩阵初始化
 * @param   matPtr      矩阵结构体地址
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @note    申请矩阵的存储空间，并赋值为零矩阵
 */
void matInit(Mat *matPtr, int numRows, int numCols)
{
    int i = 0, j = 0;
    (*matPtr).address = (double **)malloc(sizeof(double *) * numRows);
    (*matPtr).numRows = numRows;
    (*matPtr).numCols = numCols;
    for (i = 0; i < numRows; i++)
    {
        (*matPtr).address[i] = (double *)malloc(sizeof(double) * numCols);
        for (j = 0; j < numCols; j++)
        {
            (*matPtr).address[i][j] = 0;
        }
    }
}

/**
 * @brief   矩阵工具 – 矩阵存储空间释放
 * @param   matPtr      矩阵结构体地址
 * @note    释放矩阵的存储空间
 */
void matFree(Mat *matPtr)
{
    int i = 0;
    for (i = 0; i < (*matPtr).numRows; i++)
    {
        free((*matPtr).address[i]);
        (*matPtr).address[i] = NULL;
    }
    free((*matPtr).address);
    (*matPtr).address = NULL;
    (*matPtr).numRows = 0;
    (*matPtr).numCols = 0;
}

/**
 * @brief   矩阵工具 – 赋值为单位矩阵
 * @param   matrix      矩阵
 * @param   numRows     矩阵行数
 * @return  SUCCESS – 赋值成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵matrix赋值为单位矩阵，矩阵须为方阵
 */
int matSetE(Mat matrix)
{
    if (matrix.numRows = matrix.numCols)
    {
        matSetELocal(matrix.address, 0, matrix.numRows - 1, 0, matrix.numRows - 1);
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief   矩阵工具 – 局部赋值为单位矩阵
 * @param   matAdd      矩阵地址
 * @param   rowStart    起始行
 * @param   rowEnd      终止行
 * @param   colStart    起始列
 * @param   colEnd      终止列
 * @return  SUCCESS – 赋值成功
 * @return  ERROR – 范围行列数不相等
 * @note    将矩阵的指定范围赋值为单位矩阵，范围行列数须相等
 */
void matSetELocal(double **matAdd, int rowStart, int rowEnd, int colStart, int colEnd)
{
    int i = 0, j = 0;
    for (i = rowStart; i <= rowEnd; i++)
    {
        for (j = colStart; j <= colEnd; j++)
        {
            matAdd[i][j] = (i - rowStart) == (j - colStart) ? 1 : 0;
        }
    }
}

/**
 * @brief   矩阵工具 – 矩阵复制
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @return  SUCCESS – 复制成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source复制到矩阵target，源矩阵与目标矩阵须同型
 */
int matCopy(Mat source, Mat target)
{
    if (source.address == target.address)
    {
        return SUCCESS;
    }
    else if (matSameDim(source, target))
    {
        matCpLocal(source.address, target.address,
                   0, source.numRows - 1, 0, source.numRows - 1,
                   0, source.numCols - 1, 0, source.numCols - 1);
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief   矩阵工具 – 矩阵局部复制
 * @param   srcAdd      源矩阵地址
 * @param   tgtAdd      目标矩阵地址
 * @param   rowSrcSt    源矩阵起始行
 * @param   rowSrcEd    源矩阵终止行
 * @param   rowTarSt    目标矩阵起始行
 * @param   rowTarEd    目标矩阵终止行
 * @param   colSrcSt    源矩阵起始列
 * @param   colSrcEd    源矩阵终止列
 * @param   colTarSt    目标矩阵起始列
 * @param   colTarEd    目标矩阵终止列
 * @return  SUCCESS – 复制成功
 * @return  ERROR – 指定范围行列数不相等
 * @note    将源矩阵的指定范围复制到目标矩阵的指定范围，两矩阵指定范围的行列数须相等
 */
int matCpLocal(double **srcAdd, double **tgtAdd,
               int rowSrcSt, int rowSrcEd, int rowTgtSt, int rowTgtEd,
               int colSrcSt, int colSrcEd, int colTarSt, int colTarEd)
{
    int i = 0, j = 0;
    if (rowSrcEd - rowSrcSt == rowTgtEd - rowTgtSt && colSrcEd - colSrcSt == colTarEd - colTarSt)
    {
        for (i = 0; i <= rowSrcEd - rowSrcSt; i++)
        {
            for (j = 0; j <= colSrcEd - colSrcSt; j++)
            {
                tgtAdd[i + rowTgtSt][j + colTarSt] = srcAdd[i + rowSrcSt][j + colSrcSt];
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief   矩阵工具 – 矩阵同型判断
 * @param   matrix1     矩阵1
 * @param   matrix2     矩阵2
 * @return  ture – 同型
 * @return  false – 不同型
 * @note    判断矩阵matrix1与矩阵matrix2是否同型，即是否行数相等且列数相等
 */
bool matSameDim(Mat matrix1, Mat matrix2)
{
    if (matrix1.numRows == matrix2.numRows && matrix1.numCols == matrix2.numCols)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief   矩阵工具 – 矩阵相等判断
 * @param   matrix1     矩阵1
 * @param   matrix2     矩阵2
 * @return  ture – 相等
 * @return  false – 不相等
 * @note    判断矩阵matrix1与矩阵matrix2是否相等，两矩阵须同型
 */
bool matEqual(Mat matrix1, Mat matrix2)
{
    if (matrix1.address == matrix2.address)
    {
        return true;
    }
    else if (matSameDim(matrix1, matrix2))
    {
        return matEqLocal(matrix1.address, matrix2.address,
                          0, matrix1.numRows - 1, 0, matrix1.numRows - 1,
                          0, matrix1.numCols - 1, 0, matrix1.numCols - 1);
    }
    else
    {
        return false;
    }
}

/**
 * @brief   矩阵工具 – 矩阵局部相等判断
 * @param   matAdd1     矩阵1地址
 * @param   matAdd2     矩阵2地址
 * @param   rowSt1      矩阵1起始行
 * @param   rowEd1      矩阵1终止行
 * @param   rowSt2      矩阵2起始行
 * @param   rowEd2      矩阵2终止行
 * @param   colSt1      矩阵1起始列
 * @param   colEd1      矩阵1终止列
 * @param   colSt2      矩阵2起始列
 * @param   colEd2      矩阵2终止列
 * @return  true – 相等
 * @return  false – 不相等
 * @note    判断矩阵matrix1与矩阵matrix2指定范围是否相等，两矩阵范围行列数须相等
 */
bool matEqLocal(double **matAdd1, double **matAdd2,
                int rowSt1, int rowEd1, int rowSt2, int rowEd2,
                int colSt1, int colEd1, int colSt2, int colEd2)
{
    int i = 0, j = 0;
    for (i = 0; i <= rowEd1 - rowSt1; i++)
    {
        for (j = 0; j <= colEd1 - colSt1; j++)
        {
            if ((matAdd1[i + rowSt1][j + colSt1] - matAdd2[i + rowSt2][j + colSt2]) > ZEROTHRES)
            {
                return false;
            }
        }
    }
    return true;
}